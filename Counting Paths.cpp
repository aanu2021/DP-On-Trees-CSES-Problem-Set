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


ll up[200005][22];

vector<vector<ll>>graph;

vector<ll>level;

vector<ll>subtree_sum;

void preprocess(ll u,ll p,ll lvl){
    
    level[u]=lvl;
    
    for(ll v:graph[u]){
        
        if(v==p){
            continue;
        }
        
        preprocess(v,u,lvl+1);
        
    }
    
}

void binary_lifting(ll u,ll p){
    
    up[u][0]=p;
    
    for(ll i=1;i<=21;++i){
        
        if(up[u][i-1]!=-1LL){
            up[u][i]=up[up[u][i-1]][i-1];
        }
        
    }
    
    for(ll v:graph[u]){
        
        if(v==p){
            continue;
        }
        
        binary_lifting(v,u);
        
    }
    
}

ll lca(ll u,ll v){
    
    if(level[u]>level[v]){
        
        swap(u,v);
        
    }
    
    ll k=level[v]-level[u];
    
    for(ll i=21;i>=0;i--){
        
        if((k&(1LL<<i))){
            
            v=up[v][i];
            
        }
        
    }
    
    if(u==v){
        
        return u;
        
    }
    
    for(ll i=21;i>=0;i--){
        
        if(up[u][i]!=up[v][i]){
            
            u=up[u][i];
            v=up[v][i];
            
        }
        
    }
    
    u=up[u][0];
    
    return u;
    
}

void dfs(ll u,ll p){
    
    for(ll v:graph[u]){
        
        if(v==p){
            continue;
        }
        
        dfs(v,u);
        
        subtree_sum[u]+=subtree_sum[v];
        
    }
    
}

int main(){
    
    ll n,q;
    cin>>n>>q;
    
    graph.resize(n+1);
    
    level.resize(n+1,0LL);
    
    subtree_sum.resize(n+1,0LL);
    
    
    for(ll i=1;i<n;i++){
        
        ll u,v;
        cin>>u>>v;
        
        graph[u].push_back(v);
        graph[v].push_back(u);
        
    }
    
    preprocess(1LL,-1LL,0LL);
    
    for(ll i=0;i<=n;i++){
        for(ll j=0;j<=21;j++){
            up[i][j]=-1LL;
        }
    }
    
    binary_lifting(1LL,-1LL);
    
    while(q--){
        
        ll u,v;
        cin>>u>>v;
        
        ll lca_node=lca(u,v);
        
        subtree_sum[u]++;
        subtree_sum[v]++;
        
        subtree_sum[lca_node]--;
        
        ll prev_lca=up[lca_node][0];
        
        if(prev_lca!=-1LL){
            subtree_sum[prev_lca]--;
        }
        
    }
    
    dfs(1LL,-1LL);
    
    for(ll i=1;i<=n;i++){
        cout<<subtree_sum[i]<<" ";
    }cout<<"\n";
    
    return 0;

}