/***************************************************************
 * This file implements all the functions defined in Storage.h  *
 *																*
 * Done by: Ho Jia Yi                                           *
 ****************************************************************/

#include "Storage.h"
#include "ProductList.h"
#include <fstream>
#include <string>
#include <ctime>
#include <iostream>
#include <sstream>
#include "MyForm.h"

using namespace std;

//constructor
Storage::Storage(const string& filename)
{
	err_str="";
	flag=true;

	fileName = filename;
	while(fileName.find("\\")!=(string::npos))
		fileName.replace(fileName.find("\\"),1,"/");
	myFile.open(fileName,fstream::in|fstream::out);

	clog.open("Log_"+fileName.substr(fileName.find_last_of("/")+1), fstream::in|fstream::out);

}
//default constructor
Storage::Storage(){}

//destructor
Storage::~Storage()
{
	myFile.close();
	backupFile.close();
	clog.seekg(0,clog.end);
	long int length = (long int)clog.tellg();
	clog.close();
	if(length == 0)
	{
		std::remove(("Log_"+fileName.substr(fileName.find_last_of("/")+1)).c_str());
	}
}

string Storage::getErrstr()
{
	return err_str;
}
bool Storage::getFlag(){return flag;}

//reads the text file and store as product list
bool Storage::load (ProductList& ListOfPdts,CEGHypermarket::MyForm^ form)
{
	int start_prog = clock();//DO NOT DELETE
	int size=0;
	int total1=0;
	string x;	
	string newline;
	string name, category, manufacturer;
	int barcode, instock, sold;
	double price;
	form->progSet(System::Drawing::Color::IndianRed);


	//check the length of the file
	myFile.seekg(0,myFile.end);
	long int length = (long int)myFile.tellg();
	myFile.seekg(0,myFile.beg);
	if(length==0)
	{
		err_str= "Error: Empty file.";
		return false;
	}

	//check file format
	getline(myFile, newline);
	size = newline.size();
	for(int i=0;i<size;i++)
	{
		if(!isdigit(newline[i]))
		{
			err_str="Error: File Format is Wrong.";
			return false;
		}
	}
	getline(myFile,newline);
	getline(myFile,newline);
	getline(myFile,newline);
	getline(myFile,newline);
	for(int i=0;newline[i];i++)
	{
		if(!isdigit(newline[i]))
		{
			err_str="Error: File Format is Wrong.";
			return false;
		}
	}
	myFile.seekg(0,myFile.beg);

	//check size of productlist not 0
	myFile>>size;
	myFile.ignore(1,'\n');
	if(size==0)
	{
		err_str="Error: Size is 0.";
		return false;
	}

	//loop the size of product list ot read all the products
	for(int i=0;i<size;i++)
	{
		myFile.ignore(1,'\n');
		getline(myFile,name);
		getline(myFile,category);
		myFile>>barcode;
		myFile.ignore(1,'\n');
		myFile>>price;
		myFile.ignore(1,'\n');
		getline(myFile,manufacturer);
		myFile>>instock;
		myFile.ignore(1,'\n');
		myFile>>sold;
		myFile.ignore(1,'\n');

		ListOfPdts.addProduct(name, category, manufacturer, price, barcode, instock, sold);


		if((clock() - start_prog) >= 200)
		{
			stringstream status;
			double perc = (i*1.00/size);
			status<<"Loading From File ";
			status<<(int)(perc*100);
			status<<"% done...";
			/*form->textprog(double(i)/size);*/
			form->statusProg(perc,status.str());
			start_prog = clock();
		}
	}

	stringstream status;
	status<<"Loading From File 100% done...";
	form->statusProg(1.0,status.str());

	myFile.seekg(0,myFile.beg);
	return true;
}
//load another file and add the products into the existing list
bool Storage::loadAnother (ProductList& ListOfPdts, string filename,CEGHypermarket::MyForm^ form)
{
	int size=0;
	int total1=0;
	string x;	
	string newline;
	int start_prog = clock();//DO NOT DELETE
	string name, category, manufacturer;
	int barcode, instock, sold;
	double price;
	bool flag1 = false;
	form->progSet(System::Drawing::Color::IndianRed);

	if(flag)
	{
		flag1=true;
		flag = false;
	}

	//opening the other file
	ifstream anotherFile;
	while(filename.find("\\")!=(string::npos))
		filename.replace(filename.find("\\"),1,"/");
	anotherFile.open(filename);

	//check file format
	getline(myFile, newline);
	size = newline.size();
	for(int i=0;i<size;i++)
	{
		if(!isdigit(newline[i]))
		{
			err_str="Error: File Format is Wrong.";
			return false;
		}
	}

	getline(myFile,newline);
	getline(myFile,newline);
	getline(myFile,newline);
	getline(myFile,newline);
	for(int i=0;newline[i];i++)
	{
		if(!isdigit(newline[i]))
		{
			err_str="Error: File Format is Wrong.";
			return false;
		}
	}
	myFile.seekg(0,myFile.beg);


	//check the length of the file
	anotherFile.seekg(0,anotherFile.end);
	long int length = (long int)anotherFile.tellg();
	anotherFile.seekg(0,anotherFile.beg);
	if(length==0)
	{
		err_str= "Error: Empty file.";
		return false;
	}


	//check size of productlist not 0
	anotherFile>>size;
	if(size==0)
	{
		err_str="Error: Size is 0.";
		return false;
	}
	anotherFile.ignore(1,'\n');


	//loop the size of product list ot read all the products
	for(int i=0;i<size;i++)
	{
		anotherFile.ignore(1,'\n');
		getline(anotherFile,name);
		getline(anotherFile,category);
		anotherFile>>barcode;
		anotherFile.ignore(1,'\n');
		anotherFile>>price;
		anotherFile.ignore(1,'\n');
		getline(anotherFile,manufacturer);
		anotherFile>>instock;
		anotherFile.ignore(1,'\n');
		anotherFile>>sold;
		anotherFile.ignore(1,'\n');



		//add it to the list
		ListOfPdts.addProduct(name, category, manufacturer, price, barcode, instock, sold);
		if((clock() - start_prog) >= 200)
		{
			stringstream status;
			double perc = (i*1.00/size);
			status<<"Loading From File ";
			status<<(int)(perc*100);
			status<<"% done...";
			form->statusProg(perc,status.str());
			start_prog = clock();
		}
	}

	stringstream status;
	status<<"Loading From File 100% done...";
	form->statusProg(1.0,status.str());

	anotherFile.close();
	if(flag1)
		flag = true;

	log("Load",filename);

	return true;
}

