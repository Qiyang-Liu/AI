#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

void print();
void gotoxy(int x,int y);

int welcome() {		//�˺�������չʾ��Ϸģʽѡ�����, ������ѡ�����Ϸģʽ��ͬ, �����ز�ͬ��ֵ�������� 
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
	printf("������С��Ϸ");
	gotoxy(12,30);
	printf("=> �˻���ս");
	gotoxy(13,30);
	printf("   ���˶�ս");
	gotoxy(14,30);
	printf("   �˳���Ϸ");
}
