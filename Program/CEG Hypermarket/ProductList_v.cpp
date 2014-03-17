/*
* This file implements the functions defined in the productlist.h file
* using a vector. 
Done by: Thyagesh Manikandan
*/

#include "product.h"
#include "ProductList.h"
#include "Storage.h"
#include <vector>
#include<fstream>
#include<iostream>
#include<set>

using namespace std;

//constructor
ProductList::ProductList()
{
	_store=NULL;
	size=0;
	curr_idx=0;
}

//List wide methods
bool ProductList::load(const string& filename){
	err_string = "";

	if(_store==NULL)//this system is loading for the first time
		_store = new Storage(filename);

	else //the user is loading a second file
		_store->setFile(filename);

	bool loading = _store->load(*this);

	if(!loading)
	{

		err_string = _store->getErrstr();
		return false;
	}

	return true;
}
bool ProductList::checkLog()
{
	return _store->checkLog();
}
bool ProductList::loadlog()
{
	return _store->loadlog(*this);
}
bool ProductList::backup() 
{ 
	err_string ="";
	bool backup = _store->backup((*this));

	if(!backup)
		err_string = _store->getErrstr();

	return backup;
}
bool ProductList::save()
{
	err_string = "";
	bool save = _store->save(*this);
	if(!save)
		err_string+=_store->getErrstr();
	return save;
}
bool ProductList::saveAs(const string& filename)
{
	err_string = "";
	_store->setFile(filename);

	bool save = _store->save(*this);
	if(!save)
		err_string+=_store->getErrstr();
	return save;
}

//Single Product methods
bool ProductList::addProduct(string name, string cat, string manu, double price, int barcode)
{
	err_string = "";
	int start_add = clock();
	Product p1(name,cat,barcode,price,manu,0,0);
	bool add = addProduct(p1);
	int mid_add = clock();
	bool stor_add = _store->log("Add",name,cat,manu,price,barcode);

	std::set<Manufacturer>::iterator it=categories.find(cat);
	if(it == categories.end())
	{
		categories.insert(cat);
	}
	else
	{
		int k = ((it->noSold)+1);
		categories.erase(it);
		if(k>0)
			categories.emplace(cat,k);
	}

	int end_add = clock();
	_store->timeLog("ProductList", "Add", mid_add - start_add);
	_store->timeLog("ProductList", "Add with logging", end_add -  mid_add);
	if(!(add && stor_add))
		return false;

	return true;

}
bool ProductList::addProduct (const Product& prod)
{
	_list.push_back(prod);

	size++;
	return true;
}
bool ProductList::removeProduct (const int barcode)
{
	int start_rem = clock();
	err_string ="";
	int curr=0;
	for(;curr<size;curr++)
	{
		if(_list[curr].getBarcode() == barcode)
		{
			break;
		}
	}

	if(curr == size)
	{
		err_string = "No such product found!";
		return false;
	}

	else
	{
		string cat = _list[curr].getCategory();

		_list.erase(_list.begin()+curr);
		size--;				
		int mid_rem = clock();
		_store->log("Remove",barcode);

		//update the category set
		std::set<Manufacturer>::iterator it=categories.find(cat);
		int k = ((it->noSold)-1);
		categories.erase(it);
		if(k>0)
			categories.emplace(cat,k);

		int end_rem = clock();
		_store->timeLog("ProductList", "Remove", mid_rem - start_rem);
		_store->timeLog("ProductList", "Remove with logging", end_rem-mid_rem);
		return true;
	}
}
int ProductList::getSize() const
{
	return size;
}
Product ProductList::print()
{
	if(curr_idx == size)
		curr_idx=0;

	return _list[curr_idx++];
}
//search methods
bool ProductList::searchName(string name, ProductList& prodlist)
{
	err_string = "";
	ProductList p1;
	int start_name = clock();
	for(int i=0;i<size;i++)
	{
		if(_list[i].getName().find(name) != string::npos)
		{
			p1.addProduct(_list[i]);
		}
	}
	int end_name = clock();
	_store->timeLog("PL","SBN",end_name-start_name);

	if(p1.getSize()==0)
	{
		err_string = "No products matched query!";
		return false;
	}

	prodlist = p1;
	return true;
}
bool ProductList::searchCategory(string category, ProductList& prodlist)
{
	err_string = "";
	ProductList p1;
	int start_cat = clock();
	for(int i=0;i<size;i++)
	{
		if(_list[i].getCategory().find(category) != string::npos)
		{
			p1.addProduct(_list[i]);
		}
	}
	if(p1.getSize()==0)
	{
		err_string = "No products matched query!";
		return false;
	}

	prodlist = p1;
	return true;
}
bool ProductList::searchManufacturer(string manu, ProductList& prodlist)
{
	err_string = "";
	ProductList p1;
	for(int i=0;i<size;i++)
	{
		if(_list[i].getManufacturer().find(manu) != string::npos)
		{
			p1.addProduct(_list[i]);
		}
		if(p1.getSize()==0)
			return false;
	}
	prodlist = p1;
	return true;
}
bool ProductList::searchBarCode(int barcode, ProductList& prodlist)
{
	err_string = "";
	for(int i=0;i<size;i++)
	{
		if(_list[i].getBarcode() == barcode)
		{
			prodlist.addProduct(_list[i]);
			return true;
		}
	}
	err_string = "No product found with such a barcode!";
	return false;
}
bool ProductList::searchLowStock (ProductList& prodlist)
{
	err_string = "";

	bool flag = false;
	for(int i=0;i<size;i++)
	{
		if(_list[i].runningout())
		{
			prodlist.addProduct(_list[i]);
			flag = true;
		}
	}
	if(!flag)
	{
		err_string = "No products with a low stock!";
	}
	return flag;
}

