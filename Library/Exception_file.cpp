#include "Exception_file.h"

Exception_file::Exception_file(int code, const char* message)
{
	this->code = code;
	strcpy_s(msg, message);
}

void Exception_file::show()
{
	std::cout << "��������� ������. ���: " << code << std::endl;
	std::cout << msg << std::endl;
}
