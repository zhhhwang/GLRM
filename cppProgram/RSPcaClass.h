#ifndef _RS_PCS_H_
#define _RS_PCS_H_

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

// Global stuffs
#include "constants.h"

using namespace std;
using namespace Eigen;

// Author: Zhihao Huang
// Create Time: Nov. 2018
// Description: This is the prototype of the quadratic loss sparse 
// regularized low rank model. The model takes the following form
//   ||A - XY^{T}||_{2,1} + lambdaY * ||Y||_{2,1} 
// The optimization algorithm is the alternating optimization with 
// augmented lagrangian approach. 

class RSPcaClass: public GlrmClass
{
  public:
    // ctor
    RSPcaClass();
    RSPcaClass(string fileDirectory);

    // updates
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

    // Calculate object function
    double calObjFunc();

};


#endif
