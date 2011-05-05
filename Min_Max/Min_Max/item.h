#ifndef _ITEM_H_
#define _ITEM_H_
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <sstream>
#include <time.h>
#include <cmath>
using namespace std;


class Item{
public:
//ATRIBUTY:
		//poloha v ramci ctvercu na hristi
	int x;
	int y;
		//poloha na hristi v mm
	int x_mm;
	int y_mm;
		//ID skupiny prvku
	int groupID;
		//poloha vramci skupiny
	int groupPlace;
		//ID prvku 
	int ID;
		//zda je prvek zprávnì umístìn na bodované pole
	bool valide;
		//která barva má pøípadné body
	char color;
		//zda je prvek prùchozí èi nikoliv
	bool unpassable;
		//hodnota prvku
	int value;
		//nazev prvku
	string name;
		//info o  pro testovani
	string Info;
//METODY:
		//nastavi vlastnosti z vektoru stringu
	void Constr(vector<string>::iterator &itPoint){
		name=(*itPoint);
		istringstream (*(itPoint+1))>>this->x_mm;
		istringstream (*(itPoint+2))>>this->y_mm;
		this->mmToX();
		this->mmToY();
		itPoint=itPoint+3;
		valide=this->isValide();
		this->unpassable=true;
	}
		//kostruktor nastavi zakladni hodnoty vsemu	
	Item()
	{
		x=0;
		y=0;
		ID=0;
		value=0;
		groupID=0;
		string name="def";
		valide=false;
		color='d';
		unpassable=true;
	} 
		//konstruktor z vektoru stringu
	Item(vector<string>::iterator &itPoint){	
		Constr(itPoint);
	}
		//vraci ukazatel na kopii objektu
	virtual Item* copy()=0;
		//zapise objekt na zadany proudu
	virtual void writeTo(ostream &output){
		output<<endl<<" "<<this->name<<" "<<
			this->x_mm<<" "<<this->y_mm;
	}
		//vypise objekt na std vystup
	virtual void writeOutItem(){
		cout<<" ID:"<<ID;
		cout<<" name:"<<name;
		cout<<" gr-ID: "<<this->groupID;
		cout<<" gr-place: "<<this->groupPlace;
		cout<<" x:"<<this->x;
		cout<<" y:"<<this->y;
		cout<<"xy: "<<this->x_mm<<" "<<this->y_mm;
		cout<<" valid: "<<this->valide<<endl;
		
	}
	virtual int getValue(char flag)
	{	
		if (this->isValide()) return value;
		else return 0;
	}
		// zkontroluje zda je objekt platnì umístìn
	virtual bool isValide(void)
	{
		if( this->y_mm % 350> 100 
			&& this->y_mm % 350 <250 
			&& (this->x_mm-450) % 350 >100  
			&& (this->x_mm-450) % 350 <250)
		{
			this->valide=true;
			return true;
		}
		else 
		{
			this->valide= false;
			return false;
		}
	}
		//prevod souradnic v mm na polohu ve ètvercích
	int mmToX(int mm)
	{
		this->x_mm= mm;
		this->x= ((mm-100)/350);
		return this->x;
	}
	int mmToX(void)
	{
		this->x=((this->x_mm-100)/350);
		return this->x;
	}
	int mmToY(int mm)
	{
		this->y_mm= mm;
		this->y= (mm/350);
		return this->y;
	}
	int mmToY(void)
	{
		this->y= (this->y_mm/350);
		return this->y;
	}
		//prevod souradnic na mm polohu
	int xToMm(void)
	{
		this->y_mm= (this->y*350+175);
		return this->y_mm;
	}
	int yToMm(void)
	{
		this->x_mm= (this->x*350+275);
		return this->y_mm;
	}
	
};
#endif
