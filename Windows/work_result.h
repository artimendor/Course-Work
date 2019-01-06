#include "Windows/instrunments.h"
#include "Windows/workwindow.h"

#ifndef WOR_RESULT_H
#define WOR_RESULT_H


class Work_Result : private Instruments, private WorkWindow
{
    void template_to_file() override;
    void result_to_file() override;
    void add_row() override;
    void add_column() override;
    void delete_column() override;
    void delete_row() override;
    void get_result() override;
    void go_to_menu() override;
    void open_template() override;
    void back() override;


    //int row, column;

    Matrix<QString> table_to_matrix();
    bool save_to_txt_file(QString filepath, Matrix<QString> table);

public:

    Work_Result(const QString& fio, const QString& group, QWidget* parent = nullptr);
    void show();

protected:
    void closeOther(bool is_it_workw) override;
};

#endif // WOR_RESULT_H
