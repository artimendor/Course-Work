#pragma once
#include "projectbaseexception.h"

class InputException : public ProjectBaseException
{
public:

    InputException(const char* msg, QWidget * parent);

    void show_message() override;
};
