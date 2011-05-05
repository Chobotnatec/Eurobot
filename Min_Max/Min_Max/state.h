#ifndef _STATE_H
#define _STATE_H

#include "chess_items.h"

class State{
public:
//ATRIBUTY:
		//hodnotat utilitarni funkce toho stavu
	int value; 
		//time stamp of State
	int time; 
		//nejvyssi ID objektu
	int highestID;
		//nejvyssi ID tridy
	int highestGroupID;
		//pocet skupin prvku
	int numOfGroups;
		//pocet prvku ve stavu
	int numOfitems;
	string lastMoves;
	string cmd;
	int cmdX;
	int cmdY;
		//vektor obsahuje vsechny prvky stavu ve vektorech podle skupin
	vector<vector<Item*> > items; 
		//obsahuje nazvy jednotlivych skupin objektu
	vector<string> groups; 
//METODY:
			//vypise vsechny objekty ve stavu na std vystup
	void writeOut(void)
	{		
		vector<vector<Item*> >::iterator outerIt;	//iterator na skupiny objektù;
		vector<Item*>::iterator innerIt; //iterator na objekty 

		cout<< endl <<"    vypisuji stav:" << endl;
		cout<< "value: " << this->value << endl;	//vypsani stavovych hodnot stavu
		cout<< "time:" << this->time << endl;
		cout<< "highestID: " << this->highestID << endl;
		cout<< "highestgroupID: " << this->highestGroupID << endl;
		cout<< "numOfGroups: " << this->numOfGroups << endl;
		cout<< "numOfitems: " << this->numOfitems << endl;
		cout<< "groups: " <<endl;
		cout<< "predesle tahy: "<<lastMoves <<endl;
		for (unsigned int i=0; i<this->groups.size(); i++)
		{
			cout << "  " << this->groups[i];
		}
		cout<< endl;
		cout<< "items:" <<endl;
		for( outerIt= items.begin(); outerIt!= items.end(); outerIt++){
			
			for( innerIt= outerIt->begin(); innerIt!= outerIt->end(); innerIt++){
				(*innerIt)->writeOutItem();
			}
		}
		cout << endl;
	}				
			//vraci vektor vsech ukazatelù na objekty daneho typu
	vector<Item*> ReturnGroup( string groupName)
	{
		vector<vector<Item*> >::iterator groupIt;
		
		for (unsigned int i=0;i<this->items.size(); i++){
			if (groups[i]==groupName) return items[i];
		}
		vector<Item*> ret;
		return ret;
	
	}
			//vraci vektor vsech prvkù skupiny-podle groupID
	vector<Item*> ReturnGroup(int groupID)
	{
		return this->items[groupID];
	}
			//prida prvke mezi ostatni prvky
	void addItem(Item *newItem)
	{
			//prideli ID
		(this->highestID)++;			
		newItem->ID= this->highestID;
				//projdou se vsechny duhy objektù jestli odpovidaji zadanemu
		for ( unsigned int i=0 ; i<items.size(); i++)
		{	
			if (groups[i]==newItem->name)
			{
				newItem->groupID=i;	//nastaveni group ID podle mista kam je prvek zarazen
				newItem->groupPlace=items[i].size();//nastaveni group place-prvek byl dodan na konec
				items[i].push_back(newItem);
				//cout<<"succes"<<endl;
				
				return;
			}
		}
				//pokud neodpovida zadna skupina pak se vytvori nova
		
		newItem->groupID= items.size();	//prirazeni group ID 
		items.push_back(vector<Item*>());
		newItem->groupPlace= (items.end()-1)->size();	//prirazeni ob
		(items.end()-1)->push_back(newItem);
		this->groups.push_back(newItem->name);
		//cout<<"succes-new line"<<endl;
		this->highestGroupID++;
		
		
	}
		//vrati vzdalenost mezi dvema prvky v mm
	virtual int distance(Item* from,Item* to){
		return (int)sqrt((double)(from->x_mm * from->y_mm + to->x_mm * to->y_mm));
	}
		//vrati vzdlaenost mezi dvema body
	virtual int distance(int x1, int y1, int x2, int y2)
	{
		return (int)sqrt((double)(x1 * y1 + x2 * y2));
	}
		//odstrani prvek z items a upravi odpovidajici indexy
	void reMoveItem(Item *reMoveThis)
	{	
		items[reMoveThis->groupID].erase(items[reMoveThis->groupID].begin()+reMoveThis->groupPlace);//odsran prvek ze items
		for (unsigned int j=reMoveThis->groupPlace; j<items[reMoveThis->groupID].size(); j++)	//uprav vsem prvkùm za nim index place;
		{
			(items[reMoveThis->groupID][j]->groupPlace)--;		//vsem prvkùm dekrementuj index "place" o jedna
		}
		
	}
		//ulozi stav do zadaného souboru;
	void writeToFile(char* file){
		//cout<<"ukladam do souboru"<<endl;

		ofstream output(file,ios_base::app);
		vector<Item*>::iterator innerIt;
		vector<vector<Item*> >::iterator outerIt;
		output<<"0";	//nula na zacatku formatu
		for (outerIt=items.begin(); outerIt!= items.end(); outerIt++){
			
			for( innerIt=outerIt->begin(); innerIt!=outerIt->end(); innerIt++){
				(*innerIt)->writeTo(output);
			}
		}
		output<<endl;
		output.close();
	}
		//uloží stav do zadaného proudu;
	void writeTo(ostream& output){
		vector<Item*>::iterator innerIt;
		vector<vector<Item*> >::iterator outerIt;
		output<<"0";	//nula na zacatku formatu
			//pro každý objekt zavolá metodu writeTo(ostream &)
		for (outerIt=items.begin(); outerIt!= items.end(); outerIt++){
			
			for( innerIt=outerIt->begin(); innerIt!=outerIt->end(); innerIt++){
					//volani vypisovaci funkce
				(*innerIt)->writeTo(output);
			}
		}
		
	}
	int utility(char color)
	{
		//cout<<"u";
	
		this->getConsistent();
		int utilityValue=0;
		for( vector<vector<Item*> >::iterator outerIt =this->items.begin(); outerIt != this->items.end(); outerIt++)
		{
			for(vector<Item*>::iterator innerIt = outerIt->begin(); innerIt != outerIt->end(); innerIt++){
				//if((*innerIt)->valide==true &&  true /*color == (*innerIt)->color*/)
				//{
					utilityValue+= (*innerIt)->getValue('u');					
					
				//}
			}
		}
		utilityValue+= this->value;
		return utilityValue;
	}
	int score(char color)
	{
		//cout<<"s";
		this->getConsistent();
		int utilityValue=0;
		for( vector<vector<Item*> >::iterator outerIt =this->items.begin(); outerIt != this->items.end(); outerIt++)
		{
			for(vector<Item*>::iterator innerIt = outerIt->begin(); innerIt != outerIt->end(); innerIt++){
				if((*innerIt)->valide==true && true /*color == (*innerIt)->color*/)
				{
					utilityValue+= (*innerIt)->getValue('s');					

				}
			}
		}
		return utilityValue;
	}
		//pro všechny prvky  
	void getConsistent()
	{
		for( vector<vector<Item*> >::iterator outerIt =this->items.begin(); outerIt != this->items.end(); outerIt++)
		{
			for(vector<Item*>::iterator innerIt = outerIt->begin(); innerIt != outerIt->end(); innerIt++){
			(*innerIt)->mmToX(); 
			(*innerIt)->mmToY();
			(*innerIt)->isValide();
			
			}
		}
	}
		//najde neblisi volne misto k objektu
	bool findFreeSpot(int &X,int &Y, robot* rob,char color )
	{	
		this->getConsistent();
		//aktualizujisi souradnice;
		rob->mmToX();
		rob->mmToY();
		
		
		//promena uklada nejmensi vzdalenost k nalezenemu prvku
		int minAbs=12;
		//prochazi se mista v okoly robota
		for(int _x=-5; _x<5; _x++)
		{
			for(int _y=-5; _y<5; _y++)
			{
				//pokud pole se posuzuje pouze pokud má zprávnou bravu
				if (  ((_x+_y+rob->x+rob->y)%2==0 && color=='b' ) || ((_x+_y+rob->x+rob->y)%2==1 && color=='r' ) )
				{
					if( rob->x+_x<=0 || rob->x+_x>=7);
					else if( rob->y+_y<=0 || rob->y+_y>=7);
					else if (  abs( _x)+abs( _y) <minAbs)
					{
							//zkontroluj jeli pole volne
						if (this->checkIfFree(rob->x+_x,rob->y+_y)==true )
						{
								//pokud je pole volne tak ho dej jako vystup;
							X=rob->x+_x;
							Y=rob->y+_y;
							minAbs=abs(_x)+abs(_y);
						}		
					}
				}
			}

		}
			//pokud bylo nalezeno volne pole v okoli tak vrat true 
		if (minAbs<12) return true;
			//jinak false
		else return false;
	
	}
		//zkontroluje zda je zadane pole volne
	bool checkIfFree( int X, int Y)
	{
		//projde vsechny prvky a zkontroluje zda nejsou na zadaném místì
		for(unsigned int i=0; i<this->items.size(); i++)
		{
			for(unsigned  int j=0; j<this->items[i].size(); j++)
			{
					//pokud je objekt na místì je validní a je neprùchozí tak metoda vrátí false
				if( this->items[i][j]->valide==true && this->items[i][j]->unpassable==true && this->items[i][j]->x==X && this->items[i][j]->y==Y)
				{
					return false;
				}
			}
		}

		return true;
	}
		//metoda identifikuje prvek 
		//TODO vysledná metoda musí pracovat puze s Item aby bylo roèníkovì nezávyslé
	virtual Item* identifyItem(vector<string>::iterator &stringIt)
	{
		if (*stringIt=="p")return new pawn(stringIt);
		if (*stringIt=="q"||*stringIt=="k") return new figure(stringIt);	
		if (*stringIt=="y") return new robot(stringIt);
		if (*stringIt=="e") return new robot(stringIt);
		if (*stringIt=="s") return new Space();
		if (*stringIt=="f") return new figure(stringIt);
		if (*stringIt=="t") return new tower(stringIt);
		
		return NULL;
	}
		//naète stav z vstupního proudu
	void loadFrom(istream &handle)
	{
		string line;
		vector<string> strs;

		for(unsigned int i=0; i<items.size(); i++)	//smazani starych prvkù skupiny prvkù ale zùstavaji
			{
				items[i].clear();
			}
			State::highestID=0;
			for(int i=0;i<1;i++) {
				while(handle.good()) {
					getline(handle, line);
					boost::split(strs, line, boost::is_any_of(" "));
	
					if(strs.size() > 2) 
					{
						vector<string>::iterator strsIt=strs.begin();
						int vstup=0;
						string sVstup;
						while (strs.end()> strsIt)
						{
							if(istringstream (*strsIt)>>vstup )
							{  //pokud se jedna o cislo
							strsIt++; //jedna  se o neocekavany vstup proto posune o jeden string do prava
							cout<<"CHYBA-chyba formatu, neocekavany int/informace navic:"<<vstup<<endl;
							}
						
							else
							{	
							Item *newItem=identifyItem(strsIt);
							if(newItem!=NULL) addItem(newItem);
							}
						}
						cout<<"nacetl jsem cely vektor objektu"<<endl;
					}
					strs.clear();
				}
				
				handle.clear();
			}
		
	}
		// nahraje stav ze souboru State.txt
	void loadFromFile(char *out){
		string line;
		vector<string> strs;
	
		ifstream handle(out); //otevre soubor
		if(handle.is_open()) {			//pokud je otevren
			for(unsigned int i=0; i<items.size(); i++)	//smazani starych prvkù skupiny  ale zùstavaji
			{
				items[i].clear();
			}
			State::highestID=0;
			for(int i=0;i<1;i++) {
				while(handle.good()) {
					getline(handle, line);
					boost::split(strs, line, boost::is_any_of(" "));
	
					if(strs.size() > 2) 
					{
						vector<string>::iterator strsIt=strs.begin();
						int vstup=0;
						string sVstup;
						while (strs.end()> strsIt)
						{
							if(istringstream (*strsIt)>>vstup )
							{  //pokud se jedna o cislo
								strsIt++; //jedna  se o neocekavany vstup proto posune o jeden string do prava
								cout<<"CHYBA-chyba formatu, neocekavany int/informace navic:"<<vstup<<endl;
							}
							else
							{	
								//identifyItem identifikuje objekt 
								Item *newItem=identifyItem(strsIt);
								//pokud se to povede tak ho pøidej mezi prvky
								if(newItem!=NULL) addItem(newItem);
							}
						
						}
						cout<<"nacetl jsem cely vektor objektu"<<endl;
					}
					strs.clear();
					
				}
				
				handle.clear();
			}
			handle.close();
			
		} 
		else 
		{
			cout << "There is no State file in current directory" << endl;
		}
		this->getConsistent();
	}
		//zakladni konstruktor stavu bez prvku
	State(){
		
		value=0;
		time=0; 
		highestID=0;
		highestGroupID=0;
		numOfGroups=0;
		numOfitems=0;
		this->lastMoves=" ";
	}
		//kopirovaci konstruktor vytvori kopie vsech objektu ve stavu
	State(const State &original)
	{
		this->value=original.value;
		this->time=original.time;
		this->highestID=original.highestID;
		this->highestGroupID=original.highestGroupID;
		this->numOfGroups=original.numOfGroups;
		this->numOfitems=original.numOfitems;
		this->lastMoves=original.lastMoves;
		this->items.clear();
		this->groups.clear();
		for(unsigned int i=0; i<original.items.size(); i++)
		{
			this->items.push_back(vector<Item*>());
			for( unsigned int j=0; j<original.items[i].size(); j++)
			{	

				this->items[i].push_back(original.items[i][j]->copy());
				
			}
		}
		for (unsigned int i=0; i<original.groups.size(); i++)
		{
			this->groups.push_back(original.groups[i]);
		}
		

	}
		//pretizeny operator '=' vytvori kopie vsech objektu ve stavu
	State operator=(const State &original)
	{
		this->value=original.value;
		this->time=original.time;
		this->highestID=original.highestID;
		this->highestGroupID=original.highestGroupID;
		this->numOfGroups=original.numOfGroups;
		this->numOfitems=original.numOfitems;
		this->items.clear();
		this->groups.clear();
		//this->lastMoves=original.lastMoves;
		for(unsigned int i=0; i<original.items.size(); i++)
		{
			this->items.push_back(vector<Item*>());
			for( unsigned int j=0; j<original.items[i].size(); j++)
			{	

				this->items[i].push_back(original.items[i][j]->copy());
				
			}
		}
		for (unsigned int i=0; i<original.groups.size(); i++)
		{
			this->groups.push_back(original.groups[i]);
		}
		return original;
	}
		//destruktor uvolni pamet vsech objektu
	~State(){
		for(unsigned int i=0; i<items.size(); i++)
		{
			for(unsigned int j=0; j<items[i].size(); j++)
			{
				delete items[i][j];	//uvolni pamet na kterou ukazuje ukazatel v items[i][j];
			}
		}
		
	}
	
};
	//trida Move umoznuje popsat tah pomoci metody  "bool makeMove(vector<*item>,state&)"
