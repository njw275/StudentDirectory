#ifndef FULLTREE_H
#define FULLTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linkedlist.h"

typedef struct tree_node{

	int order;
	int numItems;
	int leaf;
	struct tree_node* parent;
	struct tree_node* childArray[4];
	int itemArray[4];

} tree_node;

//--------------------------------------

//Written by Nick White 
// Code adapted from Data Structures & Algorithms in Java
// By Robert Lafore (Second Edition)
// Chapter 10 (2-3-4 Trees)

//-----------------------------------


void connectChild(tree_node* thisNode, int childNum, tree_node* child){

	thisNode->childArray[childNum] = child;
	if (child != NULL){
		child->parent = thisNode;
	}
}

//------------------------------

tree_node* disconnectChild(tree_node* thisNode, int childNum){

	tree_node* tempNode = thisNode->childArray[childNum];
	thisNode->childArray[childNum] = NULL;
	return tempNode;
}

//--------------------------------------------------

tree_node* getChild(tree_node* thisNode,int childNum){

	return thisNode->childArray[childNum];

}

//------------------------------------------------

tree_node* getParent(tree_node* thisNode){

	return thisNode->parent;

}

//-----------------------------------------------

bool isLeaf(tree_node* thisNode){

	if(thisNode->leaf == 1){
		return true;
	}
	else{
		return false;
	}

}

//----------------------------------------------

int getNumItems(tree_node* thisNode){

	return thisNode->numItems;

}

//----------------------------------------------------

int getItem(tree_node* thisNode, int index){

	return thisNode->itemArray[index];

}

//-----------------------------------------------

