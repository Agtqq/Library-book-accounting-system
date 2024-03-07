#include "Exceptions.h"

Exception::Exception(int code, const char* message)
{
	std::cout << "Неверный формат ввода" << std::endl;
	std::cin.ignore(65535, '\n');
	std::cin.clear();
	this->code = code;
	strcpy_s(msg, message);
}

void Exception::show()
{
	std::cout << "Произошла ошибка. код: " << code << std::endl;
	std::cout << msg << std::endl;
	std::cout << "Попробуйте еще раз: " << std::endl;
}