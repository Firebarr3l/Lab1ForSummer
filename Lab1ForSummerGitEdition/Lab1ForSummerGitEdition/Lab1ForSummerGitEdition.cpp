// Lab1ForSummerGitEdition.cpp: главный файл проекта.
#include "stdafx.h"    // Подключение стандартного заголовочного файла
#include <stdio.h>     // Подключение библиотеки для работы с вводом-выводом
#include <stdlib.h>    // Подключение стандартной библиотеки для работы с памятью и преобразованиями
#include <conio.h>     // Подключение библиотеки для работы с консольным вводом-выводом
#include <string.h>    // Подключение библиотеки для работы со строками
#include <malloc.h>    // Подключение библиотеки для работы с динамическим распределением памяти
#include <clocale>     // Подключение библиотеки для работы с локалью
#include <windows.h>   // Подключение библиотеки Windows API

using namespace std; 
using namespace System;  
using namespace System::IO;  // Использование пространства имен System::IO  
 
#define ENTER 13  // Определение клавиши Enter
#define ESC 27  // Определение клавиши Escape
#define UP 72  // Определение клавиши стрелки вверх
#define DOWN 80  // Определение клавиши стрелки вниз
#define HOME 71 // Определение клавиши Home
#define END 79 // Определение клавиши End
#define LENGTHMENU 84 // Определение длины меню

// Определение глобальных структурных переменных
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

// Определение структуры steamcopy
struct steamcopy {
	char name[31];  // Название игры
	long cost;  // Стоимость игры
	long prodcopy;  // Количество проданных копий
	long online;  // Онлайн-игроки
	char studioname[18];  // Название студии
	char data[11];};  // Дата выпуска

// Определение структуры sp
struct sp {
	char studioname[18];  // Название студии
	long prodcopy;  // Количество проданных копий
	long online;  // Онлайн-игроки
	char data[11];  // Дата выпуска
	struct sp* pred;  // Указатель на предыдущий элемент
	struct sp* sled;};  // Указатель на следующий элемент


// Определение структуры sp2
struct sp2 {
	char name[32];  // Название игры
	char studioname[18];  // Название студии
	char data[11];  // Дата выпуска
	long cost;  // Стоимость игры
	long prodcopy;  // Количество проданных копий
	long online;  // Онлайн-игроки
	struct sp2* pred;  // Указатель на предыдущий элемент
	struct sp2* sled;};  // Указатель на следующий элемент

// Функция преобразования даты
void text_data(char *s,char *sd)
{
char s0[3],month[12][9]={
"января","февраля","марта","апреля","мая","июня",
"июля","августа","сентября","октября","ноября","декабря"};
strcpy(s,sd+8);
strcat(s," ");
strncpy(s0,sd+5,2); s0[2]=0;
strcat(s,month[ atoi(s0)-1]);
strcat(s," ");
strncat(s,sd,4);
return;
}

// Функция нахождения игры с наименьшим числом проданных копий
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
printf("Наименьшее число %ld проданных копий",best.prodcopy);
Console::CursorLeft=10;
Console::CursorTop=17;
printf("имеет игра: %s",best.name);
getch();
}


// Функция нахождения самой старой игры
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
printf("Самая \"старая\" игра принадлежит студии %s ",best->studioname);
Console::CursorLeft=10;
Console::CursorTop=17;
printf("это %s",best->name);
Console::CursorLeft=10;
Console::CursorTop=19;
printf("Была выпущенна %s ",s);
getch();
}

// Функция подсчета количества игр определенной студии
void kolvoigr(struct steamcopy *steam, int chislostrok)
{
int i,k=0;
char vvodstudio[18];
Console::ForegroundColor=ConsoleColor::Yellow;
Console::BackgroundColor=ConsoleColor::DarkGray;
Console::CursorLeft=10;
Console::CursorTop=15;
printf("Введите название студии, чтобы увидеть количество ее игр");
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
printf("Студия %s выпустила всего: %d игр",vvodstudio, k);
getch();
}

// Функция вставки информации о студиях в связанный список
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

// Функция вставки информации об играх в связанный список
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
// Функция отображения алфавитного списка игр и их информации
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
printf("\n \t\t\t\t\t\tАлфавитный список игр");
printf("\n ======================================================================================================================");
printf("\n Название игры                    Цена       Онлайн     Прод. копии    Название студии           Дата");
printf("\n ======================================================================================================================");
for(nt=spisok2; nt!=0; nt=nt->sled){
	text_data(s,nt->data);
	printf("\n %-31s %5ld %12ld %15ld    %-18s   %-17s",nt->name,nt->cost,nt->online, nt->prodcopy, nt->studioname, s);}
getch();
}




