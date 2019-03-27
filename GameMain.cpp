#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <string>
#include <sstream>
#include <complex>
#include <vector>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <set>
#include <random>
using namespace std;
 
#define mod 1000000007
#define FOR(x,to) for(int x=0;x<(to);x++)
#define FORR(x,arr) for(auto& x:arr)
#define ALL(a) (a.begin()),(a.end())
#define ZERO(a) memset(a,0,sizeof(a))
#define MINUS(a) memset(a,0xff,sizeof(a))
#define long long long
inline int rei(){int x;cin>>x;return x;}
inline long rel(){long x;cin>>x;return x;}
inline string res(){string x;cin>>x;return x;}
//------------------------------------------------------- 
namespace HalmintonSolver{
	int Map[200];
	bool finished[200];
	bool origMap[200];
	vector<int> G[200];
	int GraphPointer[200];
	int ans[200];
	int H;
	int W;
	int sh;
	int sw;
	bool Solver(){
		int lr[] = {-1,1,0,0};
		int du[] = {0,0,-1,1};
		char direct[] = {'L','R','U','D'};
		int c = 0;
		for(int i=0;i<H;i++){
			for(int j=0;j<W;j++){
				if(!origMap[i*W+j]){
					Map[i*W+j] = -1;
				}
				else{
					Map[i*W+j] = c++;
				}
			}
		}
		fill(finished,finished+c,false);
		fill(GraphPointer,GraphPointer+c,false);
		for(int i=0;i<c;i++){
			G[i].clear();
		}
		for(int i=0;i<H;i++){
			for(int j=0;j<W;j++){
				if(Map[i*W+j] == -1){
					continue;
				}
				for(int k=0;k<4;k++){
					if(j+lr[k] >= 0 && j+lr[k] < W && i+du[k] >= 0 && i+du[k] < H && Map[(i+du[k])*W+j+lr[k]] != -1){
						G[Map[i*W+j]].push_back(Map[(i+du[k])*W+j+lr[k]]);
					}
				}
			}
		}
		int spn = 0;
		ans[spn++] = Map[sh*W+sw];
		finished[Map[sh*W+sw]] = true;
		int ansnum = 0;
		while(0 < spn){
			int v = ans[spn-1];
			if(GraphPointer[v] == G[v].size()){
				GraphPointer[v] = 0;
				spn--;
				finished[v] = false;
			}
			else if(finished[G[v][GraphPointer[v]]]){
				GraphPointer[v]++;
			}
			else{
				int t = G[v][GraphPointer[v]];
				ans[spn++] = t;
				GraphPointer[v]++;
				finished[t] = true;
			}
			if(spn == c && GraphPointer[ans[c-1]] == 0){
				ansnum++;
			}
		}
		return ansnum == 1;
	}
}
int Problem[200];
int hh;
int ww;
void Calc(int ho){
	std::mt19937 mt{std::random_device{}()};
	int ar[5];
	std::uniform_int_distribution<int> dist(0,hh*ww-1);
	HalmintonSolver::H = hh;
	HalmintonSolver::W = ww;
	ho++;
	while(1){
		for(int i=0;i<ho;i++){
			while(1){
				int c = dist(mt);
				bool OK = true;
				for(int j=0;j<i;j++){
					if(c == ar[j]){
						OK = false;
					}
				}
				if(OK){
					ar[i] = c;
					break;
				}
			}
		}
		fill(HalmintonSolver::origMap,HalmintonSolver::origMap+200,true);
		HalmintonSolver::sh = ar[0] / ww;
		HalmintonSolver::sw = ar[0] % ww;
		for(int i=1;i<ho;i++){
			int h = ar[i] / ww;
			int w = ar[i] % ww;
			HalmintonSolver::origMap[h*ww+w] = false;
		}
		if(HalmintonSolver::Solver()){
			for(int i=0;i<hh;i++){
				for(int j=0;j<ww;j++){
					if(HalmintonSolver::origMap[i*ww+j]){
						if(HalmintonSolver::sh == i && HalmintonSolver::sw == j){
							Problem[i*ww+j] = 2;
						}
						else{
							Problem[i*ww+j] = 1;
						}
					}
					else{
						Problem[i*ww+j] = 0;
					}
				}
			}
			break;
		}
	}
}
int mapstate[200];
void WriteMap(int h,int w){
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			cout << mapstate[i*w+j];
		}
		cout << endl;
	}
	for(int i=h;i<9;i++){
		cout << endl;
	}
}
void OneProblem(int h,int w,int ho){
	hh = h;
	ww = w;
	Calc(ho);
	int c = ho+1;
	int hp;
	int wp;
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			if(Problem[i*w+j] == 2){
				hp = i;
				wp = j;
			}
			mapstate[i*w+j] = Problem[i*w+j];
		}
	}
	WriteMap(h,w);
	while(1){
		string input = res();
		if(input[0] == 'w'){
			//up
			if(hp != 0 && mapstate[(hp-1)*w+wp] == 1){
				c++;
				mapstate[hp*w+wp] = 0;
				hp--;
				mapstate[hp*w+wp] = 2;
			}
		}
		else if(input[0] == 'a'){
			//left
			if(wp != 0 && mapstate[hp*w+wp-1] == 1){
				c++;
				mapstate[hp*w+wp] = 0;
				wp--;
				mapstate[hp*w+wp] = 2;
			}
		}
		else if(input[0] == 's'){
			//down
			if(hp != h-1 && mapstate[(hp+1)*w+wp] == 1){
				c++;
				mapstate[hp*w+wp] = 0;
				hp++;
				mapstate[hp*w+wp] = 2;
			}
		}
		else if(input[0] == 'd'){
			//right
			if(wp != w-1 && mapstate[hp*w+wp+1] == 1){
				c++;
				mapstate[hp*w+wp] = 0;
				wp++;
				mapstate[hp*w+wp] = 2;
			}
		}
		else if(input[0] == 'r'){
			for(int i=0;i<h;i++){
				for(int j=0;j<w;j++){
					if(Problem[i*w+j] == 2){
						hp = i;
						wp = j;
					}
					mapstate[i*w+j] = Problem[i*w+j];
				}
			}
			c = ho+1;
		}
		if(c == h*w){
			return;
		}
		else{
			WriteMap(h,w);
		}
	}
}
int main(int argc,char** argv){
	OneProblem(4,4,2);
	cout << "Clear!!!!!" << endl;
	for(int i=0;i<9;i++){
		cout << endl;
	}
	OneProblem(5,5,3);
	cout << "Clear!!!!!" << endl;
	for(int i=0;i<9;i++){
		cout << endl;
	}
	OneProblem(6,6,4);
	cout << "Congratulation!!!!!!" << endl;
	for(int i=0;i<9;i++){
		cout << endl;
	}
	return 0;
}
