#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#define ROW 15
#define COL 15

extern int tag;
extern int board[ROW][COL];
static int scores[ROW][COL]={0};

typedef struct _SITE {													//自定义坐标类型SITE 

int x;

int y;

} Site;

void setTextColor(int color);
void gotoxy(int x,int y);
void output(int tag);
void modifyBoard(int siteRow,int siteCol,int tag);
int isBlank(int siteRow,int siteCol,int tag);
int isVictory();
void score();
Site analyze();
void zeroScores();

void computer(int n){												//AI端函数 
	static int status=0;
	static Site bestSite={7,7};
	
	if(n==0){
		status=0;
		return;
	}
	
	if(status!=0){
		gotoxy(2*(bestSite.x)+1, ((bestSite.y)+1)*3);
		output(tag);
	}
	score();														//对每一个空白格点进行评分 
	bestSite=analyze();												//找出分数最高的点作为电脑的下棋点 
	gotoxy(2*(bestSite.x)+1, ((bestSite.y)+1)*3);
	setTextColor(13);
	putchar(64);
	modifyBoard(bestSite.x, bestSite.y, tag);
	tag++;
	zeroScores();
	status++;
}

void score(){
	int i,j;
	
	int judge411(int i, int j);
	int judge412(int i, int j);
	int judge413(int i, int j);
	int judge421(int i, int j);
	int judge422(int i, int j);
	int judge423(int i, int j);
	int judge424(int i, int j);
	int judge311(int i, int j);
	int judge312(int i, int j);
	int judge313(int i, int j);
	int judge321(int i, int j);
	int judge322(int i, int j);
	int judge323(int i, int j);
	int judge324(int i, int j);
	int judge1(int i, int j);
	
	for(i=0; i<ROW; i++){
		for(j=0; j<COL; j++){
			if(board[i][j]==0){
				modifyBoard(i,j,tag);//分析电脑在此处落子后的情况 
				if(isVictory()==10){//xxxxx,分数+10000 
					scores[i][j]+=10000;
				}
				if(judge411(i,j)==1){//xoooox,分数+8000 
					scores[i][j]+=8000;
				}
				if(judge412(i,j)==1){//oxooo,分数+8000 
					scores[i][j]+=8000;
				}
				if(judge413(i,j)==1){//ooxoo,分数+8000 
					scores[i][j]+=8000;
				}
				if(judge421(i,j)==1){//x.xxx,分数+5000 
					if((i==0) || (j==0) || (i==14) || (j==14)){
						scores[i][j]+=200;
					}
					else {
						if(judge423(i,j)==1){//ox.xxxo,分数+200 
							scores[i][j]+=200;
						}
						else{
							scores[i][j]+=5000;
						}
					}
				}
				if(judge422(i,j)==1){//xx.xx,分数+5000 
					if((i==1) || (j==1) || (i==13) || (j==13)){
						scores[i][j]+=200;
					}
					else {
						if(judge424(i,j)==1){//oxx.xxo,分数+200 
							scores[i][j]+=200;
						}
						else{
							scores[i][j]+=5000;
						}
					}
				}
				if(judge311(i,j)==1){//xooo,分数+4000 
					scores[i][j]+=4000;
				}
				if(judge312(i,j)==1){//oxoo,分数+4000 
					scores[i][j]+=4000;
				}
				if(judge313(i,j)==1){//xooox,分数+200
					scores[i][j]+=200; 
				}
				if(judge321(i,j)==1){//ox.xx,分数+500 
					scores[i][j]+=500;
				}
				if(judge322(i,j)==1){//oxx.x,分数+500 
					scores[i][j]+=500;
				}
				if(judge323(i,j)==1){//x.xx,分数+1000 
					scores[i][j]+=1000;
				}
				if(judge324(i,j)==1){//xx.x,分数+1000 
					scores[i][j]+=1000;
				}
				if(judge1(i,j)==1){//x 
					
				}
				else {
					scores[i][j]+=100;
				}
				board[i][j]=0;
			}
		}
	}
}

int judge411(int i, int j){
	if(i<5) {
		if((board[i+1][j]==1)&&(board[i+2][j]==1)&&(board[i+3][j]==1)&&(board[i+4][j]==1)&&(board[i+5][j]==10)) return 1;
		if(j<5){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==1)&&(board[i][j+4]==1)&&(board[i][j+5]==10)) return 1;
			if((board[i+1][j+1]==1)&&(board[i+2][j+2]==1)&&(board[i+3][j+3]==1)&&(board[i+4][j+4]==1)&&(board[i+5][j+5]==10)) return 1;
		}
		else if(j<10){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==1)&&(board[i][j+4]==1)&&(board[i][j+5]==10)) return 1;
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==1)&&(board[i][j-4]==1)&&(board[i][j-5]==10)) return 1;
			if((board[i+1][j+1]==1)&&(board[i+2][j+2]==1)&&(board[i+3][j+3]==1)&&(board[i+4][j+4]==1)&&(board[i+5][j+5]==10)) return 1;
			if((board[i+1][j-1]==1)&&(board[i+2][j-2]==1)&&(board[i+3][j-3]==1)&&(board[i+4][j-4]==1)&&(board[i+5][j-5]==10)) return 1;
		}
		else {
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==1)&&(board[i][j-4]==1)&&(board[i][j-5]==10)) return 1;
			if((board[i+1][j-1]==1)&&(board[i+2][j-2]==1)&&(board[i+3][j-3]==1)&&(board[i+4][j-4]==1)&&(board[i+5][j-5]==10)) return 1;
		}
	}
	else if(i<10) {
		if((board[i+1][j]==1)&&(board[i+2][j]==1)&&(board[i+3][j]==1)&&(board[i+4][j]==1)&&(board[i+5][j]==10)) return 1;
		if((board[i-1][j]==1)&&(board[i-2][j]==1)&&(board[i-3][j]==1)&&(board[i-4][j]==1)&&(board[i-5][j]==10)) return 1;
		if(j<5){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==1)&&(board[i][j+4]==1)&&(board[i][j+5]==10)) return 1;
			if((board[i+1][j+1]==1)&&(board[i+2][j+2]==1)&&(board[i+3][j+3]==1)&&(board[i+4][j+4]==1)&&(board[i+5][j+5]==10)) return 1;
			if((board[i-1][j+1]==1)&&(board[i-2][j+2]==1)&&(board[i-3][j+3]==1)&&(board[i-4][j+4]==1)&&(board[i-5][j+5]==10)) return 1;
		}
		else if(j<10){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==1)&&(board[i][j+4]==1)&&(board[i][j+5]==10)) return 1;
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==1)&&(board[i][j-4]==1)&&(board[i][j-5]==10)) return 1;
			if((board[i+1][j+1]==1)&&(board[i+2][j+2]==1)&&(board[i+3][j+3]==1)&&(board[i+4][j+4]==1)&&(board[i+5][j+5]==10)) return 1;
			if((board[i+1][j-1]==1)&&(board[i+2][j-2]==1)&&(board[i+3][j-3]==1)&&(board[i+4][j-4]==1)&&(board[i+5][j-5]==10)) return 1;
			if((board[i-1][j+1]==1)&&(board[i-2][j+2]==1)&&(board[i-3][j+3]==1)&&(board[i-4][j+4]==1)&&(board[i-5][j+5]==10)) return 1;
			if((board[i-1][j-1]==1)&&(board[i-2][j-2]==1)&&(board[i-3][j-3]==1)&&(board[i-4][j-4]==1)&&(board[i-5][j-5]==10)) return 1;
		}
		else {
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==1)&&(board[i][j-4]==1)&&(board[i][j-5]==10)) return 1;
			if((board[i+1][j-1]==1)&&(board[i+2][j-2]==1)&&(board[i+3][j-3]==1)&&(board[i+4][j-4]==1)&&(board[i+5][j-5]==10)) return 1;
			if((board[i-1][j-1]==1)&&(board[i-2][j-2]==1)&&(board[i-3][j-3]==1)&&(board[i-4][j-4]==1)&&(board[i-5][j-5]==10)) return 1;
		}
	}
	else {
		if((board[i-1][j]==1)&&(board[i-2][j]==1)&&(board[i-3][j]==1)&&(board[i-4][j]==1)&&(board[i-5][j]==10)) return 1;
		if(j<5){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==1)&&(board[i][j+4]==1)&&(board[i][j+5]==10)) return 1;
			if((board[i-1][j+1]==1)&&(board[i-2][j+2]==1)&&(board[i-3][j+3]==1)&&(board[i-4][j+4]==1)&&(board[i-5][j+5]==10)) return 1;
		}
		else if(j<10){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==1)&&(board[i][j+4]==1)&&(board[i][j+5]==10)) return 1;
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==1)&&(board[i][j-4]==1)&&(board[i][j-5]==10)) return 1;
			if((board[i-1][j+1]==1)&&(board[i-2][j+2]==1)&&(board[i-3][j+3]==1)&&(board[i-4][j+4]==1)&&(board[i-5][j+5]==10)) return 1;
			if((board[i-1][j-1]==1)&&(board[i-2][j-2]==1)&&(board[i-3][j-3]==1)&&(board[i-4][j-4]==1)&&(board[i-5][j-5]==10)) return 1;
		}
		else {
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==1)&&(board[i][j-4]==1)&&(board[i][j-5]==10)) return 1;
			if((board[i-1][j-1]==1)&&(board[i-2][j-2]==1)&&(board[i-3][j-3]==1)&&(board[i-4][j-4]==1)&&(board[i-5][j-5]==10)) return 1;
		}
	}
	return 0;
}

