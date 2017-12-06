#include <iostream>
#include <cstdlib>  // for 'exit' function to abandon the program
#include <hc_list_helpers.h>
#include "parser.h"
#include "scanner.h"
#include <experimental/optional>
#include <string>

using std::string;
using HaverfordCS::list;
using HaverfordCS::ez_list;
using std::cout;
using std::cerr;
using std::endl;



// match this:
// START -> E   <followed by end-of-input>
// E -> number
// E -> identifier
// E -> ( E_IN_PARENS )
// E_IN_PARENS -> OP E E P
// E_IN_PARENS -> - E T
// P -> E P
// P -> (empty)
// OP --> +|*
// T --> E
//T --> e (empty)



// Declare all functions, so they can call each other in any order
//  (note: "static" means it's restricted to this scope, e.g. this file
static Tree matchE();
static Tree matchEInParens();
static string matchOp();


// FIRST and FOLLOW and NULLABLE sets for those,
//  built with lists rather than sets, for familiarity
//  defined in terms of kindOfToken from scanner-regexp.h
static list<kindOfToken> FIRST_OP  = ez_list(PLUS, TIMES);
static list<kindOfToken> FIRST_EIP = list<kindOfToken>(MINUS, FIRST_OP);
static list<kindOfToken> FIRST_E   = ez_list(INT, IDENTIFIER, LPAREN);
static list<kindOfToken> FIRST_T = FIRST_E;
//static list<kindOfToken> FIRST_MINUS = FIRST_E;
static list<kindOfToken> FIRST_P = FIRST_E;

//NULLABILITY: the set of productions that could generate empty
bool NULLABLE_OP = false;
bool NULLABLE_EIP = false;
bool NULLABLE_E = false;
bool NULLABLE_T = true;
bool NULLABLE_P = true;

static list<kindOfToken> FOLLOW_OP  = FIRST_E;
static list<kindOfToken> FOLLOW_EIP = ez_list(RPAREN);
static list<kindOfToken> FOLLOW_E   = /* append(FOLLOW_EIP, FIRST_E) */
		                              list<kindOfToken>(RPAREN, FIRST_E);
	                                  /* Dave should put "append" into list_helpers */
static list<kindOfToken> FOLLOW_T = ez_list(RPAREN);//list<kindOfToken>(EMPTY, FOLLOW_E);
static list<kindOfToken> FOLLOW_P = ez_list(RPAREN);


//if A-> NULL, PREDIT(A) = FIRST(A) U FOLLOW(A). Else, PREDICT(A) = FIRST_A
static list<kindOfToken> PREDICT_OP  = FIRST_OP;
static list<kindOfToken> PREDITCT_EIP = FIRST_EIP;
static list<kindOfToken> PREDICT_E   = FIRST_E;
static list<kindOfToken> PREDICT_T = list<kindOfToken>(RPAREN, FIRST_T); //FIRST_T U FOLLOW_T
static list<kindOfToken> PREDICT_P = list<kindOfToken>(RPAREN, FIRST_P);  //FIRST_P U FOLLOW_P

// first, a helpful function ---
//    we call this when we need to get more input,
//    i.e. when we want to move current_token along and end-of-input would be an error

void mustGetNextToken()
{
	getNextToken();
	if (!tokenAvailable()) {
		cerr << "unexpected end of input at token #" << tokenNumber() << endl;
		exit(5);
	}
}

// match a literal, assuming the token HAS been scanned already,
//  i.e. that "currentToken" is _on_ the literal we wish to match
// leave "currentToken" on the very last token of the matched pattern
static void confirmLiteral(string what)
{
	if (currentToken() != what) {
		cerr << "got " << currentToken() << " instead of " << what << " at token #" << tokenNumber() << endl;
		exit(2);
	}	
}


