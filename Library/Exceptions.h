#pragma once
#include <iostream>

enum class Errors
{
	incorrectType = 100, //тип данных
	outOfRange = 101, //индетифакационный номер
	fileIsNotOpen = 102, //открытие файла
	incorrectInput = 103, //ввод из файла
};

class Exception
{
protected:
	int code;
	char msg[80];
public:
	Exception() : code{ 0 }, msg{ "Неизвестная ошибка" }{};
	Exception(int code, const char* message);
	void show();
	Errors codes;
};
