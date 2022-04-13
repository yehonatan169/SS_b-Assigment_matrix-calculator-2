
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <stdexcept>
#include "Matrix.hpp"

using namespace std;

namespace zich {


    Matrix::Matrix(vector<double> vec, int rows, int columns) {
        if (rows < 0 || columns < 0 || vec.empty() || vec.size() != rows * columns) {
            throw invalid_argument("invalid input for matrix builder");
        }
        this->row = rows;
        this->column = columns;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                this->mat[i][j] = vec[(double) (j + i * (this->column))]; // allocate the value to its place
            }
        }

    }

    Matrix::~Matrix() {}

    /* Input and Output operators*/
    ostream &operator<<(ostream &out, const Matrix &mat2) {
        string str = string("");
        for (int i = 0; i < mat2.row; i++) {
            str += "["; // start of row
            for (int j = 0; j < mat2.column; j++) {
                str += to_string(mat2.mat.at(i).at(j)); // str = str + mat2.mat[i][j] --> the number for input
                if (j != mat2.column - 1) { // if it's not the last column (the last number) in the row make ' '
                    str += " ";
                }
            }
            str += "]"; // end of row
            if (i != mat2.row - 1) { // if it's not the last row make \n between the rows of the matrix
                str += "\n";
            }
        }
        return out << str;
    }

    istream &operator>>(istream &in, Matrix &mat2) {
        char c = ' ';
        int row = 0;
        int col = 0;
        bool first_col = true; // flag for the firs row
        string input = string("");
        while (c != '\n') {
            c = in.get();
            input += c; // enter the  whole information from the user into a string
        }
        input.pop_back();// take out the last \n
        CHECK_VALID_INPUT(input);

        vector <string> split_row = modify_row(input, ','); // split the input to rows like this [1 1 1 , 1 1 1 , 1 1 1]
        row = split_row.size();
        vector <string> split_col;
        vector<double> to_num;
        for (uint i = 0; i < row; i++) {
            split_col = modify_row(split_row[i], ' '); // modify the row to be like this [1,1,1]
            int len_col = split_col.size();
            if (first_col) { // check the number of column in the first line
                col = len_col;
                first_col = false;
            }
            if (col != len_col) { // check if the number of column is the same
                throw runtime_error("please put the same amount of number in each row");
            }

            for (uint j = 0; j < len_col; j++) {
                to_num.push_back(stod(split_col[j])); // convert string to double and put in the vector
            }
        }
        Matrix temp(to_num, row, col);
        mat2 = temp;
        return in;
    }

    /* Arithmetic operators */
    /*override operator + for adding two matrix*/
    Matrix Matrix::operator+(const Matrix &mat2) {
        CHECK_FOR_ERROR(*this, mat2);
        vector<double> addvector;
        Matrix original = *this; // copy of the original matrix
        for (int i = 0; i < mat2.row; i++) {
            for (int j = 0; j < mat2.column; j++) {
                addvector.push_back(original.mat.at(i).at(j) + mat2.mat.at(i).at(j)); // creat the vector for the matrix
            }
        }
        return Matrix(addvector, mat2.row, mat2.column); // creat the matrix
    }

    /*override operator +unary */
    Matrix Matrix::operator+() {
        Matrix v = 1 * *this; // need to check
        return v;
    }

    /*override operator += and increase the value of the matrix by a given matrix*/
    void Matrix::operator+=(const Matrix &mat2) {
        *this = *this + mat2;
    }

    /*override operator - and decrease the value of the matrix by a given matrix*/
    Matrix Matrix::operator-(const Matrix &mat2) {
        CHECK_FOR_ERROR(*this, mat2);
        vector<double> dec_vector;
        for (int i = 0; i < mat2.row; i++) {
            for (int j = 0; j < mat2.column; j++) {
                dec_vector.push_back(this->mat.at(i).at(j) - mat2.mat.at(i).at(j)); // creat the vector for the matrix
            }
        }
        return Matrix(dec_vector, mat2.row, mat2.column); // creat the matrix
    }

    /*override operator -unary */
    Matrix Matrix::operator-() {
        Matrix v = -1 * *this;
        return v;
    }

    void Matrix::operator-=(const Matrix &mat2) {
        *this = *this - mat2;
    }

    /* comparison operators */
    bool Matrix::operator>(const Matrix &mat2) const { // check ife this (the matrix of the class that active the operator) > mat 2 is equal
        pair<double, double> pairSum = sum_of_matrix(*this, mat2);
        return (pairSum.first > pairSum.second);
    }

    bool Matrix::operator>=(const Matrix &mat2) const {// check ife this (the matrix of the class that active the operator) >= mat 2 is equal
        pair<double, double> pairSum = sum_of_matrix(*this, mat2);
        return (pairSum.first >= pairSum.second);
    }

    bool Matrix::operator<(const Matrix &mat2) const { // check ife this (the matrix of the class that active the operator) < mat 2 is equal
        pair<double, double> pairSum = sum_of_matrix(*this, mat2);
        return (pairSum.first < pairSum.second);
    }

    bool Matrix::operator<=(const Matrix &mat2) const { // check ife this (the matrix of the class that active the operator) <= mat 2 is equal
        pair<double, double> pairSum = sum_of_matrix(*this, mat2);
        return (pairSum.first <= pairSum.second);
    }

    bool Matrix::operator==(const Matrix &mat2) { // check ife matrix is equal
        CHECK_FOR_ERROR(*this, mat2);
        for (int i = 0; i < this->row; i++) {
            for (int j = 0; j < this->column; j++) {
                if (this->mat.at(i).at(j) != mat2.mat.at(i).at(j)) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator==(const Matrix &mat1, const Matrix &mat2) { // check ife matrix is equal
        CHECK_FOR_ERROR(mat1, mat2);
        for (int i = 0; i < mat1.row; i++) {
            for (int j = 0; j < mat1.column; j++) {
                if (mat1.mat.at(i).at(j) != mat2.mat.at(i).at(j)) {
                    return false;
                }
            }
        }
        return true;
    }

    bool Matrix::operator!=(const Matrix &mat2) { // check ife this (the matrix of the class that active the operator) != mat 2 is equal
        CHECK_FOR_ERROR(*this, mat2);
        for (int i = 0; i < mat2.row; i++) {
            for (int j = 0; j < mat2.column; j++) {
                if (this->mat.at(i).at(j) != mat2.mat.at(i).at(j)) {
                    return true;
                }
            }
        }
        return false;
    }

    /* Increment operations */
    Matrix Matrix::operator++() {
        for (int i = 0; i < this->row; i++) {
            for (int j = 0; j < this->column; j++) {
                this->mat.at(i).at(j) += 1; // raise the value by 1
            }
        }
        return *this;
    }

    Matrix Matrix::operator++(int) {
        Matrix copy = *this;
        for (int i = 0; i < this->row; i++) {
            for (int j = 0; j < this->column; j++) {
                this->mat.at(i).at(j) += 1; // raise the value by 1
            }
        }
        return copy;
    }


    /* Decrement operations */
    Matrix Matrix::operator--() {
        for (int i = 0; i < this->row; i++) {
            for (int j = 0; j < this->column; j++) {
                this->mat.at(i).at(j) -= 1; // decries the value by 1
            }
        }
        return *this;
    }

    /* Decrement operations */
    Matrix Matrix::operator--(int) {
        Matrix copy = *this;
        for (int i = 0; i < this->row; i++) {
            for (int j = 0; j < this->column; j++) {
                this->mat.at(i).at(j) -= 1; // decries the value by 1
            }
        }
        return copy;
    }

    /* Multiplication operations */
    Matrix Matrix::operator*(const Matrix &mat2) { // this function used for Multiplication between two matrix
        double sum = 0;
        CHECK_MULTIPLICATION(*this, mat2);
        vector<double> mul_vector;
        for (int i = 0; i < this->row; i++) {
            for (int j = 0; j < mat2.column; j++) {
                for (int t = 0; t < this->column; t++) {
                    sum += this->mat.at(i).at(t) * mat2.mat.at(t).at(j);
                }
                mul_vector.push_back(sum); // creat the vector for the matrix
                sum = 0;
            }
        }
        return Matrix(mul_vector, this->row, mat2.column); // creat the matrix
    }

    Matrix operator*(double num, Matrix &mat2) {  // this function used for Multiplication between number and matrix
        vector<double> mul_vector;
        for (int i = 0; i < mat2.row; i++) {
            for (int j = 0; j < mat2.column; j++) {
                mul_vector.push_back(mat2.mat.at(i).at(j) * num); // creat the vector for the matrix
            }
        }
        return Matrix(mul_vector, mat2.row, mat2.column); // creat the matrix
    }

    Matrix operator*(Matrix &mat2, double num) {
        return num * mat2;
    }

    void Matrix::operator*=(const Matrix &mat2) {
        *this = *this * mat2;
    }

    void Matrix::operator*=(double num) {
        *this = num * *this;
    }

    // this function used to summing the value of two matrix
    pair<double, double> sum_of_matrix(const Matrix &mat1, const Matrix &mat2) {
        CHECK_FOR_ERROR(mat1, mat2);
        int sum1 = 0;
        int sum2 = 0;
        for (int i = 0; i < mat1.row; i++) {
            for (int j = 0; j < mat1.column; j++) {
                sum1 += mat1.mat.at(i).at(j);
                sum2 += mat2.mat.at(i).at(j);
            }
        }
        return make_pair(sum1, sum2);
    }

    // check for if we can add or decrease two matrix
    void CHECK_FOR_ERROR(const Matrix &mat1, const Matrix &mat2) {
        if (mat1.column != mat2.column || mat1.row != mat2.row) {
            throw invalid_argument("matrix is with different size and invalid for Increment Decrement and boolean actions");
        }
    }

    // check for if we can Multiply two matrix
    void CHECK_MULTIPLICATION(const Matrix &mat1, const Matrix &mat2) {
        if (mat1.column != mat2.row) {
            throw invalid_argument("matrix is with different size and invalid for Multiplication");
        }
    }

    /*this function used to discover and modify each line to discover the num of column */
    vector <string> modify_row(string str, char tab) {
        vector <string> col;
        string temp;
        for (uint i = 0; i < str.length(); i++) {
            if (temp.empty() && str[i] == ' ') {
                continue;
            }
            if (str[i] != '[' && str[i] != ']') {
                if (str[i] != tab) {
                    temp += str[i];
                } else {
                    col.push_back(temp);
                    temp = "";
                }
            }
        }
        col.push_back(temp); // enter the vector the modified row
        return col;
    }

    // this function used to check if the input for matrix is valid
    void CHECK_VALID_INPUT(string data) {
        for (size_t i = 0; i < data.length() - 3; i++) {
            if (data.at(i) == ']') {
                if (data.at(i + 1) != ',' || data.at(i + 2) != ' ' || data.at(i + 3) != '[') {
                    throw invalid_argument("invalid input for matrix");
                }
            }
        }
        if (data.at(data.length() - 1) != ']') {
            throw invalid_argument("invalid string");
        }
    }

}