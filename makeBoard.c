#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#define ROW 15
#define COL 15

void setTextColor(int color);
void gotoxy(int x,int y);

void makeBoard(){			//��ʾ����������� 
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
//	printf("���巽��:");
//	gotoxy(5,3*COL+4);
//	printf("����ɫ*��������λ�ú�س�������");
//	gotoxy(7,3*COL+4);
//	printf("�س����뽫��ɫ*�ƿ�,�������ܿ������µ�����");
//	gotoxy(9,3*COL+4);
//	printf("��ɫ:��� ��ɫ:����");
//	gotoxy(10,3*COL+4);
//	printf("��ɫ:�������һ���ߵ���");
}
