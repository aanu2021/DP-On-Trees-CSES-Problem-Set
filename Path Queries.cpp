//  Sum / Max / Min / GCD of the nodes in a path & Update //


#include<bits/stdc++.h>
using namespace std;


typedef long long ll;

const ll M = 1e9 + 7;

ll mod(ll a){
    return ((a%M)+M)%M;
}

ll mul(ll a,ll b){
    return mod(mod(a)*mod(b));
}

ll add(ll a,ll b){
    return mod(mod(a)+mod(b));
}


vector<ll>values;
vector<ll>ST;
vector<ll>ET;
vector<vector<ll>>graph;
vector<ll>path;
ll tree[1600002];

ll timer=0LL;

void preprocess(ll u,ll p){
    
    ST[u]=timer++;
    path.push_back(values[u]);
    
    for(ll v:graph[u]){
        
        if(v!=p){
            
            preprocess(v,u);
            
        }
        
    }
    
    path.push_back(-values[u]);
    ET[u]=timer++;
    
}

void BuildSeg(ll idx,ll low,ll high){
    
    if(low>high){
        return;
    }
    
    if(low==high){
        tree[idx]=path[low];
        return;
    }
    
    else{
        
        ll mid=(low+high)/2;
        
        BuildSeg(2*idx+1,low,mid);
        BuildSeg(2*idx+2,mid+1,high);
        
        tree[idx]=tree[2*idx+1]+tree[2*idx+2];
        
    }
    
}


void Update(ll idx,ll low,ll high,ll pos,ll val){
    
    if(low>high){
        return;
    }
    
    if(low==high){
        tree[idx]=val;
        return;
    }
    
    else{
        
        ll mid=(low+high)/2;
        
        if(pos<=mid){
            Update(2*idx+1,low,mid,pos,val);
        }else{
            Update(2*idx+2,mid+1,high,pos,val);
        }
        
        tree[idx]=tree[2*idx+1]+tree[2*idx+2];
        
    }
    
}


ll query(ll idx,ll low,ll high,ll l,ll r){
    
    if(low>high || low>r || high<l){
        return 0LL;
    }
    
    if(low==high){
        return tree[idx];
    }
    
    else if(low>=l && high<=r){
        return tree[idx];
    }
    
    else{
        
        ll mid=(low+high)/2;
        
        ll left=query(2*idx+1,low,mid,l,r);
        ll right=query(2*idx+2,mid+1,high,l,r);
        
        return left+right;
        
    }
    
}

int main(){
    
    ll n,q;
    cin>>n>>q;
    
    graph.resize(n);
    values.resize(n);
    ST.resize(n);
    ET.resize(n);
    
    for(ll i=0;i<n;i++){
        cin>>values[i];
    }
    
    for(ll i=0;i<n-1;++i){
        
        ll u,v;
        cin>>u>>v;
        
        u--;
        v--;
        
        graph[u].push_back(v);
        graph[v].push_back(u);
        
    }
    
    preprocess(0LL,-1LL);
    
    ll m=path.size();
    
    BuildSeg(0,0,m-1);
    
    while(q--){
        
        ll type;
        cin>>type;
        
        if(type==1){
            
            ll node,val;
            cin>>node>>val;
            
            node--;
            
            Update(0,0,m-1,ST[node],val);
            Update(0,0,m-1,ET[node],-val);
            
        }
        
        else{
            
            ll node;
            cin>>node;
            
            node--;
            
            ll ans=query(0,0,m-1,0,ST[node]);
            
            cout<<ans<<"\n";
            
        }
        
    }
    
    return 0;

}