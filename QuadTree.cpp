//
//  QuadTree.cpp
//  QuadTree Project
//
//  Created by Alkim Ozyuzer on 02.11.2022.
//
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

struct node{
	int x;
	int y;
	string cityName;
	node* SW;
	node* SE;
	node* NW;
	node* NE;
};

void printQuadTree (const node *root){ // pretty print the quadtree rooted at root:
	if (root != NULL){ // if the tree is not empty
		cout<<root->cityName<<endl;;
		printQuadTree(root->SE); // recursively print the south east subtree 
		printQuadTree(root->SW); // recursively print the south west subtree 
		printQuadTree(root->NE); // recursively print the north east subtree 
		printQuadTree(root->NW); // recursively print the north west subtree 
	}
}

node* compareTrees(node* &root , node* &loc){
	if(root->x > loc->x){
		if(root->y > loc->y){
			if(root->SW==NULL){
				root->SW = loc;
			}
			else{
				compareTrees(root->SW,loc);
			}
		}
		else{
			if(root->NW==NULL){
				root->NW= loc;
			}
			else{
				compareTrees(root->NW,loc);
			}
		}
	}
	else if(root->y > loc->y){
		if(root->SE==NULL){
			root->SE = loc;
		}
		else{
			compareTrees(root->SE,loc);
		}

	}
	else{
		if(root->NE==NULL){
			root->NE = loc;
		}
		else{
			compareTrees(root->NE,loc);
		}
	}
	return root;
}

void searchTree(const node *root, int x, int y, int r , vector<string> &checked , vector<string> &inRadius){
	// This function is the implementation of the "2.3.3 Search" section, which is given with the homework file.
	// The region numbers are associated with the figure 2.17 in the same pdf file.
	if(root!=NULL){
        double d = sqrt( pow((x - root->x),2) + 
		pow((y - root->y),2) );

		checked.push_back(root->cityName);

		if((y-r <= root->y) && (root->y <= y+r) &&  (x-r <= root->x) && (root->x <= x+r)){ //If the quad contains the loc
				if(r<d){
					if( x > root->x && y < root->y){ // Region 9
						searchTree(root->SE, x,y, r, checked, inRadius);
						searchTree(root->SW, x,y, r, checked, inRadius);
						searchTree(root->NE, x,y, r, checked, inRadius);
					}
					else if( x < root->x && y < root->y){ // Region 10
						searchTree(root->SE, x,y, r, checked, inRadius);
						searchTree(root->SW, x,y, r, checked, inRadius);
						searchTree(root->NW, x,y, r, checked, inRadius);
					}
					else if( x < root->x && y > root->y){ // Region 11
						searchTree(root->SE, x,y, r, checked, inRadius);
						searchTree(root->NE, x,y, r, checked, inRadius);
						searchTree(root->NW, x,y, r, checked, inRadius);
					}
					else if( x > root->x && y > root->y){ // Region 12
						searchTree(root->SW, x,y, r, checked, inRadius);
						searchTree(root->NE, x,y, r, checked, inRadius);
						searchTree(root->NW, x,y, r, checked, inRadius);
					}
				}
				else{ // Region 13 (inside the circle)
					inRadius.push_back(root->cityName);
					searchTree(root->SE, x,y, r, checked, inRadius);
					searchTree(root->SW, x,y, r, checked, inRadius);
					searchTree(root->NE, x,y, r, checked, inRadius);
					searchTree(root->NW, x,y, r, checked, inRadius);
				}
		}
		else if((x-r >= root->x) && (y+r <= root->y)){ // Region 1
			searchTree(root->SE, x,y, r, checked,  inRadius);
			if((x-r>=root->x) && (y+r==root->y)){
				searchTree(root->NE, x,y, r, checked,  inRadius);
			}  
		}
		else if((x-r <= root->x) && (y+r <= root->y) && (x+r >= root->x)){ // Region 2
			searchTree(root->SE, x,y, r, checked,  inRadius);
			searchTree(root->SW, x,y, r, checked,  inRadius);
			if(y+r == root->y && x>root->x){
				searchTree(root->NE, x,y, r, checked,  inRadius);
			}
			else if(y+r == root->y && x<root->x){
				searchTree(root->NW, x,y, r, checked,  inRadius);
			}
		}
		else if((x+r <= root->x) && (y+r <= root->y)){ // Region 3
			searchTree(root->SW, x,y, r, checked,  inRadius);
			if((x+r==root->x) && (y+r==root->y)){
				searchTree(root->SE, x,y, r, checked,  inRadius);
				searchTree(root->NW, x,y, r, checked,  inRadius);
			}
			else if((x+r<root->x) && (y+r==root->y)){
				searchTree(root->NW, x,y, r, checked,  inRadius);
			}
			else if((x+r==root->x) && (y+r<root->y)){
				searchTree(root->SE, x,y, r, checked,  inRadius);
			}
		}
		else if((x-r > root->x) && (y+r > root->y) && (y-r < root->y)){ // Region 4
			searchTree(root->SE, x,y, r, checked,  inRadius);
			searchTree(root->NE, x,y, r, checked,  inRadius);
		}
		else if((x+r < root->x) && (y+r > root->y) &&(y-r < root->y)){ // Region 5
			searchTree(root->SW, x,y, r, checked,  inRadius);
			searchTree(root->NW, x,y, r, checked,  inRadius);
		}
		else if((x-r>= root->x) && (y-r >= root->y)){ // Region 6
			searchTree(root->NE, x,y, r, checked,  inRadius);
		}
		else if( (x-r < root->x) && (y-r > root->y) && (x+r > root->x) ){ // Region 7
                searchTree(root->NE, x,y, r, checked,  inRadius);
                searchTree(root->NW, x,y, r, checked,  inRadius);
		}
		else if((x+r <= root->x) && (y-r >= root->y)){ // Region 8
			searchTree(root->NW, x,y, r, checked,  inRadius);
			if((x+r==root->x) && (y-r>=root->y)){
				searchTree(root->NE, x,y, r, checked,  inRadius);
			}
		}
	}
}

