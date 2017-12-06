#ifndef TREE_H_
#define TREE_H_

#include <functional>
#include <string>
#include <hc_list.h>
using namespace std;
using HaverfordCS::list;
using std::string;
using std::function;
//get child

class Tree {
public:
	Tree(string st, list<Tree> ls);
	Tree(string st);
	string value();
	list<Tree> getChildren();
	Tree getChildI(int i);
	bool isleaf();
	bool istree();
	//friend ostream& operator<<(ostream& os, const Tree& t);
	//height of tree goes her
	//don't know any other function to use
private:
	string tree_string;
	list<Tree> tree_list;
};
int height(Tree t);
int size(Tree t);
//string reduction(Tree t);
bool compare(Tree t, Tree tr);
Tree mapfunction(function<string (string)>, Tree);
string addexlmation(string s);
string reduction(std::function<string (string, string)> f, Tree t);
string addstring(string s1, string s2);


#endif /*TREE_H_*/

