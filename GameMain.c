#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define MaxSize 10
int Map[MaxSize][MaxSize];
int lr[] = {-1,1,0,0};
int du[] = {0,0,-1,1};
int finished[MaxSize][MaxSize];
int GraphPointer[MaxSize][MaxSize];
int ans[MaxSize][MaxSize];
int pathH[MaxSize*MaxSize];
int pathW[MaxSize*MaxSize];
int H;
int W;
int sh;
int sw;
int Plun(){
	int i,j,k;
	int edgeh;
	int edgew;
	int edgenum = 0;
	int oddnum = 0;
	int evennum = 0;
	for(i=0;i<H;i++){
		for(j=0;j<W;j++){
			if(Map[i][j]){
				if((i+j) % 2 == 0){
					evennum++;
				}
				else{
					oddnum++;
				}
			}
			int c = 0;
			for(k=0;k<4;k++){
				int th = i+du[k];
				int tw = j+lr[k];
				if(th >= 0 && th < H && tw >= 0 && tw < W && Map[th][tw]){
					c++;
				}
			}
			if(c == 1){
				edgenum++;
				edgeh = i;
				edgew = j;
			}
		}
	}
	if(edgenum == 0 || edgenum > 2){
		return -1;
	}
	if(oddnum == evennum){
		return edgeh*W+edgew;
	}
	else{
		if(((edgeh+edgew) % 2 == 0 && evennum == oddnum+1) || ((edgeh+edgew) % 2 == 1 && evennum+1 == oddnum)){
			return edgeh*W+edgew;
		}
		else{
			return -1;
		}
	}
	
}
void Solver(int vnum){
	int i,j;
	int c = vnum;
	for(i=0;i<H;i++){
		for(j=0;j<W;j++){
			finished[i][j] = 0;
			GraphPointer[i][j] = 0;
			ans[i][j] = 0;
		}
	}
	int spn = 1;
	pathH[0] = sh;
	pathW[0] = sw;
	finished[sh][sw] = 1;
	while(0 < spn){
		int h = pathH[spn-1];
		int w = pathW[spn-1];
		if(spn == c && GraphPointer[h][w] == 0){
			ans[h][w]++;
		}
		if(GraphPointer[h][w] == 4){
			GraphPointer[h][w] = 0;
			spn--;
			finished[h][w] = 0;
		}
		else{
			int th = h + du[GraphPointer[h][w]];
			int tw = w + lr[GraphPointer[h][w]];
			GraphPointer[h][w]++;
			if(th >= 0 && th < H && tw >= 0 && tw < W && !finished[th][tw] && Map[th][tw]){
				pathH[spn] = th;
				pathW[spn++] = tw;
				finished[th][tw] = 1;
			}
		}
	}
}
int ar[5];
void GenerateProblem(int ho){
	int i,j;
	srand((unsigned)time(NULL));
	while(1){
		for(i=0;i<ho;i++){
			while(1){
				int hop = rand() % (H*W);
				int OK = 1;
				for(j=0;j<i;j++){
					if(hop == ar[j]){
						OK = 0;
					}
				}
				if(OK){
					ar[i] = hop;
					break;
				}
			}
		}
		for(i=0;i<H;i++){
			for(j=0;j<W;j++){
				Map[i][j] = 1;
			}
		}
		for(i=0;i<ho;i++){
			int h = ar[i] / W;
			int w = ar[i] % W;
			Map[h][w] = 0;
		}
		int start = Plun();
		if(start == -1){
			continue;
		}
		sh = start / W;
		sw = start % W;
		Solver(H*W-ho);
		for(i=0;i<H;i++){
			for(j=0;j<W;j++){
				if(ans[i][j] == 1){
					sh = i;
					sw = j;
					return;
				}
			}
		}
	}
}
int mapstate[MaxSize][MaxSize];
void WriteMap(){
	for(int i=0;i<H;i++){
		for(int j=0;j<W;j++){
			if(mapstate[i][j] == 0){
				printf(".");
			}
			if(mapstate[i][j] == 1){
				printf("#");
			}
			if(mapstate[i][j] == 2){
				printf("P");
			}
		}
		printf("\n");
	}
	for(int i=H;i<9;i++){
		printf("\n");
	}
}
char input[1000];
void OneProblem(int H_,int W_,int ho){
	H = H_;
	W = W_;
	int i,j;
	GenerateProblem(ho);
	int hp = sh;
	int wp = sw;
	for(i=0;i<H;i++){
		for(j=0;j<W;j++){
			mapstate[i][j] = Map[i][j];
		}
	}
	mapstate[sh][sw] = 2;
	WriteMap();
	int c = ho+1;
	while(1){
		scanf("%s",input);
		if(input[0] == 'w'){
			//up
			if(hp != 0 && mapstate[hp-1][wp] == 1){
				c++;
				mapstate[hp][wp] = 0;
				hp--;
				mapstate[hp][wp] = 2;
			}
		}
		else if(input[0] == 'a'){
			//left
			if(wp != 0 && mapstate[hp][wp-1] == 1){
				c++;
				mapstate[hp][wp] = 0;
				wp--;
				mapstate[hp][wp] = 2;
			}
		}
		else if(input[0] == 's'){
			//down
			if(hp != H-1 && mapstate[hp+1][wp] == 1){
				c++;
				mapstate[hp][wp] = 0;
				hp++;
				mapstate[hp][wp] = 2;
			}
		}
		else if(input[0] == 'd'){
			//right
			if(wp != W-1 && mapstate[hp][wp+1] == 1){
				c++;
				mapstate[hp][wp] = 0;
				wp++;
				mapstate[hp][wp] = 2;
			}
		}
		else if(input[0] == 'r'){
			for(int i=0;i<H;i++){
				for(int j=0;j<W;j++){
					mapstate[i][j] = Map[i][j];
				}
			}
			mapstate[sh][sw] = 2;
			hp = sh;
			wp = sw;
			c = ho+1;
		}
		if(c == H*W){
			return;
		}
		else{
			WriteMap();
		}
	}
}
int main(int argc,char** argv){
	int i;
	printf("(a):left (w):up (d):right (s):down (r):reset\n");
	#ifdef CUSTOM
		while(1){
			int h,w,ho;
			scanf("%d %d %d",&h,&w,&ho);
			if(h == 0){
				break;
			}
			OneProblem(h,w,ho);
			printf("Clear!!!!!\n");
			for(i=1;i<8;i++){
				printf("\n");
			}
		}
	#else
		OneProblem(4,4,2);
		printf("Clear!!!!!\n");
		for(i=1;i<8;i++){
			printf("\n");
		}
		OneProblem(5,5,3);
		printf("Clear!!!!!\n");
		for(i=1;i<8;i++){
			printf("\n");
		}
		OneProblem(6,6,4);
		printf("Congratulation!!!!!!\n");
		for(i=1;i<8;i++){
			printf("\n");
		}
	#endif
	return 0;
}
