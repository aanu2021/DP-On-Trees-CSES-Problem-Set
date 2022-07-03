#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<vector<int>>graph;

int dp1[50002][502];
int dp2[50002][502];


void dfs(int u,int p,int k){
  
  for(int v:graph[u]){
      
      if(v!=p){
          
          dfs(v,u,k);
          
      }
      
  }
  
  dp1[u][0]=1; 
  
  for(int dist=1;dist<=k;dist++){
      
      dp1[u][dist]=0;
      
      for(int v:graph[u]){
          
          if(v!=p){
              
              dp1[u][dist]+=dp1[v][dist-1];
              
          }
          
      }
      
  }
  
    
}


void func(int u,int p,int &k){
    
    for(int dist=0;dist<=k;dist++){
        dp2[u][dist]=dp1[u][dist];
    }
    
    if(p!=0){
        
        dp2[u][1]+=dp1[p][0];
        
        for(int dist=2;dist<=k;dist++){
            
            dp2[u][dist]+=dp2[p][dist-1];
            
            dp2[u][dist]-=dp1[u][dist-2];
            
        }
        
    }
    
    
    for(int v:graph[u]){
        
        if(v!=p){
            
            func(v,u,k);
            
        }
        
    }
    
}


int main(){
     
         ios_base::sync_with_stdio(false);
         cin.tie(NULL);
         cout.tie(NULL);
     
         int t=1;
         //cin>>t;
        
         
         while(t--){
          
           int n,k;
           cin>>n>>k;
           
           graph.resize(n+1);
           
           for(int i=0;i<n-1;++i){
               
               int u,v;
               cin>>u>>v;
               
               graph[u].push_back(v);
               graph[v].push_back(u);
               
           }
           
           
           dfs(1,0,k); // Find number of nodes at a distance k from node u (root of the subtree)
           
           func(1,0,k); 
           
           ll ans=0LL;
           
           for(int i=1;i<=n;i++){
               //cout<<dp2[i][k]<<" ";
               ans+=(ll)dp2[i][k];
           }
           
           cout<<(ans/2)<<"\n";
           
           
          
         }
      
    return 0;
    
}