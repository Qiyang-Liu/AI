#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#define ROW 15
#define COL 15

void setTextColor(int color);
void gotoxy(int x,int y);

void makeBoard(){			//显示五子棋的棋盘 
	system("color 0f");
		
	int m=1, n=65;
	putchar(32);
	putchar(32);
	putchar(32);
	for(int i=0; i<ROW; i++){
		putchar(n);
		putchar(32);
		putchar(32);
		n++;
	}
	putchar(10);
	
	setTextColor(10);
	
	for(int i=0; i<2*ROW-1; i++){
		if((i%2)==0){
			setTextColor(15);
			printf("%d",m);
			m++;
			putchar(32);
			if(m <=10) putchar(32);
			setTextColor(10);
			
			for(int j=0; j<2*COL-1; j++){
				if((j%2)==0){
					putchar(42);
				}
				else {
					putchar(45);
					putchar(45);
				}
			}
			putchar(10);
		}
		else {
			putchar(32);
			putchar(32);
			putchar(32);
			for(int j=0; j<2*COL-1; j++){
				if((j%2)==0){
					putchar(124);
				}
				else {
					putchar(32);
					putchar(32);
				}	
			}
			
			putchar(10);	
		}
	}
	
//	setTextColor(15);
//	gotoxy(4,3*COL+4);
//	printf("下棋方法:");
//	gotoxy(5,3*COL+4);
//	printf("将黄色*移至合适位置后回车来下棋");
//	gotoxy(7,3*COL+4);
//	printf("回车后请将黄色*移开,这样才能看到你下的棋子");
//	gotoxy(9,3*COL+4);
//	printf("白色:玩家 红色:电脑");
//	gotoxy(10,3*COL+4);
//	printf("紫色:电脑最近一步走的棋");
}
