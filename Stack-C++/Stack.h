tack header file
#include "listDemos.h"


#include <hc_list_helpers.h>
#ifndef __STACK_H_INCLUDED__  
#define __STACK_H_INCLUDED__   

#include <hc_list.h>

class Stack {
public:
	Stack();
	int size();
	int top();
	void push(int);
	int pop();
	void printstack();
private:
	HaverfordCS::list<int> example;
	int size_stack;
};

#endif 

