#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "Matrix615.h"
#include <Eigen/Core>
#include <Eigen/SVD>
#include "GlrmClass.h"
#include "QSPcaClass.h"

// Global stuffs
#include "constants.h"

// Author: Zhihao Huang
// Create Time: Nov. 2018
// Description: This is the implementation of the quadratic loss sparse 
// regularized low rank model. 

// Initialize for extra defined data member
QSPcaClass::QSPcaClass(string fileDirectory)
:GlrmClass(fileDirectory)
{
  // Initialize L
  L.resize(A.rows(), A.cols());
  for (int i = 0; i < A.rows(); ++i)
  {
    for (int j = 0; j < A.cols(); ++j)
    {
      L(i, j) = getUniform();
    }
  }

  // Initlaize E
  E.resize(A.rows(), A.cols());
  E = X * Y.transpose();

  // Initialize parameters
  mu = 1;
  rho = 5;
}


void QSPcaClass::getSolution()
{
  int maxIter = 0, currentIter = 1, innerIter = 1;
  double tol = 0, objVal = 1, objValNew = 0;
  bool verbose = false;

  cout << "Please specify the largest iteration times: ";
  cin >> maxIter;
  cout << "Please specify the constraints error threshold level: ";
  cin >> tol;
  cout << "Do you want to see the update process? ";
  cout << "Type 0 for NO and other YES: ";
  cin >> verbose;

  while (tol < abs(objValNew - objVal) / objVal && currentIter <= maxIter)
  {
    objVal = calObjFunc();
    innerIter = 1;
    while (innerIter < MAX_ITERATION)  
    {      
      updateX();
      updateY();
      updateE();
      innerIter ++;
      printProgBar(innerIter * 100 / MAX_ITERATION);
    }
    updateParas();

    // Print out current iteration
    if (verbose)
    {
      printIter(currentIter, objVal);
    }

    currentIter ++;
    objValNew = calObjFunc();
  }
  cout << "Iteration complete! " << endl;
}

void QSPcaClass::updateX()
{
  // Initialize temp matrix
  MatrixXd tempMat;
  tempMat.resize(A.rows(), A.cols());

  tempMat = E + (1 / mu) * L;
  tempMat = tempMat * Y;

  // svd
  JacobiSVD<MatrixXd> svd(tempMat, ComputeThinU | ComputeThinV);
  X = svd.matrixU() * svd.matrixV().transpose();
}

void QSPcaClass::updateY()
{
  double rowEucNorm = 0;
  MatrixXd tempMat;

  // Initialize temp matrix
  tempMat.resize(A.rows(), A.cols());

  tempMat = E + (1 / mu) * L;
  tempMat = tempMat.transpose() * X;
  for (int i = 0; i < Y.rows(); ++i)
  {
    rowEucNorm = matRowEucNorm(tempMat, i);
    if (rowEucNorm > lambdaY / mu)
    {
      for (int j = 0; j < tempMat.cols(); ++j)
      {
        Y(i, j) = (1 - lambdaY / (rowEucNorm * mu)) * tempMat(i, j);
      }
    }
    else
    {
      for (int j = 0; j < tempMat.cols(); ++j)
      {
        Y(i, j) = 0;
      }
    }
  }
}

void QSPcaClass::updateE()
{
  MatrixXd tempMat;
  tempMat.resize(A.rows(), A.cols());

  tempMat = 2 * A - L;
  tempMat = tempMat + mu * X * Y.transpose();
  E = tempMat * (1 / (2 + mu));
}

void QSPcaClass::updateParas()
{
  MatrixXd tempMat;
  tempMat.resize(A.rows(), A.cols());
  tempMat = E - X * Y.transpose();

  // Update L
  L = L + mu * tempMat;

  // Update mu
  if (mu < MU_MAX)
  {
    mu = mu * rho;
  }
  else
  {
    mu = MU_MAX;
  }
}

double QSPcaClass::calObjFunc()
{
  MatrixXd tempMat = A - X * Y.transpose();
  return lambdaY * l21Norm(Y) + froNorm(tempMat) * froNorm(tempMat);
}


