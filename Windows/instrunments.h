#ifndef INSTRUNMENTS_H
#define INSTRUNMENTS_H

#include <QMainWindow>

namespace Ui {
class instrunments;
}

class Instruments : public QMainWindow
{
    Q_OBJECT
protected:
    virtual void template_to_file() = 0;
    virtual void result_to_file() = 0;
    virtual void add_row() = 0;
    virtual void add_column() = 0;
    virtual void delete_column() = 0;
    virtual void delete_row() = 0;
    virtual void get_result() = 0;
    virtual void go_to_menu() = 0;
    virtual void open_template() = 0;
    virtual void back() = 0;

    virtual void closeOther(bool is_it_workw) = 0;

public:

    void closeEvent(QCloseEvent *event) override;

    explicit Instruments(QWidget *parent = nullptr);
    ~Instruments() override;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_10_clicked();

private:
    Ui::instrunments *ui;
};

#endif // INSTRUNMENTS_H
