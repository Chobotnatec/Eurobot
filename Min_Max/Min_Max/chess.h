#ifndef _CHESS_H_
#define _CHESS_H_

#include "state.h"
class Take:public Move{
public:
	Take(string robot,string object,string space)
	{
		
		this->stringPrototype.push_back(robot);
		this->stringPrototype.push_back(object);
		this->stringPrototype.push_back(space);
	}
		//metoda pro urèení zda je tah možný
	virtual bool usable(Item *item,unsigned int & order)
	{
		if(order==2)
		{
			if( static_cast<Space*>(item)->pawnSpace==0) return false;
		}
		else if(order==1)
		{
			//ubdatovani pozice y
			item->mmToY();
			//zajimaji nas pouze objekty na chranenych plochach
			if (item->y==6 && item->valide==true);
			else return true;
			
			item->mmToX();
			if (item->x==2 || item->x==3 || item->x==6 || item->x==7) return false;
			//
		}
		return true;
	}
		//metoda vykonávající tah
	virtual bool makeMove(vector<Item*> items,State &thatState)
	{
			//pokud je uz v zasobniku jeden pawn tak se da pouze nabrat dalsi
		if (static_cast<Space*>(items[2])->pawnSpace==1)
		{		//pokud ibjekt neni pawn tah je nepripustny
			if (items[1]->name!="p") return false;
				//pokud je pawn tak se snizi pocet mist pro pawny na 0
			else static_cast<Space*>(items[2])->pawnSpace=0;
		}
			//pokud je v zasobiku pouze figura tak je mozno vzit jeden nebo dva pawny
		else if( static_cast<Space*>(items[2])->figureSpace==false)
		{
			if (items[1]->name=="p")
			{
				static_cast<Space*>(items[2])->pawnSpace=1;
			}
			else if (items[1]->name=="pp")
			{
				static_cast<Space*>(items[2])->pawnSpace=0; 
			}
			else return false;
		}
		else
		{
			for ( unsigned int i=0; i<items[1]->name.size(); i++)
			{
				if (items[1]->name[i]=='p')
				{
					static_cast<Space*>(items[2])->pawnSpace--;
				}
				else if (items[1]->name[i]=='q')
				{
					static_cast<Space*>(items[2])->figureSpace=0;
					break;
				}
				else if (items[1]->name[i]=='k')
				{
					static_cast<Space*>(items[2])->figureSpace=0;
					break;
				}
			}
		}	
			//vypocet trvani tahu;
		int time=thatState.distance(items[0],items[1])*2;
			//vypocet casove znamky noveho casu
		thatState.time=thatState.time+time;
			//tah je povolen jen pokud celkový èas nebude pod 90000ms
		if (thatState.time>=90000)
		{
			return false;
		}
			//premisteni robota
		items[0]->x=items[1]->x;
		items[0]->y=items[1]->y;
		items[0]->x_mm=items[1]->x_mm;
		items[0]->y_mm=items[1]->y_mm;
			 
		thatState.reMoveItem(items[1]);
		
		return true;
	}
	
};
	//tah èekání 1s
class Wait:public Move{
public:
	Wait(string robot)
	{
		this->stringPrototype.push_back(robot);	
	}
	virtual bool makeMove(vector<Item*> items, State& thatState)
	{
		thatState.time+=1000;
		return true;
	}
};
	//trida pohybu vysadi novy objekt na nejblizi volne misto v okoly robota	
class Release:public Move{
public:
		//metoda urcuje kdy se daný prvek bere v potaz
	virtual bool usable(Item *item,unsigned int & order)
	{
		if(order==1)
		{
			//ulozny prostor je nepozitelny pokud je  jsou dve mista pro pisky a jedno pro vezku
			if( static_cast<Space*>(item)->pawnSpace==2 && static_cast<Space*>(item)->figureSpace==true) return false;
			
		}
		return true;
	}
		//kostruktor nacte jmena objektu
	Release(string robot, string space)
	{   
		this->stringPrototype.push_back(robot);
		this->stringPrototype.push_back(space);
		
	}
		//metoda vykoná tah takový ze vypusti vezku na zadané místo
	virtual bool makeMove(vector<Item*> items, State& thatState)
	{
			//vežka kterou robot vypustí
		Item* newItem;
			//rozhodnoutí jakou vezku robot vypustí
			//pokud neni zadne misto jsou v robotovy dva pisci
			//tak se urcitì vypusti vezka
		if ( static_cast<Space*>(items[1])->pawnSpace==0 )
		{	
			newItem=new tower();
				//rozhodnuti zda bude na vezce figura nebo ne
			if( static_cast<Space*>(items[1])->figureSpace==false)
			{
				newItem->name="ppq";
			}
			else
			{
				newItem->name="pp";
			}
		}
			//pokud neni v robotu zadny pisek tak se vypusti jen figura
		else if ( static_cast<Space*>(items[1])->pawnSpace==2 )
		{	
				
			newItem=new figure();
			newItem->name="q";
		}
			//jinak je tedy v robotu jeden pisek 
		else
		{
			if ( static_cast<Space*>(items[1])->figureSpace==false ) 
			{
				 newItem=new tower();
				 newItem->name="pq";
			}
			else 
			{
				newItem=new pawn();
				newItem->name="p";
			}
		}
		//urèení polohy nového prvku
		if ( thatState.findFreeSpot( newItem->x,newItem->y, static_cast<robot*>(items[0]),'b') )
		{
			thatState.time=thatState.time+thatState.distance(items[0],newItem)*2;
			items[0]->x=newItem->x;
			items[0]->x=newItem->y;
			items[0]->xToMm();
			items[0]->yToMm();
			newItem->xToMm();
			newItem->yToMm();


		}
		else 
		{
			return false;
		}
		thatState.addItem(newItem);
		
		if(thatState.time>90000) return false;
		return true;		
	}
};


#endif