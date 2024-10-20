//
//  QuadClass.cpp
//  QuadTree Project
//
//  Created by Alkim Ozyuzer on 02.11.2022.
//
//  QuadTree Class functions for main method.

#include <iostream>
#include <cmath>
#include "QuadClass.h"

using namespace std;

QuadTree :: QuadTree(){ // default constructor
		bottomLeft = location(0,0);
		topRight = location(0,0);
		Node = NULL;

		NW = NULL;
		NE = NULL;
		SW = NULL;
		SE = NULL;
	}

QuadTree :: QuadTree(location botLeft , location tRight){ // constructor with parameters
		bottomLeft = botLeft;
		topRight = tRight;
		Node = NULL;

		NW = NULL;
		NE = NULL;
		SW = NULL;
		SE = NULL;
}

QuadTree :: ~QuadTree(){	// QuadTree destructor
		bottomLeft = location();
		topRight = location();
		Node = NULL;

		NW = NULL;
		NE = NULL;
		SW = NULL;
		SE = NULL;
}

void QuadTree :: printQuadTree (const QuadTree *root){ // pretty print the quadtree rooted at root:
	if (root != NULL){ // if the tree is not empty
		cout<<root->Node->cityName<<endl;;
		printQuadTree(root->SE); // recursively print the south east subtree 
		printQuadTree(root->SW); // recursively print the south west subtree 
		printQuadTree(root->NE); // recursively print the north east subtree 
		printQuadTree(root->NW); // recursively print the north west subtree 
	}
}

void QuadTree :: insert(QuadTree * & qt,node *n){

	if(qt->Node->loc.x > n->loc.x){
		if(qt->Node->loc.y > n->loc.y){
			if(qt->SW==NULL){
				qt->SW->Node = n;
			}
			else{
				insert(qt->SW,n);
			}
		}
		else{
			if(qt->NW==NULL){
				qt->NW->Node = n;
			}
			else{
				insert(qt->NW,n);
			}
		}
	}
	else if(qt->Node->loc.y > n->loc.y){
		if(qt->SE==NULL){
			qt->SE->Node = n;
		}
		else{
			insert(qt->SE,n);
		}

	}
	else{
		if(qt->NE==NULL){
			qt->NE->Node = n;
		}
		else{
			insert(qt->NE,n);
		}
	}
}