int judge412(int i, int j){
	if(i<4) {
		if((board[i+1][j]==1)&&(board[i+2][j]==1)&&(board[i+3][j]==1)&&(board[i-1][j]==1)) return 1;
		if(j<4){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==1)&&(board[i][j-1]==1)) return 1;
			if((board[i+1][j+1]==1)&&(board[i+2][j+2]==1)&&(board[i+3][j+3]==1)&&(board[i-1][j-1]==1)) return 1;
		}
		else if(j<11){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==1)&&(board[i][j-1]==1)) return 1;
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==1)&&(board[i][j+1]==1)) return 1;
			if((board[i+1][j+1]==1)&&(board[i+2][j+2]==1)&&(board[i+3][j+3]==1)&&(board[i-1][j-1]==1)) return 1;
			if((board[i+1][j-1]==1)&&(board[i+2][j-2]==1)&&(board[i+3][j-3]==1)&&(board[i-1][j+1]==1)) return 1;
		}
		else {
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==1)&&(board[i][j+1]==1)) return 1;
			if((board[i+1][j-1]==1)&&(board[i+2][j-2]==1)&&(board[i+3][j-3]==1)&&(board[i-1][j+1]==1)) return 1;
		}
	}
	else if(i<11) {
		if((board[i+1][j]==1)&&(board[i+2][j]==1)&&(board[i+3][j]==1)&&(board[i-1][j]==1)) return 1;
		if((board[i-1][j]==1)&&(board[i-2][j]==1)&&(board[i-3][j]==1)&&(board[i+1][j]==1)) return 1;
		if(j<4){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==1)&&(board[i][j-1]==1)) return 1;
			if((board[i+1][j+1]==1)&&(board[i+2][j+2]==1)&&(board[i+3][j+3]==1)&&(board[i-1][j-1]==1)) return 1;
			if((board[i-1][j+1]==1)&&(board[i-2][j+2]==1)&&(board[i-3][j+3]==1)&&(board[i+1][j-1]==1)) return 1;
		}
		else if(j<11){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==1)&&(board[i][j-1]==1)) return 1;
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==1)&&(board[i][j+1]==1)) return 1;
			if((board[i+1][j+1]==1)&&(board[i+2][j+2]==1)&&(board[i+3][j+3]==1)&&(board[i-1][j-1]==1)) return 1;
			if((board[i+1][j-1]==1)&&(board[i+2][j-2]==1)&&(board[i+3][j-3]==1)&&(board[i-1][j+1]==1)) return 1;
			if((board[i-1][j+1]==1)&&(board[i-2][j+2]==1)&&(board[i-3][j+3]==1)&&(board[i+1][j-1]==1)) return 1;
			if((board[i-1][j-1]==1)&&(board[i-2][j-2]==1)&&(board[i-3][j-3]==1)&&(board[i+1][j+1]==1)) return 1;
		}
		else {
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==1)&&(board[i][j+1]==1)) return 1;
			if((board[i+1][j-1]==1)&&(board[i+2][j-2]==1)&&(board[i+3][j-3]==1)&&(board[i-1][j+1]==1)) return 1;
			if((board[i-1][j-1]==1)&&(board[i-2][j-2]==1)&&(board[i-3][j-3]==1)&&(board[i+1][j+1]==1)) return 1;
		}
	}
	else {
		if((board[i-1][j]==1)&&(board[i-2][j]==1)&&(board[i-3][j]==1)&&(board[i+1][j]==1)) return 1;
		if(j<4){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==1)&&(board[i][j-1]==1)) return 1;
			if((board[i-1][j+1]==1)&&(board[i-2][j+2]==1)&&(board[i-3][j+3]==1)&&(board[i+1][j-1]==1)) return 1;
		}
		else if(j<11){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==1)&&(board[i][j-1]==1)) return 1;
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==1)&&(board[i][j+1]==1)) return 1;
			if((board[i-1][j+1]==1)&&(board[i-2][j+2]==1)&&(board[i-3][j+3]==1)&&(board[i+1][j-1]==1)) return 1;
			if((board[i-1][j-1]==1)&&(board[i-2][j-2]==1)&&(board[i-3][j-3]==1)&&(board[i+1][j+1]==1)) return 1;
		}
		else {
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==1)&&(board[i][j+1]==1)) return 1;
			if((board[i-1][j-1]==1)&&(board[i-2][j-2]==1)&&(board[i-3][j-3]==1)&&(board[i+1][j+1]==1)) return 1;
		}
	}
	return 0;
}

