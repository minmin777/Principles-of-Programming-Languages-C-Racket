#include <HERA.h>
#include <HERA-print.h>  // This is needed to use the hera 'print' function
/*
 *
 * This lab work is by Mimi Benkoussa, Yasmine Ayad, and Alison Rosenman (all in Dave's section).
 *
 *
 *
 */
// FIRST, some definitions that tell us how much of this project we want to attempt
#define PRELAB      0
#define STACK_TESTS 1
#define STACK_IMPL  0//changed from 0

void HERA_main()
{
  // Put any #defines or, strings, or other data declarations here, or get them with #includes, e.g.
#include <Tiger-stdlib-reg-data.hera>

#if STACK_TESTS
#include "Stack-tests-data.hera"
#endif
#if STACK_IMPL
#include "Stack-data.hera"
#endif
#if PRELAB
#include "prelab-data.hera"
#endif

    // Set the carry block before doing any other operations:
    //SETCB()
    DLABEL (START_OF_STACK)
    DSKIP(5000) //Allocate 5000 memory cells for the rest of our stack
	DLABEL(our_string)
		//LP_STRING("2 3 * ! 3 2 2 ! * + * . !")

		LP_STRING("7 6 5 6 8 - . !")
		//LP_STRING("1 2 3 4 + + !")
		//LP_STRING("2 2 1 4 + - !")
		//LP_STRING("1 .")
		//LP_STRING("7 8 2 - * !")
	SETCB()
    SET(R6, START_OF_STACK) //Starting address of the stack
    SET(R8, START_OF_STACK) //Address of the stack top


	SET(R2, our_string)

    //INstead: before CALL(R5, push) SET R5 to be the desired push value.
        //SET(R5, 7)//R5 IS THE VALUE WE WANT TO PUSH. Stuck at 7 for now, will edit to be some sort of input later...


// Put the main body of your HERA program after the initialization and testing of Stack

    //Initialize top_of_stack by giving it the bottom value (make it empty)

      // first, run the test suite, or #include a file that does:
#if STACK_TESTS
#include "Stack-tests.hera"
#endif
#if STACK_IMPL
#include "Stack.hera"
#endif
#if PRELAB
#include "prelab.hera"
#endif

      HALT()    // end of main HERA program

    // Put any HERA function definitions here, or #include a file containing them



//PUSH
	  LABEL(PUSH)
	  	  INC(R8, 1)//R8 address of current cell so it should have the top
		  STORE(R1, 0, R8) //R1 is where PUTCHAR_ORD comes in.
		  RETURN(R12, RT)//Go back
//TOP
	LABEL(TOP)
	  	  LOAD(R1, 0 , R8)
		  CALL(R12, printint)
		  std::cout<< std::endl;
		  //print_reg(R1)
		  RETURN(R12, RT)//Go back

//POP
    LABEL(POP)
		LOAD(R1, 0, R8)// put the top in r1
		CALL(R12, printint) //print the old top
		std::cout<< std::endl;
          DEC(R8, 1)//Ignoring the existing old "top"
          RETURN(R12, RT)//Go back


//SIZE OF THE STACK
          LABEL(stack_size)
              SUB(R4, R8, R6)
              RETURN(R12, RT)
//CHECK IF STACK IS EMPTY
          LABEL(CHECK_EMPTY)
              SUB(R1,R6, R8) //r1 is the size of the stack
              BS(stack_is_not_empty)
              //"return true"
                  SET(R1, 1)
                  RETURN(R12, RT)
              LABEL(stack_is_not_empty)
              //"return false"
                  SET(R1, 0)
                  RETURN(R12, RT)

//PRINT THE STACK "BACKWARDS"
          LABEL(stack_print)
              SUB(R2, R8, R6) //R2 is zero off of String2, i.e. LENGTH (to start).
              SET(R3, 1) //R3 is 1.
              LABEL(LOOPSTART1)//Loops Starts Here
                  BZ(LOOPEXIT1)//If you have zero, break to the exit, where all you do is print.
                  ADD(R5, R3, R6)//Add into RT the string2 address and how far off it you're going
                  LOAD(R4, 0, R5)//R3 now has the character at R2+R1+0 spaces, that is, the "current" character as you iterate, so it should be printed!
				  print_reg(R4)
                  INC(R3,1) //"distance" off of start of string 2 increases by 1; go to the next character
                  DEC(R2,1) //Length decreases by 1. Eventually, this will become 0 which is good because we use BZ.
                  BR(LOOPSTART1)
              LABEL(LOOPEXIT1)
              RETURN(R12, RT)

//STACK ADD TAKES TWO NUMBERS ADD THEM AND THEN PUT THEM BACK IN THE STACK
          LABEL(stack_add)
              CALL(R12, POP) //R12 has the top
              MOVE(R9, R1) //Put this top labelin R9
              CALL(R12, POP)//Take off the top—that is, operate on one memory cell above (one address number HIGHER)
			  MOVE(R7, R1) //second numer to add
              ADD(R1, R9, R7) //We need a sum to put in the address
              CALL(R12, PUSH)//has to push what is in R5
              RETURN(R12, RT)//Go back
//STACK SUB
          LABEL(stack_sub)
			  CALL(R12, POP) //R12 has the top
			  MOVE(R9, R1) //Put this top labelin R9
			  CALL(R12, POP)//Take off the top—that is, operate on one memory cell above (one address number HIGHER)
			  MOVE(R7, R1)
			  SUB(R1, R9, R7) //We need a sub to put in the address
			  CALL(R12, PUSH)//has to push what is in R5
			  RETURN(R12, RT)//Go back

//STACK MULT
          LABEL(stack_mult)
			  CALL(R12, POP) //R12 has the top
			  MOVE(R9, R1) //Put this top labelin R9
			  CALL(R12, POP)//Take off the top—that is, operate on one memory cell above (one address number HIGHER)
			  MOVE(R7, R1)
			  MULT(R1, R9, R7) //We need a mult to put in the address
			  CALL(R12, PUSH)//has to push what is in R5
			  RETURN(R12, RT)//Go back
//.s
          LABEL(dot_s)
              SET(R1, '<')
			  CALL(R12, putchar_ord)
              CALL(R12, stack_size)
			  MOVE(R1, R4)
			  CALL(R12, printint)
              SET(R1, '>')
			  CALL(R12, putchar_ord)
              CALL(R12, stack_print)
			  RETURN(R12, Rt)

		LABEL(CALCULATOR)
			LOAD(R3,0,R2)// put the size of the string in r3
			INC(R2, 1) //next char

			LABEL(start) //start of the loop
			CMP(R3, R0) //see if size if zero
			BZ(size_zero) //branch is the size is zero to the end of the function

			LOAD(R1, 0, R2) //putting next char into r1
			SET(R7, 32) //is space
			CMP(R7, R1)
			BZ(space_next)
			SET(R7, 43) //add
			CMP(R1, R7)
			BZ(add_op)
			SET(R7, 45) //sub
			CMP(R7, R1)
			BZ(sub_op)
			SET(R7, 42)//mult
			CMP(R7, R1)
			BZ(mult_op)
			SET(R7, 46) //.
			CMP(R7, R1)
			BZ(dot_op)
			SET(R7, 33) //! or .s
			CMP(R7, R1)
			BZ(dot_s_op)
			BR(push_op) //if integer branch to the instructions

			LABEL(add_op) //instructions of add
			CALL(R12, stack_add)
			INC(R2, 1)
			DEC(R3, 1)
			BR(start)

			LABEL(sub_op) //instructions if r1 is sub
			CALL(R12, stack_sub)
			INC(R2, 1)
			DEC(R3, 1)
			BR(start)

			LABEL(mult_op) //instructions if r1 is mult
			CALL(R12, stack_mult)
			INC(R2, 1)
			DEC(R3, 1)
			BR(start)

			LABEL(dot_op) //instructions if r1 is .
			CALL(R12, POP)
			INC(R2, 1)
			DEC(R3, 1)
			BR(start)

			LABEL(dot_s_op) //instructions if r1 is !
			CALL(R12, dot_s)
			INC(R2, 1)
			DEC(R3, 1)
			BR(start)

			LABEL(push_op) //instructions if r1 is an int
			SET(Rt, '0')
			SUB(R1, R1, Rt)
			CALL(R12, PUSH)
			INC(R2, 1)
			DEC(R3, 1)
			BR(start)

			LABEL(space_next) //instructions if r1 is a space
			INC(R2,1)
			DEC(R3, 1)
			BR(start)
			LABEL(size_zero)
			RETURN(R12, Rt)

      HALT()  // just cautious programming to make sure the program doesn't run straight into the library functions
//The following include is needed to use the hera 'print' function
#include <Tiger-stdlib-reg.hera>
}


