#ifndef _CHESS_items_H_
#define _CHESS_items_H_


#include "item.h"

class robot: public Item{
public:
	int team;
	int orientation;	
	string content;
	robot(){
	orientation=0;
	}
	robot(vector<string>::iterator &itPoint){	//ukazatel na iterator do pole stringu;
		Constr(itPoint);
		value=0;
		istringstream (*itPoint)>>orientation;
		itPoint=itPoint+1;
	}
	virtual void writeTo(ostream& vystup){
		Item::writeTo(vystup);
		vystup<<" "<<this->orientation<<" "<<this->content;
	}
	void writeOutItem(void){
		Item::writeOutItem();
		cout<<" orientace: "<<orientation<<" uvnitø je:"<<content<<endl;
	}
	virtual Item* copy(void){
		robot* output=new robot();
		*output=*this;
		return output;
	}
};

class pawn: public Item{
public:
	pawn(){};
	pawn(vector<string>::iterator &itPoint){	//ukazatel na iterator do pole stringu;
		Constr(itPoint);
		value=10;
	}
	virtual void writeTo(ostream &vystup){
		Item::writeTo(vystup);
	}
	virtual Item* copy(void){
		 pawn* output=new pawn();
		*output=*this;
		return output;
	}
};
class tower: public Item{
public:
	string tOfTower;
	tower(){};
	tower(vector<string>::iterator &itPoint){	//ukazatel na iterator do pole stringu;
		this->tOfTower=(*itPoint);
		Constr(itPoint);
		
	}
	  virtual void writeTo(ofstream &vystup){
		Item::writeTo(vystup);
	}
	  void writeOutItem(void){
		Item::writeOutItem();
		cout<<" slozeni: "<<tOfTower<<endl;
	}
	int points(void){
		if (valide==false) return 0;
		if (tOfTower=="ppk")return 90;
		else if (tOfTower=="pk") return 60;
		else if (tOfTower=="ppq") return 60;
		else if (tOfTower=="pq") return 40;
		else return 10;
	}
	virtual Item* copy(void){
		 tower* output=new tower();
		*output=*this;
		return output;
	}
};
class figure: public Item{
public:
	figure(vector<string>::iterator &itPoint){	//ukazatel na iterator do pole stringu;
		Constr(itPoint);	
	}
	 virtual void writeTo(ostream vystup){
		Item::writeTo(vystup);
	}
	 figure(void){
	 }
	 virtual Item* copy(void){
		 figure *output=new figure();
		*output=*this;
		return output;
	}
};
class king: public figure{
public:
	king(void){
	value=30;
	}
	virtual Item* copy(void){
		 king *output=new king();
		*output=*this;
		return output;
	}
};
class queen: public figure{
	queen(void){
	value=20;
	}
	virtual Item* copy(void){
		 queen *output=new queen();
		*output=*this;
		return output;
	}
};
class Space:public Item{
public:	
	int pawnSpace;
	bool figureSpace;
	Space(){
		pawnSpace=2;
		figureSpace=false;
	}
	virtual Item* copy(void)
	{
		return new Space(*this);
	}
};

#endif