//
//  main.cpp
//  QuadTree Project
//
//  Created by Alkim Ozyuzer on 02.11.2022.
//
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "QuadClass.h"

using namespace std;

void vectorPrint(vector<string> v){
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
	fileName2="queries0.txt";
	file1.open(fileName1.c_str());

	int len , hei;
	getline(file1,fileContent);
	stringstream ss1;
	ss1<<fileContent;
	ss1>>len>>hei;
	QuadTree myQuadTree(location(0,0),location(len,hei));
	QuadTree *ptr = &myQuadTree; // ptr points to my quadtree.

	while(getline(file1,fileContent)){ // Reading the rest of the txt file
		stringstream ss2;
		string cityName;
		int x_ , y_;
		ss2<<fileContent;
		ss2>>cityName>>x_>>y_; // reading the content from the string stream
		node temp(location(x_,y_),cityName); // temp node pre insertion
		myQuadTree.insert(ptr,&temp); // inserting to the tree
	}
	
	myQuadTree.printQuadTree(ptr);

	file2.open(fileName2.c_str());

	while(getline(file2,fileContent2)){
		stringstream ss3;
		ss3<<fileContent2;
		string xStr , yStr , radiusStr;
		int x , y , radius;
		getline(ss3 , xStr , ',');
		getline(ss3 , yStr , ',');
		getline(ss3 , radiusStr , ',');
		location l(stoi(xStr),stoi(yStr)); // string manipulations to retrieve data off the txt file.
		radius = stoi(radiusStr);
						
									// These vectors will be used in the search method later on.
		vector<string> checked;		// Keeps track of the checked cities names'.
		vector<string> inRadius;	// Lists the cities inside the radius.
		myQuadTree.searchTree(ptr,l,radius,checked,inRadius);

		vectorPrint(inRadius);
		vectorPrint(checked);
	}

	file1.close();
	file2.close();
	return 0;
}
