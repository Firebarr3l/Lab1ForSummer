// Lab1ForSummerGitEdition.cpp: ������� ���� �������.
#include "stdafx.h"    // ����������� ������������ ������������� �����
#include <stdio.h>     // ����������� ���������� ��� ������ � ������-�������
#include <stdlib.h>    // ����������� ����������� ���������� ��� ������ � ������� � ����������������
#include <conio.h>     // ����������� ���������� ��� ������ � ���������� ������-�������
#include <string.h>    // ����������� ���������� ��� ������ �� ��������
#include <malloc.h>    // ����������� ���������� ��� ������ � ������������ �������������� ������
#include <clocale>     // ����������� ���������� ��� ������ � �������
#include <windows.h>   // ����������� ���������� Windows API

using namespace std; 
using namespace System;  
using namespace System::IO;  // ������������� ������������ ���� System::IO  
 
#define ENTER 13  // ����������� ������� Enter
#define ESC 27  // ����������� ������� Escape
#define UP 72  // ����������� ������� ������� �����
#define DOWN 80  // ����������� ������� ������� ����
#define HOME 71 // ����������� ������� Home
#define END 79 // ����������� ������� End
#define LENGTHMENU 84 // ����������� ����� ����

// ����������� ���������� ����������� ����������
struct steamcopy  *steamcopy = NULL;
struct sp *spisok = NULL;
struct sp2 *spisok2 = NULL;

int menu(int, char [][LENGTHMENU]);
void vstavka(struct steamcopy*,char *, int);
void vstavkagames(struct steamcopy*, char *, int);
void alfalistgames(struct steamcopy*, int);
void alfalist(struct steamcopy*, int);
void text_data(char *,char *);
void minn(struct steamcopy*, int);
void oldest(struct steamcopy*, int);
void kolvoigr(struct steamcopy*, int);
void listing(struct sp2*, int);
void diagramstudio(struct steamcopy*, int);
void diagramgames(struct steamcopy*, int);
void CompereCostofgames(struct steamcopy*, int);

// ����������� ��������� steamcopy
struct steamcopy {
	char name[31];  // �������� ����
	long cost;  // ��������� ����
	long prodcopy;  // ���������� ��������� �����
	long online;  // ������-������
	char studioname[18];  // �������� ������
	char data[11];};  // ���� �������

// ����������� ��������� sp
struct sp {
	char studioname[18];  // �������� ������
	long prodcopy;  // ���������� ��������� �����
	long online;  // ������-������
	char data[11];  // ���� �������
	struct sp* pred;  // ��������� �� ���������� �������
	struct sp* sled;};  // ��������� �� ��������� �������


// ����������� ��������� sp2
struct sp2 {
	char name[32];  // �������� ����
	char studioname[18];  // �������� ������
	char data[11];  // ���� �������
	long cost;  // ��������� ����
	long prodcopy;  // ���������� ��������� �����
	long online;  // ������-������
	struct sp2* pred;  // ��������� �� ���������� �������
	struct sp2* sled;};  // ��������� �� ��������� �������

// ������� �������������� ����
void text_data(char *s,char *sd)
{
char s0[3],month[12][9]={
"������","�������","�����","������","���","����",
"����","�������","��������","�������","������","�������"};
strcpy(s,sd+8);
strcat(s," ");
strncpy(s0,sd+5,2); s0[2]=0;
strcat(s,month[ atoi(s0)-1]);
strcat(s," ");
strncat(s,sd,4);
return;
}

// ������� ���������� ���� � ���������� ������ ��������� �����
void minn(struct steamcopy* steam,int chislostrok)
{
int i=0;
struct steamcopy best;
strcpy(best.name,steam[0].name);
best.prodcopy=steam[0].prodcopy;
for(i=1;i<chislostrok;i++){
	if (steam[i].prodcopy<best.prodcopy){
		strcpy(best.name,steam[i].name);
		best.prodcopy=steam[i].prodcopy;}
}
Console::ForegroundColor=ConsoleColor::Yellow;
Console::BackgroundColor=ConsoleColor::DarkGray;
Console::CursorLeft=10;
Console::CursorTop=15;
printf("���������� ����� %ld ��������� �����",best.prodcopy);
Console::CursorLeft=10;
Console::CursorTop=17;
printf("����� ����: %s",best.name);
getch();
}


// ������� ���������� ����� ������ ����
void oldest(struct steamcopy* steam, int chislostrok)
{
int i;
char s[17];
struct steamcopy* best=steam;
for(i=1;i<chislostrok;i++){
	if (strcmp(steam[i].data,best->data)<0){
		best=&steam[i];}
}
text_data(s,best->data);
Console::ForegroundColor=ConsoleColor::Yellow;
Console::BackgroundColor=ConsoleColor::DarkGray;
Console::CursorLeft=10;
Console::CursorTop=15;
printf("����� \"������\" ���� ����������� ������ %s ",best->studioname);
Console::CursorLeft=10;
Console::CursorTop=17;
printf("��� %s",best->name);
Console::CursorLeft=10;
Console::CursorTop=19;
printf("���� ��������� %s ",s);
getch();
}

