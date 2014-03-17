/**************************************************************************
 * This file implements the functions defined in the productlist.h file   *
 * using a linked list with dummy head.                                   *
 * Done by: Thyagesh Manikandan                                           *
 **************************************************************************/

#include "ProductList.h"
#include "Product.h"
#include "Storage.h"
#include "MyForm.h"
#include "BatchProcessor.h"
#include <cstring>
#include <set>
#include <utility>
#include <sstream>

using namespace std;

//constructor
ProductList::ProductList()
{
	_head = new ProductNode;//dummy head
	_head->next  = NULL;
	_tail = _head;
	print_curr = _head;

	_store = NULL;
	size=0;
	loading = false;
	err_string="";
}

//List wide methods (mainly linker methods, where PL acts as a intermediate between UI and Storage
bool ProductList::load(const string& filename,CEGHypermarket::MyForm^ form){
	err_string = "";
	bool loaded;

	loading = true;//set the loading flag to be true

	//first time load
	if(_store==NULL)
	{
		_store = new Storage(filename);
		loaded = _store->load(*this,form);
	}

	//subsequent load calls
	else
		loaded = _store->loadAnother(*this,filename,form);

	//check if load was successful
	if(!loaded)
	{
		err_string = _store->getErrstr();	//if not successful, set error string
		return false;
	}
	return true;
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
	bool save = _store->save(*this, true);

	if(!save)
		err_string+=_store->getErrstr();
	return save;
}
bool ProductList::saveAs(const string& filename)
{
	err_string = "";
	_store->setFile(filename);

	bool save = _store->save(*this, false);

	if(!save)
		err_string+=_store->getErrstr();

	return save;
}
bool ProductList::checkLog()
{
	if(_store!=NULL)
		return _store->checkLog();
	
	return true;
}
bool ProductList::loadlog(CEGHypermarket::MyForm^ form)
{
	return _store->loadlog(*this,form);
}
void ProductList::emptylog()
{
	_store->emptylog();
}

//Single Product functions
bool ProductList::addProduct(string name, string cat, string manu, double price, int barcode,int stock, int nosold)
{
	err_string = "";
	Product p1(name,cat,barcode,price,manu,stock,nosold);
	bool add = addProduct(p1);

	if(add)
	{
		bool stor_add = _store->log("Add",name,cat,manu,price,barcode);

		if(!loading)
		{

			std::set<Combo>::iterator it=categories.find(cat);	//update the categories set
			if(it == categories.end())
			{
				categories.insert(cat);
			}
			else
			{
				int k = ((it->noSold)+1);//add one to the no of products under this category
				categories.erase(it);
				if(k>0)
					categories.emplace(cat,k);
			}

			it=manufacturers.find(manu);//update the manufacturers set
			if(it == manufacturers.end())
			{
				manufacturers.emplace(manu,0);
			}

		}

		return true;
	}

	else
		return false;
}
bool ProductList::addProduct (const Product& prod)
{
	pair<std::set<int>::iterator,bool> ret = Barcodes.insert(prod.getBarcode());//try to insert the new barcode into the set
	
	if(ret.second)	//if insertion is successful, then the barcode does not exist so add it to list
	{
		ProductNode *ptr = new ProductNode;
		ptr->prod = prod;
		ptr->next = NULL;

		_tail->next = ptr;
		_tail = ptr;

		size++;
		return true;
	}

	else
	{
		err_string = "Barcode already exists!";	//else update the err_string
		return false;
	}
}

bool ProductList::removeProduct (const int& barcode)
{
	err_string ="";
	ProductNode *curr = _head->next;
	ProductNode *prev = _head;

	while (curr!=NULL)
	{
		if(curr->prod.getBarcode() == barcode)
			break;

		prev = curr;
		curr = curr->next;
	}

	if(curr == NULL)
	{
		err_string = "No such product found!";
		return false;
	}
	else
	{
		string cat = curr->prod.getCategory();
		string manu = curr->prod.getManufacturer();

		//update the manufacturer set
		std::set<Combo>::iterator it=manufacturers.find(manu);
		int k = ((it->noSold)- curr->prod.getNosold());
		manufacturers.erase(it);
		if(k>0)
			manufacturers.emplace(manu,k);

		//update the category set
		it=categories.find(cat);
		k = ((it->noSold)-1);
		categories.erase(it);
		if(k>0)
			categories.emplace(cat,k);

		//update the barcode set
		Barcodes.erase(barcode);


		if(curr == _tail)
			_tail = prev;

		prev->next = curr->next;
		delete curr;
		size--;
		
		_store->log("Remove",barcode);

		return true;
	}
}

