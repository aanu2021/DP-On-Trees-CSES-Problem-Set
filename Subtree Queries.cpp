// Tree in the form of a Segment Tree // 

// Subtree Sum / Max / Min / GCD  & Update //

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

vector<ll>flatten;           // Flattening the tree using DFS
vector<ll>values;           // Stores the values of every node
vector<vector<ll>>graph;   // Adjacency List
vector<ll>in;             // Time when we enter the node in the DFS call , (using as an index of segment tree)
vector<ll>subtree;       // Size of the subtree
ll tree[800005];        // Segment Tree Representation

ll timer=0LL;

void preprocess(ll u,ll p){
    
    subtree[u]=1LL;
    in[u]=timer++;
    
    flatten.push_back(u);
    
    for(ll v:graph[u]){
        
        if(v==p){
            continue;
        }
        
        preprocess(v,u);
        
        subtree[u]+=subtree[v];
        
    }
    
}

void BuildSeg(ll idx,ll low,ll high){
    
    if(low>high){
        return;
    }
    
    if(low==high){
        
        tree[idx]=values[flatten[low]];
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
    in.resize(n);
    subtree.resize(n);
    
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
    
    BuildSeg(0,0,n-1);
    
    while(q--){
        
        ll type;
        cin>>type;
        
        if(type==1){
            
            ll node,val;
            cin>>node>>val;
            
            node--;
            
            Update(0,0,n-1,in[node],val);
            values[node]=val;
            
        }
        
        else{
            
            ll node;
            cin>>node;
            
            node--;
            
            ll ans=query(0,0,n-1,in[node],in[node]+subtree[node]-1);
            
            cout<<ans<<"\n";
            
        }
        
    }
    
    return 0;

}