
#ifndef MATRIX_CALCULATOR_A_MATRIX_H
#define MATRIX_CALCULATOR_A_MATRIX_H
#pragma one

#include <vector>
#include <map>
#include <iostream>
#include <string>

using namespace std;
namespace zich {

    class Matrix {
    private:
        int row;
        int column;
        map<int, map<int, int>> mat;
    public:
        Matrix(vector<double> vec, int rows, int columns);

        ~Matrix();

        /* Input and Output operators Declarations*/
        friend ostream &operator<<(ostream &out, const Matrix &mat);

        friend istream &operator>>(istream &in, Matrix &mat);

        /* Arithmetic operators Declarations */
        Matrix operator+(const Matrix &mat);

        Matrix operator+();// unari

        void operator+=(const Matrix &mat2);

        Matrix operator-(const Matrix &mat2);

        Matrix operator-();//unari

        void operator-=(const Matrix &mat2);

        /* comparison operators Declarations */
        bool operator>(const Matrix &mat2) const;

        bool operator>=(const Matrix &mat2) const;

        bool operator<(const Matrix &mat2) const;

        bool operator<=(const Matrix &mat2) const;

        bool operator==(const Matrix &mat2);

        friend bool operator==(const Matrix &mat1,const Matrix &mat2);

        bool operator!=(const Matrix &mat2);

        /* Increment operations Declarations */
        Matrix operator++();
        Matrix operator++(int);

        /* Decrement operations Declarations */
        Matrix operator--();
        Matrix operator--(int);

        /* Multiplication operations Declarations */
        Matrix operator*(const Matrix &mat2);

        friend Matrix operator*(double num, Matrix &mat);

        friend Matrix operator*(Matrix &mat, double num);

        void operator*=(const Matrix &mat2);

        void operator*=(double num);

        friend void CHECK_FOR_ERROR(const Matrix &mat1, const Matrix &mat2);

        friend void CHECK_MULTIPLICATION(const Matrix &mat1, const Matrix &mat2);

        friend pair<double, double> sum_of_matrix(const Matrix &mat1, const Matrix &mat2);

    };
     void CHECK_VALID_INPUT(string);

     vector<string> modify_row(string str, char tab);
}

#endif //MATRIX_CALCULATOR_A_MATRIX_H
