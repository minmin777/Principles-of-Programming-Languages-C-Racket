#include <string>
#include <hc_list_helpers.h>
#include "tree.h"
#include <hc_list.h>
#include <iostream>
#include <typeinfo>

using std::cout; using std::endl;
using std::string; // use 'string' rather than 'std::string'
using HaverfordCS::list;
using HaverfordCS::list;
Tree::Tree(string st, list<Tree> ls){
	tree_string = st;
	tree_list = ls;
}

Tree::Tree(string st){ //for base case
	tree_string = st;
}

bool Tree::isleaf(){
	if(length(tree_list) == 0){
		return true;
	}
	else{
		return false;
	}
}

bool Tree::istree(){
	if(length(tree_list) > 0){
		return true;
	}
	else{
		return false;
	}
}
string Tree::value(){
	return tree_string;

}
list<Tree> Tree::getChildren(){
	if(length(tree_list) > 0){
		return tree_list;
	}
	else{
		list<Tree> hello;
		return hello;
		//throw "no children";
	}
}


bool compare(Tree t, Tree tr){
	bool first;
	list<Tree> two_list = t.getChildren();
	list<Tree> three_list = tr.getChildren();
	if(size(t) == size(tr)){
		if(t.isleaf() && tr.isleaf()){
			if(t.value() == tr.value()){
				return true;
			}
			else{
				return false;
			}
		}
		else{
			for(int i =0; i < length(t.getChildren()); i++){
				first = compare(head(two_list), head(three_list)); //use and
				if(first == false){
					return false;
				}
				two_list = rest(two_list);
				three_list = rest(three_list);
			}
			return first;
		}
	}
	else{
		return false;
	}
}


string addexlmation(string s){
	return s + "!";
}

Tree mapfunction(std::function<string (string)> f, Tree t){
	//HaverfordCS::map<>(addMe, t.getChildren()) // can't use haverford map create a function for map
	if(t.isleaf()){
		string s = f(t.value());
		return Tree(s);
	}
	else{
		list<Tree> example;
		for(int i = 0; i < length(t.getChildren()); i++){
			Tree new_child = mapfunction(f, t.getChildI(i));
			example = list<Tree>(new_child, example);
			//return Tree(f(t.value()), t.getChildren()) && mapfunction(f, t.getChildI(i));
		}
		return Tree(f(t.value()), example);
	}
}

//int sum1 = HaverfordCS::reduce<int, int>(sumlist, 0, addone);
string addstring(string s1, string s2){ //takes two strings
		return s1 + s2 + " ";
}
string reduction(std::function<string (string, string)> f, Tree t){ //take two strings // work with list reductin function - helper function doesn't take any trees with list of trees take in strings
	list<string> example;
	example = list<string>(t.value(), example);
	/*if(t.isleaf()){
		return t.value();
	}
	else{*/
		for(int i =0; i < length(t.getChildren()); i++){
			string hello = reduction(f, t.getChildI(i));
			example = list<string>(hello, example);
		}
		return HaverfordCS::reduce<string, string>(f, "", example);

}
int height(Tree t){
	int h = 0;
	if(t.isleaf()){
		return 0;
	}
	else{
	for(int i =0; i < length(t.getChildren()); i++){
		h = std::max(h, height(t.getChildI(i))); //learned about max: http://www.geeksforgeeks.org/stdmax-in-cpp/
	}
	}
	return h+1;

}

int size_helper(Tree t){
	if(length(t.getChildren()) == 0){
		return 1;
	}
	else{
		return 1 + length(t.getChildren());
	}
}
int size(Tree t){
	int s = 0;
	int total = 0;
	list<Tree> two_list = t.getChildren();
	for(int i = 0; i < length(t.getChildren()); i++){
		//total += s;
		s = size_helper(head(two_list));
		//total += s;
		two_list = rest(two_list);
		total += s;
	}
	return total + 1;
}
Tree getChildIhelper(list<Tree> list_tree, int i, int j){
	if(i == j){
		return head(list_tree);
	}
	else{
		return getChildIhelper(rest(list_tree), i, j+1);
	}
}

Tree Tree::getChildI(int i){
	list<Tree> second_list = tree_list;
	return getChildIhelper(second_list, i, 0);
}

