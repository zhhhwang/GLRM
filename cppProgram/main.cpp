// Libraries
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include "Matrix615.h"
#include <Eigen/Core>
#include <Eigen/SVD>

// Global stuffs
#include "constants.h"

// Classes
#include "GlrmClass.h"
#include "QRPcaClass.h"
#include "QSPcaClass.h"
#include "RSPcaClass.h"

using namespace std;
using namespace Eigen;

// Author: Zhihao Huang
// Create Time: Nov. 2018
// Description: This is the main function of the glrm. User can choose to 
// input the file directory, and the methods of low rank approaches. A user
// menu is (will be) included as well.

int main(){

  cout << endl;
  cout << "####################################################" << endl;
  cout << "# Generalized Low Rank Model for Feature Selection #" << endl;
  cout << "####################################################" << endl;

  cout << endl;
  cout << "argmin_{X, Y} loss(A, XY^{T}) + lambda1 * reg(X) + lambda2 * reg(Y)";
  cout << endl;
  cout << endl;

  cout << "This is the GLRM for Feature Selection program." << endl;
  cout << "You may choose your own specification to run a generalized low rank model with";
  cout << " concentration on feature selection." << endl;
  cout << "Please follow the instructions as printed." << endl;

  cout << endl;

  cout << "Please specify the input data directory: ";
  string fileDirectory;
  cin >> fileDirectory;

  cout << endl;

  cout << "Please specify your model. Choose the listed options. "<< endl;
  cout << "1. Quadratic loss (F norm), quadratic regularizer (F norm). " << endl;
  cout << "2. Quadratic loss (F norm), sparse regularizer (l-2,1 norm). "<< endl;
  cout << "3. Robust loss (l-2,1 norm), sparse regularizer (l-2,1 norm)." << endl;
  cout << "Your option is: ";

  int modelOption = 0;
  cin >> modelOption;
  cout << endl;

  cout << "Please follow the instructions to complete the model specification." << endl;

  if (modelOption == QLQR)
  {
    QRPcaClass glrmObj(fileDirectory);
    string outDirectoryX = "OutX.csv";
    string outDirectoryY = "OutY.csv";
    glrmObj.getSolution();
    glrmObj.writeX(outDirectoryX);
    glrmObj.writeY(outDirectoryY);

  }
  else if (modelOption == QLSR)
  {
    QSPcaClass glrmObj(fileDirectory);
    string outDirectoryX = "OutX.csv";
    string outDirectoryY = "OutY.csv";
    glrmObj.getSolution();
    glrmObj.writeX(outDirectoryX);
    glrmObj.writeY(outDirectoryY);
  }
  else if (modelOption == RLSR)
  {
    RSPcaClass glrmObj(fileDirectory);
    string outDirectoryX = "OutX.csv";
    string outDirectoryY = "OutY.csv";
    glrmObj.getSolution();
    glrmObj.writeX(outDirectoryX);
    glrmObj.writeY(outDirectoryY);
  }


  cout << endl;
  cout << "The trained X and Y are output as csv file in your code directory." << endl;
  cout << "Thank you for using this program! :)" << endl;



  // string fileDirectory = "test.csv";
  // string outDirectory = "OutY.csv";
  // RSPcaClass test(fileDirectory);

  // test.getSolution();

  // // test.writeY(outDirectory);
  // test.writeY(outDirectory);
  return 0;
}
