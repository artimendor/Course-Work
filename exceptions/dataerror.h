#ifndef DATAERROR_H
#define DATAERROR_H
#include "projectbaseexception.h"
#include "QWidget"

class DataError : public ProjectBaseException
{
    int row, column;
public:
    DataError(int row, int column, const char* message = "Матрица введена неверно");
    void setParent(QWidget* parent);
    void show_message() override;
};

#endif // DATAERROR_H
