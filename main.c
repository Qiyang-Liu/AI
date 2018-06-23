#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#define ROW 15
#define COL 15

int board[ROW][COL]={0};

int welcome();
void makeBoard();
void setTextColor(int color);
void gotoxy(int x,int y);
void play(int mode);

int main() {
	int tag = welcome();								//调用首页游戏模式选择函数 
	
	while(1){											//选择游戏模式 
		switch(tag){
			case 1:{									//人机对战 
				makeBoard();
				play(12);
				break;
			}
			case 2:{									//人人对战 
				makeBoard();
				play(11);
				break;
			}
			case 3:{									//退出游戏 
				exit(0);
			}
			default:;
		}
		tag = welcome();
	}
	return 0;
}



void gotoxy(int x,int y){										//定位光标位置到指定坐标
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos={y,x};
	SetConsoleCursorPosition(hOut,pos);
}

void setTextColor(int color){									//自定义文本颜色设置函数
/*0 = 黑色       8 = 灰色
1 = 蓝色       9 = 淡蓝色
2 = 绿色       a = 淡绿色    10
3 = 浅绿色     b = 淡浅绿色  11
4 = 红色       c = 淡红色    12
5 = 紫色       d = 淡紫色    13
6 = 黄色       e = 淡黄色    14
7 = 白色       f = 亮白色    15*/ 
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if(color < 10){
		SetConsoleTextAttribute(hConsole,color);
	}
	else{
		switch(color){
			case 10:{
				SetConsoleTextAttribute(hConsole, 0xA);
				break;
			}
			case 11:{
				SetConsoleTextAttribute(hConsole, 0xB);
				break;
			}
			case 12:{
				SetConsoleTextAttribute(hConsole, 0xC);
				break;
			}
			case 13:{
				SetConsoleTextAttribute(hConsole, 0xD);
				break;
			}
			case 14:{
				SetConsoleTextAttribute(hConsole, 0xE);
				break;
			}
			case 15:{
				SetConsoleTextAttribute(hConsole, 0xF);
				break;
			}
		}
	}
	
}


