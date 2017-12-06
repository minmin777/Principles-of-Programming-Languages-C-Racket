	StackInterface header file


#ifndef __CALCULATOR_H_INCLUDED__   // if x.h hasn't been included yet...
#define __CALCULATOR_H_INCLUDED__   //   #define this so the compiler knows it has been included

void runCalculator();
Stack add(Stack);
Stack multiply(Stack);
Stack subtract(Stack);
Stack popAndprint(Stack);
Stack printStack(Stack);
Stack lessthan(Stack);
Stack equalfunction(Stack);
Stack greaterthan(Stack);
Stack drop(Stack);
Stack nip(Stack);
Stack dup(Stack);
Stack swapover(Stack);
Stack over(Stack);
Stack tuck(Stack);



#endif

