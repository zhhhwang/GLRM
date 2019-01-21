// Librariess
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "Matrix615.h"
#include <Eigen/Core>
#include <Eigen/SVD>
#include "GlrmClass.h"
#include "QRPcaClass.h"

using namespace std;
using namespace Eigen;

// Author: Zhihao Huang
// Create Time: Nov. 2018
// Description: This is the implementation of the quadratic loss quadratic 
// regularized low rank model. 

QRPcaClass::QRPcaClass()
{
}

void QRPcaClass::getSolution()
{
  int maxIter = 0, currentIter = 1;
  double tol = 0, objVal = 1, objValNew = 0;
  bool verbose = false;

  cout << "Please specify the largest iteration times: ";
  cin >> maxIter;
  cout << "Please specify the threshold level: ";
  cin >> tol;
  cout << "Do you want to see the update process? ";
  cout << "Type 0 for NO and other YES: ";
  cin >> verbose;

  while (currentIter < maxIter && tol < abs(objValNew - objVal) / objVal)
  {
    objVal = calObjFunc();

    // Print out iteration info
    if (verbose)
    {
      printIter(currentIter, objVal);
    }

    updateX();
    updateY();
    objValNew = calObjFunc();
    currentIter ++;
    printProgBar(currentIter * 100 / maxIter);
  }
  cout << "Iteration complete! " << endl;
}

void QRPcaClass::updateX()
{
  JacobiSVD<MatrixXd> svd(Y, ComputeThinU | ComputeThinV);
  MatrixXd singularValue = svd.singularValues();

  for (int i = 0; i < singularValue.rows(); ++i)
  {
    singularValue(i, 0) = 
    singularValue(i, 0) / (lambdaX + singularValue(i, 0) * singularValue(i, 0));
  }

  X = A * svd.matrixU() * 
      singularValue.asDiagonal() * svd.matrixV().transpose();
}

void QRPcaClass::updateY()
{
  JacobiSVD<MatrixXd> svd(X, ComputeThinU | ComputeThinV);
  MatrixXd singularValue = svd.singularValues();

  for (int i = 0; i < singularValue.rows(); ++i)
  {
    singularValue(i, 0) = 
    singularValue(i, 0) / (lambdaY + singularValue(i, 0) * singularValue(i, 0));
  }

  Y = (svd.matrixV() * singularValue.asDiagonal() * 
      svd.matrixU().transpose() * A).transpose();
}

double QRPcaClass::calObjFunc()
{
  MatrixXd tempMat = A - X * Y.transpose();
  return lambdaX * froNorm(X) * froNorm(X) + lambdaY * 
         froNorm(Y) * froNorm(Y) + froNorm(tempMat) * froNorm(tempMat);
}


