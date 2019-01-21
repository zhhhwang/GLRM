#ifndef _GLRM_CLASS_H_
#define _GLRM_CLASS_H_

// Librariess
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "Matrix615.h"
#include <Eigen/Core>
#include <Eigen/SVD>

using namespace std;
using namespace Eigen;

// Author: Zhihao Huang
// Create Time: Nov. 2018
// Description: This is the prototype of the glrm class. Glrm class is the 
// basis class for all low rank models. Data members are kept protected, and 
// low rank models have almost the same structure. Member functions are 
// some commonly used functionality for low rank models. 

class GlrmClass
{
  protected:
    // Attributes
    MatrixXd A;
    MatrixXd X;
    MatrixXd Y;
    double lambdaX;
    double lambdaY;

  public:
    // ctor 
    GlrmClass();
    GlrmClass(string fileDirectory);

    // General functionality
    void writeX(string fileDirectory);
    void writeY(string fileDirectory);
    double getUniform();
    void printIter(const int currentIter, const double objVal);
    void printProgBar(int precent);

    // Matrix norm
    double froNorm(MatrixXd &inMat);
    double l21Norm(MatrixXd &inMat);
    double matRowEucNorm(MatrixXd &inMat, int iRow);
};

#endif