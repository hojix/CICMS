/********************************************************************
 * This file defines the various functions that we					*
 * have written that interact with files such as saving to file,	*
 * backing up the list, loading from file and keeping multiple logs	*
 *																	*
 * Done by: Ho Jia Yi												*
 ********************************************************************/

#ifndef _STORAGE_H_
#define _STORAGE_H_

#include<fstream>
#include<string>
#include<ctime>
#include<iostream>

using namespace std;

class ProductList; //forward declaration

namespace CEGHypermarket
{
	ref class MyForm;
}

class Product;

//Storage.h
class Storage
{
private:
	//inFile and outFile is same
	fstream myFile;
	ofstream backupFile;
	fstream clog;
	string fileName;
	string err_str;	
	bool flag;

public:
	//constructor
	Storage();
	Storage(const string& filename);
	~Storage();

	//save
	bool save (ProductList& ListOfPdts, bool save);
	bool backup(ProductList& ListOfPdts);
	void setFile(const string& filename);
	
	//load
	bool load (ProductList& ListOfPdts,CEGHypermarket::MyForm^ form);
	bool loadAnother (ProductList& ListOfPdts, string filename,CEGHypermarket::MyForm^ form);

	//log
	bool checkLog();
	bool loadlog(ProductList& ListOfPdts,CEGHypermarket::MyForm^ form);
	void emptylog();
	
	string getErrstr();

	bool getFlag();
	
	//add and update
	bool log(string functiontype, string name, string cat, string manu, double price, int barcode);
	//remove
	bool log(string functiontype, int barcode);
	//for loading another file
	bool Storage::log(string functiontype, string fname);
	//sell and restock
	bool log(string fucntiontype, int barcode, int qty);
};
#endif