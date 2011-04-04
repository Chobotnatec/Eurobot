include <"Min_Max.cpp">

class node:state{
public:
	vector<node*>nodes;
	
	 ~node(void){
		for(vector<node*>::iterator it=nodes.begin(); it!=nodes.end(); it++){
			(*it)->~node();		

		}
	}
	void expand(moves* Moves){
		 vector<move>::iterator moveIt;
		 
	 
	 
	 }
	
};

class algorythm(){
	vector <move>;
	move* find.move(node initial Node){
		
		
	}

	
}
class max:algorythm{
	int points;
	findMax(int time,int depth,evalution* eval){	//rekurzivní algoritmus
		if (time<baseAlg->time ){

			
		}
		else if (depth==0){ 
			//return eval
		}
		else{
			
		}
	}

}
class game{
public:
	state actualState;
	int time;
	
	int maxTime;

	
	
	game(state InitialState,int MaxTime,char color){
		time=time(NULL);
		maxTime=time+1;
		actualState=InitialState;

	}
	
	state play(){
		while(maxTime<=time){
			actualState
		
		}
		
		cout<<"konec hry"<<endl;
		return: actualState;
	}
}

/*

main{	
	while(cin!)
	game=*(new game(state;90;));
	
	cout<<"type "go" for run<<endl;
	while( vstup!= "go"){

		
	}
	game.play();
	game.end;
	cin<<end;
}



*/