//return true if log is empty
bool Storage::checkLog()
{
	string temp;
	clog.seekp(0,clog.end);
	long int length = (long int)clog.tellp();
	
	clog.close();
	if(length < 1)	//file does not exist or is empty
	{
		clog.open("Log_"+fileName.substr(fileName.find_last_of("/")+1), fstream::out);
		return true;
	}
	else
	{
		clog.open("Log_"+fileName.substr(fileName.find_last_of("/")+1), fstream::in|fstream::out);
		return false;
	}
}
//when program opens, already open an fstream clog to check if is empty
//when flag is false product list funtions don't add to log
//read the clog file and make appropriate changes
bool Storage::loadlog(ProductList& ListOfPdts,CEGHypermarket::MyForm^ form)
{
	clog.seekg(0,clog.beg);
	string functype, name, manufacturer, category;
	int barcode, qty;
	double price;
	//don't add to log
	flag=false;

	//loop until eof
	while(!clog.eof())
	{
		//get the type of change
		getline(clog,functype);

		//does the appropriate changes
		if(functype=="Update")
		{
			getline(clog,name);
			getline(clog,category);
			clog>>barcode;
			clog.ignore(1,'\n');
			getline(clog,manufacturer);
			clog>>price;
			clog.ignore(1,'\n');

			//update details of the product
			ListOfPdts.updateProduct(name, category,manufacturer, price, barcode);
		}

		else if(functype=="Add")
		{
			getline(clog,name);
			getline(clog,category);
			clog>>barcode;
			clog.ignore(1,'\n');
			getline(clog,manufacturer);
			clog>>price;
			clog.ignore(1,'\n');

			ListOfPdts.addProduct(name, category, manufacturer, price, barcode);
		}

		else if(functype=="Remove")
		{
			clog>>barcode;
			clog.ignore(1,'\n');

			//remove the product from the product list
			ListOfPdts.removeProduct(barcode);
		}

		else if(functype=="Sell")
		{
			clog>>barcode;
			clog.ignore(1,'\n');
			clog>>qty;
			clog.ignore(1,'\n');

			//make changes in product list
			ListOfPdts.specifySale(barcode, qty);
		}

		else if (functype == "Restock")
		{
			clog>>barcode;
			clog.ignore(1,'\n');
			clog>>qty;
			clog.ignore(1,'\n');

			//increases the stock of the product in the list
			ListOfPdts.reStock(barcode, qty);
		}
		else if(functype == "Load")
		{
			string fname;
			getline(clog,fname);
			loadAnother(ListOfPdts,fname,form);
		}
		clog.ignore(1,'\n');
	}
	emptylog();
	flag=true;
	return true;
}
//empties the log file
void Storage::emptylog()
{
	clog.close();
	clog.open("Log_"+fileName.substr(fileName.find_last_of("/")+1), fstream::in|fstream::out|fstream::trunc);
}

