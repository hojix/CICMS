/*******************************************************************
* This file contains the definition of
* all the graphical elements that interact with the user.
* All the click events and displaying functions are covered here
* Done by: Koh Wen Yao
*******************************************************************/

#ifndef _H_MYFORM
#define _H_MYFORM
#pragma once

#include <iostream>

class BatchProcessor;
class ProductList;

using namespace std;

namespace CEGHypermarket {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void); //constructor

	protected:
		~MyForm(); //destructor

#pragma endregion

#pragma region initialise
	private: bool bManu;
	private: int lastSelected;
	private: int column;
	private: bool order;
	private: bool loaded;
	private: bool addprod;
	private: ProductList* list; //initialise list

	private: System::Windows::Forms::ToolStripContainer^  toolStripContainer1;		 
	private: System::Windows::Forms::TextBox^  textBoxFBar;
	private: System::Windows::Forms::ComboBox^  comboBoxCat;
	private: System::Windows::Forms::Button^  buttonFilter;
	private: System::Windows::Forms::TextBox^  textBoxCat;
	private: System::Windows::Forms::TextBox^  textNoSold;
	private: System::Windows::Forms::TextBox^  textBoxName;
	private: System::Windows::Forms::Button^  buttonUpdate;
	private: System::Windows::Forms::TextBox^  textBoxStock;
	private: System::Windows::Forms::TextBox^  textBoxBar;
	private: System::Windows::Forms::TextBox^  textBoxManu;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Button^  buttonSell;
	private: System::Windows::Forms::Button^  buttonRestock;
	private: System::Windows::Forms::TextBox^  textBoxFName;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  backupToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::RadioButton^  radiobuttonManu;
	private: System::Windows::Forms::RadioButton^  radiobuttonCat;
	private: System::Windows::Forms::RadioButton^  radiobuttonBar;
	private: System::Windows::Forms::RadioButton^  radiobuttonName;
	private: System::Windows::Forms::GroupBox^  Details;
	private: System::Windows::Forms::ListView^  listView1;
	private: System::Windows::Forms::ColumnHeader^  Items;
	private: System::Windows::Forms::ColumnHeader^  Price;
	private: System::Windows::Forms::ColumnHeader^  Manufacturer;
	private: System::Windows::Forms::ColumnHeader^  Stock;
	private: System::Windows::Forms::ColumnHeader^  Category;
	private: System::Windows::Forms::GroupBox^  filterBox;
	private: System::Windows::Forms::TextBox^  textBoxPrice;
	private: System::Windows::Forms::TextBox^  textBoxQty;
	private: System::Windows::Forms::ColumnHeader^  NoSold;
	private: System::Windows::Forms::GroupBox^  stockBox;
	private: System::Windows::Forms::ToolStripMenuItem^  statisticsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  bestToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  bestsellingManufacturerToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  lowStockToolStripMenuItem;
	private: System::Windows::Forms::ColumnHeader^  BarCode;
	private: System::Windows::Forms::Button^  buttonRemove;
	private: System::Windows::Forms::ToolStripMenuItem^  newToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  productToolStripMenuItem1;
	private: System::Windows::Forms::ComboBox^  comboBoxManu;
	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  saveAsToolStripMenuItem;
	private: System::Windows::Forms::StatusStrip^  statusbar;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
	private: System::Windows::Forms::StatusStrip^  prodNumBar;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel2;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel3;
	private: System::Windows::Forms::ToolStripTextBox^  toolStripTextBox1;
	private: System::Windows::Forms::ToolStripMenuItem^  pleaseEnterUpperLimitBelowToolStripMenuItem;
	private: System::Windows::Forms::Button^  buttonShowAll;
	private: System::Windows::Forms::ToolStripMenuItem^  productListToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  batchJobsToolStripMenuItem;
	private: System::Windows::Forms::StatusStrip^  progressBar;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel5;
	private: System::Windows::Forms::ToolStripStatusLabel^  statbarLabel;
	private: System::Windows::Forms::ToolStripStatusLabel^  statbarStatus;
	private: System::Windows::Forms::ToolStripStatusLabel^  progbarLabel;
	private: System::Windows::Forms::ToolStripStatusLabel^  progbarStatus;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;

#pragma endregion

#pragma region Windows Form Designer generated code
			 /// Required method for Designer support - do not modify
			 /// the contents of this method with the code editor.
			 void InitializeComponent(void);
