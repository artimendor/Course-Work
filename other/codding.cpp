#include "codding.h"
#include <QDebug>
#include <map>
#include <cmath>
#include <algorithm>
#include <iostream>

Matrix<QString> Codding::just_result(Matrix<QString>& mtr)
{
    auto simple = simplify_matrix(mtr);
    auto costs = get_costs(simple);
    //for(auto i: costs)
    //    qDebug() << i << '\n';
    for(int i = 0; i < costs.get_row_count(); i++)
    {
        for(int j = 0; j < costs.get_column_count(); j++)
            std::cout << costs.get(i, j) << " ";
        std::cout << std::endl;
    }

    return get_string_result(costs, mtr);

}

Matrix<int> Codding::simplify_matrix(Matrix<QString> &mtr)
{
   int dim = 0;
   int temp_dim = mtr.get_row_count() - 1;
   while(temp_dim){
       temp_dim/=2;
       dim++;
   }

   Matrix<int> res(int(pow(2, dim)) + 1, mtr.get_column_count());
   res.set(0, 0, 0);

   for(int i = 1; i < mtr.get_column_count(); i++)
   {
       int temp = 0;
       for(QChar j : mtr.get(0,i))
       {

           if(j.toLatin1() == '0'){ // number 001 == 1
               temp*=10; //i've chosen 2 like temp number (0 -> 2)
               temp+=2; // because 221 != 1
           }            // we use 2 meaning that it is 0
           else{
               temp*=10;
               temp+=1;
           }
       }
       res.set(temp, 0, i);
   }


   for(int i = 1; i < mtr.get_row_count(); i++)
   {
       temp_dim = i + 1;
       for(int j = 0; j < res.get_column_count(); j++)
       {
           for (int k = 1; k < res.get_row_count(); k++)
               if (mtr.get(i, j) == mtr.get(k, 0))
               {
                   res.set(k, i, j); //set k in pos (i, j)
                   break; //то есть состояния буду кодированы цифрами
               }
       }
   }

   if(temp_dim < res.get_row_count() - 1)
       for(; temp_dim < res.get_row_count(); temp_dim++)
           for(int i = 0; i<res.get_column_count(); i++)
               res.set(temp_dim, temp_dim, i);
   return res;
}

void Codding::validate_matrix(Matrix<QString> &data) throw(DataError)
{
    //проверяем, что все входные записаны правильно
    for(int i = 1; i < data.get_column_count(); i++)
    {
        if(data.get(0, i).length() == 0)
            throw DataError(0,1);
        for(auto j : data.get(0,i))
            if(j != '0' && j != '1')
                throw DataError(0,1);
     }
    //проверяем сигналы на размерность
    for(int i = 1; i < data.get_column_count() - 1; i++)
    {
        if(data.get(0, i).length() != data.get(0,i + 1).length())
            throw DataError(0, i + 1, "Размерность входных сигналов не совпадает");
    }
    //проверяем, не повторяются ли входные сигналы
    for(int i = data.get_column_count() - 1; i > 0; i--)
    {
        if(data.get(0, i).length() == 0)
            throw DataError(i,0);
        for(int j = i - 1; j > 0; j--)
            if(data.get(0, i) == data.get(0,j))
                throw DataError(i, 0, "Повторная декларация входного сигнала");
    }
    //проверяем, не повторяются ли состояния
    for(int i = data.get_row_count() - 1; i > 0; i--)
    {
        if(data.get(i, 0).length() == 0)
            throw DataError(i,0);
        for(int j = i - 1; j > 0; j--)
            if(data.get(i,0) == data.get(j,0))
                throw DataError(i, 0, "Повторная декларация состояния");
    }
    //проверяем, что все переходы записаны правильно
    for(int i = 1; i < data.get_row_count(); i++)
    {
        for(int j = 1; j < data.get_column_count(); j++)
        {
            bool fl = false;
            for(int k = 1; k < data.get_row_count(); k++)
                if(data.get(k, 0) == data.get(i, j))
                {
                    fl = true;
                    break;
                }
            if(!fl)
                throw DataError(i, j);
        }
    }
}

Matrix<int> Codding::get_costs(Matrix<int>& mtr)
{
    Matrix<int> res(mtr.get_row_count() - 1, mtr.get_row_count() - 1);
    for(int i = 0; i < res.get_row_count(); i++)
        for(int j = 0; j < res.get_column_count(); j++)
            if(i == j)
                res.set(-1, i, j);
            else {
                res.set(getCost1(i + 1, j + 1, mtr) + getCost2(i + 1, j + 1, mtr), i, j);
            }
    return res;
}

