//#include <iostream>
//#include <map>
//#include <vector>
//#include <string>
//#include <stdexcept>
//#include "Matrix.hpp"
//
//
//using namespace std;
//using namespace zich;
//
//int main(){
//
//    vector<double> vec1 = {1,0,0,0,1,0,0,0,1}; // 3x3
//    vector<double> vec2 = {1,1,1,1,1,1}; // 3x2
//    Matrix mat1(vec1,3,3);
//    cout << mat1 << " --good--" << endl;
//    try{
//        Matrix mat2(vec2,0,2);
//    }
//    catch (exception& ex){
//        cout << "caught exception: " << ex.what() << endl;
//    }
//    Matrix mat2(vec2,3,2);
//    cout << mat2 << " --good--" << endl;
//    try{
//        Matrix m = mat2 * mat1;
//    }
//    catch (exception& ex){
//        cout << "caught exception: " << ex.what() << endl;
//    }
//    Matrix mul = mat1 * mat2; // 3x2
//    mat1 *= mat2;
//
//    try{
//        bool t = true;
//        t = mat1 >= mat2;
//        cout << t << " --> big and equal <--" << endl;
//        t = mat1 <= mat2;
//        cout << t << " --> equal and smaller <--" << endl;
//        t = mat1 > mat2;
//        cout << t << " --> bigger <--" << endl;
//        t = mat1 < mat2;
//        cout << t << " --> smaller <--" << endl;
//    }
//    catch (exception& ex){
//        cout << "caught exception: " << ex.what() << endl;
//    }
//
//    try{
//        Matrix add = mat2 + mat1;
//        cout << add << " --good--" << endl;
//    }
//    catch (exception& ex){
//        cout << "caught exception: " << ex.what() << endl;
//    }
//
//
//
//    return 0;
//}