int judge413(int i, int j){
	if(i<3) {
		if((board[i+1][j]==1)&&(board[i+2][j]==1)&&(board[i-2][j]==1)&&(board[i-1][j]==1)) return 1;
		if(j<3){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j-2]==1)&&(board[i][j-1]==1)) return 1;
			if((board[i+1][j+1]==1)&&(board[i+2][j+2]==1)&&(board[i-2][j-2]==1)&&(board[i-1][j-1]==1)) return 1;
		}
		else if(j<12){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j-2]==1)&&(board[i][j-1]==1)) return 1;
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j+2]==1)&&(board[i][j+1]==1)) return 1;
			if((board[i+1][j+1]==1)&&(board[i+2][j+2]==1)&&(board[i-2][j-2]==1)&&(board[i-1][j-1]==1)) return 1;
			if((board[i+1][j-1]==1)&&(board[i+2][j-2]==1)&&(board[i-2][j+2]==1)&&(board[i-1][j+1]==1)) return 1;
		}
		else {
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j+2]==1)&&(board[i][j+1]==1)) return 1;
			if((board[i+1][j-1]==1)&&(board[i+2][j-2]==1)&&(board[i-2][j+2]==1)&&(board[i-1][j+1]==1)) return 1;
		}
	}
	else if(i<12) {
		if((board[i+1][j]==1)&&(board[i+2][j]==1)&&(board[i-2][j]==1)&&(board[i-1][j]==1)) return 1;
		if((board[i-1][j]==1)&&(board[i-2][j]==1)&&(board[i+2][j]==1)&&(board[i+1][j]==1)) return 1;
		if(j<3){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j-2]==1)&&(board[i][j-1]==1)) return 1;
			if((board[i+1][j+1]==1)&&(board[i+2][j+2]==1)&&(board[i-2][j-2]==1)&&(board[i-1][j-1]==1)) return 1;
			if((board[i-1][j+1]==1)&&(board[i-2][j+2]==1)&&(board[i+2][j-2]==1)&&(board[i+1][j-1]==1)) return 1;
		}
		else if(j<12){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j-2]==1)&&(board[i][j-1]==1)) return 1;
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j+2]==1)&&(board[i][j+1]==1)) return 1;
			if((board[i+1][j+1]==1)&&(board[i+2][j+2]==1)&&(board[i-2][j-2]==1)&&(board[i-1][j-1]==1)) return 1;
			if((board[i+1][j-1]==1)&&(board[i+2][j-2]==1)&&(board[i-2][j+2]==1)&&(board[i-1][j+1]==1)) return 1;
			if((board[i-1][j+1]==1)&&(board[i-2][j+2]==1)&&(board[i+2][j-2]==1)&&(board[i+1][j-1]==1)) return 1;
			if((board[i-1][j-1]==1)&&(board[i-2][j-2]==1)&&(board[i+2][j+2]==1)&&(board[i+1][j+1]==1)) return 1;
		}
		else {
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j+2]==1)&&(board[i][j+1]==1)) return 1;
			if((board[i+1][j-1]==1)&&(board[i+2][j-2]==1)&&(board[i-2][j+2]==1)&&(board[i-1][j+1]==1)) return 1;
			if((board[i-1][j-1]==1)&&(board[i-2][j-2]==1)&&(board[i+2][j+2]==1)&&(board[i+1][j+1]==1)) return 1;
		}
	}
	else {
		if((board[i-1][j]==1)&&(board[i-2][j]==1)&&(board[i+2][j]==1)&&(board[i+1][j]==1)) return 1;
		if(j<3){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j-2]==1)&&(board[i][j-1]==1)) return 1;
			if((board[i-1][j+1]==1)&&(board[i-2][j+2]==1)&&(board[i+2][j-2]==1)&&(board[i+1][j-1]==1)) return 1;
		}
		else if(j<12){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j-2]==1)&&(board[i][j-1]==1)) return 1;
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j+2]==1)&&(board[i][j+1]==1)) return 1;
			if((board[i-1][j+1]==1)&&(board[i-2][j+2]==1)&&(board[i+2][j-2]==1)&&(board[i+1][j-1]==1)) return 1;
			if((board[i-1][j-1]==1)&&(board[i-2][j-2]==1)&&(board[i+2][j+2]==1)&&(board[i+1][j+1]==1)) return 1;
		}
		else {
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j+2]==1)&&(board[i][j+1]==1)) return 1;
			if((board[i-1][j-1]==1)&&(board[i-2][j-2]==1)&&(board[i+2][j+2]==1)&&(board[i+1][j+1]==1)) return 1;
		}
	}
	return 0;
}

int judge421(int i,int j){
	if(i<4) {
		if((board[i+1][j]==10)&&(board[i+2][j]==10)&&(board[i+3][j]==10)) return 1;
		if(j<4){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==10)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==10)&&(board[i+3][j+3]==10)) return 1;
		}
		else if(j<11){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==10)) return 1;
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==10)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==10)&&(board[i+3][j+3]==10)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==10)&&(board[i+3][j-3]==10)) return 1;
		}
		else {
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==10)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==10)&&(board[i+3][j-3]==10)) return 1;
		}
	}
	else if(i<11) {
		if((board[i+1][j]==10)&&(board[i+2][j]==10)&&(board[i+3][j]==10)) return 1;
		if((board[i-1][j]==10)&&(board[i-2][j]==10)&&(board[i-3][j]==10)) return 1;
		if(j<4){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==10)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==10)&&(board[i+3][j+3]==10)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==10)&&(board[i-3][j+3]==10)) return 1;
		}
		else if(j<11){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==10)) return 1;
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==10)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==10)&&(board[i+3][j+3]==10)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==10)&&(board[i+3][j-3]==10)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==10)&&(board[i-3][j+3]==10)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==10)&&(board[i-3][j-3]==10)) return 1;
		}
		else {
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==10)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==10)&&(board[i+3][j-3]==10)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==10)&&(board[i-3][j-3]==10)) return 1;
		}
	}
	else {
		if((board[i-1][j]==10)&&(board[i-2][j]==10)&&(board[i-3][j]==10)) return 1;
		if(j<4){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==10)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==10)&&(board[i-3][j+3]==10)) return 1;
		}
		else if(j<11){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==10)) return 1;
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==10)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==10)&&(board[i-3][j+3]==10)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==10)&&(board[i-3][j-3]==10)) return 1;
		}
		else {
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==10)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==10)&&(board[i-3][j-3]==10)) return 1;
		}
	}
	return 0;
}

int judge422(int i,int j){
	if(i<4) {
		if((board[i+1][j]==10)&&(board[i+2][j]==10)&&(board[i-1][j]==10)) return 1;
		if(j<4){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j-1]==10)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==10)&&(board[i-1][j-1]==10)) return 1;
		}
		else if(j<11){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j-1]==10)) return 1;
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j+1]==10)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==10)&&(board[i-1][j-1]==10)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==10)&&(board[i-1][j+1]==10)) return 1;
		}
		else {
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j+1]==10)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==10)&&(board[i-1][j+1]==10)) return 1;
		}
	}
	else if(i<11) {
		if((board[i+1][j]==10)&&(board[i+2][j]==10)&&(board[i-1][j]==10)) return 1;
		if((board[i-1][j]==10)&&(board[i-2][j]==10)&&(board[i+1][j]==10)) return 1;
		if(j<4){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j-1]==10)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==10)&&(board[i-1][j-1]==10)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==10)&&(board[i+1][j-1]==10)) return 1;
		}
		else if(j<11){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j-1]==10)) return 1;
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j+1]==10)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==10)&&(board[i-1][j-1]==10)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==10)&&(board[i-1][j+1]==10)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==10)&&(board[i+1][j-1]==10)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==10)&&(board[i+1][j+1]==10)) return 1;
		}
		else {
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j+1]==10)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==10)&&(board[i-1][j+1]==10)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==10)&&(board[i+1][j+1]==10)) return 1;
		}
	}
	else {
		if((board[i-1][j]==10)&&(board[i-2][j]==10)&&(board[i+1][j]==10)) return 1;
		if(j<4){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j-1]==10)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==10)&&(board[i+1][j-1]==10)) return 1;
		}
		else if(j<11){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j-1]==10)) return 1;
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j+1]==10)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==10)&&(board[i+1][j-1]==10)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==10)&&(board[i+1][j+1]==10)) return 1;
		}
		else {
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j+1]==10)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==10)&&(board[i+1][j+1]==10)) return 1;
		}
	}
	return 0;
}

