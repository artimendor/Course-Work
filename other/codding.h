 #ifndef CODDING_H
#define CODDING_H
#include "containers/matrix.cpp"
#include "QString"
#include "exceptions/dataerror.h"

class Codding
{
private:
public:
    static bool is_neighbor(int code1, int code2);
    static int getCost1(int row1, int row2, Matrix<int>& mtr);
    static int getCost2(int row1, int row2, Matrix<int>& mtr);
    static Matrix<int> simplify_matrix(Matrix<QString>& mtr);
    static Matrix<int> get_costs(Matrix<int>& mtr);
    //static Matrix<int> get_result(Matrix<int>& costs, Matrix<int> mtr);
    static Matrix<QString> get_string_result(Matrix<int>& res, Matrix<QString>& data);
    static Matrix<QString> just_result(Matrix<QString> & data);
    static void validate_matrix(Matrix<QString> & data) throw (DataError);
};

#endif // CODDING_H
