#ifndef _CHESS_H_
#define _CHESS_H_

#define SPEED 2
#include "state.h"

#define TIME_FOR_FUNNY 3000
#define EARLIEST_FUNNY 70000
class Funny:public Move{
public: 
	int where_x;
	int where_y;
	Funny(string robot, string space,int x, int y )
	{
		this->stringPrototype.push_back(robot);
		this->stringPrototype.push_back(space);
		where_x=x;
		where_y=y;
	}
	virtual bool usable(Item *item,unsigned int & order)
	{
		if(order==1)
		{
			if( static_cast<Space*>(item)->cargo!="p") return false;
		}
		return true;
	}
	virtual bool makeMove(vector<Item*> items,State &thatState){
			//robot bude brát
		if(thatState.time<EARLIEST_FUNNY) return false;
		if(thatState.distance(items[0]->x,items[0]->y, where_x, where_y)*SPEED+thatState.time > 90000-TIME_FOR_FUNNY) return false;
		thatState.reMoveItem(items[0]);
		thatState.lastMoves=thatState.lastMoves+" Funny "+items[1]->name;
		thatState.value=50;
		thatState.cmd= "funny";
		thatState.cmdX= where_x;
		thatState.cmdY= where_y;
		return true;
	}
};
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
				//prvek space je nepoužitelný pokud nemá místo pro pawn
			if( static_cast<Space*>(item)->cargo=="ppf") return false;
			if( static_cast<Space*>(item)->cargo=="pp") return false;

		}
		else if(order==1)
		{
			//ubdatovani pozice y
			item->mmToY();
			//zajimaji nas pouze objekty na chranenych plochach posledni rade 
			if (item->y==6 && item->valide==true);
			else return true;
			//a to v místech chránìných ploch
			item->mmToX();
			if (item->x==2 || item->x==3 || item->x==6 || item->x==7) return false;
			//
		}
		
		return true;
	}
		//metoda vykonávající tah
	virtual bool makeMove(vector<Item*> items,State &thatState)
	{
		if( static_cast<Space*>(items[2])->cargo!="" &&( items[1]->x < 560 ||items[1]->x >2440) ); return false;
			//pokud je uz v zasobniku jeden pawn tak se da pouze nabrat dalsi
		if (items[1]->name=="t")
		{
			static_cast<Space*>(items[2])->cargo=static_cast<tower*>(items[1])->tOfTower + static_cast<Space*>(items[2])->cargo;
		}
		else 
		{
			static_cast<Space*>(items[2])->cargo=items[1]->name + static_cast<Space*>(items[2])->cargo;
		}
		if( static_cast<Space*>(items[2])->cargo == "p");
		else if( static_cast<Space*>(items[2])->cargo == "pp");
		else if( static_cast<Space*>(items[2])->cargo == "f");
		else if( static_cast<Space*>(items[2])->cargo == "pf");
		else if( static_cast<Space*>(items[2])->cargo == "ppf");
		else return false;
	
		thatState.lastMoves=thatState.lastMoves+" take "+items[1]->name;//+(boost::str(boost::format("%1% %2%") % items[1]->x_mm % items[1]->y_mm));
		thatState.cmd= "take";
		thatState.cmdX= items[1]->x_mm;
		thatState.cmdY= items[1]->y_mm;
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
		thatState.time+=3000;
		thatState.value+=1;
		thatState.lastMoves=thatState.lastMoves+" w";
		thatState.cmd= "wait";
		thatState.cmdX= 0;
		thatState.cmdY= 0;
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
			if( static_cast<Space*>(item)->cargo=="") return false;
			
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
		if (static_cast<Space*>(items[1])->cargo=="p") newItem=new pawn();
		else if(static_cast<Space*>(items[1])->cargo=="f") newItem= new figure();
		else newItem=new tower( static_cast<Space*>(items[1])->cargo);
		//urèení polohy nového prvku
		if ( thatState.findFreeSpot( newItem->x,newItem->y, static_cast<robot*>(items[0]),'b') )
		{
			thatState.time=thatState.time+1000;//thatState.distance(items[0],newItem)*2;
			//cout<<thatState.distance(items[0],newItem);
			
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
		
		thatState.lastMoves=thatState.lastMoves+" put";//+(boost::str(boost::format("%1% %2%") % newItem->x_mm % newItem->y_mm));
		thatState.cmd= "put";
		thatState.cmdX= newItem->x_mm;
		thatState.cmdY= newItem->y_mm;
		if(thatState.time>90000) return false;
			//uvolnìní nákladu
		static_cast<Space*>(items[1])->cargo="";
		
		
		return true;		
	}
};


#endif