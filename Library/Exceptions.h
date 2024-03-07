#pragma once
#include <iostream>

enum class Errors
{
	incorrectType = 100, //��� ������
	outOfRange = 101, //����������������� �����
	fileIsNotOpen = 102, //�������� �����
	incorrectInput = 103, //���� �� �����
};

class Exception
{
protected:
	int code;
	char msg[80];
public:
	Exception() : code{ 0 }, msg{ "����������� ������" }{};
	Exception(int code, const char* message);
	void show();
	Errors codes;
};
