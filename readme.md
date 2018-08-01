{\rtf1\ansi\ansicpg1252\cocoartf1561\cocoasubrtf600
{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\margl1440\margr1440\vieww10800\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 Completed Tasks:\
\
init - creates 2-4 Tree\
ins - inserts studentID courseID courseName Grade\
load - loads the input file specified\
find - finds student based on studID\
range - display info for students from StudID(A) to StudID(B)\
gpa - shows gpa of student or average gpa for students from A->B\
del - deletes info for specific course of student\
\
-------------------------------------------------\
\
I implemented the childArray to hold tree node's so the children dont have to be link lists although I append llNode's to the childArray as well. From my testing, it seemed to have worked for me. \
\
The implementation of load created a mroe modular design of running the different calls.\
\
The implementation of the tree is based on a textbook for data structures (Java) as stated in the fulltree.h file. \
\
The implementation of recDisplayTree has an error, but I could not find the bug. It doesnt show the right child even though it exists (you can use find and find the info on the right child as proof).\
}
