#include<bits/stdc++.h>
using namespace std;

vector<int>ans;

vector<vector<int>>graph;

int func(int u){
    
    if(graph[u].size()==0){
        ans[u]=0;
        return 1;
    }
    
    int curr=0;
    
    for(int v:graph[u]){
        curr+=func(v);
    }
    
    ans[u]=curr;
    
    return 1+curr;
    
}

int main(){
    
    int n;
    cin>>n;
    
    vector<int>p(n+1);
    
    graph=vector<vector<int>>(n+1);
    
    for(int i=2;i<=n;i++){
        cin>>p[i];
        graph[p[i]].push_back(i);
    }
    
    ans.resize(n+1,0);
    
    func(1);
    
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<" ";
    }cout<<"\n";
    
    return 0;
    
}