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

