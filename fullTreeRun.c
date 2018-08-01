#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "fullTree.h"

#define MAXLINE 4096

//------------------------------------

tree_node* run_init(tree_node*);
tree_node* run_ins(tree_node*,char*,char*,char*,char*);
void run_find(tree_node*,char*);
void run_range(tree_node*,tree_node*,char*,char*);
void run_gpa(tree_node*,tree_node*,char*,char*);
void run_del(tree_node*,tree_node*,char*,char*);
void run_display(tree_node*);
void run_exit(tree_node*);

int main(){


        while(1){
		int answer;

                tree_node* root;
                tree_node* foundNode;
                char *cmd, *sendCopy, *sendline;

                char *student,*courname,*course,*grade;

                char *cmdOriginal;

                printf("myrecs> ");	


		cmd = malloc(MAXLINE);
                courname = malloc(MAXLINE);
                course = malloc(MAXLINE);
                grade = malloc(MAXLINE);
                sendCopy = malloc(MAXLINE);
                sendline = malloc(MAXLINE);
                student = malloc(MAXLINE);

		courname = "";
		student = "";
		grade = "";
		course = "";


                fgets(sendline, MAXLINE, stdin);
                strcpy(sendCopy, sendline);
                int c = 0;
                cmd = strtok(sendCopy, " \n");
                while(cmd != NULL){
                        if (c == 0){
                                cmdOriginal = cmd;
                        }
                        if(c == 1){
                                student = cmd;
                        }
			 if (c == 2){
                                course = cmd;
                        }
                        if (c == 3){
                                courname = cmd;
                        }
                        if (c == 4){
                                grade = cmd;
                        }
                        c++;
                        cmd = strtok(NULL, " \n");
                }
                cmd = cmdOriginal;

		if(strcmp("load",cmd) == 0){
                        if(student != ""){
				printf("student %s\n",student);
				char file[50];
				strcpy(file,student);
				printf("file %s\n",file);
				printf("%s\n",file); 
                                char buff[100];
                                FILE *fp = fopen(file,"r");
				while(fgets(buff,100,(FILE*)fp)){
					cmd = strtok(buff, " \n");
					printf("cmd now: %s\n",cmd);
					int c = 0;
	               			while(cmd != NULL){
        	                		if (c == 0){
                	                		cmdOriginal = cmd;
        	                		}
	        	                	if(c == 1){
        	        	                	student = cmd;
                	        		}
	                        	 	if (c == 2){
 		                               		course = cmd;
        		                	}
                		        	if (c == 3){
                        		        	courname = cmd;
                       				}
 	 	                      		if (c == 4){
        		                        	grade = cmd;
                		        	}
                        			c++;
          	        	      		cmd = strtok(NULL, " \n");
                			}
                			cmd = cmdOriginal;
					printf("cmd: %s student %s course %s courname %s grade %s\n",cmd,student,course,courname,grade);
					if(strcmp("init",cmd) == 0){
						root = run_init(root);
					}
					else if(strcmp("ins",cmd) == 0){
						if(student != "" && course != "" && courname != "" && grade != ""){
							root =run_ins(root,student,course,courname,grade);
						}
						else{
							printf("Improper call of ins");
						}
					}
					else if (strcmp("find",cmd) == 0){
						if(student != ""){
							run_find(root,student);
						}
						else{
							printf("Improper call of find\n");
						}
					}
					else if(strcmp("range",cmd) == 0){
						if(student != "" && course != ""){
							run_range(root,foundNode,student,course);
						}
						else{
							printf("Improper call of range\n");
						}

					}
					else if(strcmp("gpa",cmd) == 0){
						if(student != ""){
							run_gpa(root,foundNode, student, course);
						}
						else{
							printf("Improper call of gpa\n");
						}
					}
					else if(strcmp("del",cmd) == 0){
						if(student != "" && course != ""){
							run_del(root,foundNode,student,course);
						}
						else{
							printf("Improper call of del\n");
						}
					}
					else if(strcmp("display",cmd) == 0){
						run_display(root);
					}
					cmd = "";
					student ="";
					course="";
					courname="";
					grade="";
				}//end while
                        }       
                        else{   
                                printf("Improper Load Call\n");
                        }     
			cmd="";
			student="";
			course="";
			courname="";
			grade="";  
                }//end if load

		if(strcmp("init",cmd) == 0){
                	root = run_init(root);
                }
                if(strcmp("ins",cmd) == 0){
                        if(student != "" && course != "" && courname != "" && grade != ""){
                 	       root =run_ins(root,student,course,courname,grade);
                        }
                        else{
                               printf("Improper call of ins");
                        }
                }
                if (strcmp("find",cmd) == 0){
                        if(student != ""){
                               run_find(root,student);
                        }
                        else{
                               printf("Improper call of find\n");
                        }
                }
                if(strcmp("range",cmd) == 0){
                        if(student != "" && course != ""){
                               run_range(root,foundNode,student,course);
                        }
                        else{
                               printf("Improper call of range\n");
                        }
		}
		if(strcmp("gpa",cmd) == 0){
                        if(student != ""){
                               run_gpa(root,foundNode,student,course);
                        }
                        else{
                               printf("Improper call of gpa\n");
                        }
                }
                if(strcmp("del",cmd) == 0){
                       if(student != "" && course != ""){
                               run_del(root,foundNode,student,course);
                       }
                       else{
                               printf("Improper call of del\n");
                       }
                }
		if(strcmp("display",cmd) == 0){
			run_display(root);
		}
		if(strcmp("exit",cmd) == 0){
			run_exit(root);
			break;
		}
	}//end big while loop
	return 0;

} //end main  



