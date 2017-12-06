	Stack.cc

/*--Includes*/
#include "listDemos.h"

#include <hc_list.h>	// gets files from /home/courses/include folder, thanks to -I flag on compiler
#include <hc_list_helpers.h>
#include "Stack.h"
using HaverfordCS::list; // allow use of HaverfordCS::list as just 'list'
#include <string>
using namespace std;  // allow all included parts of std, e.g. strings
using HaverfordCS::ez_list;

Stack::Stack()
{

	// example = ...;
	size_stack = 0;

}

int Stack::size()
{
	return size_stack;
}

int Stack::top()
{
	if(empty(example)){
		throw "illegal call to Stack::top on empty stack";
	}
	else{
		return head(example);

	}

}

void Stack::push(int n)
{
	example = list<int>(n, example);
	size_stack++;

}

int Stack::pop()
{
	if(empty(example)){
		throw "illegal call, list is empty";
	}
	else{
		int pop_num = head(example);
		example = rest(example);
		size_stack--;
		return pop_num;
	}

}

void Stack::printstack()
{
	int num;
	HaverfordCS::list<int> exa;
	HaverfordCS::list<int> exa1;
	exa = example;
	while(!empty(exa)){
		num = head(exa);
		exa = rest(exa);
		exa1 = list<int>(num, exa1);
	}
	cout << exa1 << endl;



}