//search methods
bool ProductList::searchName(string name, ProductList& prodlist){
	err_string = "";
	ProductNode *ptr = _head->next;
	ProductList temp[3];
	string lname = toLower(name);

	while(ptr!=NULL)
	{
		if(ptr->prod.getName() == name)	//if exact match, add to list
		{
			prodlist.addProduct(ptr->prod);	
		}
		else if(toLower(ptr->prod.getName()) == lname)
		{
			temp[0].addProduct(ptr->prod);
		}
		else if(ptr->prod.getName().find(name) != string::npos)// if partial match, add to temp
		{
			temp[1].addProduct(ptr->prod);
		}
		else if(toLower(ptr->prod.getName()).find(lname) != string::npos)
		{
			temp[2].addProduct(ptr->prod);
		}
		ptr = ptr->next;
	}

	for(int i=0;i<3;i++)
	{
		if(temp[i].getSize()>0)	// if there are partial matches, add it to the end of the prodlist
		{
			prodlist._tail->next = temp[i]._head->next;
			prodlist._tail = temp[i]._tail;
			prodlist.size +=temp[i].size;

			temp[i]._tail = temp[i]._head;
			temp[i]._head->next = NULL;
			temp[i].size = 0;
		}
		temp[i].Finalize();
	}

	if(prodlist.getSize() == 0)
	{
		err_string = "No products matched query!";
		return false;
	}
	return true;
}
bool ProductList::searchCategory(string category, ProductList& prodlist){
	err_string = "";
	ProductNode *ptr = _head->next;

	while(ptr!=NULL)
	{
		if(ptr->prod.getCategory() == category)	// only exact matches are possible since we give them a combo box
		{
			prodlist.addProduct(ptr->prod);
		}
		ptr = ptr->next;
	}
	if(prodlist.getSize() == 0)
	{
		err_string = "No products have"+category+" as their category!";
		return false;
	}
	return true;
}
bool ProductList::searchManufacturer(string manu, ProductList& prodlist){
	err_string = "";
	ProductNode *ptr = _head->next;

	while(ptr!=NULL)
	{
		if(ptr->prod.getManufacturer() == manu)	//exact matches only
		{
			prodlist.addProduct(ptr->prod);
		}
		ptr = ptr->next;
	}
	if(prodlist.getSize() == 0)
	{
		err_string = "No products have "+manu+" as manufacturer!";
		return false;
	}
	return true;
}
bool ProductList::searchBarCode(int barcode, ProductList& prodlist){
	err_string = "";
	ProductNode *ptr=NULL;
	std::set<int>::iterator it = Barcodes.find(barcode);	// check if barcode exists

	if(it != Barcodes.end())
	{
		prodlist.addProduct((*this)[barcode]);
		return true;
	}
	else
	{
		err_string = "No product with this barcode!";
	}
	return false;
}
bool ProductList::searchLowStock (int num,ProductList& prodlist)
{
	err_string = "";
	ProductNode *ptr = _head->next;

	while(ptr!=NULL)
	{
		if(ptr->prod.runningout(num))
		{
			prodlist.addProduct(ptr->prod);
		}
		ptr = ptr->next;
	}
	if(prodlist.getSize() == 0)
	{
		err_string = "No products with a low stock!";
		return false;
	}
	return true;
}
	/*private func*/
bool ProductList::RsearchBarCode(int barcode, ProductNode **prodnode){
	err_string = "";
	ProductNode *ptr = _head->next;

	while (ptr!=NULL)
	{
		if(ptr->prod.getBarcode() == barcode)
		{
			*prodnode=ptr;
			return true;
		}
		else
		{
			ptr = ptr->next;
		}
	}

	err_string = "Product Not Found!";
	return false;
}

