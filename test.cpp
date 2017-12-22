#include <iostream>
#include <vector>
// #include "PatternElement.h"
#include "PatternUtils.h"
#include "Boundaries.h"

using namespace std;
namespace putl = PatternUtils;

// c++ -lm -o test test.cpp src/PatternUtils.cc  --std=c++11 -I interface/

int main()
{
    // PatternElement<> p(10,10);
    // std::vector<PatternElement<>> v (10, PatternElement<>(1,1) );
    // for (auto& pp : v)
    //     cout << pp.get().first << " " << pp.get().second << endl;

    // putl::PatternElement<> p(10,10);
    // std::vector<putl::PatternElement<>> v (10, putl::PatternElement<>(1,1) );
    // v.back() = {1,2};
    // for (auto& pp : v)
    //     cout << pp.first << " " << pp.second << endl;

    // putl::Pattern<3> patt;

    // patt.at(0).first  = 1;
    // patt.at(0).second = 20;

    // patt.at(1).first  = 1+1;
    // patt.at(1).second = 20+1;

    // patt.at(2).first  = 1+2;
    // patt.at(2).second = 20+2;

    // cout << " ------------------ " << endl;
    // cout << patt.at(0).first << " " << patt.at(0).second << endl;
    // cout << patt.at(1).first << " " << patt.at(1).second << endl;
    // cout << patt.at(2).first << " " << patt.at(2).second << endl;

    std::vector<int> v = {1,3,5,7,9};
    Boundaries<int> bd (v);

    bd.printVector(bd.getBins());

    std::vector<int> to_test = {-999, 1, 2, 3, 4, 5, 6 ,7, 8, 9, 10 , 100};
    for (int tt : to_test)
        cout << tt << " " << bd.findBin(tt) << " is Uflow? " << (bd.findBin(tt) == -1) << " is Oflow? " << (bd.findBin(tt) == bd.getBins().size() -1) << endl;
}