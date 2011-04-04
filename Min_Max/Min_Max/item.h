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
		//ID skuiny prvku
	int groupID;
		//poloha vramci skupiny
	int groupPlace;
		//ID prvku 
	int ID;
		//zda je prvkej zpravne umisten
	bool valide;
	bool unpassable;
		//hodnota prvku
	int value;
		//nazev prvku
	string name;
		//info o  pro testovani
	string Info;
//METODY:
		//nastavi vlastni z vektoru stringu
	void Constr(vector<string>::iterator &itPoint){
		name=(*itPoint);
		istringstream (*(itPoint+1))>>this->x_mm;
		istringstream (*(itPoint+2))>>this->y_mm;
		this->mmToX();
		this->mmToY();
		itPoint=itPoint+3;
		valide=false;
	}
		//kostruktor nastavi zakladni hodnoty vsemu	
	Item()
	{
		x=0;
		y=0;
		ID=0;
		groupID=0;
		string name="def";
		valide=false;
	} 
		//konstruktor z vektoru stringu
	Item(vector<string>::iterator &itPoint){	
		Constr(itPoint);
	}
		//vraci ukazatel na kopii objektu
	virtual Item* copy(void)=0;
		//zapise objekt do vystupni ho proudu
		//TODO:predelat do obecneho vystupniho proudu a ne file;
	
	virtual void writeTo(ostream &output){
		output<<endl<<" "<<this->name<<" "<<
			this->x_mm<<" "<<this->y_mm;
	}
		//vypise objekt na std vystup
	virtual void writeOutItem(void){
		cout<<" ID:"<<ID;
		cout<<" name:"<<name;
		cout<<" gr-ID: "<<this->groupID;
		cout<<" gr-place: "<<this->groupPlace;
		cout<<" x:"<<this->x;
		cout<<" y:"<<this->y;
		cout<<"xy: "<<this->x_mm<<" "<<this->y_mm;
		cout<<" valid: "<<this->valide<<endl;
		
	}	
		//prevod souradnic v mm na polohu
	void mmToX(int mm)
	{
		this->x=((mm-100)/350);
	}
	void mmToX(void)
	{
		this->x=((this->x_mm-100)/350);
	}
	void mmToY(int mm)
	{
		this->y=(mm/350);
	}
	void mmToY(void)
	{
		this->y=(this->y_mm/350);
	}
		//prevod souradnic na mm polohohu
	void xToMm(void)
	{
		this->y_mm=(this->y*350+175);
	}
	void yToMm(void)
	{
		this->x_mm=(this->x*350+275);
	}
};
#endif
