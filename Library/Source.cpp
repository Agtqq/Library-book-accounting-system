#define _CRT_SECURE_NO_WARNINGS
#include "menu.h"
#include<string.h>
#include<iomanip>
#include<iostream>
#include "book.h"
#include "student.h"
#include <locale.h> 
#include <Windows.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	menu Menu;
	Menu.Start();

	system("pause");
	
	return 0;
}