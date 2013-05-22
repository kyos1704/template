#include<iostream>
#include<cstdio>
#include<bitset>
#include<algorithm>
#include<vector>
using namespace std;
#define MAX_N 100

class union_find{
private:
	vector<int> parents;
	vector<int> rank;
public:
	union_find(int n){
		parents.resize(n);
		rank.resize(n);
		for(int i=0;i<n;i++){
			parents[i]=i;
			rank[i]=0;
		}
	}
	int find(int x){
		if(parents[x]==x){
			return x;
		}else{
			return parents[x]=find(parents[x]);
		}
	}
	void unite(int x,int y){
		x=find(x);
		y=find(y);
		if(x==y)return;
		if(rank[x]<rank[y]){
			parents[x]=y;
		}else{
			parents[y]=x;
			if(rank[x]==rank[y])rank[x]++;
		}
	}
	bool same(int x,int y){
		return (find(x)==find(y));
	}
};
int main(){
}
