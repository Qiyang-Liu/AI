#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#define ROW 15
#define COL 15

extern int board[ROW][COL];
int tag=0;
static int siteRow=7, siteCol=7;

void setTextColor(int color);
void gotoxy(int x,int y);
void output(int tag);
void modifyBoard(int siteRow,int siteCol,int tag);
int isBlank(int siteRow,int siteCol,int tag);
int isVictory();
void outPoint(int siteRow,int siteCol,int n);
void movePoint();
void computer(int n);
void dataReset();

void play(int mode){
	int victory=isVictory();
	outPoint(siteRow, siteCol, 2);			//输出下棋位置的标记点 
	while(victory==0){
		
		movePoint();						//调用移动标记点的函数, 移动下棋标记点 
		
		if(isBlank(siteRow,siteCol,tag)==1){
			gotoxy(2*siteRow+1,(siteCol+1)*3);
			output(tag);
			modifyBoard(siteRow,siteCol,tag);
			tag++;
			victory=isVictory();
			if(victory != 0) break;
			
			if(mode==12){
				computer(1);
			}
			victory=isVictory();
		}
	}
	gotoxy(2*COL+1,0);
	setTextColor(15);
	if(victory==1){
		printf("白棋胜! ");
	}
	else {
		printf("红棋胜! ");
	}
	dataReset();
	system("pause");
	system("cls");
}

void output(int tag){
	if((tag%2)==0) {
		setTextColor(15);
	}
	else {
		setTextColor(12);
	}
	putchar(64);
	setTextColor(15);
}

int isBlank(int siteRow,int siteCol,int tag){
	if(board[siteRow][siteCol]==0) return 1;
	else return 0;
}

void modifyBoard(int siteRow,int siteCol,int tag){
	if((tag%2)==0){
		board[siteRow][siteCol]=1;
	}
	else {
		board[siteRow][siteCol]=10;
	}
}

int isVictory(){
	int n1, n2, n3, n4;
	int judgeRow();//检测列 
	int judgeCol();//检测行 
	int judgeLeft();//检测左斜 
	int judgeRight();//检测右斜 
	n1=judgeRow();
	n2=judgeCol();
	n3=judgeLeft();
	n4=judgeRight();
	if(((n1+n2+n3+n4)>=1)&&((n1+n2+n3+n4)<10)) return 1;
	else if((n1+n2+n3+n4)>=10) return 10;
	else return 0;
}

int judgeRow(){
	for(int i=0; i<(ROW-5); i++){
		for(int j=0; j<COL; j++){
			if((board[i][j]+board[i+1][j]+board[i+2][j]+board[i+3][j]+board[i+4][j])==5){
				return 1;
			}
			else if((board[i][j]+board[i+1][j]+board[i+2][j]+board[i+3][j]+board[i+4][j])==50){
				return 10;
			}
		}
	}
	return 0;
}

int judgeCol(){
	for(int i=0; i<ROW; i++){
		for(int j=0; j<(COL-5); j++){
			if((board[i][j]+board[i][j+1]+board[i][j+2]+board[i][j+3]+board[i][j+4])==5){
				return 1;
			}
			else if((board[i][j]+board[i][j+1]+board[i][j+2]+board[i][j+3]+board[i][j+4])==50){
				return 10;
			}
		}
	}
	return 0;
}

int judgeLeft(){
	for(int i=0; i<(ROW-5); i++){
		for(int j=0; j<(COL-5); j++){
			if((board[i][j]+board[i+1][j+1]+board[i+2][j+2]+board[i+3][j+3]+board[i+4][j+4])==5){
				return 1;
			}
			else if((board[i][j]+board[i+1][j+1]+board[i+2][j+2]+board[i+3][j+3]+board[i+4][j+4])==50){
				return 10;
			}
		}
	}
	return 0;
}

int judgeRight(){
	for(int i=0; i<(ROW-5); i++){
		for(int j=4; j<COL; j++){
			if((board[i][j]+board[i+1][j-1]+board[i+2][j-2]+board[i+3][j-3]+board[i+4][j-4])==5){
				return 1;
			}
			else if((board[i][j]+board[i+1][j-1]+board[i+2][j-2]+board[i+3][j-3]+board[i+4][j-4])==50){
				return 10;
			}
		}
	}
	return 0;
}

void movePoint(){
	int canMove(char ch2);
	
	outPoint(siteRow, siteCol,2);
	char ch1, ch2;
	while(1){
		while(1){
			ch1=getch();
			if(ch1==13){
				break;
			}
			else if(ch1== -32){
				ch2=getch();
				break;
			}
			else if(ch1==27){
				exit(0);
			}
		}
		
		if(ch1==13){
			outPoint(siteRow, siteCol,1);
			return;
		}
		else if(ch1== -32){
			if(canMove(ch2)==0){
				continue;
			}
			if(board[siteRow][siteCol]==1){
				outPoint(siteRow, siteCol,3);
			}
			else if(board[siteRow][siteCol]==10){
				outPoint(siteRow, siteCol,4);
			}
			else{
				outPoint(siteRow, siteCol,1);
			}
			
			switch(ch2){
				case 72:{
					siteRow--;
					break;
				}
				case 80:{
					siteRow++;
					break;
				}
				case 75:{
					siteCol--;
					break;
				}
				case 77:{
					siteCol++;
					break;
				}
				default:;
			}
			outPoint(siteRow, siteCol,2);
		}
	}
	
}

void outPoint(int siteRow,int siteCol,int n){
	gotoxy(2*siteRow+1,(siteCol+1)*3);
	putchar(32);
	gotoxy(2*siteRow+1,(siteCol+1)*3);
	setTextColor(10);
	
	if(n==1){
		putchar(42);
	}
	
	if(n==2){
		setTextColor(14);
		putchar(42);
	}
	if(n==3){
		output(0);
	}
	if(n==4){
		output(1);
	} 
}

int canMove(char ch2){
	switch(ch2){
		case 72:{
			if(siteRow==0) return 0;
			break;
		}
		case 80:{
			if(siteRow==14) return 0;
			break;
		}
		case 75:{
			if(siteCol==0) return 0;
			break;
		}
		case 77:{
			if(siteCol==14) return 0;
			break;
		}
		default:;
	}
	return 1;
}

void dataReset(){
	for(int i=0; i<ROW; i++){
		for(int j=0; j<COL; j++){
			board[i][j]=0;
		}
	}
	tag=0;
	siteRow=7, siteCol=7;
	computer(0);
}


