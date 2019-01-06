#ifndef DOUBLETABLE_H
#define DOUBLETABLE_H

#include <QMainWindow>
#include <QString>
#include "containers/matrix.h"

namespace Ui {
class DoubleTable;
}

class DoubleTable : public QMainWindow
{
    Q_OBJECT

    QString fio, groupe;

    Matrix<QString>* result;

    int number_of_test;

    std::list<Matrix<QString>> saved_tables;

public:
    explicit DoubleTable(QString fio, QString group, QString filepath,QWidget *parent = nullptr);
    ~DoubleTable();

private slots:
    void on_check_clicked();

    //void on_workField_cellChanged(int row, int column);

    void on_back_clicked();

    void on_workField_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

private:

    void move_back();
    void backup_table();

    Ui::DoubleTable *ui;
};

#endif // DOUBLETABLE_H
