#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<vector<ll>>graph;

ll n;

vector<ll>sub_count; // Store total number of nodes in the subtree rooted at u.

vector<ll>sub_ans; // Store distance of all the descendant nodes from root of the subtree.

vector<ll>ans; // Total distance of all the nodes from node u.

void preprocessing1(ll u,ll p){
    
    ll cntnodes=1LL;
    
    for(ll v:graph[u]){
        
        if(v!=p){
            
            preprocessing1(v,u);
            
            cntnodes+=sub_count[v];
            
        }
        
    }
    
    sub_count[u]=cntnodes;
    
}


void preprocessing2(ll u,ll p){
    
    ll currdist=0;
    
    for(ll v:graph[u]){
        
        if(v!=p){
            
            preprocessing2(v,u);
            
            currdist+=(sub_count[v]+sub_ans[v]);
            
        }
        
    }
    
    sub_ans[u]=currdist;
    
}


void func(ll u,ll p,ll par_ans){
    
    ll cnt_node_sub=sub_count[u];
    
    ll rest_node_tree=(n-cnt_node_sub);
    
    ll curr_cnt=sub_ans[u];
    
    ans[u] = curr_cnt + rest_node_tree + par_ans ;
  
  
    for(ll v:graph[u]){
        
        if(v!=p){
            
            ll currval=ans[u] - (sub_count[v] + sub_ans[v]);
            
            func(v,u,currval);
            
        }
        
    }
    
    
   // ans[u] = curr_cnt + rest_node_tree + par_ans ;
    
}


int main(){
    
    cin>>n;
    
    graph.resize(n+1);
    
    sub_count.resize(n+1,0);
    
    sub_ans.resize(n+1,0);
    
    ans.resize(n+1,0);
    
    for(ll i=0;i<n-1;i++){
        
        ll u,v;
        cin>>u>>v;
        
        graph[u].push_back(v);
        graph[v].push_back(u);
        
    }
    
    
    preprocessing1(1,0);
    
    preprocessing2(1,0);
    
    func(1,0,0);
    
    // for(int i=1;i<=n;i++){
    //     cout<<sub_count[i]<<" ";
    // }cout<<"\n";
    
    // for(int i=1;i<=n;i++){
    //     cout<<sub_ans[i]<<" ";
    // }cout<<"\n";
    
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<" ";
    }cout<<"\n";
    
    
    
    
    return 0;
    
}