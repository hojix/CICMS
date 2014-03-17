/************************************************************************
 * This file implements all the functions defined in the product.h file *
 *  Done by: Rupali Roy Choudhury                                       *
 ************************************************************************/

#include "product.h"
#include <string>
#include<iostream>
#include<fstream>
using namespace std;

//constructor with parameters
//gives value to the private members according to the parameters
Product::Product(const string& name, const string& category,const int& barcode,const double& price, const string& manufacturer, const int& noInstock,const int& noSold)
{
	_name=name;
	_category=category;
	_barcode=barcode;
	_price=price;
	_manufacturer=manufacturer;
	_noInstock=noInstock;
	_noSold=noSold;
}

//Default constructor
//gives default value to the private members
Product::Product()
{
	_name=" ";
	_category=" ";
	_barcode=0;
	_price=0.0;
	_manufacturer=" ";
	_noInstock=0;
	_noSold=0;
}

//this function checks if product can be sold 
bool Product::saleofpdt(int amt)         
{
	if(amt<0)
	{
		err_string = "Sale cannot take negative value!";
		return false;
	}
	else if(_noInstock <amt)
	{
		err_string = "Sale cannot be more than inventory!";
		return false;
	}
	else
	{
	   _noInstock-=amt;
	   _noSold+=amt;
	   return true;
	}
}

//this function restocks the product with the quantity specified
bool Product::restock(int qty)
{
	err_string = "";
	if(qty<0)
	{
		err_string = "Quantity cannot be negative!";
		return false;
	}
	else
	{
	   _noInstock+=qty;
	   return true;
	}
}


//getter functions
string Product::getName()const { return _name; }
string Product::getCategory()const { return _category; }
string Product::getManufacturer()const { return _manufacturer; }
int Product::getInstock()const { return _noInstock; }
int Product::getBarcode()const { return _barcode; }
int Product::getNosold()const { return _noSold; }
double Product::getPrice()const { return _price; }
string Product::getErrorMessage() const {return err_string;}


//setter functions
//this function sets the name of the product
bool Product::setName(string name)
{
	
	 if(name==" ")
	{
		err_string="Invalid name. Please do not put space";
		return false;
	}
	else if(name=="\0")
	{
		err_string="Invalid name. Please do not put null";
		return false;
	}
	else 
	{
		_name=name;
		cout<<_name;
		return true;
	}
}

//this function sets the category of the product
bool Product::setCategory(string cat)
{
	if(cat==" ")
	{
		err_string="Invalid name. Please do not put space";
		return false;
	}
	else if(cat=="\0")
	{
		err_string="Invalid name. Please do not put null";
		return false;
	}
	else
	{
		_category=cat;
		cout<<_category;
		return true;
	}
}

//this function sets the manufacturer name of the product
bool Product::setManufacturer(string man)
{
   
	if(man==" ")
	{
		err_string="Invalid name. Please do not put space";
		return false;
	}
	else if(man=="\0")
	{
		err_string="Invalid name. Please do not put null";
		return false;
	}
	else
	{
		_manufacturer=man;
		cout<<_manufacturer;
		return true;
	}
}

//this function sets the price of the product
bool Product::setPrice(double price)
{
	if(price==0.0)
	{
		err_string="Invalid price because the price has been set to 0";
		return false;
	}
	else if(price<0.0)
	{
		err_string="Invalid price because the price has been set to a negative value";
		return false;
	}
	else
	{
		_price=price;
		cout<<_price;
		return true;
	}
}

//checks if the product is running out
bool Product::runningout(int num)
{
	if(_noInstock>num)
	{
		err_string="stock is NOT running out";
		return false;
	}
	else
		return true;
}
