#pragma once

template<class T>
class Matrix;

template <class T>
class Iter
{
    friend class Matrix<T>;
    T** mtr_ptr;
    int max_row, max_column,
        pos_row, pos_column;
public:
   Iter();
   Iter(const Iter& other);

   Iter<T>& operator++();
   Iter<T>& operator--();

   Iter<T> operator++(int);
   Iter<T> operator--(int);

   T& operator*();
   T* operator->();

   bool operator==(const Iter& other);
   bool operator!=(const Iter& other);
};

template <class T>
class Matrix
{
    T** mtr_ptr;
    int row, column;
public:

    Matrix(int row, int column);
    Matrix(const Matrix<T>& opther);

    void set(const T& obj, int row, int column);
    T& get(int row, int column);

    Iter<T> begin();
    Iter<T> end();

    int get_row_count() const;
    int get_column_count() const;

    ~Matrix();
};
