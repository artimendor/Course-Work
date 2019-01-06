#ifndef PTR_EXCEPTION_H
#define PTR_EXCEPTION_H
#include "exceptions/projectbaseexception.h"

class Ptr_exception : public ProjectBaseException
{
public:
    Ptr_exception(const char* msg);

    void show_message() override;
};

#endif // PTR_EXCEPTION_H
