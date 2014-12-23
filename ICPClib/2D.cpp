#include<bits/stdc++.h>
using namespace std;

const double EPS = 1e-8;
const double INF = 1e12;

typedef complex<double> P;

#define X real()
#define Y imag()

#define Curr(P,i) P[(i)%P.size()]
#define Next(P,i) P[(i+1)%P.size()]
#define Prev(P,i) P[(i+P.size()-1)%P.size()]

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
  return p + 2.0 * (projection(a,p)-p);
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
    * ccw(a[0],a[1],b[1]) <= 0
    &&
    ccw(b[0],b[1],a[0])
    * ccw(b[0],b[1],a[1]) <= 0;
}
bool isCrossSP(S a,P p){
  return abs(a[0]-p)+abs(a[1]-p)-abs(a[0]-a[1]) < EPS;
}


// 距離 CP CL CS は(distXP(x,c.p)-c.r)
double distPP(P a,P b){
  return abs(a-b);
}
double distLP(L a,P p){
  return abs(p-projection(a,p));
}
double distLL(L a,L b){
  return isCrossLL(a,b) ? 0 : distLP(a,b[0]);
}
double distLS(L a,S b){
  return isCrossLS(a,b) ? 0 : min(distLP(a,b[0]),distLP(a,b[1]));
}
double distSP(S a,P p){
  const P r = projection(a,p);
  return isCrossSP(a,r) ? abs(p-r) : min(abs(a[0]-p),abs(a[1]-p));
}
double distSS(S a,S b){
  return isCrossSS(a,b)?0:
    min(
      min(distSP(a,b[0]),distSP(a,b[1])),
      min(distSP(b,a[0]),distSP(b,a[1]))
    );
}

//円の交差判定
bool isCrossCP(C a,P p){
  return abs(a.p-p)-a.r<=EPS;
}
bool isCrossCL(C a,L l){
  return distLP(l,a.p)-a.r<EPS;
}
double distSP_MAX(S a,P p){
  return max(abs(a[0]-p),abs(a[1]-p));
}
bool isCrossCS(C a,S s){
  return distSP(s,a.p)-a.r<-EPS&&distSP_MAX(s,a.p)-a.r>+EPS;
}
bool isCrossCC(C a,C b){//接してる時は交差
  return abs(a.p-b.p)-(a.r+b.r) <= EPS;
}


//交差点
//先に交差判定をすること
P crossP_LL(L a,L b){
  double A = cross(a[1]-a[0],b[1]-b[0]);
  double B = cross(a[1]-a[0],a[1]-b[0]);
  if(abs(A)<EPS && abs(B)<EPS)return b[0];
  if(abs(A)<EPS)assert(false);
  return b[0]+B/A*(b[1]-b[0]);
}
vector<P> crossP_CL(C c,L l){
  P tmp = projection(l,c.p);
  P e = (l[0]-l[1])/abs(l[0]-l[1]);
  double h = abs(c.p-tmp)*abs(c.p-tmp);
  double t = sqrt(c.r*c.r - h*h);
  if(t<EPS)return {tmp};
  return {tmp + e*t,tmp - e*t};
}
vector<P> crossP_CC(C a,C b){
  P A = conj(a.p-b.p);
  P B = (b.r*b.r - a.r*a.r - (b.p-a.p)*conj(b.p-a.p));
  P C = a.r*a.r*(a.p-b.p);
  P D = B*B-4.0*A*C;
  P z1 = (-B+sqrt(D))/(2.0*A)+a.p;
  P z2 = (-B+sqrt(D))/(2.0*A)+b.p;
  return {z1,z2};
}



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
bool isConvex(G g){
  for(int i=0; i<g.size();i++){
    if(ccw(Prev(g,i),Curr(g,i),Next(g,i))>0)return false;
  }
}



//接線
//TODO check
vector<L> TLine_CP(C c,P p){
  P v = c.p - p;
  double t = asin(abs(c.r)/(abs(v)));
  P e = v/abs(v) * exp(P(.0,t));
  P n1 = sqrt(abs(v)*abs(v) - c.r*c.r)*e + p;
  P n2 = reflection(L(p,c.p),n1);
  return {L(p,n1),L(p,n2)};
}

// TLine CC
vector<L> TLine_CPr(C c,P p,double r){
  P v = c.p - p;
  double t = asin(abs(c.r)/(abs(v)));
  P e = v/abs(v) * exp(P(.0,t));
  P n1 = sqrt(abs(v)*abs(v) - c.r*c.r)*e + p;
  P e1 = (n1-c.p)/abs(n1-c.p) * r;
  P n2 = reflection(L(p,c.p),n1);
  P e2 = (n2-c.p)/abs(n2-c.p) * r;
  return {L(p+e1,n1+e1),L(p+e2,n2+e2)};
}
vector<L> TLine_CC(C a,C b){
  //接してる時がヤバイ
  vector<L> res;
  if(!isCrossCC(a,b)&&(abs(a.r)>EPS)&&(abs(b.r>EPS))){
    P tmp = (a.p-b.p)*(b.r)/(a.r+b.r) + b.p;
    auto t1 = TLine_CP(a,tmp);
    auto t2 = TLine_CP(b,tmp);
    res.push_back(L(t1[0][1],t2[0][1]));
    res.push_back(L(t1[1][1],t2[1][1]));
  }
  if(abs(a.r-b.r)<EPS){
    const auto r = a.r;
    P e = (a.p-b.p)/abs(a.p-b.p) * exp(P(.0,90.0/180.0*M_PI));
    res.push_back(L(a.p+(e*r),b.p+(e*r)));
    if(abs(r)>=EPS)res.push_back(L(a.p-(e*r),b.p-(e*r)));
  }else{
    if(a.r<b.r)swap(a,b);
    auto t3 = TLine_CPr(C(a.p,a.r-b.r),b.p,b.r);
    for(auto i:t3){
      res.push_back(i);
    }
  }
  return res;
}



//原点を起点とした回転
P rotate(P a,double r){
  return a*exp(P(0.0,r*M_PI/180.0));
}

int main(){
}