bool isFull(tree_node* thisNode){
		printf("num item %d\n", thisNode->numItems);
		int ord = thisNode->order;
		if(thisNode->numItems == ord){
			return true;
		}
		else{
			return false;
		}

	}

	//-----------------------------------------------

	int findItem(tree_node* thisNode, int key){
		int ord = thisNode->order;
		int j;
		for(j=0;j<ord;j++){  //originally ord-1
			if(thisNode->itemArray[j]==NULL){
				break;
			}
			else if(thisNode->itemArray[j] == key){
				return j;
			}
		}
		return -1;
	}

	//--------------------------------------

	int insertItem(tree_node* thisNode, int newItem){

		thisNode->numItems = thisNode->numItems + 1;
		int newKey = newItem;

		int ord = thisNode->order;
		int j;	
		for(j=ord-2;j>=0;j--){
			if(thisNode->itemArray[j] == NULL){
				continue;
			}
			else{
				int itsKey = thisNode->itemArray[j];
				if(newKey < itsKey){
					thisNode->itemArray[j+1] = thisNode->itemArray[j];
				}
				else{
					thisNode->itemArray[j+1] = newItem;
					printf("new ins item: %d\n",thisNode->itemArray[j+1]);
					return j+1;
				}
			}
		}
		thisNode->itemArray[0] = newItem;
		return 0;
	}

	//----------------------------------------------------------

	int removeItem(tree_node* thisNode){

		printf("num itm: %d\n",thisNode->numItems);
		int pos = (thisNode->numItems) - 1;
		int temp = thisNode->itemArray[pos];
		thisNode->itemArray[pos] = NULL;
		thisNode->numItems = thisNode->numItems - 1;
		return temp;

	}

	//-----------------------------------------------

	void displayNode(tree_node* thisNode){

		int j;
		int my_items = thisNode->numItems;
		for(j=0;j<my_items;j++){
			printf("%d",thisNode->itemArray[j]);
			printf(" || ");
		}
		printf("\n");

	}

	//---------------------------------------------------
	//---------------------------------------------------
	//---------------------------------------------------
	//---------------------------------------------------

	tree_node* getNextChild(tree_node* theNode, int value){ 

		int j;  
		int numItems = getNumItems(theNode);
		printf("y num items for children: %d\n",numItems);
		for(j=0;j<numItems-1;j++){
			if(value < getItem(theNode,j)){
				return getChild(theNode,j);
			}       
		}       
		return getChild(theNode,j);
	}

	//--------------------------------------------------

	int find(tree_node* root, int key){

		tree_node* curNode = root;
		int childNumber;

		while(1){
			
			childNumber = findItem(curNode, key);
			if(childNumber != -1){
				return childNumber;
			}
			else if(isLeaf(curNode)){
				return -1;
			}
			else{
				curNode = getNextChild(curNode, key);
			}
		}
	}

	//----------------------------------------------------------------

	tree_node* findNode(tree_node* root, int key){

		tree_node* curNode = root;
		int childNumber;

		while(1){
		
			childNumber = findItem(curNode, key);
			if(childNumber != -1){ 
				return curNode;
			}       
			else if(isLeaf(curNode)){
				return NULL;
			}       
			else{   
				curNode = getNextChild(curNode, key);
			}       
		}       
	}


	//-------------------------------------------------------

	tree_node* split(tree_node* root, tree_node* thisNode){

		int itemB;
		int itemC;
		tree_node* parent;
		tree_node* child2;
		tree_node* child3;
		int itemIndex;

		itemC = removeItem(thisNode);
		itemB = removeItem(thisNode);
		child2 = disconnectChild(thisNode,2);
		child3 = disconnectChild(thisNode,3);


		tree_node* newRight = (tree_node*)malloc(sizeof(tree_node));
		newRight->leaf = 1;
		newRight->order = 4;	
		if(thisNode == root){
			root = (tree_node*)malloc(sizeof(tree_node));
			root->leaf = 0;
			root->order = 4;
			parent = root;
			connectChild(root, 0, thisNode);
		}
		else{
			parent = getParent(thisNode);
		}
		printf("copying highest to parent %d\n",thisNode->itemArray[thisNode->numItems-1]);
		itemIndex = insertItem(parent, thisNode->itemArray[thisNode->numItems-1]); 
		//printf("inserted item b %d\n",itemB);
		int n = getNumItems(parent);

		int j;
		for(j=n-1;j>itemIndex;j--){
			tree_node* temp = disconnectChild(parent,j);
			connectChild(parent,j+1, temp);
		}

		connectChild(parent,itemIndex+1, newRight);
		insertItem(newRight,itemB);
		printf("insert item b %d\n",itemB);
		insertItem(newRight,itemC);
		printf("inserted item c %d\n",itemC);
		connectChild(newRight,0, child2);
		connectChild(newRight,1, child3);
		//insert 5 here before copying&&
		printf("copying highest to parent from right %d\n", newRight->itemArray[newRight->numItems-1]);
		insertItem(parent,newRight->itemArray[newRight->numItems-1]);
		return parent;
	}

	//----------------------------------------------------

	tree_node* insert(tree_node* root, int value){

		tree_node* newParent = root;
		tree_node* curNode = root;
		int tempItem = value;

		while(true){

			if(isFull(curNode)){
				newParent = split(root,curNode);
                        curNode = getParent(curNode);
			printf("peter: %d\n",curNode->itemArray[0]);
                        curNode = getNextChild(curNode, value);
			printf("peter child: %d\n",curNode->itemArray[0]);
                }
                else if(isLeaf(curNode)){
			printf("else if");
                        break;
                }
                else{
			printf("else");
                        curNode = getNextChild(curNode, value);
                }
        }
        insertItem(curNode,tempItem);
	printf("num Items in curNode: %d\n", curNode-> numItems);
	printf("max of curNode :%d\n",curNode -> itemArray[curNode->numItems -1]);
	printf("next biggest in currNode :%d\n", curNode-> itemArray[curNode->numItems-2]);

	if (root != curNode){
		
	
		if(value == curNode->itemArray[curNode->numItems-1]){
			int prevMax = curNode->itemArray[curNode->numItems - 2];
	
			int q;
			for(q=0;q< newParent->numItems ;q++){
				printf("newParent value[%d]: %d\n", q, newParent->itemArray[q]); 
				if(newParent->itemArray[q] == prevMax){
					printf("we're changing shit around now. \n");
					newParent->itemArray[q] = value;

					break;
				}
			}
		}
	}
	printf("im alive send help: %d\n", curNode->itemArray[0]);
        printf("newparent num items: %d\n", newParent->numItems);
	printf("new parent oder: %d\n",newParent->order);
	return newParent;
}



//----------------------------------------------------------------------------
void displayTree(tree_node* root){

	recDisplayTree(root, 0, 0);

}

//---------------------------------

void recDisplayTree(tree_node* thisNode, int level, int childNumber){

	printf("Level: %d || Child: %d \n",level,childNumber);
	displayNode(thisNode);
	int numItems = getNumItems(thisNode);
	printf("num items = %d\n",numItems);

	int j;
	for(j=0;j<numItems+1;j++){
		if(isLeaf(thisNode) == 0){
			tree_node* nextNode = getChild(thisNode,j);
			if(nextNode != NULL){
				recDisplayTree(nextNode, level+1, j);
			}
			else{
				return;
			}
		}
		else{ 
			return;
		}
	}
}

//-----------------------------------------------------


#endif



