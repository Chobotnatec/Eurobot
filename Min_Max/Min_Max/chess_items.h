#ifndef _CHESS_items_H_
#define _CHESS_items_H_


#include "item.h"

class robot: public Item{
public:
	int team;
	string content;
	int orientation;	
	
	robot()
	{
	orientation=0;
	this->value=0;
	this->name="e";
	this->unpassable=false;
	}
	robot(string name)
	{
		this->name=name;
		this->value=0;
		this->unpassable=false;
	}
	
	robot(vector<string>::iterator &itPoint){	//ukazatel na iterator do pole stringu;
		Constr(itPoint);
		value=0;
		istringstream (*itPoint)>>orientation;
		itPoint=itPoint+1;
		this->unpassable=false;
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
	pawn()
	{
		this->name="p";
		this->value=10;
	};
	pawn(vector<string>::iterator &itPoint){	//ukazatel na iterator do pole stringu;
		Constr(itPoint);
		this->value=10;
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
	tower(){
		this->name="t";
		this->tOfTower="d";
	}
	tower(string tower){
		this->name="t";
		this->tOfTower=tower;
		
	}
	tower(vector<string>::iterator &itPoint){	//ukazatel na iterator do pole stringu;
		this->tOfTower=(*itPoint);
		
		name="t";
		istringstream (*(itPoint+1))>>this->x_mm;
		istringstream (*(itPoint+2))>>this->y_mm;
		this->mmToX();
		this->mmToY();
		this->tOfTower=*(itPoint+3);
		itPoint=itPoint+4;
		valide=this->isValide();
		
	}
	  virtual void writeTo(ofstream &vystup){
		Item::writeTo(vystup);
	}
	  void writeOutItem(void){
		Item::writeOutItem();
		cout<<" slozeni: "<<tOfTower<<endl;
	}
	int getValue(char flag){
		
		if (tOfTower=="ppk")return 90;
		else if (tOfTower=="pk") return 60;
		else if (tOfTower=="ppq") return 60;
		else if (tOfTower=="pq") return 40;
		else if (tOfTower=="ppf") return 75;
		else if (tOfTower=="pf") return 50;
		
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
		 this->name= "f";
		 this->value= 25;
	 }
	 virtual Item* copy(void){
		 figure *output= new figure();
		*output= *this;
		return output;
	}
};
class king: public figure{
public:
	king(void){
	this->name="k";
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
	this->name="q";
	value=20;
	}
	virtual Item* copy(void){
		 queen *output=new queen();
		*output=*this;
		
		return output;
	}
};
class Space:public Item
{
public:	
	
	string cargo;
	Space(){
		value=0;
		this->name="s";
		cargo="";
		
		
	}
	virtual Item* copy()
	{
		return new Space(*this);
	}
	void writeOutItem()
	{
		cout<<"ID:"<<this->ID<<" name:"<<this->name<<" gr-ID: "<<this->groupID<<" cargo:"<<cargo<<endl;
	
	}
	int getValue(char flag){	
		if (flag=='u')
		{
			if (cargo=="ppk")return 80;
			else if (cargo=="pk") return 50;
			else if (cargo=="ppq") return 50;
			else if (cargo=="pq") return 30;
			else if (cargo=="ppf") return 60;
			else if (cargo=="pf") return 40;
			else if (cargo=="p") return 6;
			else if (cargo=="pp") return 12;
			else return 0;
		}
		else if(flag=='s')
		{
			if (cargo=="ppk")return 8;
			else if (cargo=="pk") return 6;
			else if (cargo=="ppq") return 6;
			else if (cargo=="pq") return 4;
			else if (cargo=="ppf") return 7;
			else if (cargo=="pf") return 5;
			else if (cargo=="p") return 2;
			else if (cargo=="pp") return 2;
			else return 0;
		
		}
		else return 0;
	}
	//TO DO: metoda která vrací zda prvek mùže být sebrán
};

#endif