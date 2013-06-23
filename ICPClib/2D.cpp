#include<algorithm>
#include<vector>
#include<utility>
#include<cmath>
using namespace std;
#define X first
#define Y second

typedef long double ld;
typedef long long ll;
typedef ll P_type;
typedef pair<ll,ll> P;

const ld INF = 1e39;
const ld EPS = 1e-8;
const ld  PI = acos(-1);

P_type out_pro(P a,P b) {
  return (a.X * b.Y - b.X * a.Y);
}

P_type in_pro(P a,P b){
  return (a.X * b.X + a.Y *b.Y);
}

//以下２つは小数点以下が必要なことがあるのでldにする
ld pow_len(P a) {
  return a.X * a.X + a.Y * a.Y;
}

ld len(P a){
  return sqrt(pow_len(a));
}

P make_v(P a,P b) {
  return P(a.X - b.X, a.Y - b.Y);
}
//凸法
vector<P> convex(vector<P> list) {
  int m=0;
  vector<P> res(list.size()*2);
  sort(list.begin(),list.end());
  for(int i=0; i<list.size(); res[m++]=list[i++]){
    for(;m>1&&out_pro(make_v(res[m-1],res[m-2]),make_v(list[i],res[m-2]))<=EPS;--m);
  }
  for(int i=list.size()-2,r=m; i>=0; res[m++]=list[i--]){
    for(;m>r&&out_pro(make_v(res[m-1],res[m-2]),make_v(list[i],res[m-2]))<=EPS;--m);
  }
  res.resize(m-1);
  return res;
}
 

int main(){}
