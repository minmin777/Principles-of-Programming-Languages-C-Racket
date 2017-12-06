/*
	StackInterface.cc
	This file contains all of the function definitions for the StackInterface.
	These will be used to generate the text interface for the stack

	Functions:
	Title			  		Description
	------------------------------------------
 */

/*----------Includes---------*/
#include <hc_list.h>
#include "Stack.h"
// like using namespace HaverfordCS, but just for one name
#include "Calculator.h"
#include <map>
#include <string>
#include <iostream>
#include <regex>
#include <vector>

using namespace std;



Stack add(Stack st)
{
	if(st.size() < 2){
		throw "illegal call for add on empty stack";
	}
	int add1 = st.pop();
	int add2 = st.pop();
	int add3 = add1 + add2;
	st.push(add3);
	return st;
}

Stack multiply(Stack st)
{
	if(st.size() < 2){
		throw "illegal call for multiplication on empty stack";
	}
	int mul1 = st.pop();
	int mul2 = st.pop();
	int mul3 = mul1 * mul2;
	st.push(mul3);
	return st;
}


Stack power(Stack st){
	if(st.size() < 2){
		throw "illegal call for power on empty stack";
	}
	int base = st.pop();
	int exp = st.pop();
	int result = 1;
	for(int i = 0; i < exp; i++){
		result *= base;
	}
	st.push(result);
	return st;
}

Stack subtract(Stack st)
{
	if(st.size() < 2){
		throw "illegal call for subtract on empty stack";
	}
	int sub1 = st.pop();
	int sub2 = st.pop();
	int sub3 = sub2 - sub1;
	st.push(sub3);
	return st;
}
Stack equalfunction(Stack st){
	if(st.size() < 2){
		throw "illegal call for subtract on empty stack";
	}
	int top = st.pop();
	int bottom = st.pop();
	if(top == bottom){
		st.push(-1);
	}
	else{
		st.push(0);
	}
	return st;
}
Stack greaterthan(Stack st){
	if(st.size() < 2){
		throw "illegal call for subtract on empty stack";
	}
	int top = st.pop();
	int bottom = st.pop();
	if(bottom > top){
		st.push(-1);
	}
	else{
		st.push(0);
	}
	return st;
}
Stack greaterthanequal(Stack st){
	if(st.size() < 2){
		throw "illegal call for subtract on empty stack";
	}
	int top = st.pop();
	int bottom = st.pop();
	if(bottom >= top){
		st.push(-1);
	}
	else{
		st.push(0);
	}
	return st;
}
Stack lessthan(Stack st){
	if(st.size() < 2){
		throw "illegal call for subtract on empty stack";
	}
	int top = st.pop();
	int bottom = st.pop();
	if(bottom < top){
		st.push(-1);
	}
	else{
		st.push(0);
	}
	return st;
}
Stack lessthanequal(Stack st){
	if(st.size() < 2){
		throw "illegal call for subtract on empty stack";
	}
	int top = st.pop();
	int bottom = st.pop();
	if(bottom <= top){
		st.push(-1);
	}
	else{
		st.push(0);
	}
	return st;
}
Stack popAndprint(Stack st)
{
	if(st.size() == 0){
		throw "illegal call to popAndprint on empty stack";
	}
	int pop = st.pop();
	cout << pop << endl;
	return st;
}

Stack drop(Stack st){
	if(st.size() == 0){
		throw "illegal call to drop in empty stack";
	}
	st.pop();
	return st;
}
Stack nip(Stack st){
	if(st.size() == 0){
		throw "illegal call to nip in empty stack";
	}
	int top = st.pop();
	st.pop();
	st.push(top);
	return st;
}
Stack dup(Stack st){
	int top = st.top();
	st.push(top);
	return st;
}
Stack over(Stack st){
	if(st.size() == 0){
		throw "illegal call to over in empty stack";
	}
	int pop = st.pop();
	int top = st.top();
	st.push(pop);
	st.push(top);
	return st;
}
Stack tuck(Stack st){
	if(st.size() == 0){
		throw "illegal call to tuck in empty stack";
	}
	int tuck1 = st.pop();
	int tuck2 = st.pop();
	st.push(tuck1);
	st.push(tuck2);
	st.push(tuck1);
	return st;
}
Stack swapover(Stack st){
	if(st.size() == 0){
		throw "illegal call to swap in empty stack";
	}
	int top = st.pop();
	int bottom = st.pop();
	st.push(top);
	st.push(bottom);
	return st;
}
Stack printStack(Stack st)
{
	int size = st.size();
	cout << "<" << size << ">" << " ";
	st.printstack();
	return st;
}
bool looksLikeInt(string s)
{
	std::regex intPattern("-?[0-9]+"); // optional minus followed by at least one numeral
	return std::regex_match(s, intPattern);
}
// recursing by calling it on itself
/*Tree ifstatement(std::vector<string> myvector){

}
Tree parserforth(std::map<string, std::vector<string>> mymap){

}*/
Stack forthinter(std::map<string, std::function<Stack (Stack)>> pairs, std::map<string, std::vector<string>> mymap, string token, Stack tester);

