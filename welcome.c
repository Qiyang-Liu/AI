#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

void print();
void gotoxy(int x,int y);

int welcome() {		//此函数用于展示游戏模式选择界面, 并根据选择的游戏模式不同, 而返回不同的值到主函数 
	print();
	char ch1,ch2;
	int x=12, tag=1;
	while(1){
		ch1=getch();
		if(ch1==224 || ch1==-32 || ch1==0){
			ch2=getch();
		}
		else{
			ch2=0;
		}
		switch(ch2){
			case 80:{
				if(tag != 3){
					gotoxy(x,30);
					printf("  ");
					x++;
					gotoxy(x,30);
					printf("=>");
					tag++;
				}
				break;
			}
			case 72:{
				if(tag != 1){
					gotoxy(x,30);
					printf("  ");
					x--;
					gotoxy(x,30);
					printf("=>");
					tag--;
				}
				break;
			}
			default:;
		}
		if(ch1==13){
			break;
		}
		if(ch1==27){
			exit(0);
		}
	}
	system("cls");
	return tag;	
}

void print(){
	gotoxy(10,30);
	printf("五子棋小游戏");
	gotoxy(12,30);
	printf("=> 人机对战");
	gotoxy(13,30);
	printf("   人人对战");
	gotoxy(14,30);
	printf("   退出游戏");
}
