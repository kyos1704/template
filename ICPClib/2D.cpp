#include<utility>
#include<cmath>
using namespace std;
#define X first
#define Y second

typedef long long ll;
typedef pair<ll,ll> P;
int n;

int outer_product(P a,P b) {
  return (a.X * b.Y - b.X * a.Y);
}

int inner_product(P a,P b){
  return (a.X * b.X + a.Y *b.Y);
}

ll pow_len(P a) {
  return a.X * a.X + a.Y * a.Y;
}

ll sqrt_len(P a){
  return sqrt(pow_len(a));
}

P mkvec(P a,P b) {
  return P(a.X - b.X, a.Y - b.Y);
}

int main(){}
