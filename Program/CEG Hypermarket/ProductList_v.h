/*
 * This file defines all the functions the list class does and has private
 * variables that assist in the implementation of this using a vector.
 * Functions involving loading, adding or removing products,
 * updating changes and searching by a specific criteria are shown here

	Done by: Thyagesh Manikandan
 */

#ifndef _PRODUCTLISTV_H_
#define _PRODUCTLISTV_H_
#include "Storage.h"
#include "product.h"
#include <vector>
#include<set>

using namespace std;

class Storage;

class ProductList
{
     public:
			 ProductList();
			 struct Manufacturer
			 {
					string name;
					int noSold;

					Manufacturer (const string& strKey = "", const int& Data=1)
					{
						name = strKey;
						noSold = Data;
					}

					bool operator<(const Manufacturer& rhs) const
					{
						return name < rhs.name;
					}	

					bool operator==(const Manufacturer& r)
					{
						return name == r.name;
					} 
			 };//for the UI combo box

		     //listwide functions (connector to the storage methods)
             bool load(const string& filename);
			 bool checkLog();//check if system did not crash (false if system did crash)
			 bool loadlog();//in case the user wants to recover the changes
			 bool backup();
			 bool save();
			 bool saveAs(const string& filename);

			 //single product funcs
             bool addProduct (const Product& prod);
			 bool addProduct(string name, string cat, string manu, double price, int barcode);
			 bool removeProduct (const int barcode);

             //search methods
             bool searchName(string name, ProductList& prodlist);
             bool searchCategory(string category, ProductList& prodlist);
             bool searchManufacturer(string manu, ProductList& prodlist);
             bool searchBarCode(int barcode, ProductList& prodlist);
			 bool searchLowStock (ProductList& prodlist);

			 //getter funcs
			 int getSize() const;			 
			 bool getCategories(set<Manufacturer>& cat);
			 bool getBestSeller(ProductList& pdtlist);
			 bool getManufacturerInfo(set<Manufacturer>& manu);
			 string getErrorString();
             
			 //mutator methods
			 bool ProductList::updateProduct(const string& name, const string& category, const string& manu, const double& price, const int& barcode);
			 /*product count methods(connector to the product class)*/
             bool specifySale(int barcode, int amt);
             bool reStock(int barcode, int qty);
             
             //convenience methods
             bool isEmpty(int barcode);
             bool isRunningOut(int barcode);
			 /*prints out the products in order*/
			 Product print();

			 //timer functions
			 void timeLog(string name, string function, long time);


			 ~ProductList();
	  private:
			  int size;
			  vector<Product> _list;
			  set<ProductList::Manufacturer> categories;
			  set<ProductList::Manufacturer> manufacturers;
			  string err_string;
			  
			  bool RsearchBarCode(const int& barcode, Product* prod);
			  Product& operator[] (const int& barcode);//for convenience ;)
			  void empty();

			  int curr_idx;
			  Storage *_store;
};
#endif