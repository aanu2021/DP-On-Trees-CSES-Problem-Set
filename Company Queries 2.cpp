//      Time Complexity : O(N*logN*logN)   //

//      Binary Search + Binary Lifting    //


// ---------------------------------------------  //

//          Binary Lifting + Greedy          //

//     Time Complexity : O(N*logN)     //


// --------------------------------------------- //

#include<bits/stdc++.h>
using namespace std;

vector<vector<int>>graph;

int up[200005][21];

int lvl[200005];


void level_find(int u,int level){
    
   lvl[u]=level;
   
   for(int v:graph[u]){
       
       level_find(v,level+1);
       
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
    
    if(node==-1 || jump==0){
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
    
    if(lvl[u]<lvl[v]){
        
        swap(u,v);
        
    }
    
    u=lifted_node(u,lvl[u]-lvl[v]);
    
    int low=0,high=lvl[u];
    
    int lca_node=-1;
    
    while(low<=high){
        
        int mid=(low+high)/2;
        
        int x1=lifted_node(u,mid);
        int x2=lifted_node(v,mid);
        
        if(x1==x2){
            
            lca_node=x1;
            
            high=mid-1;
            
        }
        
        else{
            
            low=mid+1;
            
        }
        
    }
    
    return lca_node;
    
}


int lca2(int u,int v){
    
    if(lvl[u] < lvl[v]){
        swap(u,v);
    }
    
    u=lifted_node(u,lvl[u]-lvl[v]);
    
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
    
    for(int i=2;i<=n;i++){
        
        int par;
        cin>>par;
        
        graph[par].push_back(i);
        
    }
    
    for(int i=0;i<=n;i++){
        for(int j=0;j<21;++j){
            up[i][j]=-1;
        }
    }
    
    for(int i=0;i<=n;i++){
        lvl[i]=0;
    }
    
    
    
    level_find(1,0);
    
    
    
    binary_lifting(1,-1);
   
   
   
    //   for(int i=1;i<=n;i++){
    //       cout<<lvl[i]<<" ";
    //   }cout<<"\n";
    
    
    
    while(q--){
        
        int u,v;
        cin>>u>>v;
        
        cout<<lca2(u,v)<<"\n";
        
    }
    
    return 0;
    
}