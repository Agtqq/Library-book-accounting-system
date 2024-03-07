#pragma once
#include "Exceptions.h"
class Exception_file :
    public Exception
{
public:
    Exception_file(int code, const char* message);
    void show();
};

