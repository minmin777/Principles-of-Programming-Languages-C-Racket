#include "test-tree.h"
#include <iostream>

using namespace std;

int main()
{
  if (tree_test() && treedemo()) {
    cout << "tree test looks  good" << endl;

    return 0;
  }
  /*if(treedemo()){
	  cout << "tree demo works wtf is happening" << endl;
  }*/
  else {
    cout << "Rats! Something wrong somewhere in tree test" << endl;
    return 1;
  }
}
