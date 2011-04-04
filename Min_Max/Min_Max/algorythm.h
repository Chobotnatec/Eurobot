#ifndef _ALGORYTHM_H
#define _ALGORYTHM_H

#include "chess.h"
#include "typeinfo"
using namespace std;

	//cilem tøídy je najít nejlepší tah
class Algorythm{
public:
	vector<Move*> moves;
	
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
	{
		vector<State> output;
		for(unsigned int i=0;i<moves.size();i++)
		{	
			vector<State> pOutput=moves[i]->makeAllMoves(origState);
			output.insert(output.end(),pOutput.begin(),pOutput.end());
		}
		return output;
	}
		//metoda vracející nejlepšího následníka
	virtual State find( State& origState){
		return origState;
	}




};
class basicSearchAlgorythm: public Algorythm{
	int timeLimit;
		//metoda vracející nejlepšího následníka
	virtual State find( State& originalState){
			//nejvyssi skore nasledniku
		int highestScore=NULL;
			//index naslednika s nejvyšším skore
		int index=NULL;
			//do jak velke budoucnosti se má predikovat
		this->timeLimit=originalState.time+5000;
			//zajisteni ze se bude predikovat max do 90000ms
		if(this->timeLimit>90000) this->timeLimit=90000;
			//nalezeni nasledniku
		vector<State> naslednici=this->nextStates( originalState);
			//projdou se naslednici 
		for(unsigned int i=0; i<naslednici.size();i++)
		{	
			//pokud neni naslednik za casovim limitem tak se na neho zavola metoda node
			if (naslednici[i].time<this->timeLimit){
					//node vraci score nejlepsi cesty
				int score=node(naslednici[i]);
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
		if (index==NULL) return originalState;
			//jinak se vrati nelepsi naslednik
		return naslednici[index];



	}
		//metoda vraci hodnotu nejlepsi ho naslednika ktereho nalezl
	int node( State& originalState){
		
		int highestScore=NULL;
		vector<State> naslednici=this->nextStates( originalState);
		for(unsigned int i=0; i<naslednici.size();i++)
		{
			if (naslednici[i].time<this->timeLimit){
				int score=node(naslednici[i]);
				if (score>highestScore)
				{
					highestScore=score;
				}
			}	
		}
		if (highestScore==NULL)
		{
			if(this->timeLimit>85000) return originalState.score('b');
			else return originalState.utility('b');
		}
		else return highestScore;
	
	}


};



#endif