int judge423(int i, int j){
	if(i<5) {
		if((board[i+1][j]==10)&&(board[i+2][j]==10)&&(board[i+3][j]==10)&&(board[i+4][j]==1)&&(board[i-1][j]==1)) return 1;
		if(j<5){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==10)&&(board[i][j+4]==1)&&(board[i][j-1]==1)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==10)&&(board[i+3][j+3]==10)&&(board[i+4][j+4]==1)&&(board[i-1][j-1]==1)) return 1;
		}
		else if(j<10){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==10)&&(board[i][j+4]==1)&&(board[i][j-1]==1)) return 1;
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==10)&&(board[i][j-4]==1)&&(board[i][j+1]==1)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==10)&&(board[i+3][j+3]==10)&&(board[i+4][j+4]==1)&&(board[i-1][j-1]==1)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==10)&&(board[i+3][j-3]==10)&&(board[i+4][j-4]==1)&&(board[i-1][j+1]==1)) return 1;
		}
		else {
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==10)&&(board[i][j-4]==1)&&(board[i][j+1]==1)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==10)&&(board[i+3][j-3]==10)&&(board[i+4][j-4]==1)&&(board[i-1][j+1]==1)) return 1;
		}
	}
	else if(i<10) {
		if((board[i+1][j]==10)&&(board[i+2][j]==10)&&(board[i+3][j]==10)&&(board[i+4][j]==1)&&(board[i-1][j]==1)) return 1;
		if((board[i-1][j]==10)&&(board[i-2][j]==10)&&(board[i-3][j]==10)&&(board[i-4][j]==1)&&(board[i+1][j]==1)) return 1;
		if(j<5){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==10)&&(board[i][j+4]==1)&&(board[i][j-1]==1)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==10)&&(board[i+3][j+3]==10)&&(board[i+4][j+4]==1)&&(board[i-1][j-1]==1)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==10)&&(board[i-3][j+3]==10)&&(board[i-4][j+4]==1)&&(board[i+1][j-1]==1)) return 1;
		}
		else if(j<10){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==10)&&(board[i][j+4]==1)&&(board[i][j-1]==1)) return 1;
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==10)&&(board[i][j-4]==1)&&(board[i][j+1]==1)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==10)&&(board[i+3][j+3]==10)&&(board[i+4][j+4]==1)&&(board[i-1][j-1]==1)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==10)&&(board[i+3][j-3]==10)&&(board[i+4][j-4]==1)&&(board[i-1][j+1]==1)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==10)&&(board[i-3][j+3]==10)&&(board[i-4][j+4]==1)&&(board[i+1][j-1]==1)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==10)&&(board[i-3][j-3]==10)&&(board[i-4][j-4]==1)&&(board[i+1][j+1]==1)) return 1;
		}
		else {
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==10)&&(board[i][j-4]==1)&&(board[i][j+1]==1)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==10)&&(board[i+3][j-3]==10)&&(board[i+4][j-4]==1)&&(board[i-1][j+1]==1)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==10)&&(board[i-3][j-3]==10)&&(board[i-4][j-4]==1)&&(board[i+1][j+1]==1)) return 1;
		}
	}
	else {
		if((board[i-1][j]==10)&&(board[i-2][j]==10)&&(board[i-3][j]==10)&&(board[i-4][j]==1)&&(board[i+1][j]==1)) return 1;
		if(j<5){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==10)&&(board[i][j+4]==1)&&(board[i][j-1]==1)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==10)&&(board[i-3][j+3]==10)&&(board[i-4][j+4]==1)&&(board[i+1][j-1]==1)) return 1;
		}
		else if(j<10){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==10)&&(board[i][j+4]==1)&&(board[i][j-1]==1)) return 1;
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==10)&&(board[i][j-4]==1)&&(board[i][j+1]==1)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==10)&&(board[i-3][j+3]==10)&&(board[i-4][j+4]==1)&&(board[i+1][j-1]==1)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==10)&&(board[i-3][j-3]==10)&&(board[i-4][j-4]==1)&&(board[i+1][j+1]==1)) return 1;
		}
		else {
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==10)&&(board[i][j-4]==1)&&(board[i][j+1]==1)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==10)&&(board[i-3][j-3]==10)&&(board[i-4][j-4]==1)&&(board[i+1][j+1]==1)) return 1;
		}
	}
	return 0;
}

int judge424(int i, int j){
	if(i<4) {
		if((board[i+1][j]==10)&&(board[i+2][j]==10)&&(board[i+3][j]==1)&&(board[i-2][j]==1)&&(board[i-1][j]==10)) return 1;
		if(j<4){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==1)&&(board[i][j-2]==1)&&(board[i][j-1]==10)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==10)&&(board[i+3][j+3]==1)&&(board[i-2][j-2]==1)&&(board[i-1][j-1]==10)) return 1;
		}
		else if(j<11){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==1)&&(board[i][j-2]==1)&&(board[i][j-1]==10)) return 1;
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==1)&&(board[i][j+2]==1)&&(board[i][j+1]==10)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==10)&&(board[i+3][j+3]==1)&&(board[i-2][j-2]==1)&&(board[i-1][j-1]==10)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==10)&&(board[i+3][j-3]==1)&&(board[i-2][j+2]==1)&&(board[i-1][j+1]==10)) return 1;
		}
		else {
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==1)&&(board[i][j+2]==1)&&(board[i][j+1]==10)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==10)&&(board[i+3][j-3]==1)&&(board[i-2][j+2]==1)&&(board[i-1][j+1]==10)) return 1;
		}
	}
	else if(i<11) {
		if((board[i+1][j]==10)&&(board[i+2][j]==10)&&(board[i+3][j]==1)&&(board[i-2][j]==1)&&(board[i-1][j]==10)) return 1;
		if((board[i-1][j]==10)&&(board[i-2][j]==10)&&(board[i-3][j]==1)&&(board[i+2][j]==1)&&(board[i+1][j]==10)) return 1;
		if(j<4){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==1)&&(board[i][j-2]==1)&&(board[i][j-1]==10)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==10)&&(board[i+3][j+3]==1)&&(board[i-2][j-2]==1)&&(board[i-1][j-1]==10)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==10)&&(board[i-3][j+3]==1)&&(board[i+2][j-2]==1)&&(board[i+1][j-1]==10)) return 1;
		}
		else if(j<11){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==1)&&(board[i][j-2]==1)&&(board[i][j-1]==10)) return 1;
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==1)&&(board[i][j+2]==1)&&(board[i][j+1]==10)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==10)&&(board[i+3][j+3]==1)&&(board[i-2][j-2]==1)&&(board[i-1][j-1]==10)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==10)&&(board[i+3][j-3]==1)&&(board[i-2][j+2]==1)&&(board[i-1][j+1]==10)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==10)&&(board[i-3][j+3]==1)&&(board[i+2][j-2]==1)&&(board[i+1][j-1]==10)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==10)&&(board[i-3][j-3]==1)&&(board[i+2][j+2]==1)&&(board[i+1][j+1]==10)) return 1;
		}
		else {
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==1)&&(board[i][j+2]==1)&&(board[i][j+1]==10)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==10)&&(board[i+3][j-3]==1)&&(board[i-2][j+2]==1)&&(board[i-1][j+1]==10)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==10)&&(board[i-3][j-3]==1)&&(board[i+2][j+2]==1)&&(board[i+1][j+1]==10)) return 1;
		}
	}
	else {
		if((board[i-1][j]==10)&&(board[i-2][j]==10)&&(board[i-3][j]==1)&&(board[i+2][j]==1)&&(board[i+1][j]==10)) return 1;
		if(j<4){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==1)&&(board[i][j-2]==1)&&(board[i][j-1]==10)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==10)&&(board[i-3][j+3]==1)&&(board[i+2][j-2]==1)&&(board[i+1][j-1]==10)) return 1;
		}
		else if(j<11){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==1)&&(board[i][j-2]==1)&&(board[i][j-1]==10)) return 1;
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==1)&&(board[i][j+2]==1)&&(board[i][j+1]==10)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==10)&&(board[i-3][j+3]==1)&&(board[i+2][j-2]==1)&&(board[i+1][j-1]==10)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==10)&&(board[i-3][j-3]==1)&&(board[i+2][j+2]==1)&&(board[i+1][j+1]==10)) return 1;
		}
		else {
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==1)&&(board[i][j+2]==1)&&(board[i][j+1]==10)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==10)&&(board[i-3][j-3]==1)&&(board[i+2][j+2]==1)&&(board[i+1][j+1]==10)) return 1;
		}
	}
	return 0;
}