Matrix<QString> Codding::get_string_result(Matrix<int>& codes, Matrix<QString>& data)
{
    Matrix<QString> str(data.get_row_count(), data.get_row_count());

    for(int i = 0; i < data.get_row_count(); i++)
    {
        str.set(data.get(i, 0), i, 0);
        str.set(data.get(i, 0), 0, i);
    }

    for(int i = 0; i < data.get_row_count() - 1; i++)
        for(int j = 0; j < data.get_row_count() - 1; j++)
            str.set(QString::number(codes.get(i, j)), i + 1, j + 1);

    return str;
}

int Codding::getCost1(int row1, int row2, Matrix<int>& mtr)
{
    int res = 0;
    for(int i = 1; i < mtr.get_column_count(); i++)
        if (mtr.get(row1, i) == mtr.get(row2, i))
            res++;
    return res;
}
int Codding::getCost2(int row1, int row2, Matrix<int>& mtr)
{
    int sost1 = mtr.get(row1, 0);
    int sost2 = mtr.get(row2, 0);

    int res = 0;

    for (int i = 1; i < mtr.get_row_count(); i++) //going in rows
    {
        for(int j = 1; j < mtr.get_column_count(); j++) //search all sost1 in row
        {
            if(mtr.get(i, j) == sost1)
            {
                for(int k = 1; k < mtr.get_column_count(); k++) // search all sost2 in row
                {
                    if (mtr.get(i, k) == sost2)
                    {
                        if(is_neighbor(mtr.get(0, j), mtr.get(0,k))) // if codes are neigbors (example: 10 is neigbor of 11)
                        {
                            res++;
                        }
                    }
                }
            }
        }
    }
    return res;
}

bool Codding::is_neighbor(int code1, int code2)
{
    int res = 0;
    while(code1 != 0)
    {
        if ((code1 - (code1/10) * 10) != (code2 - (code2/10) * 10))
            res++;
         code1/=10;
         code2/=10;
    }

    if (res <= 1)
            return true;
    else
        return false;
}


/*
Matrix<int> Codding::get_result(Matrix<int>& costs, Matrix<int> mtr)
{
    std::list<Cube> cubes;
    for(int i = 1; i < mtr.get_row_count(); i++)
        cubes.push_back(Cube(i));

    Cube res = get_res_cube(cubes, costs);

}

Cube get_res_cube(std::list<Cube>& cubes, Matrix<int>& costs) // получаем итоговый куб
{
    static int kl = 0;
    qDebug() << kl;
    if(cubes.size() == 1)
        return *cubes.begin();

    std::list<Cube> res;
    int pos[3];
    pos[0] = pos[1] = pos[2] = -1;

    while(cubes.size())
    {
        qDebug() << "size is" << cubes.size();
        for(int i = 0; i < cubes.size(); i++)
        for(int j = i + 1; j < cubes.size(); j++)
        {
            int cost = get_cost_of_adding(getfrom(cubes, i),getfrom(cubes, j),costs);
            if (cost > pos[2])
            {
                pos[2] = cost;
                pos[0] = i; pos[1] = j;
            }

        }
        Cube a = getfrom(cubes, pos[0]);
        Cube b = getfrom(cubes, pos[1]);
        res.push_front(get_max_sum(a, b, costs));
        pop(cubes, a);
        pop(cubes, b);
        pos[0] = pos[1] = pos[2] = -1;
    }

    return get_res_cube(res, costs);
}

Cube get_max_sum(Cube& one, Cube& two, Matrix<int>& costs)
{
    int max = get_cost_of_adding(one, two, costs);

    while(Cube::getCost(one, two, costs) != max)
        two.rotate_cube();

    return one + two;
}

template <class T>
T& getfrom(std::list<T>& cont, int pos)
{
    auto it = cont.begin();
    for(;pos; pos--)
        it++;
    return *it;
}

template <class T>
void pop(std::list<T>&list, T& obj)
{
    int pos = 0;
    for(auto i: list)
        if (obj == i)
        {
            break;
        }
        else {
            pos++;
        }
    for(; pos < list.size() - 1; pos++)
        getfrom(list, pos) = getfrom(list, pos + 1);

    list.pop_back();
}


int get_cost_of_adding(Cube& one, Cube& two, Matrix<int>& cost)

{
    int max = 0;
    for(int i = 0; i < pow(2, one.dimension_size() + 1); i++)
    {
        int temp = Cube::getCost(one, two, cost);
        if(temp>max)
            max = temp;
        //one.rotate_cube();
        two.rotate_cube();
    }
    return max;
}

*/
