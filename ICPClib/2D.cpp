#include<complex>
#include<algorithm>
#include<vector>
#include<utility>
#include<cmath>
using namespace std;
#define X real()
#define Y imag()

typedef long double ld;
typedef long long ll;
typedef ld P_type;
typedef complex<P_type> P;

const ld INF = 1e39;
const ld EPS = 1e-8;
const ld  PI = acos(-1);

namespace std{
  bool operator<(P a, P b) {
    if(a.X!=b.X){
      return a.X < b.X;
    }else{
      return a.Y < b.Y;
    }
  }
}

P_type out_pro(P a,P b) {
  return (a.X * b.Y - b.X * a.Y);
}

P_type in_pro(P a,P b){
  return (a.X * b.X + a.Y *b.Y);
}

P_type pow_len(P a) {
  return a.X * a.X + a.Y * a.Y;
}

//以下２つは小数点以下が必要なことがあるのでldにする
ld len(P a){
  return sqrt(pow_len(a));
}

//凸法
vector<P> convex(vector<P> list) {
  int m=0;
  vector<P> res(list.size()*2);
  sort(list.begin(),list.end());
  for(int i=0; i<list.size(); res[m++]=list[i++]){
    for(;m>1&&out_pro(res[m-1]-res[m-2],list[i]-res[m-2])<=EPS;--m);
  }
  for(int i=list.size()-2,r=m; i>=0; res[m++]=list[i--]){
    for(;m>r&&out_pro(res[m-1]-res[m-2],list[i]-res[m-2])<=EPS;--m);
  }
  res.resize(m-1);
  return res;
}
 
int main(){}