int judge311(int i, int j){
	if(i<5) {
		if((board[i+1][j]==1)&&(board[i+2][j]==1)&&(board[i+3][j]==1)&&(board[i+4][j]==0)) return 1;
		if(j<5){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==1)&&(board[i][j+4]==0)) return 1;
			if((board[i+1][j+1]==1)&&(board[i+2][j+2]==1)&&(board[i+3][j+3]==1)&&(board[i+4][j+4]==0)) return 1;
		}
		else if(j<10){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==1)&&(board[i][j+4]==0)) return 1;
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==1)&&(board[i][j-4]==0)) return 1;
			if((board[i+1][j+1]==1)&&(board[i+2][j+2]==1)&&(board[i+3][j+3]==1)&&(board[i+4][j+4]==0)) return 1;
			if((board[i+1][j-1]==1)&&(board[i+2][j-2]==1)&&(board[i+3][j-3]==1)&&(board[i+4][j-4]==0)) return 1;
		}
		else {
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==1)&&(board[i][j-4]==0)) return 1;
			if((board[i+1][j-1]==1)&&(board[i+2][j-2]==1)&&(board[i+3][j-3]==1)&&(board[i+4][j-4]==0)) return 1;
		}
	}
	else if(i<10) {
		if((board[i+1][j]==1)&&(board[i+2][j]==1)&&(board[i+3][j]==1)&&(board[i+4][j]==0)) return 1;
		if((board[i-1][j]==1)&&(board[i-2][j]==1)&&(board[i-3][j]==1)&&(board[i-4][j]==0)) return 1;
		if(j<5){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==1)&&(board[i][j+4]==0)) return 1;
			if((board[i+1][j+1]==1)&&(board[i+2][j+2]==1)&&(board[i+3][j+3]==1)&&(board[i+4][j+4]==0)) return 1;
			if((board[i-1][j+1]==1)&&(board[i-2][j+2]==1)&&(board[i-3][j+3]==1)&&(board[i-4][j+4]==0)) return 1;
		}
		else if(j<10){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==1)&&(board[i][j+4]==0)) return 1;
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==1)&&(board[i][j-4]==0)) return 1;
			if((board[i+1][j+1]==1)&&(board[i+2][j+2]==1)&&(board[i+3][j+3]==1)&&(board[i+4][j+4]==0)) return 1;
			if((board[i+1][j-1]==1)&&(board[i+2][j-2]==1)&&(board[i+3][j-3]==1)&&(board[i+4][j-4]==0)) return 1;
			if((board[i-1][j+1]==1)&&(board[i-2][j+2]==1)&&(board[i-3][j+3]==1)&&(board[i-4][j+4]==0)) return 1;
			if((board[i-1][j-1]==1)&&(board[i-2][j-2]==1)&&(board[i-3][j-3]==1)&&(board[i-4][j-4]==0)) return 1;
		}
		else {
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==1)&&(board[i][j-4]==0)) return 1;
			if((board[i+1][j-1]==1)&&(board[i+2][j-2]==1)&&(board[i+3][j-3]==1)&&(board[i+4][j-4]==0)) return 1;
			if((board[i-1][j-1]==1)&&(board[i-2][j-2]==1)&&(board[i-3][j-3]==1)&&(board[i-4][j-4]==0)) return 1;
		}
	}
	else {
		if((board[i-1][j]==1)&&(board[i-2][j]==1)&&(board[i-3][j]==1)&&(board[i-4][j]==0)) return 1;
		if(j<5){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==1)&&(board[i][j+4]==0)) return 1;
			if((board[i-1][j+1]==1)&&(board[i-2][j+2]==1)&&(board[i-3][j+3]==1)&&(board[i-4][j+4]==0)) return 1;
		}
		else if(j<10){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==1)&&(board[i][j+4]==0)) return 1;
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==1)&&(board[i][j-4]==0)) return 1;
			if((board[i-1][j+1]==1)&&(board[i-2][j+2]==1)&&(board[i-3][j+3]==1)&&(board[i-4][j+4]==0)) return 1;
			if((board[i-1][j-1]==1)&&(board[i-2][j-2]==1)&&(board[i-3][j-3]==1)&&(board[i-4][j-4]==0)) return 1;
		}
		else {
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==1)&&(board[i][j-4]==0)) return 1;
			if((board[i-1][j-1]==1)&&(board[i-2][j-2]==1)&&(board[i-3][j-3]==1)&&(board[i-4][j-4]==0)) return 1;
		}
	}
	return 0;
}

