//
// Created by jherskow on 1/8/18.
//

#ifndef CPP_EX2_H
#define CPP_EX2_H

#include <iostream>

using namespace std;

class ex2
{

    long double x, y, vx, vy, t;
    unsigned int m, n;

    std::string outFilename = "output.txt";
    std::string inFilename = "";


public:

    /**
     * @brief Does everything
     */
    void doall(int argc, char *argv[]);


private:


};


#endif //CPP_EX2_H
