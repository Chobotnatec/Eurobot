
//posledn� editace 27.2 NO ISSUE

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
#include "server.h"
#include <sys/time.h>

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
	cout<<"nacteno...";
	
	char buffer[256];
	  State lastState=State();
	State newState=State();
	bool newS= false;
	stringstream converter;
	string converted;
	const int socket=init_socket();
	state_update(socket,"logic_online","true");

	while(1)
	{
		
		while(newS==false)
		{
			usleep(100000);
			if (state_query(socket,"end",buffer)==0)
			{
				stringstream converter;
				converter<<buffer;
				converter>>converted;
				if(converted=="true")
				{
					cout<<"konec programu"<<endl;
					return 0;
				}
			}

		    if(state_query(socket,"isNewState",buffer)==0)
			{
				stringstream converter;
				converter<<buffer;
				converter>>converted;
				if(converted=="true")
				{
					newS==true;
				}
			}
		}
			
		state_update(socket,"isNewState","false");
		if(state_query(socket,"newState",buffer)==0)
		{
			{
			stringstream converter;
			converter<<buffer;
			newState.loadFrom(converter);
			}
			lastState= myAlgorythm.find(newState,9000);

			state_update(socket,"cmd",lastState.cmd.c_str());
			stringstream converter;
			converter<<lastState.cmdX;
			converter>>converted;
			state_update(socket,"cmdX",converted.c_str());

			converter<<lastState.cmdY;
			converter>>converted;
			state_update(socket,"cmdY",converted.c_str());
			state_update(socket,"newTask","true");
		}

	}
}
		

		
		//if (konec=="konec") return 0;
		//cin>>konec;
		//origState=myAlgorythm.find(origState);
		//origState.writeOut();
		//cout<<myAlgorythm.way<<endl;
		//outState =myAlgorythm.find(outState);
		//outState.writeOut();
		//outState =myAlgorythm.find(outState);
		//outState.writeOut();
	
		//outState.writeToFile("ostate.txt");
		//cin>>konec;
	


