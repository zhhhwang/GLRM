// Librariess
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "Matrix615.h"
#include <Eigen/Core>
#include <Eigen/SVD>
#include "RSPcaClass.h"

// Classes
#include "GlrmClass.h"

// Global stuffs
#include "constants.h"

using namespace std;
using namespace Eigen;

// Author: Zhihao Huang
// Create Time: Nov. 2018
// Description: This is the implementation of the quadratic loss sparse 
// regularized low rank model.

RSPcaClass::RSPcaClass(string fileDirectory)
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

void RSPcaClass::getSolution()
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

void RSPcaClass::updateX()
{
  // Initialize temp matrix
  MatrixXd tempMat;
  tempMat.resize(A.rows(), A.cols());

  tempMat = A - E + (1 / mu) * L;
  tempMat = tempMat * Y;

  // svd
  JacobiSVD<MatrixXd> svd(tempMat, ComputeThinU | ComputeThinV);
  X = svd.matrixU() * svd.matrixV().transpose();
}

void RSPcaClass::updateY()
{
  double rowEucNorm = 0;
  MatrixXd tempMat;

  // Initialize temp matrix
  tempMat.resize(A.rows(), A.cols());

  tempMat = A - E + (1 / mu) * L;
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

void RSPcaClass::updateE()
{
  double rowEucNorm = 0;
  MatrixXd tempMat;

  // Initialize temp matrix
  tempMat.resize(A.rows(), A.cols());

  tempMat = A - X * Y.transpose() + (1 / mu) * L;

  for (int i = 0; i < E.rows(); ++i)
  {
    rowEucNorm = matRowEucNorm(tempMat, i);
    if (rowEucNorm > 1.0 / mu)
    {
      for (int j = 0; j < tempMat.cols(); ++j)
      {
        E(i, j) = (1 - 1.0 / (rowEucNorm * mu)) * tempMat(i, j);
      }
    }
    else
    {
      for (int j = 0; j < tempMat.cols(); ++j)
      {
        E(i, j) = 0;
      }
    }
  }
}

void RSPcaClass::updateParas()
{
  MatrixXd tempMat;
  tempMat.resize(A.rows(), A.cols());
  tempMat = A - E - X * Y.transpose();

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

double RSPcaClass::calObjFunc()
{
  MatrixXd tempMat = A - X * Y.transpose();
  return lambdaY * l21Norm(Y) + l21Norm(tempMat);
}