// match an "E", i.e, anything on the right hand side of any "E-->..." production
//  assume the first token of the E has been scanned
//   (i.e., assuming currentToken is the first token of the "E" we're matching)
//  leave "currentToken" on the very last token of the matched pattern
static Tree matchE()
{
	if (currentTokenKind() == INT) {
		// check to see if we're at the start of "E -> number"
	        return Tree(currentToken());	// we're already on the number, which is last token of the to-be-matched pattern "E"
	} else if (currentTokenKind() == IDENTIFIER) {	// check to see if we're at the start of "E -> identifier"
	    	return Tree(currentToken());	// we're already on the id, which is last token of the to-be-matched pattern "E"
	} else if (currentTokenKind() == LPAREN) {	// check to see if we're at the start of "E -> ( E_IN_PARENS )"
		confirmLiteral("(");
		mustGetNextToken();  // advance current token to be the operator, or fail if there isn't one
		Tree it = matchEInParens();
		// if that left off at the end of the E_IN_PARENS, we still need a ")" in the E we're matching
		confirmLiteral(")");
		return it;
	} else {				// if we're not in either of those "E -> " productions, we're in trouble :-(
		std::cerr << "Illegal token (" << currentToken() << ") at token #" << tokenNumber() << endl;
		exit(3);
	}
}
// match a "T", i.e, anything on the right hand side of any "T-->..." production
//  assume the first token of the T has been scanned and is an E or empty
//   (i.e., assuming currentToken is the first token of the "T" we're matching which is another E or empty)
//  leave "currentToken" on the very last token of the matched pattern so it isn't on the right paranthesis
//http://en.cppreference.com/w/cpp/utility/optional
static std::experimental::optional<Tree> matchT()
{
	if(find(currentTokenKind(), FIRST_E)){
		//check to see if first part of T-> which is E so first is either number, identifier or '('
		return matchE();
	}
	else if(find(currentTokenKind(), FOLLOW_E)){
		//check to see if it's empty then return nothing
		return std::experimental::nullopt;
	}
	else {				// if we're not in either of those "T -> " productions, we're in trouble :-(
		std::cerr << "Illegal token (" << currentToken() << ") at token #" << tokenNumber() << endl;
		exit(3);
	}

}
// match a "P", i.e, anything on the right hand side of any "P-->..." production
//  assume the first token of the P has been scanned and is an E followed by P again or empty
//   (i.e., assuming currentToken is the first token of the "P" we're matching so another E followed by P again which is another E or empty)
//  leave "currentToken" on the very last token of the matched pattern so it isn't on the right paranthesis
//allows for arity
static list<Tree> matchP(){ //post-order function of tree -- return a list of trees

	if(find(currentTokenKind(), FIRST_E)){
		Tree first = matchE();
		mustGetNextToken();
		list<Tree> it = list<Tree>(first, matchP());
		return it;
	}
	else if(find(currentTokenKind(), FOLLOW_E)){
		return ez_list(Tree(""));
	}
	else {				// if we're not in either of those "E -> " productions, we're in trouble :-(
			std::cerr << "Illegal token (" << currentToken() << ") at token #" << tokenNumber() << endl;
			exit(3);
		}
}
// match an "E_IN_PARENS",
//  assuming that the currentToken is at the start of the E_IN_PARENS, e.g. a "+"
//  leave the currentToken at the last part of what was matched,
//  i.e. *before* the ")" that should come after the E_IN_PARENS
static Tree matchEInParens() {

	if (find(currentTokenKind(), FIRST_OP)) {
		string theOp = matchOp();
		mustGetNextToken(); // get the first of the first E
		Tree firstChild = matchE();
		mustGetNextToken();  // get to first of the second E
		Tree secondChild = matchE();
		mustGetNextToken(); //get the first of the third E
		list<Tree> listOfTrees = matchP(); //many of the first of E
		listOfTrees = list<Tree>(secondChild, listOfTrees);
		listOfTrees = list<Tree>(firstChild, listOfTrees);

		return Tree(theOp, listOfTrees);
	}
	else if(currentTokenKind() == MINUS){
		string theOp = currentToken();
		mustGetNextToken(); //get the first of the first E
		Tree firstChild = matchE();
		mustGetNextToken(); //get the first of the second E
		Tree secondChild = matchT().value_or(Tree("")); //Tree of E or empty - which is Tree("")
		if(secondChild.value() != ""){
			mustGetNextToken(); //get the first of the third E which is the second number
			return Tree(theOp, ez_list(firstChild, secondChild));
		}
		//if secondChild is empty then don't get the next token so it is uninary
		return Tree(theOp, ez_list(firstChild, secondChild));



	}else {
		std::cerr << "Illegal token (" << currentToken() << ") at token #" << tokenNumber() << endl;
		exit(3);
	}
}


// match an operator, assuming that it is the currentToken
//  leave the currentToken at the last part of what was matched, i.e. unchanged
static string matchOp()
{
	// could do three cases here, but that's so tedious...
	assert (find(currentTokenKind(), FIRST_OP));
	return currentToken();
}


translatedResult matchStartSymbolAndEOF()
{
	getNextToken();
	if (!tokenAvailable()) {
		cerr << "Illegal end of input" << endl;
		exit(2);
	}

	Tree fullExpression = Tree(matchE());

	// now make sure there isn't anything else!
	getNextToken();
	if (tokenAvailable()) {
		cerr << "Warning: extra input after end: " << currentToken() << endl;
		exit (1);
	}

	return fullExpression;
}

