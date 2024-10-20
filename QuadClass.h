#ifndef alkimozyuzer_Ozyuzer_AlkimBelit_hw1_QuadClass_h
#define alkimozyuzer_Ozyuzer_AlkimBelit_hw1_QuadClass_h

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct location{
int x;
int y;
location(int x, int y)
		:x(x),
		y(y){}
location(){
	x=0;
	y=0;
}	
};

struct node{
location loc;
string cityName;
node(location loc , string cityName)
	:loc(loc),
	cityName(cityName){};
};

class QuadTree{
private:
	location bottomLeft; 
	location topRight;

	node *Node;

	QuadTree* NW;
	QuadTree* NE;
	QuadTree* SW;
	QuadTree* SE;

public:
	QuadTree();
	QuadTree(location botLeft , location tRight);
	~QuadTree();
	void insert(QuadTree*& , node*);
	void printQuadTree(const QuadTree*);
	void searchTree(const QuadTree* ,location l, int r , vector<string> &, vector<string> &);
};
#endif