Stack loopstatement(std::map<string, std::function<Stack (Stack)>> pairs, std::map<string, std::vector<string>> mymap, vector<string> begin, vector<string> whileloop, Stack tester);

Stack ifstatement(std::map<string, std::function<Stack (Stack)>> pairs, std::map<string, std::vector<string>> mymap, vector<string> finishline, Stack tester);

Stack loopstatement(std::map<string, std::function<Stack (Stack)>> pairs, std::map<string, std::vector<string>> mymap, vector<string> begin, vector<string> whileloop, Stack tester){

	if(std::find(begin.begin(), begin.end(), "begin") != begin.end() || std::find(whileloop.begin(), whileloop.end(), "begin") != whileloop.end() || whileloop.empty()){
		while(tester.top() != 0){
			//tester.pop();
			//cout << "top in loopstatement " << tester.top() << endl;
			if(tester.top() == -1 || tester.top() == 0){
				tester.pop();
			}
			tester = ifstatement(pairs, mymap, begin,tester);
			//tester.pop();
			if(tester.top() == 0) break;
			if(!whileloop.empty()){
				tester = ifstatement(pairs, mymap, whileloop, tester);}
		}
	}
	else{
		while(ifstatement(pairs, mymap, begin,tester).top() != 0){
			/*if(tester.top() == -1 || tester.top() == 0){
						tester.pop();
						}*/
			tester = ifstatement(pairs, mymap, whileloop, tester);}

	}
	return tester;
}
Stack ifstatement(std::map<string, std::function<Stack (Stack)>> pairs, std::map<string, std::vector<string>> mymap, vector<string> finishline, Stack tester){
	for(std::vector<string>::iterator it = finishline.begin(); it != finishline.end(); ++it){
		//cout << "in ifstatement " << endl;
		if (looksLikeInt(*it)) {
			int to = stoi(*it);
			tester.push(to);

		}
		else if(pairs.count(*it)){
			tester = pairs.find(*it)->second(tester);
		}
		else if(mymap.count(*it)){
			tester = forthinter(pairs, mymap, *it, tester);
		}
		//else if(std::find(finishline.begin(), finishline.end(), "if") != finishline.end()){
		else if(*it == "if"){
			std::vector<string> ifvector;
			std::vector<string> elsevector;
			if(std::count(finishline.begin(), finishline.end(), "if") != std::count(finishline.begin(), finishline.end(), "else")){
				throw "An if doesn't have a matching else";
			}
			else if(std::count(finishline.begin(), finishline.end(), "else") != std::count(finishline.begin(), finishline.end(), "endif")){
				throw "An else doesn't have a matching endif";
			}
			int statement = 1;
			it++;
			//cout << "if statement else if in ifstatement " << *it << endl;
			while(statement != 0){ //error if while but no begin
				/*if(statement == 1 && *it == "endif"){
									throw "no else to matching if";
								}*/
				ifvector.push_back(*it);
				it++;
				//cout << "string is in helper" << *it <<endl;
				if(*it == "if"){statement += 1;}
				else if(*it == "else"){statement -= 1;}
				//cout << "statement in ifstatement helper " << statement << endl;
			}
			it++;
			//cout << "see if it's after if in helper " << *it << endl;
			int endifcount = 0;
			while(endifcount >= 0){
				/*if(endifcount >= 0 && *it == "endif"){
									throw "no matching endif to else";
								}*/
				elsevector.push_back(*it);
				it++;
				if(*it == "else"){endifcount += 1;}
				if(*it == "endif") endifcount -= 1;
			}
			//cout << "see if it's at endif in helper " << *it << endl;
			if(tester.top() != 0){
				/*for(std::vector<string>::iterator b = ifvector.begin(); b != ifvector.end(); ++b){

					cout << *b << " if vector in helper" << endl;
				}*/
				tester.pop();
				tester = ifstatement(pairs, mymap, ifvector,tester);
			}
			else{
				/*for(std::vector<string>::iterator g = elsevector.begin(); g != elsevector.end(); ++g){

					cout << *g << " else vector in helper" << endl;
				}*/
				tester.pop();
				tester = ifstatement(pairs, mymap, elsevector, tester);
			}



		}
		else if(*it == "begin"){
			std::vector<string> ifvector;
			std::vector<string> elsevector;
			if(std::count(finishline.begin(), finishline.end(), "begin") != std::count(finishline.begin(), finishline.end(), "while")){
				throw "A begin doesn't have a matching while";
			}
			else if(std::count(finishline.begin(), finishline.end(), "while") != std::count(finishline.begin(), finishline.end(), "repeat")){
				throw "A while doesn't have a matching repeat";
			}
			int statement = 1;
			//cout << "print it here beginning of else if begin in inter" << *it << endl;
			it++;
			while(statement != 0){ //error if while but no begin
				ifvector.push_back(*it);
				it++;
				//cout << "statement " << statement << endl;
				//cout << "string is " << *it <<endl;
				if(*it == "begin"){statement += 1;}
				else if(*it == "while"){statement -= 1;}

			}
			it++;
			//cout << "after first while in loop " << *it << endl;
			int endifcount = 0;
			while(endifcount >= 0){
				elsevector.push_back(*it);

				it++;
				if(*it == "while"){endifcount += 1;}
				if(*it == "repeat"){endifcount -= 1;}
			}
			//cout << "see if it's at endif " << *it << endl;
			//tester.pop();
			/*if(tester.top() == -1 || tester.top() == 0){
									tester.pop();
								}*/
			tester = loopstatement(pairs, mymap, ifvector, elsevector, tester);



		}
	}
	return tester;
}
Stack forthinter(std::map<string, std::function<Stack (Stack)>> pairs, std::map<string, std::vector<string>> mymap, string token, Stack tester){
	auto search1 = mymap.find(token);
	for(std::vector<string>::iterator it = search1->second.begin(); it != search1->second.end(); ++it){
		//http://www.cplusplus.com/reference/vector/vector/begin/ -- looked how to iterate through a vector
		//cout << "see what it is at begining of forthinter " << tester.top() << endl;
		if (looksLikeInt(*it)) {
			int to = stoi(*it);
			tester.push(to);

		}
		else if(pairs.count(*it)){
			tester = pairs.find(*it)->second(tester);
		}
		else if(*it == "if"){
			std::vector<string> ifvector;
			std::vector<string> elsevector;
			if(std::count(search1->second.begin(), search1->second.end(), "if") != std::count(search1->second.begin(), search1->second.end(), "else")){
				throw "An if doesn't have a matching else";
			}
			else if(std::count(search1->second.begin(), search1->second.end(), "else") != std::count(search1->second.begin(), search1->second.end(), "endif")){
				throw "An else doesn't have a matching endif";
			}
			int statement = 1;
			//cout << "print it here beginning of else if in inter for if " << *it << endl;
			//if(*(it++) != "else"){
			it++;
			//}
			if(*it == "else"){
				statement -= 1;
			}
			while(statement != 0){ //error if while but no begin

				ifvector.push_back(*it);
				it++;
				if(*it == "if"){statement += 1;}
				else if(*it == "else"){statement -= 1;}

			}
			it++;
			int endifcount = 0;
			if(*it == "endif"){
				endifcount -= 1;
			}
			while(endifcount >= 0){
				/*if(endifcount >= 0 && *it == "endif"){
					throw "no matching endif to else";
				}*/
				elsevector.push_back(*it);
				it++;
				if(*it == "else"){endifcount += 1;}
				if(*it == "endif") endifcount -= 1;
			}
			//cout << "see if it's at endif " << tester.top() << endl;
			if(tester.top() != 0){

				tester.pop(); //don't want the -1 or 0
				//cout << "see if in tester.top() != 0 " << endl;
				tester = ifstatement(pairs, mymap, ifvector,tester);
			}
			else{
				tester.pop(); //don't want the -1 or 0
				tester = ifstatement(pairs, mymap, elsevector, tester);
			}



		}
		else if(*it == "begin"){
			std::vector<string> ifvector;
			std::vector<string> elsevector;
			if(std::count(search1->second.begin(), search1->second.end(), "begin") != std::count(search1->second.begin(), search1->second.end(), "while")){
				throw "A begin doesn't have a matching while";
			}
			else if(std::count(search1->second.begin(), search1->second.end(), "while") != std::count(search1->second.begin(), search1->second.end(), "repeat")){
				throw "A while doesn't have a matching repeat";
			}
			int statement = 1;
			it++;
			if(*it == "while"){
				statement -= 1;
			}
			while(statement != 0){ //error if while but no begin
				ifvector.push_back(*it);
				it++;
				if(*it == "begin"){statement += 1;}
				else if(*it == "while"){statement -= 1;}

			}
			it++;
			int endifcount = 0;
			if(*it == "repeat"){
				endifcount -= 1;
			}
			while(endifcount >= 0){
				elsevector.push_back(*it);

				it++;
				if(*it == "while"){endifcount += 1;}
				if(*it == "repeat") endifcount -= 1;

			}

			tester = loopstatement(pairs, mymap, ifvector, elsevector, tester);


		}
		else{
			tester = forthinter(pairs, mymap, *it, tester);
		}
	}
	return tester;
}