void vectorPrint(vector<string> v){ // This function prints out the given vector
	if(v.size()!=0){
		for(int i=0; i<v.size();i++){
			if(i!=v.size()-1){
				cout<<v[i]<<", ";
			}
			else{
				cout<<v[i]<<"\n\n";
			}
		}
	}
	else{
		cout<<"<None>\n";
	}
}

int main(){
	string fileName1 , fileName2 , fileContent ,fileContent2;
	ifstream file1 , file2;
	fileName1="cities.txt";
	fileName2="queries.txt";
	file1.open(fileName1.c_str());

	int length , height;
	getline(file1,fileContent);
	stringstream ss1;
	ss1<<fileContent;
	ss1>>length>>height; // These are the length and height of the top right of the quadtree.
	
	node *root=NULL; // Initializing the root

	while(getline(file1,fileContent)){ // Reading the rest of the txt file and building the tree.
		stringstream ss2;
		string cityName_;
		int x_ , y_;
		ss2<<fileContent;
		ss2>>cityName_>>x_>>y_; // reading the content from the string stream
		if(root == NULL){
			root = new node;
			root->cityName = cityName_;
			root->x = x_;
			root->y = y_;
			root->SW=NULL;
			root->SE=NULL;
			root->NW=NULL;
			root->NE=NULL;
		}
        else{
			node* temp = new node;
			temp->cityName = cityName_;
			temp->x= x_;
			temp->y = y_;
			temp->SW=NULL;
			temp->SE=NULL;
			temp->NW=NULL;
			temp->NE=NULL;
			root = compareTrees(root,temp);

			//delete temp; // to prevent data leak
        }
	}
	printQuadTree(root);
	cout<<endl;
	file2.open(fileName2.c_str()); // Opening the queries file.
	while(getline(file2,fileContent2)){
		stringstream ss3;
		ss3<<fileContent2;
		string xStr , yStr , radiusStr;
		int x , y , radius;
		getline(ss3 , xStr , ',');
		getline(ss3 , yStr , ',');
		getline(ss3 , radiusStr , ',');
		x=stoi(xStr);
		y=stoi(yStr);
		radius = stoi(radiusStr);
						
									// These vectors will be used in the search method.
		vector<string> checked;		// Keeps track of the checked cities names'.
		vector<string> inRadius;	// Lists the cities inside the radius.
		searchTree(root,x,y,radius,checked,inRadius);

		vectorPrint(inRadius);
		vectorPrint(checked);
	}

	delete root; // To prevent data leak.
	file1.close();
	file2.close();

	return 0;
}