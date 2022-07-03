#include<bits/stdc++.h>
using namespace std;

vector<vector<int>>graph;

int maxLen=0;

pair<int,int>func(int u,int p){
    
    bool leaf=true;
    
    for(int v:graph[u]){
        
        if(v!=p){
            
            leaf=false;
            break;
            
        }
        
    }
    
    if(leaf){
        
        maxLen=max(maxLen,1);
        
        return {1,1};
        
    }
    
    vector<int>vec;
    
    for(int v:graph[u]){
        
        if(v!=p){
            
            auto curr=func(v,u);
            
            vec.push_back(curr.first);
            
        }
        
    }
    
    sort(vec.rbegin(),vec.rend());
    
    int sz=vec.size();
    
    int longest_path=0,internal_path=0;
    
    if(sz==1){
        
        longest_path=1+vec[0];
        
        internal_path=1+vec[0];
        
    }
    
    else{
        
        longest_path=1+vec[0];
        
        internal_path=1+vec[0]+vec[1];
        
    }
    
    maxLen=max(maxLen,max(longest_path,internal_path));
    
    return {longest_path,internal_path};
    
}

int main(){
    
    int n;
    cin>>n;
    
    graph.resize(n+1);
    
    for(int i=0;i<n-1;i++){
        
        int u,v;
        cin>>u>>v;
        
        graph[u].push_back(v);
        graph[v].push_back(u);
        
    }
    
    
    func(1,-1);
    
    cout<<(maxLen-1)<<"\n";
    
    return 0;
    
}