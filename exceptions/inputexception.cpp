#include "inputexception.h"
#include <QMessageBox>

InputException::InputException(const char* msg, QWidget * parent)
    :  ProjectBaseException(msg, parent)
{
}

void InputException::show_message()
{
    QMessageBox::warning(parent, "Ошибка ввода", this->what());
}
