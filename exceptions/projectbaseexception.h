#pragma once
#include <stdexcept>
#include <QWidget>


class ProjectBaseException : public std::logic_error
{
protected:
    QWidget * parent;
public:
    ProjectBaseException(const char* msg, QWidget* parent);

    virtual void show_message() = 0;
};

