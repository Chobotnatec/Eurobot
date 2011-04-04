
//poslední editace 27.2 NO ISSUE

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <sstream>
#include <time.h>
#include <cmath>
#include "chess.h"
#include "algorythm.h"
using namespace std;
	



class BadAlgorythm:public Algorythm{
	//funkce najde nejkratsi cestu jak pozbirat prvky

};


int _tmain(int argc, _TCHAR* argv[])
{	
	State origState;
	
	basicSearchAlgorythm myAlgorythm;
	myAlgorythm.loadMove(new Take("y","p","s"));
	myAlgorythm.loadMove(new Wait("y"));
	myAlgorythm.loadMove(new Release("y","s"));
	istream* input=&cin;
	ostream* output=&cout;
	string konec="ahoj";
	
	while(1)
	{
		while(konec!="NEW_STATE")
		{
			if (konec=="END") return 1;
		}
		origState.loadFrom( *input);
		myAlgorythm.find(origState).writeToFile("ostate.txt");
		
	}
}

