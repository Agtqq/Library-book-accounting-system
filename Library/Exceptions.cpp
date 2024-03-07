#include "Exceptions.h"

Exception::Exception(int code, const char* message)
{
	std::cout << "�������� ������ �����" << std::endl;
	std::cin.ignore(65535, '\n');
	std::cin.clear();
	this->code = code;
	strcpy_s(msg, message);
}

void Exception::show()
{
	std::cout << "��������� ������. ���: " << code << std::endl;
	std::cout << msg << std::endl;
	std::cout << "���������� ��� ���: " << std::endl;
}