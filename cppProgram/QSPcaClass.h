#ifndef _QSPCA_CLASS_H_
#define _QSPCA_CLASS_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "Matrix615.h"
#include <Eigen/Core>
#include <Eigen/SVD>
#include "GlrmClass.h"

// Global stuffs
#include "constants.h"

// Author: Zhihao Huang
// Create Time: Nov. 2018
// Description: This is the prototype of the quadratic loss sparse 
// regularized low rank model. The model takes the following form
//   ||A - XY^{T}||_{F}^{2} + lambdaY * ||Y||_{2,1} 
// The optimization algorithm is the alternating optimization with 
// augmented lagrangian approach. 

class QSPcaClass: public GlrmClass
{
  public:
    // ctor
    QSPcaClass();
    QSPcaClass(string fileDiretory);

    // update
    void getSolution();
    void updateX();
    void updateY();
    void updateE();
    void updateParas();

  private:
    MatrixXd L;
    MatrixXd E;
    double mu;
    double rho;

    double calObjFunc();
};



#endif