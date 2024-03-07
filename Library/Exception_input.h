#pragma once
#include "Exceptions.h"

class Exception_input :
    public Exception
{
public:
    Exception_input(int code, const char* message);
    void show();
};
