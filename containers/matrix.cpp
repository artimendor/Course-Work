#pragma once
#include "matrix.h"
#include "exceptions/ptr_exception.h"

template<class T>
Matrix<T>::Matrix(int row, int column)
    : row(row), column(column)
{
    this->mtr_ptr = new T*[row];
    for(int i = 0; i < row; i++)
    {
        this->mtr_ptr[i] = new T[column];
    }

}
template<class T>
void Matrix<T>::set(const T& obj, int row, int column)
{
   if (column > this->column || row > this->row)
       throw Ptr_exception("Системная ошибка. Индекс вышел за пределы контейнера");
   else {
       this->mtr_ptr[row][column] = obj;
   }
}
template<class T>
T& Matrix<T>::get(int row, int column)
{
    if (column > this->column || row > this->row)
        throw Ptr_exception("индекс вышел за пределы матрицы");
    else {
        return this->mtr_ptr[row][column];
    }
}
template<typename T>
Iter<T> Matrix<T>::begin()
{
    Iter<T> temp;
    temp.max_row = this->row;
    temp.max_column = this->column;
    temp.pos_row = 0;
    temp.pos_column = 0;
    temp.mtr_ptr = this->mtr_ptr;

    return temp;
}
template<class T>
Iter<T> Matrix<T>::end()
{
    Iter<T> temp;
    temp.max_row = this->row;
    temp.max_column = this->column;
    temp.pos_row = this->row;
    temp.pos_column = 0;
    temp.mtr_ptr = this->mtr_ptr;

    return temp;
}

template<class T>
Iter<T>::Iter()
{
    this->max_row = 0;
    this->pos_row = 0;

    this->pos_column = 0;
    this->max_column = 0;

    this->mtr_ptr = nullptr;
}
template<class T>
Iter<T>::Iter(const Iter& other)
{
    this->max_row = other.max_row;
    this->pos_row = other.pos_row;

    this->pos_column = other.pos_column;
    this->max_column = other.max_column;

    this->mtr_ptr = other.mtr_ptr;
}

template<class T>
Iter<T>& Iter<T>::operator++()
{
    if (this->pos_row == this->max_row)
        throw Ptr_exception("иттератор вышел за пределы массива");
    this->pos_column++;
    if (this->pos_column == this->max_column)
    {
        this->pos_column = 0;
        this->pos_row++;
    }
    return *this;
}
template<class T>
Iter<T>& Iter<T>::operator--()
{
    if(!this->pos_column)
        if(this->pos_row){
            this->pos_row--;
            this->pos_column = this->max_column - 1;
        }else{
            throw Ptr_exception("Иттератор вышел за пределы массива");
        }
    else{
        this->pos_column--;
    }
    return *this;
}

template<class T>
Iter<T> Iter<T>::operator++(int)
{
    return ++(*this);
}
template<class T>
Iter<T> Iter<T>::operator--(int)
{
    return --(*this);
}

template<class T>
T& Iter<T>::operator*()
{
    if (this->pos_row < this->max_row)
        return this->mtr_ptr[pos_row][pos_column];
    else {
        throw Ptr_exception("Попытка разодресовать недоступный участок памяти!");
    }
}
template<class T>
T* Iter<T>::operator->()
{
    if (this->pos_row < this->max_row)
        return &this->mtr_ptr[pos_row][pos_column];
    else {
        throw Ptr_exception("Попытка разодресовать недоступный участок памяти!");
    }
}

template<class T>
bool Iter<T>::operator==(const Iter<T>& other)
{
    if(this->mtr_ptr == other.mtr_ptr &&
       this->pos_row == other.pos_row &&
       this->pos_column == other.pos_column)
        return true;
    else
        return false;
}
template<class T>
bool Iter<T>::operator!=(const Iter& other)
{
    return !(*this == other);
}

template<class T>
int Matrix<T>::get_row_count() const
{
    return this->row;
}
template<class T>
int Matrix<T>::get_column_count() const
{
    return this->column;
}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& other) : Matrix(other.row, other.column)
{
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            this->mtr_ptr[i][j] = other.mtr_ptr[i][j];
}

template<class T>
Matrix<T>::~Matrix()
{
    for(int i = 0; i < row; i++)
        delete[] mtr_ptr[i];
    delete[] mtr_ptr;
}
