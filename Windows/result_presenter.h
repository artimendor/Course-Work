#ifndef RESULT_PRESENTER_H
#define RESULT_PRESENTER_H

#include <QDialog>
#include "containers/matrix.cpp"

namespace Ui {
class Result_Presenter;
}

class Result_Presenter : public QDialog
{
    Q_OBJECT

    Matrix<QString>& mtr;
public:
    explicit Result_Presenter(QWidget *parent, Matrix<QString>& mtr);
    ~Result_Presenter();

private:
    Ui::Result_Presenter *ui;
};

#endif // RESULT_PRESENTER_H