//getter funcs
bool ProductList::getBestSeller(ProductList &pdtlist)
{
	err_string = "";

	if(size == 0)
	{
		pdtlist.err_string = "No items in the list!";
		return false;
	}

	ProductNode *big=_head->next;
	pdtlist.addProduct(big->prod);
	ProductNode *move=big->next;

	while(move!=NULL)
	{
		if(move->prod.getNosold()>big->prod.getNosold())	//if 
		{
			pdtlist.empty();
			big=move;
			pdtlist.addProduct(big->prod);
		}
		else if(move->prod.getNosold()==big->prod.getNosold())
			pdtlist.addProduct(move->prod);

		move=move->next;
	}

	return true;
}
bool ProductList::getManufacturerInfo(set<ProductList::Combo>& manuf,CEGHypermarket::MyForm^ form)
{
	if(manufacturers.empty())	//if we have not populated the manufacturers set before, then populate it
	{
		form->progSet(System::Drawing::Color::DarkOrange);
		int start_prog = clock(); //DO NOT DELETE
		for(int i=0;i<size;i++)
		{
			Product ptemp = print();
			string manu = ptemp.getManufacturer();
			std::set<Combo>::iterator it=manufacturers.find(manu);

			if(it == manufacturers.end())
			{
				manufacturers.emplace(manu,ptemp.getNosold());
			}

			else
			{
				int k = (it->noSold+ptemp.getNosold());
				manufacturers.erase(it);
				manufacturers.emplace(manu,k);
			}
					if((clock() - start_prog) >= 200)
					{

						stringstream status;
						double perc = (i*1.00/size);
						status<<"Populating Manufacturers ";
						status<<(int)(perc*100);
						status<<"% done...";
						/*form->textprog(double(i)/size);*/
						form->statusProg(perc,status.str());
						start_prog = clock();
					}		
		}

		stringstream status;
		status<<"Populating Manufacturers 100% done...";
		form->statusProg(1.0,status.str());
	}
	manuf = manufacturers;
	return (getSize()==0);
}
int ProductList::getSize() const 
{
	return size; 
}
bool ProductList::getCategories(set<ProductList::Combo>& cat,CEGHypermarket::MyForm^ form)
{
	if(loading || categories.empty())//check we have already populated the set, if not then populate it again
	{
		int start_prog = clock(); //DO NOT DELETE
		form->progSet(System::Drawing::Color::DarkOrange);
		for(int i=0;i<size;i++)
		{
			string cat = print().getCategory();
			std::set<Combo>::iterator it=categories.find(cat);

			if(it == categories.end())
			{
				categories.emplace(cat);
			}

			else
			{
				int k = (it->noSold+1);
				categories.erase(it);
				categories.emplace(cat,k);
			}
			if((clock() - start_prog) >= 200)
			{

				stringstream status;
				double perc = (i*1.00/size);
				status<<"Populating Categories ";
				status<<(int)(perc*100);
				status<<"% done...";
				/*form->textprog(double(i)/size);*/
				form->statusProg(perc,status.str());
				start_prog = clock();
			}

		}

		loading = false;

		stringstream status;
		status<<"Populating Categories 100% done...";
		form->statusProg(1.0,status.str());

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
	set<int>::iterator it = Barcodes.find(barcode);
	if(it == Barcodes.end())
	{
		err_string = "Could not find product with that barcode";	
		return false;
	}

	Product *prod = &(*this)[barcode];

	string ini_cat = prod->getCategory();
	err_string += prod->setCategory(category)?"":prod->getErrorMessage();//"Could not set the category!\n";

	if(err_string=="" && ini_cat!= category)
	{
		//add the new category into list/ update number of items under this category
		std::set<Combo>::iterator it=categories.find(category);
		if(it == categories.end())
		{
			categories.insert(prod->getCategory());
		}
		else
		{
			int k = ((it->noSold)+1);
			categories.erase(it);
			categories.emplace(category,k);
		}


		//remove category without any product
		it = categories.find(ini_cat);
		int k = ((it->noSold)-1);
		categories.erase(it);
		if(k>0)
			categories.emplace(ini_cat,k);
	}

	err_string += prod->setName(name)?"":prod->getErrorMessage();//"Could not set the name!\n";

	string ini_manu = prod->getManufacturer();
	bool manu_update = prod->setManufacturer(manu);
	err_string += manu_update?"":prod->getErrorMessage();//"Could not change the manufacturer!\n";

	if(manu_update && ini_manu!= manu)
	{
		//add the new manufacturer into list/ update number of items under this category
		std::set<Combo>::iterator it=manufacturers.find(manu);
		if(it == manufacturers.end())
		{
			manufacturers.emplace(prod->getManufacturer(),0);
		}
		else
		{
			int k = ((it->noSold)+prod->getNosold());
			manufacturers.erase(it);
			manufacturers.emplace(manu,k);
		}


		//remove manufacturer without any product
		it = manufacturers.find(ini_manu);
		int k = ((it->noSold)-prod->getNosold());
		manufacturers.erase(it);
		if(k>0)
			manufacturers.emplace(ini_manu,k);
	}

	err_string += prod->setPrice(price)?"":prod->getErrorMessage();//"Could not set the price!\n";
	if(err_string == "")
	{
		_store->log("Update",name,category,manu,price,barcode);
	}
	return  err_string == "";
}
/*product count methods*/
bool ProductList::specifySale(int barcode, int amt){
	set<int>::iterator it = Barcodes.find(barcode);
	if(it == Barcodes.end())
	{
		err_string = "Could not find product with that barcode";	
		return false;
	}

	err_string ="";

	Product& temp_p = (*this)[barcode];
	err_string += temp_p.saleofpdt(amt)?"":temp_p.getErrorMessage();

	if(err_string == "")
	{
		set<Combo>::iterator it = manufacturers.find(temp_p.getManufacturer());
		int k = ((it->noSold)+amt);//add one to the no of products under this category
		manufacturers.erase(it);
		if(k>0)
			manufacturers.emplace(temp_p.getManufacturer(),k);
		_store->log("Sell",barcode,amt);

	}

	return err_string == "";
}
bool ProductList::reStock(int barcode, int qty){
	set<int>::iterator it = Barcodes.find(barcode);
	if(it == Barcodes.end())
	{
		err_string = "Could not find product with that barcode";
		return false;
	}

	err_string = "";
	Product& temp_p=(*this)[barcode];
	err_string += temp_p.restock(qty)?"":temp_p.getErrorMessage();//"Quantity not positive!";

	if(err_string == "")
		_store->log("Restock",barcode,qty);

	return err_string == "";
}

//convenience methods
bool ProductList::isRunningOut(int barcode,int num){

	err_string = "";
	ProductNode *ptr;

	set<int>::iterator it = Barcodes.find(barcode);
	if(it == Barcodes.end())
	{
		err_string = "Could not find product with that barcode";		
		return false;
	}

	if(RsearchBarCode(barcode,&ptr))
	{
		return ptr->prod.runningout(num);
	}

	return false;
}
Product& ProductList::operator[] (const int& barcode)
{
	ProductNode* ptr;
	RsearchBarCode(barcode,&ptr);
	return ptr->prod;
}
string ProductList::toLower(string s)
{
	int length =s.length();
	for(int i=0;i<length;i++)
	{
		s[i] = tolower(s[i]);
	}
	return s;
}

/*empties the current list*/
void ProductList::empty()
{
	if(size == 0)
		return;

	ProductNode *ptr = _head->next;

	while(ptr!=NULL)
	{
		_head->next = ptr->next;
		delete ptr;
		ptr = _head->next;
	}

	_tail = _head;

	size=0;
}
/*prints out the products in order*/
Product ProductList::print()
{
	if(print_curr->next==NULL)
		print_curr = _head;

	print_curr = print_curr->next;

	return print_curr->prod;
}
void ProductList::printItem(System::Windows::Forms::ListViewItem^ item)//for GUI
{
	Product p1 = print();
	//convert to system string
	System::String^ sys_name = gcnew System::String(p1.getName().c_str()); //name
	System::String^ sys_bar = System::Convert::ToString(p1.getBarcode()); //barcode
	System::String^ sys_price = System::Convert::ToString(p1.getPrice()); //price
	System::String^ sys_manu = gcnew System::String(p1.getManufacturer().c_str()); //manufacturer
	System::String^ sys_instock = System::Convert::ToString(p1.getInstock()); //number in stock
	System::String^ sys_cat = gcnew System::String(p1.getCategory().c_str()); //category
	System::String^ sys_nosold = System::Convert::ToString(p1.getNosold()); //number sold

	item->BeginEdit();

	item->SubItems[0]->Text = sys_name;

	//creating item for listview
	item->SubItems->Add(sys_bar); //add barcode
	item->SubItems->Add(sys_cat); //add category	 
	item->SubItems->Add(sys_manu); //add manu
	item->SubItems->Add(sys_price); //add price
	item->SubItems->Add(sys_nosold); //add number sold
	item->SubItems->Add(sys_instock); //add number in stock
}

//batchProcess
bool ProductList::batchProcess(const string& filename,CEGHypermarket::MyForm^ form)
{
	BatchProcessor bp;

	return bp.batchProcess(filename,*this,form);

}

//Finalizer
void ProductList::Finalize()
{
	if(_store!=NULL)
	{
		_store->save(*this, true);
		delete _store;
		_store = NULL;
	}
	if(_head!=NULL)
	{
		this->empty();
		delete _head;
		_head = NULL;
	}
	return;
}

//destructor
ProductList::~ProductList()
{
	if(_head!=NULL)
	{
		this->Finalize();
	}
}