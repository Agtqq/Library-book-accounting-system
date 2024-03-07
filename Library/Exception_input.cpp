#include "Exception_input.h"

Exception_input::Exception_input(int code, const char* message)
{
	this->code = code;
	strcpy_s(msg, message);
}

void Exception_input::show()
{
	std::cout << "��������� ������. ���: " << code << std::endl;
	std::cout << "�������� �������������� �����" << std::endl;
	std::cout << msg << std::endl;
	std::cout << "���������� ��� ���: " << std::endl;
}