#pragma endregion


			 /*****************************/
			 /*         Functions         */
			 /*****************************/

			 //Add new product
	private: void addNew();

			 //load product list
	private: void loadFunc();

			 //load batch jobs
	private: void batchFunc();

			 ///Save
	private: void saveFunc();

			 //Backup
	private: void backupFunc();

			 //Best Selling product
	private: void bestSellingFunc();

			 //Best Manufacturer
	private: void bestManuFunc();

			 //Filter
	private: void filterFunc();


			 /*****************************/
			 /*      Other Functions      */
			 /*****************************/

			 //update status for batch processing - to be called by batchprocessor
	public: void updateStatus(string stat);

			//initial set up of progressbar
	public: void progSet(Color colour);

			//Update text on progress bar
	public: void statusProg(double perc, string str);

			///convert system string to string
	private: Void static MarshalString ( System::String^ s, std::string& os )
			 {
				 using namespace System::Runtime::InteropServices;   
				 const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();   
				 os = chars;
				 Marshal::FreeHGlobal(IntPtr((void*)chars));
			 }

			 //refresh combobox
	private: void comboRefresh();

			 //print out list in listview*
	private: void printlist (ProductList *list1);

			 //Accept only digits and the Backspace character
	private: System::Void Digitonly_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);

			 //Accept only one decimal point and 2 digits after decimal
	private: System::Void priceKeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);

			 //Clear all product details from textboxes
	private: void clearDetails();

			 //Change status bar text and colour
	private: void statusChange(String^ str, Color colour);

			 //change number of products in status bar
	private: void prodnum(int num);

			 //Set statusbar to ready
	private: void statusReady();

			 //Check if best manufacturer is displayed, if displayed, revert back to normal
	private: void checkBestManu();


			 /*****************************/
			 /*      Event Functions      */
			 /*****************************/

			 /*****file menu*****/

			 //when user clicks on add new product
	private: System::Void clickAddNew(System::Object^  sender, System::EventArgs^  e);
			 //when user clicks on load
	private: System::Void Load_Click(System::Object^  sender, System::EventArgs^  e);
			 //when user clicks on load batch jobs
	private: System::Void batchProcess(System::Object^  sender, System::EventArgs^  e);
			 //when user clicks on save
	private: System::Void Save(System::Object^  sender, System::EventArgs^  e);
			 //when user clicks on saveas
	private: System::Void SaveAs(System::Object^  sender, System::EventArgs^  e);
			 //when user clicks on backup
	private: System::Void BackUp(System::Object^  sender, System::EventArgs^  e);
			 

			 /*****Statistics Menu*****/

			 //when user clicks on best manufacturer
	private: System::Void bestManu(System::Object^  sender, System::EventArgs^  e);
			 //when user click on best selling product
	private: System::Void BestSelling(System::Object^  sender, System::EventArgs^  e);
			 //clear low stock textbox 
	private: System::Void clearLowStkBox(System::Object^  sender, System::EventArgs^  e);
			 //when user presses "enter" after typing upperlimit for low stock
	private: System::Void lowStockPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
			 //when user clicks on showall products
	private: System::Void ShowAll(System::Object^  sender, System::EventArgs^  e);


			 /*****Filter Bar*****/

			 //when user clicks on 'filter'
	private: System::Void filter_click(System::Object^  sender, System::EventArgs^  e);
			 //when user presses 'enter' after specifying filter criteria
	private: System::Void filterDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);


			 /*****listview*****/

			 //when user clicks on a column
	private: System::Void listView1_ColumnClick(System::Object^  sender, System::Windows::Forms::ColumnClickEventArgs^  e);
			 //when user clicks on an item in the list
	private: System::Void listView1_ItemActivate(System::Object^  sender, System::EventArgs^  e);


			 /*****Stockkeeping box*****/

			 //when user clicks on quantity textbox in stockkeeping section
	private: System::Void textBoxQty_Click(System::Object^  sender, System::EventArgs^  e);
			 //when user clicks on restock 
	private: System::Void Restock(System::Object^  sender, System::EventArgs^  e);
			 //when user clicks on sell
	private: System::Void sell_click(System::Object^  sender, System::EventArgs^  e);


			 /*****Product Details box*****/

			 //when user clicks on remove/cancel button
	private: System::Void removeClick(System::Object^  sender, System::EventArgs^  e);
			 //when user clicks on update/add product
	private: System::Void updateClick(System::Object^  sender, System::EventArgs^  e);
			 //clears barcode textbox
	private: System::Void clearBarBox(System::Object^  sender, System::EventArgs^  e);
			 //clears name textbox
	private: System::Void clearNameBox(System::Object^  sender, System::EventArgs^  e);
			 //clears category textbox
	private: System::Void clearCatBox(System::Object^  sender, System::EventArgs^  e);
			 //clears manufacturer textbox
	private: System::Void clearManuBox(System::Object^  sender, System::EventArgs^  e);
			 //clears price textbox
	private: System::Void clearPriceBox(System::Object^  sender, System::EventArgs^  e);


			 /*****Shortcut keys*****/
	private: System::Void shortcuts(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
	};
}
#endif