void QuadTree :: searchTree(const QuadTree *ptr, location l, int r , vector<string> &checked , vector<string> &inRadius){
	// This function is the implementation of the "2.3.3 Search" section, which is given with the homework file.
	// The region numbers are associated with the figure 2.17 in the same pdf file.
	if(ptr->Node!=NULL){
        double d = sqrt( pow((l.x - ptr->Node->loc.x),2) + 
		pow((l.y - ptr->Node->loc.y),2) );

		inRadius.push_back(ptr->Node->cityName);

		if((l.y-r <= ptr->Node->loc.y) && (ptr->Node->loc.y <= l.y+r) &&  (l.x-r <= ptr->Node->loc.x) && (ptr->Node->loc.x <= l.x+r)){ //If the quad contains the loc
				if(r<d){
					if( l.x > ptr->Node->loc.x && l.y < ptr->Node->loc.y){ // Region 9
						searchTree(ptr->SE, l, r, checked, inRadius);
						searchTree(ptr->SW, l, r, checked, inRadius);
						searchTree(ptr->NE, l, r, checked, inRadius);
					}
					else if( l.x < ptr->Node->loc.x && l.y < ptr->Node->loc.y){ // Region 10
						searchTree(ptr->SE, l, r, checked, inRadius);
						searchTree(ptr->SW, l, r, checked, inRadius);
						searchTree(ptr->NW, l, r, checked, inRadius);
					}
					else if( l.x < ptr->Node->loc.x && l.y > ptr->Node->loc.y){ // Region 11
						searchTree(ptr->SE ,l, r, checked, inRadius);
						searchTree(ptr->NE, l, r, checked, inRadius);
						searchTree(ptr->NW, l, r, checked, inRadius);
					}
					else if( l.x > Node->loc.x && l.y > Node->loc.y){ // Region 12
						searchTree(ptr->SW, l, r, checked, inRadius);
						searchTree(ptr->NE, l, r, checked, inRadius);
						searchTree(ptr->NW, l, r, checked, inRadius);
					}
				}
				else{ // Region 13 (inside the circle)
					inRadius.push_back(ptr->Node->cityName);
					searchTree(ptr->SE, l, r, checked, inRadius);
					searchTree(ptr->SW, l, r, checked, inRadius);
					searchTree(ptr->NE, l, r, checked, inRadius);
					searchTree(ptr->NW, l, r, checked, inRadius);
				}
		}
		else if((l.x-r >= ptr->Node->loc.x) && (l.y+r <= ptr->Node->loc.y)){ // Region 1
			searchTree(ptr->SE, l, r, checked,  inRadius);
			if((l.x-r>=ptr->Node->loc.x) && (l.y+r==ptr->Node->loc.y)){
				searchTree(ptr->NE, l, r, checked,  inRadius);
			}  
		}
		else if((l.x-r <= ptr->Node->loc.x) && (l.y+r <= ptr->Node->loc.y) && (l.x+r >= ptr->Node->loc.x)){ // Region 2
			searchTree(ptr->SE, l, r, checked,  inRadius);
			searchTree(ptr->SW, l, r, checked,  inRadius);
			if(l.y+r == ptr->Node->loc.y && l.x>ptr->Node->loc.x){
				searchTree(ptr->NE, l, r, checked,  inRadius);
			}
			else if(l.y+r == ptr->Node->loc.y && l.x<ptr->Node->loc.x){
				searchTree(ptr->NW, l, r, checked,  inRadius);
			}
		}
		else if((l.x+r <= ptr->Node->loc.x) && (l.y+r <= ptr->Node->loc.y)){ // Region 3
			searchTree(ptr->SW, l, r, checked,  inRadius);
			if((l.x+r==ptr->Node->loc.x) && (l.y+r==ptr->Node->loc.y)){
				searchTree(ptr->SE, l, r, checked,  inRadius);
				searchTree(ptr->NW, l, r, checked,  inRadius);
			}
			else if((l.x+r<ptr->Node->loc.x) && (l.y+r==ptr->Node->loc.y)){
				searchTree(ptr->NW, l, r, checked,  inRadius);
			}
			else if((l.x+r==ptr->Node->loc.x) && (l.y+r<ptr->Node->loc.y)){
				searchTree(ptr->SE, l, r, checked,  inRadius);
			}
		}
		else if((l.x-r > ptr->Node->loc.x) && (l.y+r > ptr->Node->loc.y) && (l.y-r < ptr->Node->loc.y)){ // Region 4
			searchTree(ptr->SE, l, r, checked,  inRadius);
			searchTree(ptr->NE, l, r, checked,  inRadius);
		}
		else if((l.x+r < ptr->Node->loc.x) && (l.y+r > ptr->Node->loc.y) &&(l.y-r < ptr->Node->loc.y)){ // Region 5
			searchTree(ptr->SW, l, r, checked,  inRadius);
			searchTree(ptr->NW, l, r, checked,  inRadius);
		}
		else if((l.x-r>= ptr->Node->loc.x) && (l.y-r >= ptr->Node->loc.y)){ // Region 6
			searchTree(ptr->NE, l, r, checked,  inRadius);
		}
		else if( (l.x-r < ptr->Node->loc.x) && (l.y-r > ptr->Node->loc.y) && (l.x+r > ptr->Node->loc.x) ){ // Region 7
                searchTree(ptr->NE, l, r, checked,  inRadius);
                searchTree(ptr->NW, l, r, checked,  inRadius);
		}
		else if((l.x+r <= ptr->Node->loc.x) && (l.y-r >= ptr->Node->loc.y)){ // Region 8
			searchTree(ptr->NW, l, r, checked,  inRadius);
			if((l.x+r==ptr->Node->loc.x) && (l.y-r>=ptr->Node->loc.y)){
				searchTree(ptr->NE, l, r, checked,  inRadius);
			}
		}
	}
}