// ������� �������� ���������� ��� ������������ ������
void kolvoigr(struct steamcopy *steam, int chislostrok)
{
int i,k=0;
char vvodstudio[18];
Console::ForegroundColor=ConsoleColor::Yellow;
Console::BackgroundColor=ConsoleColor::DarkGray;
Console::CursorLeft=10;
Console::CursorTop=15;
printf("������� �������� ������, ����� ������� ���������� �� ���");
SetConsoleCP(1251);
Console::CursorLeft=10;
Console::CursorTop=17;
scanf("%s", vvodstudio);
SetConsoleCP(866);
for(i=0;i<chislostrok;i++){
	if (strcmp(steam[i].studioname,vvodstudio)==0){
		k++;}
}
Console::ForegroundColor=ConsoleColor::Yellow;
Console::BackgroundColor=ConsoleColor::DarkGray;
Console::CursorLeft=10;
Console::CursorTop=19;
printf("������ %s ��������� �����: %d ���",vvodstudio, k);
getch();
}

// ������� ������� ���������� � ������� � ��������� ������
void vstavka(struct steamcopy* steamstudio,char* studioname, int chislostrok) 
{ 
int i; 
struct sp *nov,*nt,*z=0; 
for(nt=spisok; nt!=0 && strcmp(nt->studioname,studioname)<0; z=nt, nt=nt->sled); 
if(nt && strcmp(nt->studioname,studioname)==0) return; 
nov=(struct sp *) malloc(sizeof(struct sp)); 
strcpy(nov->studioname,studioname); 
nov->sled=nt; 
nov->prodcopy=0;
nov->online=0;
nov->pred = z;
for(i=0;i<chislostrok;i++){
	if(strcmp(steamstudio[i].studioname,studioname)==0){ 
		nov->prodcopy+=steamstudio[i].prodcopy;
		nov->online+=steamstudio[i].online;}
}
if(!z) spisok=nov; 
if(z) z->sled=nov; 
if(nt) nt->pred=nov; 
return; 
}

// ������� ������� ���������� �� ����� � ��������� ������
void vstavkagames(struct steamcopy* steamgames,char* name, int chislostrok) 
{ 
int i; 
struct sp2 *nov,*nt,*z=0; 
for(nt=spisok2; nt!=0 && strcmp(nt->name,name)<0; z=nt, nt=nt->sled); 
if(nt && strcmp(nt->name,name)==0) return; 
nov=(struct sp2 *) malloc(sizeof(struct sp2)); 
strcpy(nov->name,name); 
nov->sled=nt; 
nov->prodcopy=0;
nov->online=0;
nov->cost=0;
strcpy(nov->studioname,"");
strcpy(nov->data,"");
nov->pred = z;
for(i=0;i<chislostrok;i++){ 
	if(strcmp(steamgames[i].name,name)==0){ 
		nov->prodcopy+=steamgames[i].prodcopy;
		nov->online+=steamgames[i].online;
		nov->cost+=steamgames[i].cost;
		strcat(nov->studioname, steamgames[i].studioname);
		strcat(nov->data, steamgames[i].data);}
}
if(!z) spisok2=nov; 
if(z) z->sled=nov; 
if(nt) nt->pred=nov; 
return; 
}
// ������� ����������� ����������� ������ ��� � �� ����������
void alfalistgames(struct steamcopy* steam, int chislostrok)
{
int i;
char s[17];
struct sp2 *nt;
Console::ForegroundColor=ConsoleColor::Yellow;
Console::BackgroundColor=ConsoleColor::DarkMagenta;
Console::Clear();
if(!spisok2){
	for(i=0;i<chislostrok;i++){
		vstavkagames(steam,steam[i].name, chislostrok);}
}
Console::Clear();
printf("\n \t\t\t\t\t\t���������� ������ ���");
printf("\n ======================================================================================================================");
printf("\n �������� ����                    ����       ������     ����. �����    �������� ������           ����");
printf("\n ======================================================================================================================");
for(nt=spisok2; nt!=0; nt=nt->sled){
	text_data(s,nt->data);
	printf("\n %-31s %5ld %12ld %15ld    %-18s   %-17s",nt->name,nt->cost,nt->online, nt->prodcopy, nt->studioname, s);}
getch();
}




// ������� ����������� ����������� � ��������� ������ ������ � ��������� ���-�� ��������� ����� ��� ���� ������
void alfalist(struct steamcopy* steam,int chislostrok)
{
int i;
struct sp *nt,*z;
Console::ForegroundColor=ConsoleColor::Yellow;
Console::BackgroundColor=ConsoleColor::DarkMagenta;
Console::Clear();
printf("\n    ���������� ������ ������");
printf(" \t\t\t\t   �������� ���������� ������ ������");
printf("\n========================================================================================================================");
if(!spisok){
	for(i=0;i<chislostrok;i++){
		vstavka(steam,steam[i].studioname, chislostrok);}
}
for(nt=spisok; nt!=0; nt=nt->sled){
	printf("\n %-20s %10ld",nt->studioname,nt->prodcopy);}
for(nt=spisok,z=0; nt!=0; z=nt,nt=nt->sled);{
	Console::CursorTop=3;
	for(nt=z; nt!=0; nt=nt->pred){
		Console::CursorLeft=60;
		printf("%-20s %10ld",nt->studioname,nt->prodcopy);
		Console::CursorTop+=1;}
}
getch();
}


