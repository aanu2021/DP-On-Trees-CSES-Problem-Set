class Solution {
public:

typedef long long ll;

vector<vector<int>>graph;
    
vector<int>level;
    
vector<int>subtree;

vector<vector<int>>up;

    
void preprocess(int u,int p,int lvl){
        
        level[u]=lvl;
        
        
        for(int v:graph[u]){
            
            if(v==p){
                continue;
            }
            
            preprocess(v,u,lvl+1);
            
        }
        
}
    
    
int lca(int u,int v){
    
    if(level[u]>level[v]){
        
        swap(u,v);
        
    }
    
    int k=level[v]-level[u];
    
    for(int i=0;i<=19;++i){
        
        if((k&(1<<i))){
            
            v=up[v][i];
            
        }
        
    }
    
    if(u==v){
        return u;
    }
    
    for(int i=19;i>=0;i--){
        
        if(up[u][i]!=up[v][i]){
            
            u=up[u][i];
            v=up[v][i];
            
        }
        
    }
    
    return up[u][0];
    
}

void dfs(int u,int p){
    
    for(int v:graph[u]){
        
        if(v==p){
            continue;
        }
        
        dfs(v,u);
        
        subtree[u]+=subtree[v];
        
    }
    
}
    

long long findMin(int n, int m, vector<int> &p, vector<int> &wt, vector<int> &source, vector<int> &destination) {
        
        up.clear();
        
        up=vector<vector<int>>(n,vector<int>(20,-1));
        
        graph.clear();
        
        level.clear();
        
        subtree.clear();
        
        graph.resize(n+1);
        
        level.resize(n+1,0LL);
        
        subtree.resize(n+1,0LL);
        
        
        for(int i=1;i<n;i++){
            up[i][0]=p[i];
        }
        
        for(int j=1;j<=19;j++){
            for(int i=0;i<n;i++){
                if(up[i][j-1]!=-1){
                    up[i][j]=up[up[i][j-1]][j-1];
                }
            }
        }
        
      
        
        for(int i=1;i<n;i++){
            
            graph[p[i]].push_back(i);
            
        }
        
         preprocess(0LL,-1LL,0LL);
        
         vector<ll>weight;
        
        for(ll i=1;i<n;i++){
            weight.push_back(wt[i]);
        }
        
        sort(weight.begin(),weight.end());
        
        for(ll i=0;i<m;i++){
            
            int u=source[i];
            int v=destination[i];
            
            int lca_node=lca(u,v);
            
            subtree[u]++;
            subtree[v]++;
            
            subtree[lca_node]-=2;
            
          
        }
        
        
        dfs(0,-1);
        
        vector<ll>vec;
        
        for(ll i=1;i<n;i++){
            vec.push_back(subtree[i]);
        }
        
        sort(vec.rbegin(),vec.rend());
        
        ll ans=0LL;
        
        for(ll i=0;i<vec.size();++i){
            
            ans+=(vec[i]*weight[i]);
            
        }
        
        return ans;
        
    }
};