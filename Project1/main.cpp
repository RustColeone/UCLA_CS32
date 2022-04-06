#include "History.h"
	#include "Mesa.h"
	#include <iostream>
	using namespace std;

	int main()
	{
	    Mesa m(1, 3);
	    m.history().record(1, 2);
	    Mesa m2(1, 2);
	    m2.history().record(1, 1);
	    m.history().display();
	    cout << "===" << endl;
	}