//getter functions
bool ProductList::getBestSeller(ProductList &pdtlist)
{
	err_string = "";
	if(size == 0)
	{
		pdtlist.err_string = "No items in the list!";
		return false;
	}

	int big=0;
	int move = big + 1;
	pdtlist.addProduct(_list[big]);


	while(move<size)
	{
		if(_list[move].getNosold() > _list[big].getNosold())
		{
			pdtlist.empty();
			big=move;
			pdtlist.addProduct(_list[big]);
		}
		else if(_list[move].getNosold()==_list[big].getNosold())
			pdtlist.addProduct(_list[move]);

		move++;
	}

	return true;
}
bool ProductList::getManufacturerInfo(set<Manufacturer>& manu)
{
	if(manufacturers.empty())
	{
		int start_manu = clock();

		for(int i=0;i<size;i++)
		{
			string manu = print().getManufacturer();
			std::set<Manufacturer>::iterator it=manufacturers.find(manu);

			if(it == manufacturers.end())
			{

				manufacturers.emplace(manu);
			}

			else
			{

				int k = (it->noSold+1);
				manufacturers.erase(it);
				manufacturers.emplace(manu,k);
			}
		}
		int end_manu = clock();
		_store->timeLog("ProductList","Load (Manufacturer)",end_manu-start_manu);//(manu&cat)

	}
	manu = manufacturers;
	return (getSize()==0);
}
bool ProductList::getCategories(set<ProductList::Manufacturer>& cat)
{
	if(categories.empty())
	{
		int start_cat = clock();
		for(int i=0;i<size;i++)
		{
			string cat = print().getCategory();
			std::set<Manufacturer>::iterator it=categories.find(cat);

			if(it == categories.end())
			{
				//Manufacturer m(manu);
				categories.emplace(cat);
			}

			else
			{
				//Manufacturer m(ptr->prod.getManufacturer(),(it->noSold+1));
				int k = (it->noSold+1);
				categories.erase(it);
				categories.emplace(cat,k);
			}
		}

		/*
		for(int i=0;i<size;i++)
		{
		categories.emplace(print().getCategory());
		}
		*/

		int stop_cat = clock();
		_store->timeLog("PL","CAT",stop_cat-start_cat);
	}

	cat = categories;
	return true;
}

string ProductList::getErrorString()
{
	string a = err_string;
	err_string = "";
	return a;
}
//mutator methods
bool ProductList::updateProduct(const string& name, const string& category, const string& manu, const double& price, const int& barcode)
{
	err_string = "";
	Product *prod = &(*this)[barcode];

	string ini_cat = prod->getCategory();
	err_string += prod->setCategory(category)?"":"Could not set the category!\n";

	if(err_string=="" && ini_cat!= category)
	{
		//add the new category into list/ update number of items under this category
		std::set<Manufacturer>::iterator it=categories.find(category);
		if(it == categories.end())
		{
			categories.insert(prod->getCategory());
		}
		else
		{
			int k = ((it->noSold)+1);
			categories.erase(it);
			if(k>0)
				categories.emplace(category,k);
		}
	}

	err_string += prod->setName(name)?"":"Could not set the name!\n";
	err_string += prod->setManufacturer(manu)?"":"Could not change the manufacturer!\n";
	err_string += prod->setPrice(price)?"":"Could not set the name!\n";

	return  err_string == "";
}
/*product count methods*/
bool ProductList::specifySale(int barcode, int amt){
	return (*this)[barcode].saleofpdt(amt);
}
bool ProductList::reStock(int barcode, int qty){
	return (*this)[barcode].restock(qty);
}

//convenience methods
bool ProductList::isEmpty(int barcode)
{
	return (*this)[barcode].isempty();
}
bool ProductList::isRunningOut(int barcode)
{
	return (*this)[barcode].runningout();
}
Product& ProductList::operator[] (const int& barcode)
{
	Product* p;
	RsearchBarCode(barcode, p);

	return *p;
}
void ProductList::timeLog(string name, string function, long time)
{
	return _store->timeLog(name,function,time);
}

bool ProductList::RsearchBarCode(const int& barcode, Product* prod)
{
	for(int i=0;i<size;i++)
	{
		if(_list[i].getBarcode() == barcode)
		{
			ofstream a("on");
			a<<i<<" "<<size<<endl;
			a<<_list[i].getBarcode();
			a<<&(_list[i]);
			prod = &(_list[i]);
			a<<prod;
			a.close();
			return true;
		}
	}
	ofstream a("off");
	a.close();

	return false;
}

void ProductList::empty()
{
	_list.clear();
	size=0;
}

//destructor
ProductList::~ProductList()
{}