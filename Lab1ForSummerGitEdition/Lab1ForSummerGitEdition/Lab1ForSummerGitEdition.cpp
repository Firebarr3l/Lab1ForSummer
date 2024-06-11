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

//����� ��� �� �������� ������ ������������ ���������� ������� � ����
void listing(struct steamcopy* steam,int chislostrok) 
{ 
int orn, price, i; 
char vvodstudio[18];
struct sp2 *net;
if(!spisok2){
	for(i=0;i<chislostrok;i++){
		vstavkagames(steam,steam[i].name, chislostrok);}
}
Console::Clear();
Console::ForegroundColor=ConsoleColor::Yellow; 
Console::BackgroundColor=ConsoleColor::DarkMagenta; 
Console::Clear();
Console::CursorLeft=0;
Console::CursorTop=1;
printf("������� �������� ������: ");
SetConsoleCP(1251);
Console::CursorLeft=27;
Console::CursorTop=1;
scanf("%s", vvodstudio);
SetConsoleCP(866);
Console::CursorLeft=0;
Console::CursorTop=3;
printf("������� ����������� ������ � ����: ");
SetConsoleCP(1251);
Console::CursorLeft=36;
Console::CursorTop=3;
scanf("%d", &orn);
SetConsoleCP(866);
Console::CursorLeft=0;
Console::CursorTop=5;
printf("������� ����������� ���������: ");
SetConsoleCP(1251);
Console::CursorLeft=32;
Console::CursorTop=5;
scanf("%d", &price);
SetConsoleCP(866);
Console::Clear();
printf("\n                        ���� ��������������� ��������  ");
printf("\n                                                                                                ");
printf("\n����                             ������                       ����/������"); 
printf("\n======================================================================================================================="); 
for (net = spisok2; net != 0; net = net->sled){
	if (strcmp(net->studioname,vvodstudio)==0){
		if ((((net->online)>=orn) && ((net->cost)>=price))){
			printf("\n%-31s   %-18s          %4ld/%-7ld",net->name, net->studioname, net->cost, net->online);}
	}
}
getch();

} 


//������� ������������ ��������� ��������� ����� �� ������
void diagramstudio(struct steamcopy *steam, int chislostrok)
{
struct sp* nt;
int len,i,NColor;
long copy = 0;
char str1[200];
char str2[200];
System::ConsoleColor Color;
Console::BufferHeight=720;
Console::BufferWidth=1280;
Console::ForegroundColor=ConsoleColor::Yellow;
Console::BackgroundColor=ConsoleColor::DarkMagenta;
Console::Clear();
for(i=0;i<chislostrok;i++)copy = copy+steam[i].prodcopy;
if(!spisok){
	for(i=0;i<chislostrok;i++){
		vstavka(steam, steam[i].studioname, chislostrok);}
}
printf("          ��������� ��������� ����� ��� ������������ ������");
printf("\n============================================================================");
Color=ConsoleColor::DarkYellow; NColor=7;
for(nt=spisok,i=1; nt!=0; nt=nt->sled,i++){
sprintf(str1,"%s",nt->studioname);
sprintf(str2,"%3.1f%%",(nt->prodcopy*100./copy));
Console::ForegroundColor=ConsoleColor::Yellow;
Console::BackgroundColor= ConsoleColor::DarkMagenta;
Console::CursorLeft=0; Console::CursorTop=i+1;
printf(str1);
Console::CursorLeft=17;
printf("%s",str2);
Console::BackgroundColor=++Color;NColor++;
Console::CursorLeft=23;
for(len=0; len<(nt->prodcopy*100)/copy; len++) 
	printf(" ");
	if(NColor==13){
		Color=ConsoleColor::DarkYellow; NColor=7;}

}
getch();
return ;
}


