#ifndef CUBE_EXCEPTION_H
#define CUBE_EXCEPTION_H
#include "exceptions/ptr_exception.h"

class Cube_exception : Ptr_exception
{
public:
    Cube_exception(const char* msg);

    void show_message() override;
};

#endif // CUBE_EXCEPTION_H
