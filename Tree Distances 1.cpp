#include<bits/stdc++.h>
using namespace std;

vector<vector<int>>graph;

vector<int>depth;

vector<int>ans;

int n;

void preprocessing(int u,int p){
    
    depth[u]=0;
    
    for(int v:graph[u]){
        
        if(v!=p){
            
            preprocessing(v,u);
            
            depth[u]=max(depth[u],1+depth[v]);
            
        }
        
    }
    
}


void func(int u,int p,int par_ans){
    
    vector<int>prefix;
    vector<int>suffix;
    
    for(int v:graph[u]){
        
        if(v!=p){
            
            prefix.push_back(depth[v]);
            
            suffix.push_back(depth[v]);
            
        }
        
    }
    
    int sz=prefix.size();
    
    for(int i=1;i<sz;i++){
        prefix[i]=max(prefix[i-1],prefix[i]);
    }
    
    for(int i=sz-2;i>=0;i--){
        suffix[i]=max(suffix[i+1],suffix[i]);
    }
    
    int child=0;
    
    for(int v:graph[u]){
        
        if(v!=p){
            
            int op1=(child>=1 ? prefix[child-1] : -1e9);
            
            int op2=(child+1<sz ? suffix[child+1] : -1e9);
            
            int partial_ans=1+max(max(op1,op2),par_ans);
            
            func(v,u,partial_ans);
            
            child++;
            
        }
        
    }
    
    ans[u] = 1 + max(par_ans,(sz==0 ? -1 : prefix.back()));
    
}


int main(){
    
    cin>>n;
    
    
    graph.resize(n+1);
    
    depth.resize(n+1);
    
    ans.resize(n+1);
    
    
    for(int i=0;i<n-1;++i){
        
        int u,v;
        cin>>u>>v;
        
        graph[u].push_back(v);
        graph[v].push_back(u);
        
    }
    
    
    preprocessing(1,-1);
    
    // for(int i=1;i<=n;i++){
    //     cout<<depth[i]<<" ";
    // }cout<<"\n";
    
    
    func(1,0,-1);
    
    for(int i=1;i<=n;i++){
        
        cout<<ans[i]<<" ";
        
    }cout<<"\n";
    
    return 0;
    
}