//������� ������������ ���������� ����������� ������� � �����
void diagramgames(struct steamcopy *steam,int chislostrok) 
{ 
struct sp2* nt; 
int len,i,NColor; 
long sum1 = 0 ; 
long sum; 
char str1[200]; 
char str2[200]; 
System::ConsoleColor Color; 
Console::ForegroundColor=ConsoleColor::Yellow; 
Console::BackgroundColor=ConsoleColor::DarkMagenta; 
Console::Clear(); 
for(i=0;i<chislostrok;i++) sum1 = sum1+steam[i].online; 
sum=sum1/chislostrok; 
if(!spisok2){ 
	for(i=0;i<chislostrok;i++){ 
		vstavkagames(steam,steam[i].name, chislostrok);}
}
Color=ConsoleColor::DarkYellow; NColor=7; 
Console::BackgroundColor=ConsoleColor::DarkMagenta; 
Console::ForegroundColor=ConsoleColor::Cyan; 
printf("C�. ����. ������� � ����� (%d)   100%%  ",sum);
Console::BackgroundColor=ConsoleColor::Cyan; 
Console::CursorLeft=55; 
for(len=0; len<25; len++)printf(" ");
Console::BackgroundColor=ConsoleColor::DarkMagenta; 
Console::ForegroundColor=ConsoleColor::Yellow;
printf("\n========================================================================================================================================================================="); 
for(nt=spisok2,i=1; nt!=0; nt=nt->sled,i++) { 
sprintf(str1,"%s",nt->name); 
sprintf(str2,"%3.1f%%",(nt->online*100./sum)); 
Console::ForegroundColor=ConsoleColor::Yellow; 
Console::BackgroundColor= ConsoleColor::DarkMagenta; 
Console::CursorLeft=0; Console::CursorTop=i+1; 
printf(str1); 
Console::CursorLeft=35; 
printf("%-s",str2);
Console::BackgroundColor=++Color;NColor++;
Console::CursorLeft=44;
for(len=0; len<(nt->online)*10/sum; len++) printf(" "); 
	if(NColor==12){ 
		Color=ConsoleColor::DarkYellow; NColor=7;} 
} 
getch(); 
return ; 
}

//������� ������. ���� ������������ ����� ����� ��������
void CompereCostofgames(struct steamcopy* steam, int chislostrok)
{
int i, j, proverka=0;
Console::ForegroundColor=ConsoleColor::Yellow; 
Console::BackgroundColor=ConsoleColor::DarkGray; 
Console::CursorTop=15;
Console::CursorLeft=10;
for (i = 0; i < chislostrok - 1; i++) {
	for (j = i + 1; j < chislostrok; j++) {
		if (steam[i].cost == steam[j].cost) {
			proverka=1;
			Console::CursorLeft=10;
			printf("���� %s (%s) � %s (%s) ����� ���������: %ld ���.\n", steam[i].name, steam[i].studioname, steam[j].name,steam[j].studioname, steam[i].cost);
			Console::CursorTop+=1;}
		
	}
break;}
if (!proverka){
	printf("��� � ����������� ������ ���!");}
getch();
}







