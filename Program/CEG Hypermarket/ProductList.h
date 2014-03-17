/****************************************************************************
 * This file defines all the functions the list class does and has private	*
 * variables that assist in the implementation of this using a linkedlist.	*
 * Functions involving loading, adding or removing products,				*
 * updating changes and searching by a specific criteria are shown here		*
 *
 *	Done by: Thyagesh Manikandan											*
 ****************************************************************************/

#ifndef _PRODUCTLIST_H_
#define _PRODUCTLIST_H_
#include <set>
#include <cstring>
#include "product.h"

using namespace std;

namespace CEGHypermarket
{
	ref class MyForm;
}

class Storage;

class ProductList
{
     public:
			 //constructor
			 ProductList();
			 struct Combo	//using the same struct for categories and manufacturers for reusing code
			 {
					string name;	//name of manufacturer or category
					int noSold;		//no. of products sold in the case of manufacturer, but no of products for the case of category

					Combo (const string& strKey = "", const int& Data=1)
					{
						name = strKey;
						noSold = Data;
					}

					bool operator<(const Combo& rhs) const
					{
						return name < rhs.name;
					}	

					bool operator==(const Combo& r)
					{
						return name == r.name;
					} 
			 };//for the UI combo box

		     //listwide functions (connector to Storage Class)
			 bool load(const string& filename,CEGHypermarket::MyForm^ form);
			 bool backup();
			 bool save();
			 bool saveAs(const string& filename);
			 bool checkLog();
			 bool loadlog(CEGHypermarket::MyForm^ form);
			 void emptylog();

			 //single product funcs
			 bool addProduct(string name, string cat, string manu, double price, int barcode,int instock=0,int nosold = 0);
			 bool removeProduct (const int& barcode);

             //search methods
             bool searchName(string name, ProductList& prodlist);
             bool searchCategory(string category, ProductList& prodlist);
             bool searchManufacturer(string manu, ProductList& prodlist);
             bool searchBarCode(int barcode, ProductList& prodlist);
			 bool searchLowStock (int num,ProductList& prodlist);

			 //getter funcs
			 int getSize() const;			 
			 bool getCategories(set<ProductList::Combo>& cat,CEGHypermarket::MyForm^ form);
			 bool getBestSeller(ProductList& pdtlist);
			 bool getManufacturerInfo(set<ProductList::Combo>& manuf,CEGHypermarket::MyForm^ form);
			 string getErrorString();

			 //mutator methods (connector to Product class)
			 bool ProductList::updateProduct(const string& name, const string& category, const string& manu, const double& price, const int& barcode);
             bool specifySale(int barcode, int amt);
             bool reStock(int barcode, int qty);

             //convenience methods
             bool isRunningOut(int barcode,int num);
			 /*prints out the products in order*/
			 Product print();//for storage
			 void printItem(System::Windows::Forms::ListViewItem^ item);//for GUI

			 //batchprocessor
			 bool batchProcess(const string& filename,CEGHypermarket::MyForm^ form);

			 void Finalize();
			 ~ProductList();
	 private:
			  /*********************
					ATTRIBUTES
			  *********************/

			  //define the node
              struct ProductNode
              {
                     Product prod;
                     ProductNode* next;
              };

			  //declare the pointers
              ProductNode *_head;
			  ProductNode *_tail;
			  ProductNode *print_curr;//helps in printing out the whole list of products quickly (check print())

			  //storage object
			  Storage *_store;

			  //the sets
			  set<ProductList::Combo> categories;//for the combo box in the UI
			  set<ProductList::Combo> manufacturers; // for the combo box in the UI
			  set<int> Barcodes;					//to avoid duplicate entries

			  
			  string err_string;//to specify what exactly went wrong
			  int size;
			  bool loading;//to know if a file is being loaded

			  /*********************
					  METHODS
			  *********************/

			  //internal addProduct function which does the actual adding
			  bool ProductList::addProduct (const Product& prod);

			  //helper for search by name
			  string toLower(string s);

			  //get the listnode with given barcode
			  bool RsearchBarCode(int barcode, ProductNode **prodnode);

			  //get a reference to the product with the given barcode
			  Product& operator[] (const int& barcode);//for convenience ;)

			  //to conveniently delete the entire list
			  void empty();
};
#endif