int judge312(int i, int j){
	if(i<4) {
		if((board[i+1][j]==1)&&(board[i+2][j]==1)&&(board[i+3][j]==0)&&(board[i-2][j]==0)&&(board[i-1][j]==1)) return 1;
		if(j<4){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==0)&&(board[i][j-2]==0)&&(board[i][j-1]==1)) return 1;
			if((board[i+1][j+1]==1)&&(board[i+2][j+2]==1)&&(board[i+3][j+3]==0)&&(board[i-2][j-2]==0)&&(board[i-1][j-1]==1)) return 1;
		}
		else if(j<11){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==0)&&(board[i][j-2]==0)&&(board[i][j-1]==1)) return 1;
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==0)&&(board[i][j+2]==0)&&(board[i][j+1]==1)) return 1;
			if((board[i+1][j+1]==1)&&(board[i+2][j+2]==1)&&(board[i+3][j+3]==0)&&(board[i-2][j-2]==0)&&(board[i-1][j-1]==1)) return 1;
			if((board[i+1][j-1]==1)&&(board[i+2][j-2]==1)&&(board[i+3][j-3]==0)&&(board[i-2][j+2]==0)&&(board[i-1][j+1]==1)) return 1;
		}
		else {
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==0)&&(board[i][j+2]==0)&&(board[i][j+1]==1)) return 1;
			if((board[i+1][j-1]==1)&&(board[i+2][j-2]==1)&&(board[i+3][j-3]==0)&&(board[i-2][j+2]==0)&&(board[i-1][j+1]==1)) return 1;
		}
	}
	else if(i<11) {
		if((board[i+1][j]==1)&&(board[i+2][j]==1)&&(board[i+3][j]==0)&&(board[i-2][j]==0)&&(board[i-1][j]==1)) return 1;
		if((board[i-1][j]==1)&&(board[i-2][j]==1)&&(board[i-3][j]==0)&&(board[i+2][j]==0)&&(board[i+1][j]==1)) return 1;
		if(j<4){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==0)&&(board[i][j-2]==0)&&(board[i][j-1]==1)) return 1;
			if((board[i+1][j+1]==1)&&(board[i+2][j+2]==1)&&(board[i+3][j+3]==0)&&(board[i-2][j-2]==0)&&(board[i-1][j-1]==1)) return 1;
			if((board[i-1][j+1]==1)&&(board[i-2][j+2]==1)&&(board[i-3][j+3]==0)&&(board[i+2][j-2]==0)&&(board[i+1][j-1]==1)) return 1;
		}
		else if(j<11){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==0)&&(board[i][j-2]==0)&&(board[i][j-1]==1)) return 1;
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==0)&&(board[i][j+2]==0)&&(board[i][j+1]==1)) return 1;
			if((board[i+1][j+1]==1)&&(board[i+2][j+2]==1)&&(board[i+3][j+3]==0)&&(board[i-2][j-2]==0)&&(board[i-1][j-1]==1)) return 1;
			if((board[i+1][j-1]==1)&&(board[i+2][j-2]==1)&&(board[i+3][j-3]==0)&&(board[i-2][j+2]==0)&&(board[i-1][j+1]==1)) return 1;
			if((board[i-1][j+1]==1)&&(board[i-2][j+2]==1)&&(board[i-3][j+3]==0)&&(board[i+2][j-2]==0)&&(board[i+1][j-1]==1)) return 1;
			if((board[i-1][j-1]==1)&&(board[i-2][j-2]==1)&&(board[i-3][j-3]==0)&&(board[i+2][j+2]==0)&&(board[i+1][j+1]==1)) return 1;
		}
		else {
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==0)&&(board[i][j+2]==0)&&(board[i][j+1]==1)) return 1;
			if((board[i+1][j-1]==1)&&(board[i+2][j-2]==1)&&(board[i+3][j-3]==0)&&(board[i-2][j+2]==0)&&(board[i-1][j+1]==1)) return 1;
			if((board[i-1][j-1]==1)&&(board[i-2][j-2]==1)&&(board[i-3][j-3]==0)&&(board[i+2][j+2]==0)&&(board[i+1][j+1]==1)) return 1;
		}
	}
	else {
		if((board[i-1][j]==1)&&(board[i-2][j]==1)&&(board[i-3][j]==0)&&(board[i+2][j]==0)&&(board[i+1][j]==1)) return 1;
		if(j<4){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==0)&&(board[i][j-2]==0)&&(board[i][j-1]==1)) return 1;
			if((board[i-1][j+1]==1)&&(board[i-2][j+2]==1)&&(board[i-3][j+3]==0)&&(board[i+2][j-2]==0)&&(board[i+1][j-1]==1)) return 1;
		}
		else if(j<11){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==0)&&(board[i][j-2]==0)&&(board[i][j-1]==1)) return 1;
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==0)&&(board[i][j+2]==0)&&(board[i][j+1]==1)) return 1;
			if((board[i-1][j+1]==1)&&(board[i-2][j+2]==1)&&(board[i-3][j+3]==0)&&(board[i+2][j-2]==0)&&(board[i+1][j-1]==1)) return 1;
			if((board[i-1][j-1]==1)&&(board[i-2][j-2]==1)&&(board[i-3][j-3]==0)&&(board[i+2][j+2]==0)&&(board[i+1][j+1]==1)) return 1;
		}
		else {
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==0)&&(board[i][j+2]==0)&&(board[i][j+1]==1)) return 1;
			if((board[i-1][j-1]==1)&&(board[i-2][j-2]==1)&&(board[i-3][j-3]==0)&&(board[i+2][j+2]==0)&&(board[i+1][j+1]==1)) return 1;
		}
	}
	return 0;
}

int judge313(int i, int j){
	if(i<5) {
		if((board[i+1][j]==1)&&(board[i+2][j]==1)&&(board[i+3][j]==1)&&(board[i+4][j]==10)) return 1;
		if(j<5){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==1)&&(board[i][j+4]==10)) return 1;
			if((board[i+1][j+1]==1)&&(board[i+2][j+2]==1)&&(board[i+3][j+3]==1)&&(board[i+4][j+4]==10)) return 1;
		}
		else if(j<10){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==1)&&(board[i][j+4]==10)) return 1;
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==1)&&(board[i][j-4]==10)) return 1;
			if((board[i+1][j+1]==1)&&(board[i+2][j+2]==1)&&(board[i+3][j+3]==1)&&(board[i+4][j+4]==10)) return 1;
			if((board[i+1][j-1]==1)&&(board[i+2][j-2]==1)&&(board[i+3][j-3]==1)&&(board[i+4][j-4]==10)) return 1;
		}
		else {
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==1)&&(board[i][j-4]==10)) return 1;
			if((board[i+1][j-1]==1)&&(board[i+2][j-2]==1)&&(board[i+3][j-3]==1)&&(board[i+4][j-4]==10)) return 1;
		}
	}
	else if(i<10) {
		if((board[i+1][j]==1)&&(board[i+2][j]==1)&&(board[i+3][j]==1)&&(board[i+4][j]==10)) return 1;
		if((board[i-1][j]==1)&&(board[i-2][j]==1)&&(board[i-3][j]==1)&&(board[i-4][j]==10)) return 1;
		if(j<5){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==1)&&(board[i][j+4]==10)) return 1;
			if((board[i+1][j+1]==1)&&(board[i+2][j+2]==1)&&(board[i+3][j+3]==1)&&(board[i+4][j+4]==10)) return 1;
			if((board[i-1][j+1]==1)&&(board[i-2][j+2]==1)&&(board[i-3][j+3]==1)&&(board[i-4][j+4]==10)) return 1;
		}
		else if(j<10){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==1)&&(board[i][j+4]==10)) return 1;
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==1)&&(board[i][j-4]==10)) return 1;
			if((board[i+1][j+1]==1)&&(board[i+2][j+2]==1)&&(board[i+3][j+3]==1)&&(board[i+4][j+4]==10)) return 1;
			if((board[i+1][j-1]==1)&&(board[i+2][j-2]==1)&&(board[i+3][j-3]==1)&&(board[i+4][j-4]==10)) return 1;
			if((board[i-1][j+1]==1)&&(board[i-2][j+2]==1)&&(board[i-3][j+3]==1)&&(board[i-4][j+4]==10)) return 1;
			if((board[i-1][j-1]==1)&&(board[i-2][j-2]==1)&&(board[i-3][j-3]==1)&&(board[i-4][j-4]==10)) return 1;
		}
		else {
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==1)&&(board[i][j-4]==10)) return 1;
			if((board[i+1][j-1]==1)&&(board[i+2][j-2]==1)&&(board[i+3][j-3]==1)&&(board[i+4][j-4]==10)) return 1;
			if((board[i-1][j-1]==1)&&(board[i-2][j-2]==1)&&(board[i-3][j-3]==1)&&(board[i-4][j-4]==10)) return 1;
		}
	}
	else {
		if((board[i-1][j]==1)&&(board[i-2][j]==1)&&(board[i-3][j]==1)&&(board[i-4][j]==10)) return 1;
		if(j<5){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==1)&&(board[i][j+4]==10)) return 1;
			if((board[i-1][j+1]==1)&&(board[i-2][j+2]==1)&&(board[i-3][j+3]==1)&&(board[i-4][j+4]==10)) return 1;
		}
		else if(j<10){
			if((board[i][j+1]==1)&&(board[i][j+2]==1)&&(board[i][j+3]==1)&&(board[i][j+4]==10)) return 1;
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==1)&&(board[i][j-4]==10)) return 1;
			if((board[i-1][j+1]==1)&&(board[i-2][j+2]==1)&&(board[i-3][j+3]==1)&&(board[i-4][j+4]==10)) return 1;
			if((board[i-1][j-1]==1)&&(board[i-2][j-2]==1)&&(board[i-3][j-3]==1)&&(board[i-4][j-4]==10)) return 1;
		}
		else {
			if((board[i][j-1]==1)&&(board[i][j-2]==1)&&(board[i][j-3]==1)&&(board[i][j-4]==10)) return 1;
			if((board[i-1][j-1]==1)&&(board[i-2][j-2]==1)&&(board[i-3][j-3]==1)&&(board[i-4][j-4]==10)) return 1;
		}
	}
	return 0;
}