//������� ���������
int main(array<System::String ^> ^args)  
{
	//������ ��������
char dan[][LENGTHMENU] = {  
"� ����� ���� ������ ����� ��������� �����?               ", 
"����� ������ ����.                                       ",  
"���������� ���������� ��� ������������ ������ �� �������.",  
"���������� ������ ������ � �������� ���������� ������.   ",  
"���������� ������ ���, �� ���� �����������.              ",  
"������ �� ������, ������������ ������� � ����.           ",
"���������. ���������� ����������� ������� � �����.       ",
"���������. ���������� ����������� ��������� �����.       ",
"����� ���������� ��� ���.                                ",
"��������� �� ���������� ��������                         ",
"�����                                                    ",};
int i, n;  
FILE *in;  
struct steamcopy *steam;
int chislostrok;
point1:;// ����� ��� ���������� �� ���������� ��������
setlocale(LC_CTYPE, "Russian");// �����������  
Console::CursorVisible::set(false);//��������� ������  
//��������� ��������� ����
Console::BufferHeight = 720; 
Console::BufferWidth = 1280;
//�������� ����� � ��������� ��� ��������
if ((in = fopen("CopySteam.dat", "r")) == NULL){
		printf("\n���� CopySteam.dat �� ������!");
		getch(); exit(1);}
//�������� ������� ������
Console::BackgroundColor=ConsoleColor::Black; 
Console::ForegroundColor=ConsoleColor::Cyan; 
printf("\n�������� ����                    ����   �������� �����      ������ �������� ������    ���� �������");
Console::BackgroundColor=ConsoleColor::Black; 
Console::ForegroundColor=ConsoleColor::White;
fscanf(in, "%d", &chislostrok);//���������� ���������� �����
steam = (struct steamcopy*)malloc(chislostrok * sizeof(struct steamcopy));
//���������� ������ �� �����
for (i = 0; i < chislostrok; i++){
	fscanf(in, "%s%ld%ld%ld%s%s", steam[i].name, &steam[i].cost, &steam[i].prodcopy, &steam[i].online, steam[i].studioname, steam[i].data);}
//������ ������ �� ����� �� �������� ����������
for (i = 0; i < chislostrok; i++){
	printf("\n%-31s %5ld %12ld %15ld %-18s %s", steam[i].name, steam[i].cost, steam[i].prodcopy, steam[i].online, steam[i].studioname, steam[i].data);}
Console::BackgroundColor=ConsoleColor::Black; 
Console::ForegroundColor=ConsoleColor::Cyan;
printf("\n");
printf("\n");
printf("\n");
printf("\n��� �������� �� ��������� �������� ������� ENTER                                                                    "); 
getch();
while (1)  {  
	Console::ForegroundColor = ConsoleColor::Yellow;  
	Console::BackgroundColor = ConsoleColor::DarkGray;  
	Console::Clear();
	Console::ForegroundColor = ConsoleColor::Yellow;  
	Console::BackgroundColor = ConsoleColor::DarkMagenta;  
	Console::CursorLeft = 10;  
	Console::CursorTop = 1;  
	printf("                                                           ");  //������ ��������
	for (i = 0; i < 12; i++){  
		Console::CursorLeft = 10;  
		Console::CursorTop = i + 2;  
		printf(" %s ", dan[i]);}  
	Console::CursorLeft = 10;  
	Console::CursorTop = 13;
	printf("                                                           ");  
n = menu(11, dan); //������������� ������� ���� � �������� ���������� ����� ������� ���� 
switch (n) {  
	case 1: minn(steam, chislostrok); break;//������������� �������(����������� �������� � ������  
	case 2: oldest(steam, chislostrok);break;  
	case 3: kolvoigr(steam,chislostrok);break;  
	case 4: alfalist(steam, chislostrok);break;  
	case 5: alfalistgames(steam, chislostrok);break;  
	case 6: listing(steam, chislostrok);break;
	case 7: diagramgames(steam, chislostrok);break;
	case 8: diagramstudio(steam, chislostrok);break;
	case 9: CompereCostofgames(steam, chislostrok); break;
	case 10:{Console::CursorLeft=0; 
Console::BackgroundColor=ConsoleColor::Black; 
Console::ForegroundColor=ConsoleColor::White; 
Console::CursorTop=0; 
Console::Clear(); 
goto point1;} 
	case 11: exit(0);  
		}  
}  
  
return 0;  
}  
  
int menu(int n,char dan[][LENGTHMENU])  //������� ����
{  

int y1 = 0, y2 = n - 1;  
char c = 1;  
while (c != ESC){  
	switch (c) {
		case DOWN: y2 = y1; y1++; break;  
		case UP: y2 = y1; y1--; break;
		case ENTER: return y1 + 1;
		case HOME: y2=y1; y1=0; break;
		case END: y2=y1; y1=n-1; break;}
 
	if (y1 > n - 1) { y2 = n - 1; y1 = 0; }  
	if (y1 < 0) { y2 = 0; y1 = n - 1; }
	Console::ForegroundColor = ConsoleColor::Yellow;  
	Console::BackgroundColor = ConsoleColor::DarkMagenta;  
	Console::CursorLeft = 11;  
	Console::CursorTop = y2 + 2;  
	printf("%s", dan[y2]);
	Console::ForegroundColor = ConsoleColor::Black;  
	Console::BackgroundColor = ConsoleColor::DarkGreen;  
	Console::CursorLeft = 11;  
	Console::CursorTop = y1 + 2;  
	printf("%s", dan[y1]);      
	c = getch();}   
exit(0);
}
