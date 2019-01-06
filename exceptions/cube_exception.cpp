#include "cube_exception.h"
#include "QMessageBox"

Cube_exception::Cube_exception(const char* msg) : Ptr_exception (msg)
{

}

void Cube_exception::show_message()
{
    QMessageBox::critical(parent, "ошибка класса куб", this->what());
}
