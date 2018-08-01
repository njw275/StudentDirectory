# Project Overview

The goal of this project is to create a 2-4 tree to fetch information of interest fast. The application was programmed in C. In this application, the user can rapidly access record information based on a student ID. There are 11 unique commands to upload data about a student, their grades in course, search student’s information, find the top courses, etc. 



## Completed Tasks:

init - creates 2-4 Tree

ins - inserts studentID courseID courseName Grade

load - loads the input file specified

find - finds student based on studID

range - display info for students from StudID(A) to StudID(B)

gpa - shows gpa of student or average gpa for students from A->B

del - deletes info for specific course of student

## Other Information

I implemented the childArray to hold tree node's so the children dont have to be link lists although I append llNode's to the childArray as well. 

The implementation of load created a more modular design of running the different calls.

The implementation of the tree is based on a textbook for data structures (Java) as stated in the fulltree.h file. 