class Move{
public:
//ATRIBUTY:
		//vektor prototypy tahu, jako string
	vector<string> stringPrototype;
	
//METODY:
		//metoda slouží k ohodnocení prvku zda je použitelný pro aplikaci 
	virtual bool usable(Item* item,unsigned int &order){
			//pokud není definováno jinak, tak jsou vsechny prvky použitelné
		return true;
	}
		//tato metoda od sebe odlisuje jednotlive potomky Move
		//vraci hodnotu zda je tah pripustny
	virtual bool makeMove(vector<Item*>,State&)=0;	
	
		
		//tado medota vraci vsechny mozne aplikace tahu na dany stav
	vector<vector<Item*> > findAplications( State &origState)
	{
		//cout<<"finding all aplications"<<endl;
			//skupiny nalezenych prvkù
		vector<vector<Item*> > orderedItems;	
			//iterator najednotlive skupiny nalezenych prvku
		//vector<vector<Item*> >::iterator orderedItemsIt;	
			//iteratory do jednotlivych skupin
		
		vector<unsigned int> indexes;
			//iterator do vektoru iteratorù do skupin
		//vector<vector<Item*>::iterator>::iterator iteratorsIt;
		
			//iterator do prototypu tahu
		//vector<string>::iterator prototypeIt;
			//vysledny vektor moznych aplikaci tahu na stav
		vector<vector<Item*> > output;	
			//pocet aplikaci
		signed int numOfAplications=1;

		for(unsigned int i=0; i<stringPrototype.size(); i++)	
		{
				//nalezne skupiny vhodnych prvkù
			vector<Item*> newLine=( origState.ReturnGroup(stringPrototype[i]));	
			
				//vlozi iterator na nalezenou skupinu prvku
			orderedItems.push_back(vector<Item*>());
			
			for(unsigned int j=0; j<newLine.size(); j++)
			{

				if(this->usable(newLine[j],i)==true )
				{
					(orderedItems.end()-1)->push_back(newLine[j]);
				
				}
				
			}

			indexes.push_back(0);
				//pocita pocet prvkù kartezkeho soucinu jednotlivych aplikaci=pocet aplikaci
			numOfAplications=numOfAplications*( (orderedItems.end()-1)->size());	
		}
		

		//cout<<"pocet nalezenych aplikaci: "<<numOfAplications<<endl;
			//opakuj podle poctu aplikaci
		//for(unsigned int i=0; i<orderedItems.size(); i++)
		//{ 
			//cout<<"GROUP: "<<endl;
		//	for( unsigned int j=0; j<orderedItems[i].size(); j++)
		//	{
			//	orderedItems[i][j]->writeOutItem();		
		//	}
		//	cout<<endl;
		//}
		for(;numOfAplications!=0;numOfAplications--)		
		{
				//pridej aplikaci
			output.push_back( vector<Item*>());				
				//ciklus generuje vsechny mozne aplikace 
			for( unsigned int i=0; i<indexes.size(); i++)
			{
					//pokud aktualni iterator ukazuje na konec mu prislusneho pole
				if ( indexes[i]==orderedItems[i].size())
				{
					indexes[i]=0;
					if( i+1<indexes.size()) indexes[i+1]++;
				}
				output[output.size()-1].push_back(orderedItems[i][indexes[i]]);
			}
				//nejnizsi index
			indexes[0]++;
		}
		//cout<<endl<<"FINDED APLICATIONS:"<<endl;
		//for(unsigned int i=0; i<output.size(); i++)
		//{ 
			//cout<<"APLICATION: "<<endl;
			//for( unsigned int j=0; j<output[i].size(); j++)
			//{
		//		output[i][j]->writeOutItem();	
		//	}
		//	cout<<endl;
		//}
			//vrat vysledny vektor aplikaci
		return output;
	};
		//vrati stav pro vsechny aplikace tahu 
	vector<State> makeAllMoves( State &origState)	
	{	
			//iterator na jednotlive aplikace tahu
		vector<vector<Item*> >::iterator itAplication;
			//iterator do vnitrku jednotlivych aplikaci
		vector<Item*>::iterator innerIt; 
			//vysledny vektor stavù
		vector<State> output;	
		
			//na originalnim stavu nalezne vsechny aplikace
		vector<vector<Item*> > aplications=findAplications(origState); 
		
			//pro kazdou aplikaci
		//cout<<"APLICAIIONS"<<endl;
		//for (unsigned int inn=0; inn<aplications.size(); inn++)
		//{
		//	cout<<"APLIKACE:"<<endl;
		//	for(unsigned int outt=0; outt<aplications[inn].size(); outt++)
		//	{
		//		 (aplications[inn][outt]->writeOutItem());
		//	}
		//	cout<<endl;
		//	cout<<endl;
		//}
		//string haluz;
		//cin>>haluz;
		for(unsigned int itAplication=0; itAplication<aplications.size(); itAplication++)	
		{
				//vytvor stejny stav jako pùvodni a pridej ho na vystup
			output.push_back(origState);	
				//pro kazdy prvkek aplikace
			//cout<<"APLICATION LOOP"<<endl;
			for(unsigned int innerIt= 0; innerIt < aplications[itAplication].size(); innerIt++)	
			{
					//prestavi ukazatele do noveho stavu
				//(*innerIt)=(output.end()-1)->items[(*innerIt)->groupID ][ (*innerIt)->groupPlace ];
				//cout<<"BEFORE LOOP:"<<endl;
				//cout<<"groupID: "<<aplications[itAplication][innerIt]->groupID<<endl;
				//cout<<"name:"<<aplications[itAplication][innerIt]->name<<endl;
				//cout<<"groupPlace: "<<aplications[itAplication][innerIt]->groupPlace<<endl;
				//(output.end()-1)->writeOut();
				aplications[itAplication][innerIt]=(output.end()-1)->items.at(aplications[itAplication][innerIt]->groupID).at(aplications[itAplication][innerIt]->groupPlace);
				//string in;
				//cout<<"AFTER LOOP"<<endl;
				//cin>>in;
			}
			//cout<<"APLICATION LOOP END"<<endl;
				//proved tah na aplikaci
			if (false==makeMove(aplications[itAplication],*(output.end()-1)))
			{	
				//pokud tah vrati false tak ho odstran stav z vystupu
				output.pop_back();		
			//	cout<<"nepovoleny tah"<<endl;
			}
			else 
			{
			//cout<<"tah proveden"<<endl;
				
			}
		}	
			//vrat vsechny nalezene stavy
		return output;
	}

};

#endif 