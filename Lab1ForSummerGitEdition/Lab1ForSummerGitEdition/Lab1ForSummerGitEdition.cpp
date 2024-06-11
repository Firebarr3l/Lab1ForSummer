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

