#include<bits/stdc++.h>
using namespace std;

vector<vector<int>>graph;

int dp[200005][2];

// dp[u][0] --> We couldn't select any edge with u as its starting point.

// dp[u][1] --> Selecting an edge of type (u-x) , where x => (c1,c2,c3,...,ck)


void func(int u,int p){
    
    dp[u][0]=0;
    dp[u][1]=0;
    
    bool leaf=true;
    
    for(int v:graph[u]){
        
        if(v!=p){
            
            leaf=false;
            
            func(v,u);
            
        }
        
    }
    
    if(leaf){
        return;
    }
    
    
    vector<int>prefix;
    vector<int>suffix;
    
    for(int v:graph[u]){
        
        if(v!=p){
            
            prefix.push_back(max(dp[v][0],dp[v][1]));
            suffix.push_back(max(dp[v][0],dp[v][1]));
            
        }
        
    }
    
    int sz=prefix.size();
    
    for(int i=1;i<sz;++i){
        prefix[i]+=prefix[i-1];
    }
    
    for(int i=sz-2;i>=0;i--){
        suffix[i]+=suffix[i+1];
    }
    
    dp[u][0]=suffix[0];
    
    int child=0;
    
    for(int v:graph[u]){
        
        if(v!=p){
            
            int left=(child>=1 ? prefix[child-1] : 0);
            int right=(child+1<sz ? suffix[child+1] : 0);
            
            dp[u][1]=max(dp[u][1],1+dp[v][0]+left+right);
            
            child++;
            
        }
        
    }
    
    return;
    
}


int main(){
    
    int n;
    cin>>n;
    
    graph.resize(n+1);
    
    for(int i=0;i<n-1;++i){
        int u,v;
        cin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    for(int i=0;i<=n;i++){
        for(int j=0;j<2;j++){
            dp[i][j]=0;
        }
    }
    
    func(1,-1);
    
    int max_edges=max(dp[1][0],dp[1][1]);
    
    cout<<max_edges<<"\n";
    
    return 0;
    
}