tree_node* run_init(tree_node* root){
        root = (tree_node*)malloc(sizeof(tree_node));
	root->leaf = 1;
	root->order = 4;
	root->numItems = 0;
        printf("Created 2-4-Tree\n");
	return root;
}

tree_node* run_ins(tree_node* root, char* student, char* course,char* courname, char* grade){
	tree_node* newRoot;
        student = atoi(student);
	printf("student %d course %s courname %s grade %s\n",student,course,courname,grade);
	node* myNewLLNode = createLLNode(student,course,courname,grade,NULL);
	tree_node* inTreeAlready = findNode(root, student);
	if (inTreeAlready == NULL){
                newRoot = insert(root,student);
		printf("root items %d\n",newRoot->itemArray[newRoot->numItems-1]);
		inTreeAlready = findNode(newRoot, student);
		inTreeAlready->childArray[find(inTreeAlready,student)] = myNewLLNode;
	}
	else{
		newRoot = root;
		int attachHere = find(inTreeAlready,student);
		node* headNode = inTreeAlready->childArray[attachHere];
		insertLLNode(student,course,courname,grade,headNode);
	}
	if(newRoot != root){
		printf("new\n");
                root = newRoot;
        }
	return newRoot;
} //end run_ins

void run_display(tree_node* root){

	displayTree(root);

} //end run_display


void run_find(tree_node* root, char* student){
	student = atoi(student);
	tree_node* inTree = findNode(root, student);
	if(inTree == NULL){
		printf("Student is not in tree yet\n");	
	}
	else{
		printf("Information for student %d\n",student);
		int positionInNode = find(inTree,student);
		displayLL(inTree->childArray[positionInNode]);
	}
} //end run_find

void run_exit(tree_node* root){
                        int i;
                        for (i=0;i<root->numItems;i++){
                                free(root->childArray[i]);
                        }
			free(root);
                        printf("Exiting..\n");
} //end run_exit 

/*
___ run_disStud(){

                if (strcmp("disStud",cmd) == 0){
                        student = atoi(student);
                        printf("stu %d\n",student);
                        foundNode = findNode(root, student);
			int here = find(foundNode, student);
			printf("Here: %d\n",here);
                }
} end run_disStud */

void run_range(tree_node* root,tree_node* foundNode, char* student, char* course){
	student = atoi(student);
	course = atoi(course);
	int y;
	for(y=student;y<=course;y++){
		printf("Information for student %d\n",y);
		foundNode = findNode(root,y);
                int positionInNode = find(root,y);
                displayLL(foundNode->childArray[positionInNode]);
	}
} //end run_range


void run_del(tree_node* root,tree_node* foundNode, char* student,char* course){
	student = atoi(student);
	foundNode = findNode(root,student);
	int pos = find(foundNode,student);
	node* newHeadNode = removeLLNode(student, course, foundNode->childArray[pos]);
	foundNode->childArray[pos] = newHeadNode;

}//end run_del


void run_gpa(tree_node* root, tree_node* foundNode, char* student, char* course){

	if(student != "" && course == ""){
		student = atoi(student);
		foundNode = findNode(root, student);
		int here = find(foundNode, student);
		float GPA = calculateGPA(foundNode->childArray[here]);
		printf("Student %d's GPA: %.2f\n",student,GPA);
	}
	else if(student != "" && course != ""){
		student = atoi(student);
		course = atoi(course);
		int k;
		float numOfStudents = 0;
		float averageGPA = 0;
		for (k=student;k<=course;k++){
			foundNode = findNode(root, k);
			int here = find(foundNode, k);
			float GPA = calculateGPA(foundNode->childArray[here]);
			averageGPA = averageGPA + GPA;
			numOfStudents++;
		}
		averageGPA = averageGPA / numOfStudents;
		printf("Average GPA of students between student %d and student %d: %.2f\n",student,course,averageGPA);
	}
}//end run_gpa




