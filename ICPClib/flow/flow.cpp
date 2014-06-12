#include<bits/stdc++.h>
using namespace std;
//基本要素
#define INF (INT_MAX/2)
struct E{
  int to,cap,cost,rev;
};

int V;//頂点数
vector<vector<E>> G;

void add_edge(int from,int to,int cap,int cost){
  G[from].push_back((E){to,cap,cost,(int)G[to].size()});
  G[to].push_back((E){from,0,-cost,(int)G[from].size()-1});
}

void input(){
  G.clear();G.resize(V);
}

//流すだけ
vector<int> used;
int dfs(int v,int t,int f){
  if(v==t)return f;
  used[v] = true;
  for(int i=0;i<G[v].size();i++){
    E& e = G[v][i];
    if(!used[e.to] && e.cap>0){
      int d = dfs(e.to,t,min(f,e.cap));
      if(d>0){
        e.cap -= d;
        G[e.to][e.rev].cap += d;
        return d;
      }
    }
  }
  return 0;
}

int max_flow(int s,int t){
  int flow = 0;
  while(1){
    used.clear();used.resize(V);
    int f = dfs(s,t,INF);
    if(f==0)return flow;
    flow+=f;
  }
}


int main(){

}
