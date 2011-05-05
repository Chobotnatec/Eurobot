
//poslední editace 27.2 NO ISSUE

//#include "stdafx.h"
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
	






//int _tmain(int argc, _TCHAR* argv[])
int main(int argc, char* argv[])
{	
	State origState;
	
	basicSearchAlgorythm myAlgorythm;
	myAlgorythm.loadMove(new Take("y","f","s"));
	myAlgorythm.loadMove(new Take("y","p","s"));
	myAlgorythm.loadMove(new Take("y","t","s"));
	myAlgorythm.loadMove(new Funny("y","s",200,1900));
	//myAlgorythm.loadMove(new Wait("y"));
	myAlgorythm.loadMove(new Release("y","s"));
	
	istream* input=&cin;
	ostream* output=&cout;
	string konec="ahoj";
	cout<<"zdarec"<<endl;
	cout<<"loading..."<<endl;
	origState.loadFromFile("state.txt");
	origState.addItem(new Space());
	origState.writeOut();
	cout<<"naceteno... dej lib. vstup"<<endl;
	cin>>konec;
	while(1)
	{
		if (konec=="konec") return 0;
		origState=myAlgorythm.find(origState);
		origState.writeOut();
		cout<<myAlgorythm.way<<endl;
		//outState =myAlgorythm.find(outState);
		//outState.writeOut();
		//outState =myAlgorythm.find(outState);
		//outState.writeOut();
	
		//outState.writeToFile("ostate.txt");
		cin>>konec;
	}
}

