#include<vector>
using namespace std;

vector<int> prime;
vector<int> prime_list;
void prime_set(int n){
	n+=100;
	prime.resize(n);
	for(int i=0;i<n;i++){
		prime[i]=1;
	}
	prime[0]=prime[1]=0;
	for(int i=0;i*i<n;i++){
		if(prime[i]){
			for(int j=i*2;j<n;j+=i){
				prime[j]=0;
			}
		}
	}
	for(int i=0;i<n;i++){
		if(prime[i])prime_list.push_back(i);
	}
}

int main(){}
