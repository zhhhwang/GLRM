##################################################
# Generalized Low Rank Model Program Instruction #
##################################################

Thank you for reading this instruction before using this program
This would save you some time if you run into some errors ... 

#####################
# Table of Contents #
#####################

1. Compiling
2. Preparing your data
3. Running the program
4. What to input during the program
5. Output of the program
6. Adding personalized low rank models

########################################

1. Compiling

The compiling can be completed in just a few steps with the Unix make file. 
Please follow the steps below. 

  i) Change library directories
     In the first line of the makefile, you will see the following line

        CFLAGS = -I ~/Downloads/Eigen -I ~/Downloads/boost

     Change "~/Downloads/Eigen" and "~/Downloads/boost" to the directories that
     contains Eigen library and boost library.

  ii) Remember to save your makefile with the changes in i) and exit makefile

  iii) In the makefile directory, run command "make". It will automatically 
     compiles all the files.

  iv) You are done with compiling. The executable program is named "proj.exe".

For your convenient, you may type "make clean" to remove all the linked files 
and executable program when you are done using this problem. All the header
files and source files will be kept. 


2. Preparing your data

There is no file format limitation as long as the content in the input file 
is double. You should specified the data file directory AFTER you execute
the program. The input file should contain a data matrix without header. Each
row is a sample and each column is a feature. There are two sample data file
comes along with the code, the "test.csv" and "testOutlier.csv". You may refer 
to these to files in terms of content formating. 


3. Running the program

Simply type "./proj.exe" ... NO command line input is needed. 


4. What to input during the program

During the execution of the program, you are asked to input a couple stuffs, 
including the data directory, model specification and your option to see the
optimization process. Please follow the EXACT instruction or there may be 
some unpleasant error ... The user input error handing part is still under 
construction. The following are the allowed input type for each prompts

  i) Input data directory
     String. And please make sure the file exists. 

  ii) Specify your model
     Int, with value of 1 - 3.

  iii) Specify low rank
     Positive Int. 

  iv) lambda for X and lambda for Y
     Double. Arbitrary value. 

  v) Largest iteration time
     Positive Int. 

  vi) Threshold value
     Positive double. 

  vii) Do you want to see the update process?
     Any input except 0 for yes. 

These are all the input that requires the user to type in during execution. 


5. Output of the program

You will have two output file after the execution of the program, an "OutX.csv"
and an "OutY.csv". These two files are the low rank representation and the 
feature representation respectively. The configuration for these two matrices
are the same as described in the report. 


6. Adding personalized low rank models

Adding personalized low rank models are possible. Our program implements 
three models only. The following are some steps for adding your own generalized
low rank models

  i) Your model should be a class that inherit  (public) the basis class, 
     the GlrmClass. In the GlrmClass, the data matrix A, X, Y, the data 
     lambda1 and lambda2 are initialized as describe in the report. 

  ii) There are some commonly used functionality in the GlrmClass. You may use
     These methods if needed. The method for write out X and Y is also included.

  iii) In your newly-defined class, all you needed to implement is the 
     optimization algorithm that updates X and Y. When the optimization 
     is completed, you may choose to write out X, Y or both. I encourage you
     to following the structure of the implemented classes. 

  iv) #include your class in the main function. Please note that the main 
     function now contains a user menu. It can be ignored if needed. 

  v) Create your object of your well-defined class and use your method to
     solve the model.


########################################
# Thank you for using this program! :) #
########################################

If you have any question, please contact the author at zhhhwang@umich.edu
