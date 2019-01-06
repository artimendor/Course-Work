#include "dataerror.h"
#include <QMessageBox>

DataError::DataError(int row, int column, const char* msg) :
    ProjectBaseException(msg, nullptr),
    row(row + 1), column(column + 1)

{
}
void DataError::setParent(QWidget* parent)
{
  this->parent = parent;
}
void DataError::show_message()
{
    QMessageBox::warning(this->parent, "матрица введена неверно",
                         this->what() + QString(".\n") + "Проверьте строку "  +
                         QString(row + '0') + " столбец " + QString(column + '0'));
}