void runCalculator()
{
	string token;
	Stack tester = Stack();
	std::map<string, std::function<Stack (Stack)>> pairs;
	pairs["+"] = add;
	pairs["-"] = subtract;
	pairs["*"] = multiply;
	pairs["."] = popAndprint;
	pairs[".s"] = printStack;
	pairs["^"] = power;
	pairs["drop"] = drop;
	pairs["nip"] = nip;
	pairs["dup"] = dup;
	pairs["swap"] = swapover;
	pairs["over"] = over;
	pairs["tuck"] = tuck;
	pairs["="] = equalfunction;
	pairs[">"] = greaterthan;
	pairs["<"] = lessthan;
	pairs["<="] = lessthanequal;
	pairs[">="] = greaterthanequal;
	std::map<string, std::vector<string>> mymap;
	std::vector<string> myvector;

	//string->vector<string> for the new map - replacing double with string "dup +"



	//cout << "calc input: ";
	while (cin >> token and token != "bye"){
		try{

			if (looksLikeInt(token)) {
				int to = stoi(token);
				tester.push(to);

			}

			else if(token == ":"){
				string first; //made a new string could've been token as well
				cin >> first;
				string functionName = first;
				cin >>first;
				while(first != ";"){
					myvector.push_back(first);
					//http://www.cplusplus.com/reference/vector/vector/push_back/ -- learned about push_back
					cin >>first;
				}
				//cin >> first;
				mymap.insert(std::pair<string, std::vector<string>>(functionName, myvector));
				//http://www.cplusplus.com/reference/map/map/insert/
				//learned about insert and using pair to insert using the link above
				myvector.clear(); //http://www.cplusplus.com/reference/vector/vector/clear/
				//want to make vecotr empty again for the next user defined function

			}
			else if(!looksLikeInt(token) && !pairs.count(token) && !mymap.count(token)){
				cerr << "Error: " << ">>>" << token << "<<<" << "is not a variable" << endl;
				//cout<< ">>>" << token << "<<<" << endl;
				//throw "not a variable!";
			}
			else {

				//auto search =
				if(pairs.count(token)){
					auto search = pairs.find(token);
					tester = search->second(tester);
				}
				else if(mymap.count(token)){
					//http://www.cplusplus.com/reference/map/map/count/
					//used count to see if token is in mymap and count will return 1 so true or 0 for false

					tester = forthinter(pairs,mymap,token, tester);

				}
				//learned about std::map and std::map::find in http://www.cplusplus.com/reference/map/map/find/
			}
		}
		catch (const char* msg){
			cerr << msg << endl;
		}
		// learned about try/catch block with http://www.cplusplus.com/doc/tutorial/exceptions/
	}
}



