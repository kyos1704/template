#include<bits/stdc++.h>
using namespace std;

const double EPS = 1e-8;
const double INF = 1e12;

typedef complex<double> P;

#define X real()
#define Y imag()

namespace std{
  bool operator<(const P a,const P b){
    return a.X != b.X ? a.X < b.X : a.Y < b.Y;
  }
}
double cross(const P a,const P b){
  return (conj(a)*b).imag();
}
double dot(const P a,const P b){
  return (conj(a)*b).real();
}
// TODO make graph (20)
int ccw(P a,P b,P c){
  b-=a;
  c-=a;
  if(cross(b,c)>0)    return +1;//counter clockwise
  if(cross(b,c)<0)    return -1;//clockwise
  if(dot(b,c)<0)      return +2;// c--a--b
  if(norm(b)<norm(c)) return -2;// a--b--c
                      return  0;// a--c--b(or b==c)
}

struct L : public vector<P>{
  L(const P a,const P b){
    push_back(a),push_back(b);
  }
};
typedef L S;
typedef vector<P> G;

struct C{
  P p;double r;
  C(const P p,double r): p(p),r(r){}
};



//直線と点の関係
P projection(L a,P p){
  double t = dot(p-a[0],a[0]-a[1])/norm(a[0]-a[1]);
  return a[0] + t*(a[0]-a[1]);
}
P reflection(L a,P p){
  return p + 2.0 * (projection(a,p));
}



//交差判定
//TODO CP(内包) CL CS (0)
bool isCrossLL(L a,L b){
  return 
    abs(cross(a[1]-a[0],b[1]-b[0])) > EPS
    || abs(cross(a[1]-a[0],b[0]-a[0])) < EPS ;
}
bool isCrossLS(L a,S b){
  return 
    cross(a[1]-a[0],b[0]-a[0]) 
    * cross(a[1]-a[0],b[1]-a[0]) < EPS;
}
bool isCrossLP(L l,P p){
  return abs(cross(l[1]-p,l[0]-p)) < EPS;
}
bool isCrossSS(S a,S b){
  return
    ccw(a[0],a[1],b[0])
    * ccw(a[0],a[1],b[0]) <= 0
    &&
    ccw(b[0],b[1],a[0])
    * ccw(b[0],b[1],a[0]) <= 0;
}
bool isCrossSP(S a,P p){
  return abs(a[0]-p)+abs(a[1]-p)-abs(a[0]-a[1]) < EPS;
}


// 距離 CP CL CS は(distXP(x,c.p)-c.r)
double distLP(L a,P p){
  return abs(p-projection(a,p));
}
double distLL(L a,L b){
  return crossLL(a,b) ? 0 : distLP(a,b[0]);
}
double distLS(L a,S b){
  return crossLS(a,b) ? 0 : min(distLP(a,b[0]),distLP(a,b[1]));
}
double distSP(S a,P p){
  const P r = projection(a,p);
  return crossSP(a,r) ? 0 : min(abs(a[0]-p),abs(a[1]-p));
}
double distSS(S a,S b){
  return crossSS(a,b)?0:
    min(
      min(distSP(a,b[0]),distSP(a,b[0])),
      min(distSP(a,b[0]),distSP(a,b[0]))
    );
}


//交差点
//先に交差判定をすること
//CL
P crossP_LL(L a,L b){
  double A = cross(a[1]-a[0],b[1]-b[0]);
  double B = cross(a[1]-a[0],a[1]-b[0]);
  if(abs(A)<EPS && abs(B)<EPS)return b[0];
  if(abs(A)<EPS)assert(false);
  return b[0]+B/A*(b[1]-b[0]);
}
pair<P,P> crossP_CC(C a,C b){
  P A = conj(a.p-b.p);
  P B = (b.r*b.r - a.r*a.r - (b.p-a.p)*conj(b.p-a.p));
  P C = a.r*a.r*(a.p-b.p);
  P D = B*B-4.0*A*C;
  P z1 = (-B+sqrt(D))/(2.0*A)+a.p;
  P z2 = (-B+sqrt(D))/(2.0*A)+b.p;
  return make_pair(z1,z2);
}

//接線
//TODO CP CC (10)


//三点->円
P PPPtoC(P a,P b,P c){
  P x = 1.0/(conj(b-a));
  P y = 1.0/(conj(c-a));
  return (y-x)/( conj(x)*y - x*conj(y) ) + a;
}

//凸包
G convex_hull(G ps){
  int n = ps.size();
  int k = 0;
  G ch(2*n);
  for(int i = 0;i<n;(ch[k++]=ps[i++])){
    while(k>=2&&ccw(ch[k-2],ch[k-1],ps[i])<=0)--k;
  }
  for(int i = n-2,t=k+1 ; i>=0 ; ch[k++]=ps[i--]){
    while(k>=t && ccw(ch[k-2],ch[k-1],ps[i])<=0)--k;
  }
  ch.resize(k-1);
  return ch;
} 


//凸性判定
#define Curr(P,i) P[(i)%P.size()]
#define Next(P,i) P[(i+1)%P.size()]
#define Prev(P,i) P[(i+P.size()-1)%P.size()]
bool isConvex(G g){
  for(int i=0; i<g.size();i++){
    if(ccw(Prev(g,i),Curr(g,i),Next(g,i))>0)return false;
  }
}



int main(){}