//makes a copy of the product list into a seperate text file
bool Storage::backup(ProductList& ListOfPdts)
{
	backupFile.open("backup.g63");
	int size=ListOfPdts.getSize();
	//check if list is empty
	if(size==0)
	{
		err_str="Error: List is empty.";
		return false;
	}

	//list not empty
	else
	{
		backupFile<<size;
		//loop through the entire list and write into file
		for(int i=0;i<size;i++)
		{
			Product addP = ListOfPdts.print();
			backupFile << endl << endl << addP.getName();
			backupFile << endl << addP.getCategory();
			backupFile << endl << addP.getBarcode();
			backupFile << endl << addP.getPrice();
			backupFile << endl << addP.getManufacturer();
			backupFile << endl << addP.getInstock();
			backupFile << endl << addP.getNosold();
		}
	}

	backupFile.close();
	return true;

}
//rewrite the entire product list into the same text file
bool Storage::save(ProductList& ListOfPdts, bool save)
{
	//true:save, false:saveas
	//no changes made
	if(save)
	{
		clog.seekg(0,clog.end);
		long int length = (long int)clog.tellg();

		if(length == 0)
			return true;
	}

	int size=ListOfPdts.getSize();
	if(size==0)
	{
		err_str="Error: List is empty.";
		return false;
	}

	else
	{
		//open a temporary file and write the list into it
		ofstream savFile("saved.txt",ofstream::app);
		savFile<<size<<endl;
		for(int i=0;i<size;i++)
		{
			Product addP = ListOfPdts.print();
			savFile << endl << addP.getName();
			savFile << endl << addP.getCategory();
			savFile << endl << addP.getBarcode();
			savFile << endl << addP.getPrice();
			savFile << endl << addP.getManufacturer();
			savFile << endl << addP.getInstock();
			savFile << endl << addP.getNosold();
			savFile << endl;
		}
		myFile.close();
		savFile.close();

		//delete the original file
		remove(fileName.c_str());
		//rename the saved file
		int result = rename("saved.txt",fileName.c_str());
		if(result!=0)
		{
			err_str="Error: Rename failed.";
			return false;
		}

		myFile.open(fileName,fstream::in|fstream::out);
	}

	//clear all changes in log after saving
	clog.close();
	clog.open("Log_"+fileName.substr(fileName.find_last_of("/")+1), fstream::out|fstream::trunc);

	return true;
}
//changing the filename during save as
void Storage::setFile(const string& filename)
{
	myFile.close();
	clog.close();

	//renaming the log file
	rename(("Log_"+fileName.substr(fileName.find_last_of("/")+1)).c_str(),("Log_"+filename.substr(filename.find_last_of("/")+1)).c_str());

	fileName = filename;
	//opening the file streams with new filename
	clog.open("Log_"+fileName.substr(fileName.find_last_of("/")+1), fstream::in|fstream::out);
	while(fileName.find("\\")!=(string::npos))
		fileName.replace(fileName.find("\\"),1,"/");
	myFile.open(fileName,fstream::in|fstream::out);

}

//The Logging funcions
//load another list
bool Storage::log(string functiontype, string fname)
{
	if(flag)
	{
		clog<<functiontype<<endl<<fname<<endl<<endl;
	}
	return true;
}
//restock, sale
bool Storage::log(string functiontype, int barcode, int qty)
{
	if(flag)
	{
		clog<<functiontype<<endl<<barcode<<endl<<qty<<endl<<endl;
	}
	return true;
}
//add and update
bool Storage::log(string functiontype, string name, string cat, string manu, double price, int barcode)
{
	if(flag)
	{
		clog<<functiontype<<endl<<name<<endl<<cat<<endl<<barcode<<endl<<manu<<endl<<price<<endl<<endl;
	}
	return true;
}
//remover
bool Storage::log(string functiontype, int barcode)
{
	if(flag)
	{
		clog<<functiontype<<endl<<barcode<<endl<<endl;
	}
	return true;
}
