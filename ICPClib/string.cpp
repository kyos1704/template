#include<vector>
#include<string>
#include<sstream>
using namespace std;

vector<string> split(string in,char c){
  vector<string> res;
  string s;
  stringstream ss(in);
  while(getline(ss,s,c))res.push_back(s);
  return res;
}

string revStr(string s){
  return string(s.rbegin(),s.rend());
}


int main(){
}
