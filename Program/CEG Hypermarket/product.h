/*************************************************
 * This file defines all the fundamental methods *
 * associated with a product in our program      *
 *	Done by: Rupali Roy Choudhury                *
 *************************************************/

#ifndef _PRODUCT_H_
#define _PRODUCT_H_
#include <string>
using namespace std;

class Product
{
private:

        string _name, _category, _manufacturer;
        int _noInstock, _barcode, _noSold;
        double _price;
		string err_string;

public:
        Product(const string& name, const string& category,const int& barcode,const double& price, const string& manufacturer, const int& noInstock,const int& noSold);
        Product();
        bool saleofpdt(int amt);
        bool restock(int qty);

        //getter functions
        string getName()const;
        string getCategory()const;
        string getManufacturer()const;
        int getInstock()const;
        int getBarcode()const;
        int getNosold()const;
        double getPrice()const;
		string getErrorMessage() const;

        //mutator functions
        bool setName(string name);
        bool setCategory(string cat);
        bool setManufacturer(string man);
        bool setPrice(double price);

		//true if stock is running out
        bool runningout(int num); 
};
#endif