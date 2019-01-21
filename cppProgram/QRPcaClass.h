#ifndef _QRPCA_CLASS_H_
#define _QRPCA_CLASS_H_

// Librariess
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "Matrix615.h"
#include <Eigen/Core>
#include <Eigen/SVD>

// Classes
#include "GlrmClass.h"

using namespace std;
using namespace Eigen;

// Author: Zhihao Huang
// Create Time: Nov. 2018
// Description: This is the prototype of the quadratic loss quadratic 
// regularized low rank model. The model takes the following form
//   ||A - XY^{T}||_{F}^{2} + lambdaX * ||X||_{F}^{2} + lambdaY * ||Y||_{F}^{2}
// The optimization algorithm is the alternating optimization. We may include
// analytical solution as well. 


class QRPcaClass: public GlrmClass
{
  public:
    // ctor
    QRPcaClass();
    QRPcaClass(string fileDirectory)
    :GlrmClass(fileDirectory){}

    // updates
    void getSolution();
    void updateX();
    void updateY();

    // Calculate object function
    double calObjFunc();

  private:
};

#endif