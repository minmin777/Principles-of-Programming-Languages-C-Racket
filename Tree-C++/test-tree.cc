#include <iostream>
#include <hc_list.h>
#include <hc_list_helpers.h>
#include "test-tree.h"
#include <string>
#include <stdio.h>
using std::cout; using std::endl;
using HaverfordCS::list;
using HaverfordCS::ez_list;
using std::string;

bool tree_test()
{
	Tree lt1a = Tree("leaf 1a");  // this should make a leaf
	Tree lt1aa = Tree("laef 1a");
	Tree lt1b = Tree("leaf 1b");
	Tree mid1 = Tree("mid-node 1", ez_list<Tree>(lt1a,lt1b));
	Tree lt2a = Tree("leaf 2a");
	Tree lt2b = Tree("leaf 2b");
	Tree lt2c = Tree("leaf 2c");
	Tree mid2 = Tree("mid-node 2", ez_list<Tree>(lt2a, lt2b, lt2c));
	Tree top  = Tree("top node",   ez_list<Tree>(mid1, mid2));
	Tree top2 = Tree("top node", ez_list<Tree>(mid2, mid1));
	Tree lt1ab = mapfunction(addexlmation, top);

	//cout << "value of new tree: " << reduction(addstring, lt1ab) << endl;
	string reducestring = reduction(addstring, lt1ab);
	cout << "foldl function : " << reducestring <<endl;
	bool test = compare(lt1a, lt1aa);
	bool new_compare = compare(top, top2);
	int heigh = height(top2);
	string i = lt1a.value();
	string j = top.value();
	string k = top.getChildI(0).value();
	return
			(
			i ==  "leaf 1a" &&
			reducestring == "leaf 1a!leaf 1b! mid-node 1! leaf 2a!leaf 2b! leaf 2c! mid-node 2!  top node! " &&
			test == false &&
			heigh == 2 &&
			new_compare == false &&
			j  ==  "top node" &&
			k == "mid-node 1" &&
			true) ;
}

string abstractionfunctionrecursion(Tree t){
	if(t.isleaf()){
		return "Tree(" + t.value() + ", list<tree>()),";
	}
	else{
		string h = "Tree(" + t.value() + ", list<tree>(";
		for(int i = 0; i < length(t.getChildren()); i++){
			h += abstractionfunctionrecursion(t.getChildI(i));

				}
		return h + ")";
	}
}
string af_helper1(string s){
	return "Tree(" + s + ", list<tree>())";
}
string af_helper_more(string s){
	return "Tree(" + s + ", list<tree>(";
}

string abstractionfunctionmapreduce(Tree t){
	//Tree new_tree;
	if(t.isleaf()){
	Tree new_tree = mapfunction(af_helper1, t);
	return reduction(addstring, new_tree);
	}
	else{
		//for(int i = 0; i < length(t.getChildren()); i++){
			Tree new_tree = mapfunction(af_helper_more, t);
			return reduction(addstring, new_tree);
		//}
		//return reduction(addstring, new_tree);
	}
	// wanted to try using af_helper1 for leafs and af_helper_more for bigger trees but since mapfunction only takes a function with input string
	//i wasn't able to do this
	// the function that reduction takes takes in two strings so i can't put extra parantheses for a leaf and commas for a true rep function
	//map changes the string which i was able to mostly have for the repr but the reduction takes a function that takes in two strings
	//so i can't do recursion or have if statements to change the representation depending on tree or leaf
	//I also can't put more parantheses for leafs or at the end, commas to separate the children or spaces
}
bool treedemo(){
	Tree lt1a = Tree("leaf 1a");  // this should make a leaf
		Tree lt1aa = Tree("laef 1a");
		Tree lt1b = Tree("leaf 1b");
		Tree mid1 = Tree("mid-node 1", ez_list<Tree>(lt1a,lt1b));
		Tree mid3 = Tree("mid-node 1", ez_list<Tree>(lt1b, mid1));
		Tree lt2a = Tree("leaf 2a");
		Tree lt2b = Tree("leaf 2b");
		Tree lt2c = Tree("leaf 2c");
		Tree mid2 = Tree("mid-node 2", ez_list<Tree>(lt2a, lt2b, lt2c));
		Tree top  = Tree("top node",   ez_list<Tree>(mid1, mid2));
		Tree top2 = Tree("top node", ez_list<Tree>(mid1, mid2));
		Tree top3 = Tree("top node 3", ez_list<Tree>(mid3, mid2));
		Tree ch7 = Tree("Ch7:");
		Tree ch6 = Tree("Ch6: Elementary");
		Tree ch5 = Tree("Ch5: Trees");
		Tree ch4 = Tree("Ch4: ADT's");
		Tree ch3 = Tree("Ch3: Elementary");
		Tree ch2 = Tree("Ch2: Analysis");
		Tree ch1 = Tree("Ch1: Intro");
		Tree part3 = Tree("mid-node 2", ez_list<Tree>(ch6, ch7));
		Tree part2  = Tree("top node",   ez_list<Tree>(ch3, ch4, ch5));
		Tree part1 = Tree("top node", ez_list<Tree>(ch1, ch2));
		Tree s_5_19 = Tree("Algo", ez_list<Tree>(part1, part2, part3));
		Tree lt1ab = mapfunction(addexlmation, s_5_19);
		string tests = reduction(addstring, lt1ab);
		cout << "reduction of a leaf " << reduction(addstring, lt1ab) << endl;
		cout << "abstraction function with recursion " << endl << abstractionfunctionrecursion(top) << endl;
		cout << "abstraction function with map and reduce " << endl << abstractionfunctionmapreduce(top) << endl;
		int heigh = height(top3);
		return (size(s_5_19) == 11 && heigh == 3 && compare(top, top2) == true && compare(top2, top3) == false && true);
				//(tests == "leaf 1a!leaf 1b! mid-node 1! leaf 2a!leaf 2b! leaf 2c! mid-node 2!  top node! " && true);
		Tree(top node,
				list<tree>(Tree(mid-node 1, list<tree>(Tree(leaf 1a, list<tree>()),Tree(leaf 1b, list<tree>())),
					         Tree(mid-node 2, list<tree>(Tree(leaf 2a, list<tree>()),Tree(leaf 2b, list<tree>()),Tree(leaf 2c, list<tree>()),))

		Tree(leaf 1a, list<tree>(Tree(leaf 1b,
				list<tree>( Tree(mid-node 1, list<tree>( Tree(leaf 2a, list<tree>(Tree(leaf 2b, list<tree>( Tree(leaf 2c, list<tree>( Tree(mid-node 2, list<tree>(  Tree(top node, list<tree>(


}