int judge321(int i, int j){
	if(i<4) {
		if((board[i+1][j]==10)&&(board[i+2][j]==10)&&(board[i+3][j]==1)) return 1;
		if(j<4){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==1)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==10)&&(board[i+3][j+3]==1)) return 1;
		}
		else if(j<11){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==1)) return 1;
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==1)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==10)&&(board[i+3][j+3]==1)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==10)&&(board[i+3][j-3]==1)) return 1;
		}
		else {
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==1)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==10)&&(board[i+3][j-3]==1)) return 1;
		}
	}
	else if(i<11) {
		if((board[i+1][j]==10)&&(board[i+2][j]==10)&&(board[i+3][j]==1)) return 1;
		if((board[i-1][j]==10)&&(board[i-2][j]==10)&&(board[i-3][j]==1)) return 1;
		if(j<4){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==1)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==10)&&(board[i+3][j+3]==1)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==10)&&(board[i-3][j+3]==1)) return 1;
		}
		else if(j<11){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==1)) return 1;
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==1)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==10)&&(board[i+3][j+3]==1)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==10)&&(board[i+3][j-3]==1)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==10)&&(board[i-3][j+3]==1)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==10)&&(board[i-3][j-3]==1)) return 1;
		}
		else {
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==1)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==10)&&(board[i+3][j-3]==1)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==10)&&(board[i-3][j-3]==1)) return 1;
		}
	}
	else {
		if((board[i-1][j]==10)&&(board[i-2][j]==10)&&(board[i-3][j]==1)) return 1;
		if(j<4){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==1)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==10)&&(board[i-3][j+3]==1)) return 1;
		}
		else if(j<11){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==1)) return 1;
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==1)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==10)&&(board[i-3][j+3]==1)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==10)&&(board[i-3][j-3]==1)) return 1;
		}
		else {
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==1)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==10)&&(board[i-3][j-3]==1)) return 1;
		}
	}
	return 0;
}

int judge322(int i, int j){
	if(i<3) {
		if((board[i+1][j]==10)&&(board[i+2][j]==1)&&(board[i-1][j]==10)) return 1;
		if(j<3){
			if((board[i][j+1]==10)&&(board[i][j+2]==1)&&(board[i][j-1]==10)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==1)&&(board[i-1][j-1]==10)) return 1;
		}
		else if(j<12){
			if((board[i][j+1]==10)&&(board[i][j+2]==1)&&(board[i][j-1]==10)) return 1;
			if((board[i][j-1]==10)&&(board[i][j-2]==1)&&(board[i][j+1]==10)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==1)&&(board[i-1][j-1]==10)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==1)&&(board[i-1][j+1]==10)) return 1;
		}
		else {
			if((board[i][j-1]==10)&&(board[i][j-2]==1)&&(board[i][j+1]==10)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==1)&&(board[i-1][j+1]==10)) return 1;
		}
	}
	else if(i<12) {
		if((board[i+1][j]==10)&&(board[i+2][j]==1)&&(board[i-1][j]==10)) return 1;
		if((board[i-1][j]==10)&&(board[i-2][j]==1)&&(board[i+1][j]==10)) return 1;
		if(j<3){
			if((board[i][j+1]==10)&&(board[i][j+2]==1)&&(board[i][j-1]==10)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==1)&&(board[i-1][j-1]==10)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==1)&&(board[i+1][j-1]==10)) return 1;
		}
		else if(j<12){
			if((board[i][j+1]==10)&&(board[i][j+2]==1)&&(board[i][j-1]==10)) return 1;
			if((board[i][j-1]==10)&&(board[i][j-2]==1)&&(board[i][j+1]==10)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==1)&&(board[i-1][j-1]==10)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==1)&&(board[i-1][j+1]==10)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==1)&&(board[i+1][j-1]==10)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==1)&&(board[i+1][j+1]==10)) return 1;
		}
		else {
			if((board[i][j-1]==10)&&(board[i][j-2]==1)&&(board[i][j+1]==10)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==1)&&(board[i-1][j+1]==10)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==1)&&(board[i+1][j+1]==10)) return 1;
		}
	}
	else {
		if((board[i-1][j]==10)&&(board[i-2][j]==1)&&(board[i+1][j]==10)) return 1;
		if(j<3){
			if((board[i][j+1]==10)&&(board[i][j+2]==1)&&(board[i][j-1]==10)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==1)&&(board[i+1][j-1]==10)) return 1;
		}
		else if(j<12){
			if((board[i][j+1]==10)&&(board[i][j+2]==1)&&(board[i][j-1]==10)) return 1;
			if((board[i][j-1]==10)&&(board[i][j-2]==1)&&(board[i][j+1]==10)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==1)&&(board[i+1][j-1]==10)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==1)&&(board[i+1][j+1]==10)) return 1;
		}
		else {
			if((board[i][j-1]==10)&&(board[i][j-2]==1)&&(board[i][j+1]==10)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==1)&&(board[i+1][j+1]==10)) return 1;
		}
	}
	return 0;
}

