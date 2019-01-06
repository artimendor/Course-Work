#include "ptr_exception.h"
#include "QMessageBox"

Ptr_exception::Ptr_exception(const char* msg) :
    ProjectBaseException (msg, nullptr)
{
    this->show_message();
}

void Ptr_exception::show_message()
{
    QMessageBox::critical(parent, "Системная ошибка", this->what());
}
