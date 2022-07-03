#include<bits/stdc++.h>
using namespace std;

// up[i][j] --> denotes the node (2^j) th level up from the i-th node (-1 if not exists).

// Time Complexity : O(N*logN)

int up[200005][21];

vector<vector<int>>graph;

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


int ans_query(int node,int jump){
    
    if(node==-1 || jump==0){
        
        return node;
        
    }
    
    for(int i=20;i>=0;i--){
        
        if(jump>=(1<<i)){
            
            return ans_query(up[node][i],jump-(1<<i));
            
        }
        
    }
    
    return -1;
    
}

int main(){
    
    int n,q;
    cin>>n>>q;
    
    graph.resize(n+1);
    
    for(int i=0;i<=n;i++){
        for(int j=0;j<-20;++j){
            up[i][j]=-1;
        }
    }
    
    vector<int>p(n+1);
    
    for(int i=2;i<=n;i++){
        cin>>p[i];
        graph[p[i]].push_back(i);
    }
    
    binary_lifting(1,-1);
    
    while(q--){
        
        int node,jump;
        cin>>node>>jump;
        
        cout<<ans_query(node,jump)<<"\n";
        
    }
    
    return 0;
    
}