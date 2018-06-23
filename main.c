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
	int tag = welcome();								//������ҳ��Ϸģʽѡ���� 
	
	while(1){											//ѡ����Ϸģʽ 
		switch(tag){
			case 1:{									//�˻���ս 
				makeBoard();
				play(12);
				break;
			}
			case 2:{									//���˶�ս 
				makeBoard();
				play(11);
				break;
			}
			case 3:{									//�˳���Ϸ 
				exit(0);
			}
			default:;
		}
		tag = welcome();
	}
	return 0;
}



void gotoxy(int x,int y){										//��λ���λ�õ�ָ������
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos={y,x};
	SetConsoleCursorPosition(hOut,pos);
}

void setTextColor(int color){									//�Զ����ı���ɫ���ú���
/*0 = ��ɫ       8 = ��ɫ
1 = ��ɫ       9 = ����ɫ
2 = ��ɫ       a = ����ɫ    10
3 = ǳ��ɫ     b = ��ǳ��ɫ  11
4 = ��ɫ       c = ����ɫ    12
5 = ��ɫ       d = ����ɫ    13
6 = ��ɫ       e = ����ɫ    14
7 = ��ɫ       f = ����ɫ    15*/ 
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


