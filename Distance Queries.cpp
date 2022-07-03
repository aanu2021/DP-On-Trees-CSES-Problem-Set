//             Time Complexity : O(Q*logN)            //

#include<bits/stdc++.h>
using namespace std;

int up[200005][21];

int dist[200005];

vector<vector<int>>graph;


void find_distance(int u,int p,int level){
    
    dist[u]=level;
    
    for(int v:graph[u]){
        
        if(v!=p){
            
            find_distance(v,u,level+1);
            
        }
        
    }
    
}


void binary_lifting(int u,int p){
    
    up[u][0]=p;
    
    for(int i=1;i<=20;++i){
        
        if(up[u][i-1]!=-1){
            
            up[u][i]=up[up[u][i-1]][i-1];
            
        }
        
        else{
            
            up[u][i]=-1;
            
        }
        
    }
    
    
    for(int v:graph[u]){
        
        if(v!=p){
            
            binary_lifting(v,u);
            
        }
        
    }
    
}



int lifted_node(int node,int jump){
    
    if(jump==0 || node==-1){
        
        return node;
        
    }
    
    for(int i=20;i>=0;i--){
        
        if(jump>=(1<<i)){
            
            return lifted_node(up[node][i],jump-(1<<i));
            
        }
        
    }
    
    return -1;
    
}



int lca(int u,int v){
    
    if(dist[u]<dist[v]){
        
        swap(u,v);
        
    }
    
    u=lifted_node(u,dist[u]-dist[v]);
    
    if(u==v){
        return u;
    }
    
    for(int i=20;i>=0;i--){
        
        if(up[u][i]!=up[v][i]){
            
            u=up[u][i];
            v=up[v][i];
            
        }
        
    }
    
    return lifted_node(u,1);
    
}


int main(){
    
    int n,q;
    cin>>n>>q;
    
    graph.resize(n+1);
    
    for(int i=0;i<n-1;++i){
        
        int u,v;
        cin>>u>>v;
        
        graph[u].push_back(v);
        graph[v].push_back(u);
        
    }

    
    find_distance(1,-1,0);
    
    binary_lifting(1,-1);
    
    
    while(q--){
        
        int u,v;
        cin>>u>>v;
        
        int l=lca(u,v);
        
        int currval=dist[u]+dist[v]-(2*dist[l]);
        
        cout<<currval<<"\n";
        
    }
    
    return 0;
    
}