// Функция отображения алфавитного и обратного списка студий и суммарное кол-во проданных копий игр этой студии
void alfalist(struct steamcopy* steam,int chislostrok)
{
int i;
struct sp *nt,*z;
Console::ForegroundColor=ConsoleColor::Yellow;
Console::BackgroundColor=ConsoleColor::DarkMagenta;
Console::Clear();
printf("\n    Алфавитный список студий");
printf(" \t\t\t\t   Обратный алфавитный список студий");
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

//Поиск игр по названию студии минимальному количеству онлайна и цены
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
printf("Введите название студии: ");
SetConsoleCP(1251);
Console::CursorLeft=27;
Console::CursorTop=1;
scanf("%s", vvodstudio);
SetConsoleCP(866);
Console::CursorLeft=0;
Console::CursorTop=3;
printf("Введите минимальный онлайн в игре: ");
SetConsoleCP(1251);
Console::CursorLeft=36;
Console::CursorTop=3;
scanf("%d", &orn);
SetConsoleCP(866);
Console::CursorLeft=0;
Console::CursorTop=5;
printf("Введите минимальную стоимость: ");
SetConsoleCP(1251);
Console::CursorLeft=32;
Console::CursorTop=5;
scanf("%d", &price);
SetConsoleCP(866);
Console::Clear();
printf("\n                        Игры удовлетворяющие запросам  ");
printf("\n                                                                                                ");
printf("\nИгра                             Студия                       Цена/Онлайн"); 
printf("\n======================================================================================================================="); 
for (net = spisok2; net != 0; net = net->sled){
	if (strcmp(net->studioname,vvodstudio)==0){
		if ((((net->online)>=orn) && ((net->cost)>=price))){
			printf("\n%-31s   %-18s          %4ld/%-7ld",net->name, net->studioname, net->cost, net->online);}
	}
}
getch();

} 


//Функция отображающая диаграмму проданных копий по студии
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
printf("          Диаграмма проданных копий игр определенной студии");
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


//Функция отображающая процентное соотношения онлайна в играх
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
printf("Cр. знач. онлайна в играх (%d)   100%%  ",sum);
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

//Сложный вопрос. Ищет соответствие между двумя студиями
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
			printf("Игры %s (%s) и %s (%s) стоит одинаково: %ld руб.\n", steam[i].name, steam[i].studioname, steam[j].name,steam[j].studioname, steam[i].cost);
			Console::CursorTop+=1;}
		
	}
break;}
if (!proverka){
	printf("Игр с одинаковыми ценами нет!");}
getch();
}







//Главная программа
int main(array<System::String ^> ^args)  
{
	//Список вопросов
char dan[][LENGTHMENU] = {  
"У какой игры меньше всего проданных копий?               ", 
"Самая старая игра.                                       ",  
"Количество выпущенных игр определенной студии по запросу.",  
"Алфавитный список студий и обратный алфавитный список.   ",  
"Алфавитный список игр, со всей информацией.              ",  
"Запрос по студии, минимальному онлайну и цене.           ",
"Диаграмма. Процентное соотношение онлайна в играх.       ",
"Диаграмма. Процентноу соотношения проданных копий.       ",
"Поиск одинаковых цен игр.                                ",
"Вернуться на предыдущую страницу                         ",
"Выход                                                    ",};
int i, n;  
FILE *in;  
struct steamcopy *steam;
int chislostrok;
point1:;// Точка для возращения на предыдущую страницу
setlocale(LC_CTYPE, "Russian");// Локализация  
Console::CursorVisible::set(false);//Невидимый курсор  
//Установка размерров окна
Console::BufferHeight = 720; 
Console::BufferWidth = 1280;
//Открытие файла с проверкой его открытия
if ((in = fopen("CopySteam.dat", "r")) == NULL){
		printf("\nФайл CopySteam.dat не открыт!");
		getch(); exit(1);}
//Создание Таблицы данных
Console::BackgroundColor=ConsoleColor::Black; 
Console::ForegroundColor=ConsoleColor::Cyan; 
printf("\nНазвание игры                    Цена   Проданых копий      Онлайн Название студии    Дата выпуска");
Console::BackgroundColor=ConsoleColor::Black; 
Console::ForegroundColor=ConsoleColor::White;
fscanf(in, "%d", &chislostrok);//Считывание количество строк
steam = (struct steamcopy*)malloc(chislostrok * sizeof(struct steamcopy));
//Считывание данных из файла
for (i = 0; i < chislostrok; i++){
	fscanf(in, "%s%ld%ld%ld%s%s", steam[i].name, &steam[i].cost, &steam[i].prodcopy, &steam[i].online, steam[i].studioname, steam[i].data);}
//Печать данных из файла по заданным стандартам
for (i = 0; i < chislostrok; i++){
	printf("\n%-31s %5ld %12ld %15ld %-18s %s", steam[i].name, steam[i].cost, steam[i].prodcopy, steam[i].online, steam[i].studioname, steam[i].data);}
Console::BackgroundColor=ConsoleColor::Black; 
Console::ForegroundColor=ConsoleColor::Cyan;
printf("\n");
printf("\n");
printf("\n");
printf("\nДля перехода на следующую страницу нажмите ENTER                                                                    "); 
getch();
while (1)  {  
	Console::ForegroundColor = ConsoleColor::Yellow;  
	Console::BackgroundColor = ConsoleColor::DarkGray;  
	Console::Clear();
	Console::ForegroundColor = ConsoleColor::Yellow;  
	Console::BackgroundColor = ConsoleColor::DarkMagenta;  
	Console::CursorLeft = 10;  
	Console::CursorTop = 1;  
	printf("                                                           ");  //Печать вопросов
	for (i = 0; i < 12; i++){  
		Console::CursorLeft = 10;  
		Console::CursorTop = i + 2;  
		printf(" %s ", dan[i]);}  
	Console::CursorLeft = 10;  
	Console::CursorTop = 13;
	printf("                                                           ");  
n = menu(11, dan); //Использование функции меню и открытие подпрограм через функцию меню 
switch (n) {  
	case 1: minn(steam, chislostrok); break;//Использование функций(подпрограмм описаных в начале  
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
  
int menu(int n,char dan[][LENGTHMENU])  //Функция меню
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
