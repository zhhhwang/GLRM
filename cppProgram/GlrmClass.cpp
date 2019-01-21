// Libraries
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

using namespace std;
using namespace Eigen;

// Author: Zhihao Huang
// Create Time: Nov. 2018
// Description: This is the implementation of the glrm class. 

// Default ctor (not preferred)
GlrmClass::GlrmClass()
{
  ;
}

// Value ctor with file directory
GlrmClass::GlrmClass(string fileDirectory)
{
  Matrix615<double> tmpX;
  tmpX.readFromFile(fileDirectory.c_str());
  tmpX.cloneToEigen(A);

  int lowRank, nSample = A.rows(), nFeature = A.cols();
  cout << "Please specify the low rank: ";
  cin >> lowRank;

  // Initialize X
  X.resize(nSample, lowRank);
  for (int i = 0; i < nSample; ++i)
  {
    for (int j = 0; j < lowRank; ++j)
    {
      X(i, j) = getUniform() * sqrt(MATRIX_MEDIAN / lowRank);
    }
  }

  // Initialize Y
  Y.resize(nFeature, lowRank);
  for (int i = 0; i < nFeature; ++i)
  {
    for (int j = 0; j < lowRank; ++j)
    {
      Y(i, j) = getUniform() * sqrt(MATRIX_MEDIAN / lowRank);
    }
  }

  // Initialize lambdas
  cout << "Please specify the lambda for X: ";
  cin >> lambdaX;
  cout << "Please specify the lambda for Y: ";
  cin >> lambdaY;
}

void GlrmClass::writeX(string fileDirectory)
{
  ofstream outfile;
  outfile.open(fileDirectory.c_str());

  for (int i = 0; i < X.rows(); ++i)
  {
    for (int j = 0; j < X.cols(); ++j)
    {
      if (j == X.cols() - 1)
      {
        outfile << X(i, j); 
      }
      else
      {
        outfile << X(i, j) << " ";
      }
    }
    outfile << endl;
  }
  outfile.close();
}

void GlrmClass::writeY(string fileDirectory)
{
  ofstream outfile;
  outfile.open(fileDirectory.c_str());

  for (int i = 0; i < Y.rows(); ++i)
  {
    for (int j = 0; j < Y.cols(); ++j)
    {
      if (j == Y.cols() - 1)
      {
        outfile << Y(i, j); 
      }
      else
      {
        outfile << Y(i, j) << " ";
      }
    }
    outfile << endl;
  }
  outfile.close();
}

void GlrmClass::printIter(const int currentIter, const double objVal)
{
  cout << "Current iteration is #" << currentIter << ", and the value of ";
  cout << "object function is " << objVal << "." << endl;
}

void GlrmClass::printProgBar(int percent)
{
  string bar;

  for (int i = 0; i < 50; i++)
  {
    if (i < (percent / 2))
    {
      bar.replace(i, 1, "=");
    }
    else if (i == (percent / 2))
    {
      bar.replace(i, 1, ">");
    }
    else
    {
      bar.replace(i, 1, " ");
    }
  }

  cout << "\r" "[" << bar << "] ";
  cout.width(3);
  cout << percent << "%     " << std::flush;
}


double GlrmClass::getUniform()
{
  return ((double)rand() / (double)RAND_MAX);
}

double GlrmClass::froNorm(MatrixXd &inMat)
{
  double result = 0;
  for (int i = 0; i < inMat.rows(); ++i)
  {
    for (int j = 0; j < inMat.cols(); ++j)
    {
      result += inMat(i, j) * inMat(i, j);
    }
  }

  return sqrt(result);
}

double GlrmClass::l21Norm(MatrixXd &inMat)
{
  double result = 0;
  double rowSqrSum = 0;
  for (int i = 0; i < inMat.rows(); ++i)
  {
    rowSqrSum = 0;
    for (int j = 0; j < inMat.cols(); ++j)
    {
      rowSqrSum += inMat(i, j) * inMat (i, j);
    }
    result += sqrt(rowSqrSum);
  }

  return result;
}

double GlrmClass::matRowEucNorm(MatrixXd &inMat, int iRow)
{
  double result = 0;
  for (int i = 0; i < inMat.cols(); ++i)
  {
    result += inMat(iRow, i) * inMat(iRow, i);
  }
  result = sqrt(result);

  return result;
}
