#ifndef _ALGORYTHM_H
#define _ALGORYTHM_H

#include "chess.h"
#include "typeinfo"
using namespace std;

	//cilem tøídy je najít nejlepší tah
class Algorythm{
public:
	vector<Move*> moves;
	int highestEver;
	string way;
	
		//pøida jeden z možných tahù
	void loadMove(Move *moveToLoad)
	{
		for(unsigned int i=0; i<moves.size(); i++){
			if( typeid(moves[i])==typeid(*moveToLoad)) return;
		}
		moves.push_back(moveToLoad);
		cout<<"nacetly jste tah: "<<typeid(*moveToLoad).name()<<endl;
	}
		//odtraní jeden z možných tahù
	void deleteMove(string moveName)
	{
		for(unsigned int i; i<moves.size(); i++)
		{
			if(  (typeid(*(moves[i]))).name()==moveName)
			{
				moves.erase(moves.begin()+i);
			}
		}
	}
		//metoda vrátí všechny možné tahy
	vector<State> nextStates( State& origState)
	{	//cout<<"tahù:"<<this->moves.size()<<endl;
		//cout<<"finding next states"<<endl;
		vector<State> output;
		for(unsigned int i=0;i<moves.size();i++)
		{	
		//	cout<<"preotput :"<<i<<endl;
			vector<State> pOutput=moves[i]->makeAllMoves(origState);
		//	cout<<"prOUt size:"<<pOutput.size()<<endl;
			output.insert(output.end(),pOutput.begin(),pOutput.end());
		}
		
		return output;
	}
		//metoda vracející nejlepšího následníka
	virtual State find( State& origState){
		return origState;
	}




};
#define MAX_TIME 9000
class basicSearchAlgorythm: public Algorythm{
public:
	int timeLimit;
		//metoda vracející nejlepšího následníka
	virtual State find( State& originalState){
		highestEver=0;
		string way;
		cout<<"finding..."<<endl;
			//nejvyssi skore nasledniku
		int highestScore=-1;
			//index naslednika s nejvyšším skore
		int index=-1;
			//do jak velke budoucnosti se má predikovat
		this->timeLimit=originalState.time+MAX_TIME;
			//zajisteni ze se bude predikovat max do 90000ms
		if(this->timeLimit>90000) this->timeLimit=90000;
			//nalezeni nasledniku
		vector<State> naslednici=this->nextStates( originalState);
			//projdou se naslednici 
		for(unsigned int i=0; i<naslednici.size();i++)
		{	
			
			//naslednici[i].writeOut();
			//pokud neni naslednik za casovim limitem tak se na neho zavola metoda node
			if (naslednici[i].time<this->timeLimit){
					//node vraci score nejlepsi cesty
				int score=node(naslednici[i]);
				// cout <<" score: "<<score<<endl;
					//pokud je score vyssi nez nejvyssi doposud nalezene
				if (score>highestScore)
				{
					//ulozi se index score 
					highestScore=score;
					index=i;

				}
			}	
		}
			//pokud se nenalezl zadny naslednik vrati se samotny stav
		cout<< "index: "<< index <<endl;
		cout<< "highest score: "<<highestScore<<endl;
		if (index==-1)
		{
			
			return originalState;
		}
			//jinak se vrati nelepsi naslednik
		return naslednici[index];


		
	}
		//metoda vraci hodnotu nejlepsi ho naslednika ktereho nalezl
	int node( State& originalState)
	{
		
		int highestScore=NULL;
		vector<State> naslednici=this->nextStates( originalState);
		
		for(unsigned int i=0; i<naslednici.size();i++)
		{	
			//pokud naslednik nepøesáhl èasový limit
			if (naslednici[i].time<this->timeLimit){
				int score=node(naslednici[i]);
				if (score>highestScore)
				{
					highestScore=score;
				}
			}	
		}
		
		if (highestScore==NULL)
		{	//cout<<originalState.lastMoves;
			//cout<<" -end with:"<<originalState.utility('b')<<endl;
			if (originalState.utility('b')>highestEver)
			{
				this->highestEver=originalState.utility('b');
				this->way=originalState.lastMoves;
			}
			
			
			if(this->timeLimit>85000) return originalState.score('b');
			else return originalState.utility('b');
		}
		
		else
		{
			//cout<<"-backTrack"<<endl;
			return highestScore;
		}
		
	
	}


};



#endif