int judge323(int i, int j){
	if(i<4) {
		if((board[i+1][j]==10)&&(board[i+2][j]==10)&&(board[i+3][j]==0)) return 1;
		if(j<4){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==0)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==10)&&(board[i+3][j+3]==0)) return 1;
		}
		else if(j<11){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==0)) return 1;
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==0)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==10)&&(board[i+3][j+3]==0)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==10)&&(board[i+3][j-3]==0)) return 1;
		}
		else {
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==0)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==10)&&(board[i+3][j-3]==0)) return 1;
		}
	}
	else if(i<11) {
		if((board[i+1][j]==10)&&(board[i+2][j]==10)&&(board[i+3][j]==0)) return 1;
		if((board[i-1][j]==10)&&(board[i-2][j]==10)&&(board[i-3][j]==0)) return 1;
		if(j<4){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==0)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==10)&&(board[i+3][j+3]==0)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==10)&&(board[i-3][j+3]==0)) return 1;
		}
		else if(j<11){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==0)) return 1;
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==0)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==10)&&(board[i+3][j+3]==0)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==10)&&(board[i+3][j-3]==0)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==10)&&(board[i-3][j+3]==0)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==10)&&(board[i-3][j-3]==0)) return 1;
		}
		else {
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==0)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==10)&&(board[i+3][j-3]==0)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==10)&&(board[i-3][j-3]==0)) return 1;
		}
	}
	else {
		if((board[i-1][j]==10)&&(board[i-2][j]==10)&&(board[i-3][j]==0)) return 1;
		if(j<4){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==0)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==10)&&(board[i-3][j+3]==0)) return 1;
		}
		else if(j<11){
			if((board[i][j+1]==10)&&(board[i][j+2]==10)&&(board[i][j+3]==0)) return 1;
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==0)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==10)&&(board[i-3][j+3]==0)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==10)&&(board[i-3][j-3]==0)) return 1;
		}
		else {
			if((board[i][j-1]==10)&&(board[i][j-2]==10)&&(board[i][j-3]==0)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==10)&&(board[i-3][j-3]==0)) return 1;
		}
	}
	return 0;
}

int judge324(int i, int j){
	if(i<3) {
		if((board[i+1][j]==10)&&(board[i+2][j]==0)&&(board[i-1][j]==10)) return 1;
		if(j<3){
			if((board[i][j+1]==10)&&(board[i][j+2]==0)&&(board[i][j-1]==10)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==0)&&(board[i-1][j-1]==10)) return 1;
		}
		else if(j<12){
			if((board[i][j+1]==10)&&(board[i][j+2]==0)&&(board[i][j-1]==10)) return 1;
			if((board[i][j-1]==10)&&(board[i][j-2]==0)&&(board[i][j+1]==10)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==0)&&(board[i-1][j-1]==10)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==0)&&(board[i-1][j+1]==10)) return 1;
		}
		else {
			if((board[i][j-1]==10)&&(board[i][j-2]==0)&&(board[i][j+1]==10)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==0)&&(board[i-1][j+1]==10)) return 1;
		}
	}
	else if(i<12) {
		if((board[i+1][j]==10)&&(board[i+2][j]==0)&&(board[i-1][j]==10)) return 1;
		if((board[i-1][j]==10)&&(board[i-2][j]==0)&&(board[i+1][j]==10)) return 1;
		if(j<3){
			if((board[i][j+1]==10)&&(board[i][j+2]==0)&&(board[i][j-1]==10)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==0)&&(board[i-1][j-1]==10)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==0)&&(board[i+1][j-1]==10)) return 1;
		}
		else if(j<12){
			if((board[i][j+1]==10)&&(board[i][j+2]==0)&&(board[i][j-1]==10)) return 1;
			if((board[i][j-1]==10)&&(board[i][j-2]==0)&&(board[i][j+1]==10)) return 1;
			if((board[i+1][j+1]==10)&&(board[i+2][j+2]==0)&&(board[i-1][j-1]==10)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==0)&&(board[i-1][j+1]==10)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==0)&&(board[i+1][j-1]==10)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==0)&&(board[i+1][j+1]==10)) return 1;
		}
		else {
			if((board[i][j-1]==10)&&(board[i][j-2]==0)&&(board[i][j+1]==10)) return 1;
			if((board[i+1][j-1]==10)&&(board[i+2][j-2]==0)&&(board[i-1][j+1]==10)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==0)&&(board[i+1][j+1]==10)) return 1;
		}
	}
	else {
		if((board[i-1][j]==10)&&(board[i-2][j]==0)&&(board[i+1][j]==10)) return 1;
		if(j<3){
			if((board[i][j+1]==10)&&(board[i][j+2]==0)&&(board[i][j-1]==10)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==0)&&(board[i+1][j-1]==10)) return 1;
		}
		else if(j<12){
			if((board[i][j+1]==10)&&(board[i][j+2]==0)&&(board[i][j-1]==10)) return 1;
			if((board[i][j-1]==10)&&(board[i][j-2]==0)&&(board[i][j+1]==10)) return 1;
			if((board[i-1][j+1]==10)&&(board[i-2][j+2]==0)&&(board[i+1][j-1]==10)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==0)&&(board[i+1][j+1]==10)) return 1;
		}
		else {
			if((board[i][j-1]==10)&&(board[i][j-2]==0)&&(board[i][j+1]==10)) return 1;
			if((board[i-1][j-1]==10)&&(board[i-2][j-2]==0)&&(board[i+1][j+1]==10)) return 1;
		}
	}
	return 0;
}

int judge1(int i, int j){
	if(i==0){
		if(j==0) {
			if((board[i][j+1]==0)&&(board[i+1][j]==0)&&(board[i+1][j+1]==0)) return 1;
		}
		else if(j==14){
			if((board[i][j-1]==0)&&(board[i+1][j]==0)&&(board[i+1][j-1]==0)) return 1;
		}
		else {
			if((board[i][j+1]==0)&&(board[i][j-1]==0)&&(board[i+1][j]==0)&&(board[i+1][j-1]==0)&&(board[i+1][j+1]==0))
				return 1;
		}
	}
	else if(i==14){
		if(j==0) {
			if((board[i][j+1]==0)&&(board[i-1][j]==0)&&(board[i-1][j+1]==0)) return 1;
		}
		else if(j==14){
			if((board[i][j-1]==0)&&(board[i-1][j]==0)&&(board[i-1][j-1]==0)) return 1;
		}
		else {
			if((board[i][j+1]==0)&&(board[i][j-1]==0)&&(board[i-1][j]==0)&&(board[i-1][j-1]==0)&&(board[i-1][j+1]==0))
				return 1;
		}
	}
	else {
		if(j==0) {
			if((board[i][j+1]==0)&&(board[i-1][j]==0)&&(board[i+1][j]==0)&&(board[i-1][j+1]==0)&&(board[i+1][j+1]==0))
				return 1;
		}
		else if(j==14){
			if((board[i][j-1]==0)&&(board[i-1][j]==0)&&(board[i+1][j]==0)&&(board[i-1][j-1]==0)&&(board[i+1][j-1]==0))
				return 1;
		}
		else {
			if((board[i][j+1]==0)&&(board[i][j-1]==0)&&(board[i+1][j]==0)&&(board[i-1][j]==0)&&(board[i+1][j+1]==0)&&(board[i+1][j-1]==0)&&(board[i-1][j+1]==0)&&(board[i-1][j-1]==0))
				return 1;
		}
	}
	return 0;
}

Site analyze(){
	int i,j,best=scores[0][0];
	Site bestSite={7,7};
	for(i=0; i<ROW; i++){
		for(j=0; j<COL; j++){
			if(scores[i][j]>best){
				best=scores[i][j];
				bestSite.x=i;
				bestSite.y=j;
			}
		}
	}
	return bestSite;
}

void zeroScores(){
	for(int i=0; i<ROW; i++){
		for(int j=0; j<COL; j++){
			scores[i][j]=0;
		}
	}
}

