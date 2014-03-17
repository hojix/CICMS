/**************************************************************
* This file implements the functions defined in MyForm.h      *
*                                                             *
* Done by: Koh Wen Yao                                        *
***************************************************************/

#include "MyForm.h"
#include "ListViewComparer.h"
#include "ProductList.h"
#include <sstream>

using namespace CEGHypermarket;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

//constructor
MyForm::MyForm(void)
{
	bManu =false; //true if Best Manufacturer displayed
	lastSelected = -1; //index of last selected item
	column=-1;
	order = true;
	loaded = false; //true if user has loaded product list
	addprod = false; //true if user click on file->new->product
	list = new ProductList;
	InitializeComponent();
}

//destructor
MyForm::~MyForm()
{
	if(loaded && !list->checkLog()){
		//if there are unsaved changes
		if (MessageBox::Show("There are unsaved changes, do you wish to save them?\nClick Yes to save.\nClick No to discard unsaved changes","Confirmation",MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes){
			this->Cursor = Cursors::WaitCursor;
			statusChange("Saving Changes...",Color::DarkOrchid);
		}
		//clear log if changes are to be discarded
		else
			list->emptylog();

		loaded = false;
	}
	list->Finalize();
}

void MyForm::InitializeComponent(void)
{
	System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
	this->toolStripContainer1 = (gcnew System::Windows::Forms::ToolStripContainer());
	this->Details = (gcnew System::Windows::Forms::GroupBox());
	this->buttonRemove = (gcnew System::Windows::Forms::Button());
	this->textBoxPrice = (gcnew System::Windows::Forms::TextBox());
	this->label1 = (gcnew System::Windows::Forms::Label());
	this->textBoxName = (gcnew System::Windows::Forms::TextBox());
	this->textBoxCat = (gcnew System::Windows::Forms::TextBox());
	this->label3 = (gcnew System::Windows::Forms::Label());
	this->textBoxManu = (gcnew System::Windows::Forms::TextBox());
	this->textBoxBar = (gcnew System::Windows::Forms::TextBox());
	this->buttonUpdate = (gcnew System::Windows::Forms::Button());
	this->label7 = (gcnew System::Windows::Forms::Label());
	this->textNoSold = (gcnew System::Windows::Forms::TextBox());
	this->label6 = (gcnew System::Windows::Forms::Label());
	this->textBoxStock = (gcnew System::Windows::Forms::TextBox());
	this->label2 = (gcnew System::Windows::Forms::Label());
	this->label5 = (gcnew System::Windows::Forms::Label());
	this->label4 = (gcnew System::Windows::Forms::Label());
	this->prodNumBar = (gcnew System::Windows::Forms::StatusStrip());
	this->toolStripStatusLabel2 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
	this->toolStripStatusLabel3 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
	this->stockBox = (gcnew System::Windows::Forms::GroupBox());
	this->textBoxQty = (gcnew System::Windows::Forms::TextBox());
	this->buttonRestock = (gcnew System::Windows::Forms::Button());
	this->buttonSell = (gcnew System::Windows::Forms::Button());
	this->filterBox = (gcnew System::Windows::Forms::GroupBox());
	this->comboBoxManu = (gcnew System::Windows::Forms::ComboBox());
	this->textBoxFName = (gcnew System::Windows::Forms::TextBox());
	this->radiobuttonName = (gcnew System::Windows::Forms::RadioButton());
	this->textBoxFBar = (gcnew System::Windows::Forms::TextBox());
	this->radiobuttonManu = (gcnew System::Windows::Forms::RadioButton());
	this->comboBoxCat = (gcnew System::Windows::Forms::ComboBox());
	this->radiobuttonCat = (gcnew System::Windows::Forms::RadioButton());
	this->buttonFilter = (gcnew System::Windows::Forms::Button());
	this->radiobuttonBar = (gcnew System::Windows::Forms::RadioButton());
	this->listView1 = (gcnew System::Windows::Forms::ListView());
	this->Items = (gcnew System::Windows::Forms::ColumnHeader());
	this->BarCode = (gcnew System::Windows::Forms::ColumnHeader());
	this->Category = (gcnew System::Windows::Forms::ColumnHeader());
	this->Manufacturer = (gcnew System::Windows::Forms::ColumnHeader());
	this->Price = (gcnew System::Windows::Forms::ColumnHeader());
	this->NoSold = (gcnew System::Windows::Forms::ColumnHeader());
	this->Stock = (gcnew System::Windows::Forms::ColumnHeader());
	this->buttonShowAll = (gcnew System::Windows::Forms::Button());
	this->progressBar = (gcnew System::Windows::Forms::StatusStrip());
	this->progbarLabel = (gcnew System::Windows::Forms::ToolStripStatusLabel());
	this->progbarStatus = (gcnew System::Windows::Forms::ToolStripStatusLabel());
	this->statusbar = (gcnew System::Windows::Forms::StatusStrip());
	this->statbarLabel = (gcnew System::Windows::Forms::ToolStripStatusLabel());
	this->statbarStatus = (gcnew System::Windows::Forms::ToolStripStatusLabel());
	this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
	this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
	this->newToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
	this->productToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
	this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
	this->productListToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
	this->batchJobsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
	this->saveToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
	this->saveAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
	this->backupToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
	this->statisticsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
	this->bestToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
	this->bestsellingManufacturerToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
	this->lowStockToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
	this->pleaseEnterUpperLimitBelowToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
	this->toolStripTextBox1 = (gcnew System::Windows::Forms::ToolStripTextBox());
	this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
	this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
	this->toolStripContainer1->ContentPanel->SuspendLayout();
	this->toolStripContainer1->TopToolStripPanel->SuspendLayout();
	this->toolStripContainer1->SuspendLayout();
	this->Details->SuspendLayout();
	this->prodNumBar->SuspendLayout();
	this->stockBox->SuspendLayout();
	this->filterBox->SuspendLayout();
	this->progressBar->SuspendLayout();
	this->statusbar->SuspendLayout();
	this->menuStrip1->SuspendLayout();
	this->SuspendLayout();
	// 
	// toolStripContainer1
	// 
	this->toolStripContainer1->BottomToolStripPanelVisible = false;
	// 
	// toolStripContainer1.ContentPanel
	// 
	this->toolStripContainer1->ContentPanel->Controls->Add(this->Details);
	this->toolStripContainer1->ContentPanel->Controls->Add(this->prodNumBar);
	this->toolStripContainer1->ContentPanel->Controls->Add(this->stockBox);
	this->toolStripContainer1->ContentPanel->Controls->Add(this->filterBox);
	this->toolStripContainer1->ContentPanel->Controls->Add(this->listView1);
	this->toolStripContainer1->ContentPanel->Controls->Add(this->buttonShowAll);
	this->toolStripContainer1->ContentPanel->Controls->Add(this->progressBar);
	this->toolStripContainer1->ContentPanel->Controls->Add(this->statusbar);
	this->toolStripContainer1->ContentPanel->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, 
		System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
	this->toolStripContainer1->ContentPanel->Size = System::Drawing::Size(844, 422);
	this->toolStripContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
	this->toolStripContainer1->LeftToolStripPanelVisible = false;
	this->toolStripContainer1->Location = System::Drawing::Point(0, 0);
	this->toolStripContainer1->Name = L"toolStripContainer1";
	this->toolStripContainer1->RightToolStripPanelVisible = false;
	this->toolStripContainer1->Size = System::Drawing::Size(844, 446);
	this->toolStripContainer1->TabIndex = 0;
	this->toolStripContainer1->Text = L"toolStripContainer1";
	// 
	// toolStripContainer1.TopToolStripPanel
	// 
	this->toolStripContainer1->TopToolStripPanel->BackColor = System::Drawing::SystemColors::MenuBar;
	this->toolStripContainer1->TopToolStripPanel->Controls->Add(this->menuStrip1);
	this->toolStripContainer1->TopToolStripPanel->ImeMode = System::Windows::Forms::ImeMode::NoControl;
	// 
	// Details
	// 
	this->Details->BackColor = System::Drawing::SystemColors::Control;
	this->Details->Controls->Add(this->buttonRemove);
	this->Details->Controls->Add(this->textBoxPrice);
	this->Details->Controls->Add(this->label1);
	this->Details->Controls->Add(this->textBoxName);
	this->Details->Controls->Add(this->textBoxCat);
	this->Details->Controls->Add(this->label3);
	this->Details->Controls->Add(this->textBoxManu);
	this->Details->Controls->Add(this->textBoxBar);
	this->Details->Controls->Add(this->buttonUpdate);
	this->Details->Controls->Add(this->label7);
	this->Details->Controls->Add(this->textNoSold);
	this->Details->Controls->Add(this->label6);
	this->Details->Controls->Add(this->textBoxStock);
	this->Details->Controls->Add(this->label2);
	this->Details->Controls->Add(this->label5);
	this->Details->Controls->Add(this->label4);
	this->Details->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
	this->Details->Location = System::Drawing::Point(626, 109);
	this->Details->Name = L"Details";
	this->Details->Size = System::Drawing::Size(211, 242);
	this->Details->TabIndex = 43;
	this->Details->TabStop = false;
	this->Details->Text = L"Product Details";
	// 
	// buttonRemove
	// 
	this->buttonRemove->BackColor = System::Drawing::Color::Red;
	this->buttonRemove->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"buttonRemove.BackgroundImage")));
	this->buttonRemove->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
	this->buttonRemove->FlatAppearance->BorderColor = System::Drawing::Color::Red;
	this->buttonRemove->FlatAppearance->BorderSize = 10;
	this->buttonRemove->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
	this->buttonRemove->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->buttonRemove->ForeColor = System::Drawing::Color::White;
	this->buttonRemove->Location = System::Drawing::Point(22, 209);
	this->buttonRemove->Name = L"buttonRemove";
	this->buttonRemove->Size = System::Drawing::Size(86, 23);
	this->buttonRemove->TabIndex = 18;
	this->buttonRemove->Text = L"Remove";
	this->buttonRemove->UseVisualStyleBackColor = false;
	this->buttonRemove->Click += gcnew System::EventHandler(this, &MyForm::removeClick);
	// 
	// textBoxPrice
	// 
	this->textBoxPrice->Location = System::Drawing::Point(79, 101);
	this->textBoxPrice->Name = L"textBoxPrice";
	this->textBoxPrice->Size = System::Drawing::Size(121, 21);
	this->textBoxPrice->TabIndex = 13;
	this->textBoxPrice->Click += gcnew System::EventHandler(this, &MyForm::clearPriceBox);
	this->textBoxPrice->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::priceKeyPress);
	// 
	// label1
	// 
	this->label1->AutoSize = true;
	this->label1->Location = System::Drawing::Point(37, 23);
	this->label1->Name = L"label1";
	this->label1->Size = System::Drawing::Size(34, 13);
	this->label1->TabIndex = 17;
	this->label1->Text = L"Name";
	// 
	// textBoxName
	// 
	this->textBoxName->Location = System::Drawing::Point(79, 20);
	this->textBoxName->Name = L"textBoxName";
	this->textBoxName->Size = System::Drawing::Size(121, 21);
	this->textBoxName->TabIndex = 10;
	this->textBoxName->Click += gcnew System::EventHandler(this, &MyForm::clearNameBox);
	// 
	// textBoxCat
	// 
	this->textBoxCat->Location = System::Drawing::Point(79, 47);
	this->textBoxCat->Name = L"textBoxCat";
	this->textBoxCat->Size = System::Drawing::Size(121, 21);
	this->textBoxCat->TabIndex = 11;
	this->textBoxCat->Click += gcnew System::EventHandler(this, &MyForm::clearCatBox);
	// 
	// label3
	// 
	this->label3->AutoSize = true;
	this->label3->Location = System::Drawing::Point(19, 50);
	this->label3->Name = L"label3";
	this->label3->Size = System::Drawing::Size(52, 13);
	this->label3->TabIndex = 19;
	this->label3->Text = L"Category";
	// 
	// textBoxManu
	// 
	this->textBoxManu->Location = System::Drawing::Point(79, 74);
	this->textBoxManu->Name = L"textBoxManu";
	this->textBoxManu->Size = System::Drawing::Size(121, 21);
	this->textBoxManu->TabIndex = 12;
	this->textBoxManu->Click += gcnew System::EventHandler(this, &MyForm::clearManuBox);
	// 
	// textBoxBar
	// 
	this->textBoxBar->BackColor = System::Drawing::SystemColors::Control;
	this->textBoxBar->Cursor = System::Windows::Forms::Cursors::No;
	this->textBoxBar->Location = System::Drawing::Point(79, 128);
	this->textBoxBar->MaxLength = 9;
	this->textBoxBar->Name = L"textBoxBar";
	this->textBoxBar->ReadOnly = true;
	this->textBoxBar->Size = System::Drawing::Size(121, 21);
	this->textBoxBar->TabIndex = 14;
	this->textBoxBar->Click += gcnew System::EventHandler(this, &MyForm::clearBarBox);
	this->textBoxBar->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::Digitonly_KeyPress);
	// 
	// buttonUpdate
	// 
	this->buttonUpdate->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->buttonUpdate->Location = System::Drawing::Point(114, 209);
	this->buttonUpdate->Name = L"buttonUpdate";
	this->buttonUpdate->Size = System::Drawing::Size(86, 23);
	this->buttonUpdate->TabIndex = 17;
	this->buttonUpdate->Text = L"Update";
	this->buttonUpdate->UseVisualStyleBackColor = true;
	this->buttonUpdate->Click += gcnew System::EventHandler(this, &MyForm::updateClick);
	// 
	// label7
	// 
	this->label7->AutoSize = true;
	this->label7->Location = System::Drawing::Point(38, 185);
	this->label7->Name = L"label7";
	this->label7->Size = System::Drawing::Size(33, 13);
	this->label7->TabIndex = 23;
	this->label7->Text = L"Stock";
	// 
	// textNoSold
	// 
	this->textNoSold->BackColor = System::Drawing::SystemColors::Control;
	this->textNoSold->Cursor = System::Windows::Forms::Cursors::No;
	this->textNoSold->Location = System::Drawing::Point(79, 155);
	this->textNoSold->MaxLength = 500;
	this->textNoSold->Name = L"textNoSold";
	this->textNoSold->ReadOnly = true;
	this->textNoSold->Size = System::Drawing::Size(121, 21);
	this->textNoSold->TabIndex = 15;
	// 
	// label6
	// 
	this->label6->AutoSize = true;
	this->label6->Location = System::Drawing::Point(17, 158);
	this->label6->Name = L"label6";
	this->label6->Size = System::Drawing::Size(54, 13);
	this->label6->TabIndex = 22;
	this->label6->Text = L"Units Sold";
	// 
	// textBoxStock
	// 
	this->textBoxStock->BackColor = System::Drawing::SystemColors::Control;
	this->textBoxStock->Cursor = System::Windows::Forms::Cursors::No;
	this->textBoxStock->Location = System::Drawing::Point(79, 182);
	this->textBoxStock->MaxLength = 500;
	this->textBoxStock->Name = L"textBoxStock";
	this->textBoxStock->ReadOnly = true;
	this->textBoxStock->Size = System::Drawing::Size(121, 21);
	this->textBoxStock->TabIndex = 16;
	// 
	// label2
	// 
	this->label2->AutoSize = true;
	this->label2->Location = System::Drawing::Point(25, 131);
	this->label2->Name = L"label2";
	this->label2->Size = System::Drawing::Size(46, 13);
	this->label2->TabIndex = 18;
	this->label2->Text = L"Barcode";
	// 
	// label5
	// 
	this->label5->AutoSize = true;
	this->label5->Location = System::Drawing::Point(41, 104);
	this->label5->Name = L"label5";
	this->label5->Size = System::Drawing::Size(30, 13);
	this->label5->TabIndex = 21;
	this->label5->Text = L"Price";
	// 
	// label4
	// 
	this->label4->AutoSize = true;
	this->label4->Location = System::Drawing::Point(3, 77);
	this->label4->Name = L"label4";
	this->label4->Size = System::Drawing::Size(72, 13);
	this->label4->TabIndex = 20;
	this->label4->Text = L"Manufacturer";
	// 
	// prodNumBar
	// 
	this->prodNumBar->BackColor = System::Drawing::Color::CornflowerBlue;
	this->prodNumBar->Dock = System::Windows::Forms::DockStyle::None;
	this->prodNumBar->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->toolStripStatusLabel2, 
		this->toolStripStatusLabel3});
	this->prodNumBar->Location = System::Drawing::Point(626, 400);
	this->prodNumBar->Name = L"prodNumBar";
	this->prodNumBar->Size = System::Drawing::Size(157, 22);
	this->prodNumBar->SizingGrip = false;
	this->prodNumBar->TabIndex = 49;
	this->prodNumBar->Text = L"prodNumBar";
	// 
	// toolStripStatusLabel2
	// 
	this->toolStripStatusLabel2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->toolStripStatusLabel2->Name = L"toolStripStatusLabel2";
	this->toolStripStatusLabel2->Size = System::Drawing::Size(126, 17);
	this->toolStripStatusLabel2->Text = L"Number of products: ";
	// 
	// toolStripStatusLabel3
	// 
	this->toolStripStatusLabel3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->toolStripStatusLabel3->Name = L"toolStripStatusLabel3";
	this->toolStripStatusLabel3->Size = System::Drawing::Size(14, 17);
	this->toolStripStatusLabel3->Text = L"0";
	// 
	// stockBox
	// 
	this->stockBox->Controls->Add(this->textBoxQty);
	this->stockBox->Controls->Add(this->buttonRestock);
	this->stockBox->Controls->Add(this->buttonSell);
	this->stockBox->Location = System::Drawing::Point(626, 3);
	this->stockBox->Name = L"stockBox";
	this->stockBox->Size = System::Drawing::Size(211, 100);
	this->stockBox->TabIndex = 45;
	this->stockBox->TabStop = false;
	this->stockBox->Text = L"Stock Keep";
	// 
	// textBoxQty
	// 
	this->textBoxQty->Location = System::Drawing::Point(6, 20);
	this->textBoxQty->MaxLength = 9;
	this->textBoxQty->Name = L"textBoxQty";
	this->textBoxQty->Size = System::Drawing::Size(194, 21);
	this->textBoxQty->TabIndex = 19;
	this->textBoxQty->Text = L"<Enter amount to restock / sell>";
	this->textBoxQty->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
	this->textBoxQty->Click += gcnew System::EventHandler(this, &MyForm::textBoxQty_Click);
	this->textBoxQty->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::Digitonly_KeyPress);
	// 
	// buttonRestock
	// 
	this->buttonRestock->BackColor = System::Drawing::SystemColors::Control;
	this->buttonRestock->ForeColor = System::Drawing::SystemColors::ControlText;
	this->buttonRestock->Location = System::Drawing::Point(6, 47);
	this->buttonRestock->Name = L"buttonRestock";
	this->buttonRestock->Size = System::Drawing::Size(95, 38);
	this->buttonRestock->TabIndex = 20;
	this->buttonRestock->Text = L"Restock";
	this->buttonRestock->UseVisualStyleBackColor = true;
	this->buttonRestock->Click += gcnew System::EventHandler(this, &MyForm::Restock);
	// 
	// buttonSell
	// 
	this->buttonSell->Location = System::Drawing::Point(105, 47);
	this->buttonSell->Name = L"buttonSell";
	this->buttonSell->Size = System::Drawing::Size(95, 38);
	this->buttonSell->TabIndex = 21;
	this->buttonSell->Text = L"Sell";
	this->buttonSell->UseVisualStyleBackColor = true;
	this->buttonSell->Click += gcnew System::EventHandler(this, &MyForm::sell_click);
	// 
	// filterBox
	// 
	this->filterBox->BackColor = System::Drawing::SystemColors::ButtonFace;
	this->filterBox->Controls->Add(this->comboBoxManu);
	this->filterBox->Controls->Add(this->textBoxFName);
	this->filterBox->Controls->Add(this->radiobuttonName);
	this->filterBox->Controls->Add(this->textBoxFBar);
	this->filterBox->Controls->Add(this->radiobuttonManu);
	this->filterBox->Controls->Add(this->comboBoxCat);
	this->filterBox->Controls->Add(this->radiobuttonCat);
	this->filterBox->Controls->Add(this->buttonFilter);
	this->filterBox->Controls->Add(this->radiobuttonBar);
	this->filterBox->Location = System::Drawing::Point(12, 3);
	this->filterBox->Name = L"filterBox";
	this->filterBox->Size = System::Drawing::Size(608, 74);
	this->filterBox->TabIndex = 44;
	this->filterBox->TabStop = false;
	this->filterBox->Text = L"Filter Bar";
	// 
	// comboBoxManu
	// 
	this->comboBoxManu->BackColor = System::Drawing::SystemColors::Window;
	this->comboBoxManu->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
	this->comboBoxManu->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
	this->comboBoxManu->FormattingEnabled = true;
	this->comboBoxManu->Location = System::Drawing::Point(381, 39);
	this->comboBoxManu->Name = L"comboBoxManu";
	this->comboBoxManu->Size = System::Drawing::Size(121, 21);
	this->comboBoxManu->TabIndex = 10;
	// 
	// textBoxFName
	// 
	this->textBoxFName->Location = System::Drawing::Point(6, 39);
	this->textBoxFName->MaxLength = 500;
	this->textBoxFName->Name = L"textBoxFName";
	this->textBoxFName->Size = System::Drawing::Size(119, 21);
	this->textBoxFName->TabIndex = 2;
	this->textBoxFName->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::filterDown);
	// 
	// radiobuttonName
	// 
	this->radiobuttonName->AutoSize = true;
	this->radiobuttonName->Location = System::Drawing::Point(6, 19);
	this->radiobuttonName->Name = L"radiobuttonName";
	this->radiobuttonName->Size = System::Drawing::Size(52, 17);
	this->radiobuttonName->TabIndex = 1;
	this->radiobuttonName->TabStop = true;
	this->radiobuttonName->Text = L"Name";
	this->radiobuttonName->UseVisualStyleBackColor = true;
	// 
	// textBoxFBar
	// 
	this->textBoxFBar->Location = System::Drawing::Point(131, 39);
	this->textBoxFBar->MaxLength = 9;
	this->textBoxFBar->Name = L"textBoxFBar";
	this->textBoxFBar->Size = System::Drawing::Size(119, 21);
	this->textBoxFBar->TabIndex = 4;
	this->textBoxFBar->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::filterDown);
	this->textBoxFBar->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::Digitonly_KeyPress);
	// 
	// radiobuttonManu
	// 
	this->radiobuttonManu->AutoSize = true;
	this->radiobuttonManu->Location = System::Drawing::Point(381, 19);
	this->radiobuttonManu->Name = L"radiobuttonManu";
	this->radiobuttonManu->Size = System::Drawing::Size(90, 17);
	this->radiobuttonManu->TabIndex = 7;
	this->radiobuttonManu->TabStop = true;
	this->radiobuttonManu->Text = L"Manufacturer";
	this->radiobuttonManu->UseVisualStyleBackColor = true;
	// 
	// comboBoxCat
	// 
	this->comboBoxCat->BackColor = System::Drawing::SystemColors::Window;
	this->comboBoxCat->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
	this->comboBoxCat->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
	this->comboBoxCat->FormattingEnabled = true;
	this->comboBoxCat->Location = System::Drawing::Point(256, 39);
	this->comboBoxCat->Name = L"comboBoxCat";
	this->comboBoxCat->Size = System::Drawing::Size(119, 21);
	this->comboBoxCat->Sorted = true;
	this->comboBoxCat->TabIndex = 6;
	// 
	// radiobuttonCat
	// 
	this->radiobuttonCat->AutoSize = true;
	this->radiobuttonCat->Location = System::Drawing::Point(256, 19);
	this->radiobuttonCat->Name = L"radiobuttonCat";
	this->radiobuttonCat->Size = System::Drawing::Size(70, 17);
	this->radiobuttonCat->TabIndex = 5;
	this->radiobuttonCat->TabStop = true;
	this->radiobuttonCat->Text = L"Category";
	this->radiobuttonCat->UseVisualStyleBackColor = true;
	// 
	// buttonFilter
	// 
	this->buttonFilter->BackColor = System::Drawing::SystemColors::Control;
	this->buttonFilter->FlatStyle = System::Windows::Forms::FlatStyle::System;
	this->buttonFilter->Location = System::Drawing::Point(508, 20);
	this->buttonFilter->Name = L"buttonFilter";
	this->buttonFilter->Size = System::Drawing::Size(94, 40);
	this->buttonFilter->TabIndex = 9;
	this->buttonFilter->Text = L"Filter";
	this->buttonFilter->UseVisualStyleBackColor = true;
	this->buttonFilter->Click += gcnew System::EventHandler(this, &MyForm::filter_click);
	// 
	// radiobuttonBar
	// 
	this->radiobuttonBar->AutoSize = true;
	this->radiobuttonBar->Location = System::Drawing::Point(131, 19);
	this->radiobuttonBar->Name = L"radiobuttonBar";
	this->radiobuttonBar->Size = System::Drawing::Size(64, 17);
	this->radiobuttonBar->TabIndex = 3;
	this->radiobuttonBar->TabStop = true;
	this->radiobuttonBar->Text = L"Barcode";
	this->radiobuttonBar->UseVisualStyleBackColor = true;
	// 
	// listView1
	// 
	this->listView1->Activation = System::Windows::Forms::ItemActivation::OneClick;
	this->listView1->AutoArrange = false;
	this->listView1->BackColor = System::Drawing::SystemColors::Window;
	this->listView1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->listView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(7) {this->Items, this->BarCode, 
		this->Category, this->Manufacturer, this->Price, this->NoSold, this->Stock});
	this->listView1->Cursor = System::Windows::Forms::Cursors::Arrow;
	this->listView1->FullRowSelect = true;
	this->listView1->GridLines = true;
	this->listView1->HideSelection = false;
	this->listView1->Location = System::Drawing::Point(12, 83);
	this->listView1->MultiSelect = false;
	this->listView1->Name = L"listView1";
	this->listView1->Size = System::Drawing::Size(608, 309);
	this->listView1->TabIndex = 45;
	this->listView1->UseCompatibleStateImageBehavior = false;
	this->listView1->View = System::Windows::Forms::View::Details;
	this->listView1->ColumnClick += gcnew System::Windows::Forms::ColumnClickEventHandler(this, &MyForm::listView1_ColumnClick);
	this->listView1->ItemActivate += gcnew System::EventHandler(this, &MyForm::listView1_ItemActivate);
	// 
	// Items
	// 
	this->Items->Text = L"Item Name";
	this->Items->Width = 112;
	// 
	// BarCode
	// 
	this->BarCode->Text = L"BarCode";
	this->BarCode->Width = 78;
	// 
	// Category
	// 
	this->Category->Text = L"Category";
	this->Category->Width = 112;
	// 
	// Manufacturer
	// 
	this->Manufacturer->Text = L"Manufacturer";
	this->Manufacturer->Width = 110;
	// 
	// Price
	// 
	this->Price->Text = L"Price";
	this->Price->Width = 65;
	// 
	// NoSold
	// 
	this->NoSold->Text = L"No. Sold";
	this->NoSold->Width = 56;
	// 
	// Stock
	// 
	this->Stock->Text = L"Stock";
	this->Stock->Width = 62;
	// 
	// buttonShowAll
	// 
	this->buttonShowAll->Font = (gcnew System::Drawing::Font(L"Tahoma", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->buttonShowAll->Location = System::Drawing::Point(626, 357);
	this->buttonShowAll->Name = L"buttonShowAll";
	this->buttonShowAll->Size = System::Drawing::Size(211, 35);
	this->buttonShowAll->TabIndex = 50;
	this->buttonShowAll->Text = L"Show All Products";
	this->buttonShowAll->UseVisualStyleBackColor = true;
	this->buttonShowAll->Click += gcnew System::EventHandler(this, &MyForm::ShowAll);
	// 
	// progressBar
	// 
	this->progressBar->AutoSize = false;
	this->progressBar->BackColor = System::Drawing::Color::CornflowerBlue;
	this->progressBar->Dock = System::Windows::Forms::DockStyle::None;
	this->progressBar->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->progressBar->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->progbarLabel, this->progbarStatus});
	this->progressBar->Location = System::Drawing::Point(0, 400);
	this->progressBar->Name = L"progressBar";
	this->progressBar->Size = System::Drawing::Size(844, 22);
	this->progressBar->SizingGrip = false;
	this->progressBar->TabIndex = 51;
	this->progressBar->Text = L"progressBar";
	this->progressBar->Visible = false;
	// 
	// progbarLabel
	// 
	this->progbarLabel->ForeColor = System::Drawing::Color::White;
	this->progbarLabel->Name = L"progbarLabel";
	this->progbarLabel->Size = System::Drawing::Size(45, 17);
	this->progbarLabel->Text = L"Status:";
	// 
	// progbarStatus
	// 
	this->progbarStatus->ForeColor = System::Drawing::Color::White;
	this->progbarStatus->Name = L"progbarStatus";
	this->progbarStatus->Size = System::Drawing::Size(41, 17);
	this->progbarStatus->Text = L"Ready";
	// 
	// statusbar
	// 
	this->statusbar->BackColor = System::Drawing::Color::CornflowerBlue;
	this->statusbar->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->statusbar->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->statbarLabel, this->statbarStatus});
	this->statusbar->Location = System::Drawing::Point(0, 400);
	this->statusbar->Name = L"statusbar";
	this->statusbar->Size = System::Drawing::Size(844, 22);
	this->statusbar->SizingGrip = false;
	this->statusbar->TabIndex = 48;
	this->statusbar->Text = L"statusbar";
	// 
	// statbarLabel
	// 
	this->statbarLabel->Name = L"statbarLabel";
	this->statbarLabel->Size = System::Drawing::Size(45, 17);
	this->statbarLabel->Text = L"Status:";
	// 
	// statbarStatus
	// 
	this->statbarStatus->Name = L"statbarStatus";
	this->statbarStatus->Size = System::Drawing::Size(41, 17);
	this->statbarStatus->Text = L"Ready";
	// 
	// menuStrip1
	// 
	this->menuStrip1->Dock = System::Windows::Forms::DockStyle::None;
	this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->fileToolStripMenuItem, 
		this->statisticsToolStripMenuItem});
	this->menuStrip1->Location = System::Drawing::Point(0, 0);
	this->menuStrip1->Name = L"menuStrip1";
	this->menuStrip1->Size = System::Drawing::Size(844, 24);
	this->menuStrip1->TabIndex = 1;
	this->menuStrip1->Text = L"menuStrip1";
	// 
	// fileToolStripMenuItem
	// 
	this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->newToolStripMenuItem, 
		this->saveToolStripMenuItem, this->saveToolStripMenuItem1, this->saveAsToolStripMenuItem, this->backupToolStripMenuItem});
	this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
	this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
	this->fileToolStripMenuItem->Text = L"File";
	// 
	// newToolStripMenuItem
	// 
	this->newToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->productToolStripMenuItem1});
	this->newToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"newToolStripMenuItem.Image")));
	this->newToolStripMenuItem->Name = L"newToolStripMenuItem";
	this->newToolStripMenuItem->Size = System::Drawing::Size(154, 22);
	this->newToolStripMenuItem->Text = L"New";
	// 
	// productToolStripMenuItem1
	// 
	this->productToolStripMenuItem1->Name = L"productToolStripMenuItem1";
	this->productToolStripMenuItem1->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::N));
	this->productToolStripMenuItem1->Size = System::Drawing::Size(159, 22);
	this->productToolStripMenuItem1->Text = L"Product";
	this->productToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyForm::clickAddNew);
	// 
	// saveToolStripMenuItem
	// 
	this->saveToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->productListToolStripMenuItem, 
		this->batchJobsToolStripMenuItem});
	this->saveToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"saveToolStripMenuItem.Image")));
	this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
	this->saveToolStripMenuItem->Size = System::Drawing::Size(154, 22);
	this->saveToolStripMenuItem->Text = L"Load";
	// 
	// productListToolStripMenuItem
	// 
	this->productListToolStripMenuItem->Name = L"productListToolStripMenuItem";
	this->productListToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::L));
	this->productListToolStripMenuItem->Size = System::Drawing::Size(177, 22);
	this->productListToolStripMenuItem->Text = L"Product List";
	this->productListToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::Load_Click);
	// 
	// batchJobsToolStripMenuItem
	// 
	this->batchJobsToolStripMenuItem->Name = L"batchJobsToolStripMenuItem";
	this->batchJobsToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::J));
	this->batchJobsToolStripMenuItem->Size = System::Drawing::Size(177, 22);
	this->batchJobsToolStripMenuItem->Text = L"Batch Jobs";
	this->batchJobsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::batchProcess);
	// 
	// saveToolStripMenuItem1
	// 
	this->saveToolStripMenuItem1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"saveToolStripMenuItem1.Image")));
	this->saveToolStripMenuItem1->Name = L"saveToolStripMenuItem1";
	this->saveToolStripMenuItem1->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
	this->saveToolStripMenuItem1->Size = System::Drawing::Size(154, 22);
	this->saveToolStripMenuItem1->Text = L"Save";
	this->saveToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyForm::Save);
	// 
	// saveAsToolStripMenuItem
	// 
	this->saveAsToolStripMenuItem->Name = L"saveAsToolStripMenuItem";
	this->saveAsToolStripMenuItem->Size = System::Drawing::Size(154, 22);
	this->saveAsToolStripMenuItem->Text = L"Save As..";
	this->saveAsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::SaveAs);
	// 
	// backupToolStripMenuItem
	// 
	this->backupToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"backupToolStripMenuItem.Image")));
	this->backupToolStripMenuItem->Name = L"backupToolStripMenuItem";
	this->backupToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::B));
	this->backupToolStripMenuItem->Size = System::Drawing::Size(154, 22);
	this->backupToolStripMenuItem->Text = L"Backup";
	this->backupToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::BackUp);
	// 
	// statisticsToolStripMenuItem
	// 
	this->statisticsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->bestToolStripMenuItem, 
		this->bestsellingManufacturerToolStripMenuItem, this->lowStockToolStripMenuItem});
	this->statisticsToolStripMenuItem->Name = L"statisticsToolStripMenuItem";
	this->statisticsToolStripMenuItem->Size = System::Drawing::Size(65, 20);
	this->statisticsToolStripMenuItem->Text = L"Statistics";
	// 
	// bestToolStripMenuItem
	// 
	this->bestToolStripMenuItem->Name = L"bestToolStripMenuItem";
	this->bestToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Alt) 
		| System::Windows::Forms::Keys::P));
	this->bestToolStripMenuItem->Size = System::Drawing::Size(278, 22);
	this->bestToolStripMenuItem->Text = L"Best-selling Product";
	this->bestToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::BestSelling);
	// 
	// bestsellingManufacturerToolStripMenuItem
	// 
	this->bestsellingManufacturerToolStripMenuItem->Name = L"bestsellingManufacturerToolStripMenuItem";
	this->bestsellingManufacturerToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Alt) 
		| System::Windows::Forms::Keys::M));
	this->bestsellingManufacturerToolStripMenuItem->Size = System::Drawing::Size(278, 22);
	this->bestsellingManufacturerToolStripMenuItem->Text = L"Best-selling Manufacturer";
	this->bestsellingManufacturerToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::bestManu);
	// 
	// lowStockToolStripMenuItem
	// 
	this->lowStockToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->pleaseEnterUpperLimitBelowToolStripMenuItem, 
		this->toolStripTextBox1});
	this->lowStockToolStripMenuItem->Name = L"lowStockToolStripMenuItem";
	this->lowStockToolStripMenuItem->Size = System::Drawing::Size(278, 22);
	this->lowStockToolStripMenuItem->Text = L"Low Stock";
	// 
	// pleaseEnterUpperLimitBelowToolStripMenuItem
	// 
	this->pleaseEnterUpperLimitBelowToolStripMenuItem->AutoSize = false;
	this->pleaseEnterUpperLimitBelowToolStripMenuItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
	this->pleaseEnterUpperLimitBelowToolStripMenuItem->Enabled = false;
	this->pleaseEnterUpperLimitBelowToolStripMenuItem->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
	this->pleaseEnterUpperLimitBelowToolStripMenuItem->Name = L"pleaseEnterUpperLimitBelowToolStripMenuItem";
	this->pleaseEnterUpperLimitBelowToolStripMenuItem->Size = System::Drawing::Size(215, 22);
	this->pleaseEnterUpperLimitBelowToolStripMenuItem->Text = L"Please enter Upper Limit below:";
	// 
	// toolStripTextBox1
	// 
	this->toolStripTextBox1->Name = L"toolStripTextBox1";
	this->toolStripTextBox1->Size = System::Drawing::Size(150, 23);
	this->toolStripTextBox1->Text = L"<Enter Upper Limit>";
	this->toolStripTextBox1->TextBoxTextAlign = System::Windows::Forms::HorizontalAlignment::Center;
	this->toolStripTextBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::lowStockPress);
	this->toolStripTextBox1->Click += gcnew System::EventHandler(this, &MyForm::clearLowStkBox);
	// 
	// openFileDialog1
	// 
	this->openFileDialog1->FileName = L"openFD";
	// 
	// saveFileDialog1
	// 
	this->saveFileDialog1->Filter = L"Text Document|*.txt";
	this->saveFileDialog1->Tag = L".txt";
	// 
	// MyForm
	// 
	this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	this->ClientSize = System::Drawing::Size(844, 446);
	this->Controls->Add(this->toolStripContainer1);
	this->Cursor = System::Windows::Forms::Cursors::Default;
	this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
	this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
	this->MainMenuStrip = this->menuStrip1;
	this->MaximizeBox = false;
	this->Name = L"MyForm";
	this->RightToLeft = System::Windows::Forms::RightToLeft::No;
	this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
	this->Text = L"CEG Hypermarket Inventory Control and Monitoring System C06-3";
	this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::shortcuts);
	this->toolStripContainer1->ContentPanel->ResumeLayout(false);
	this->toolStripContainer1->ContentPanel->PerformLayout();
	this->toolStripContainer1->TopToolStripPanel->ResumeLayout(false);
	this->toolStripContainer1->TopToolStripPanel->PerformLayout();
	this->toolStripContainer1->ResumeLayout(false);
	this->toolStripContainer1->PerformLayout();
	this->Details->ResumeLayout(false);
	this->Details->PerformLayout();
	this->prodNumBar->ResumeLayout(false);
	this->prodNumBar->PerformLayout();
	this->stockBox->ResumeLayout(false);
	this->stockBox->PerformLayout();
	this->filterBox->ResumeLayout(false);
	this->filterBox->PerformLayout();
	this->progressBar->ResumeLayout(false);
	this->progressBar->PerformLayout();
	this->statusbar->ResumeLayout(false);
	this->statusbar->PerformLayout();
	this->menuStrip1->ResumeLayout(false);
	this->menuStrip1->PerformLayout();
	this->ResumeLayout(false);

}


/*****************************/
/*         Functions         */
/*****************************/

//Add new product
Void MyForm::addNew(){
	if(bManu){
		MessageBox::Show("Please show all products before adding new product","Error");
		return;
	}
	if(!loaded){
		MessageBox::Show("Please load a product list first","Error");
		return;
	}

	addprod = true;

	//change UI to add product mode
	this->listView1->Size = System::Drawing::Size(608, 389);
	this->listView1->Location = System::Drawing::Point(12, 3);
	this->buttonUpdate->Text = L"Add Product";
	this->buttonRemove->Text = L"Cancel";
	this->textBoxBar->ReadOnly = false;
	this->textNoSold->Text = "0";
	this->textBoxStock->Text = "0";
	this->textBoxBar->BackColor = SystemColors::Window;
	this->textBoxBar->Cursor = Cursors::IBeam;
	this->filterBox->Visible = false;
	this->stockBox->Visible = false;
	this->textBoxBar->Text = "<New Product Barcode>";
	this->textBoxName->Text = "<New Product Name>";
	this->textBoxCat->Text = "<New Product Category>";
	this->textBoxManu->Text = "<New Product Manufacturer>";
	this->textBoxPrice->Text = "<New Product Price>";
}

//load product list
Void MyForm::loadFunc(){
	if(openFileDialog1->ShowDialog() == Windows::Forms::DialogResult::OK)
	{
		string Fname;
		MarshalString(openFileDialog1->FileName,Fname);

		////graphical feedback
		this->Cursor = Cursors::WaitCursor;
		statusChange("Loading List...", SystemColors::Control);

		this->prodNumBar->Visible = false;

		if(!(list->load(Fname,%(*this))))
			MessageBox::Show(gcnew String(list->getErrorString().c_str()),"Error");

		this->progressBar->Visible = false;

		comboRefresh();

		//check if the program crashed last time only if it is first time loading
		if(!list->checkLog() && !loaded)
		{
			if (MessageBox::Show("Oops!\nIt seems like the program has ended unexpectedly the previous time it was used.\nWould you like to restore the unsaved changes?\nClick Yes to restore. \nIf you click No, your changes will be discarded.","Confirmation",MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes){
				list->loadlog(%(*this));
				MessageBox::Show("All changes have been made. Please save if you wish to make them permanent");
			}
			else
				list->emptylog();
		}
		printlist(list);
	}
}

//load batch jobs
Void MyForm::batchFunc(){
	if(loaded){
		if(openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK){
			string Fname;
			MarshalString(openFileDialog1->FileName,Fname); //convert filename into std string

			//graphical feedback
			this->Cursor = System::Windows::Forms::Cursors::WaitCursor;
			statusChange("Loading List",Color::IndianRed);
			if(!list->batchProcess(Fname, %(*this)))
				MessageBox::Show("Some of the jobs could not be completed successfully.\nPlease check the log file for error details.");
		}
		statusReady();
	}
	else{
		MessageBox::Show("Please load a product list first","Error");
		return;
	}

}

//Save
Void MyForm::saveFunc(){
	//error if product list not loaded
	if(!loaded){
		MessageBox::Show("Please load a product list first","Error");
		return;
	}

	statusChange("Saving...",Color::DarkOrchid);

	//display error if save fail
	if(!list->save()){
		MessageBox::Show(gcnew String(list->getErrorString().c_str()),"Error");
		statusReady();
		return;
	}

	statusReady();
}

//Backup
Void MyForm::backupFunc(){
	//error if product list not loaded
	if(!loaded){
		MessageBox::Show("Please load a product list first","Error");
		return;
	}

	statusChange("Backing up...",Color::DarkOrchid);

	if(list->backup())
		MessageBox::Show("Backup Success","Notification");
	else
		MessageBox::Show("Backup Failed","Error");

	statusReady();
}

//Best Selling product
Void MyForm::bestSellingFunc(){
	checkBestManu();
	ProductList flist;

	statusChange("Loading List",Color::IndianRed);

	this->listView1->BeginUpdate();
	this->listView1->Clear();
	this->listView1->Columns->AddRange(gcnew cli::array< ColumnHeader^ >(7) {this->Items, this->BarCode, 
		this->Category, this->Manufacturer, this->Price, this->NoSold, this->Stock });
	this->listView1->EndUpdate();

	if(!list->getBestSeller(flist)){
		MessageBox::Show(gcnew String(flist.getErrorString().c_str()),"Error");
		statusReady();
		return;
	}
	printlist(&flist);
}

//Best Manufacturer
Void MyForm::bestManuFunc(){
	set<ProductList::Combo> manu;
	bManu = true;

	this->listView1->Location = System::Drawing::Point(12, 3);
	this->listView1->Size = System::Drawing::Size(825, 348);
	this->buttonShowAll->Location = System::Drawing::Point(12, 357);
	this->buttonShowAll->Size = System::Drawing::Size(825, 35);
	this->filterBox->Visible = false;
	this->stockBox->Visible = false;
	this->Details->Visible = false;
	this->Cursor = Cursors::WaitCursor;

	this->listView1->BeginUpdate();
	this->listView1->Sorting = SortOrder::None;

	statusChange("Loading List",Color::IndianRed);

	list->getManufacturerInfo(manu, %(*this));

	statusChange("Writing List",Color::LightSeaGreen);

	set<ProductList::Combo>::iterator it = manu.begin();

	this->listView1->Clear();

	//sort number sold in descending order
	this->listView1->ListViewItemSorter = gcnew ListViewItemComparer1(1,true);

	this->listView1->Columns->AddRange(gcnew cli::array< ColumnHeader^ >(2) {this->Manufacturer, this->NoSold});

	array<ListViewItem^>^ temp;
	int size = manu.size();
	Array::Resize(temp,size);

	for(int i=0;it!=manu.end();it++,i++){
		String^ sys_name = gcnew String(it->name.c_str()); //name
		String^ sys_sold = Convert::ToString(it->noSold); //barcode
		ListViewItem^  listViewItem = 
			(gcnew ListViewItem(gcnew cli::array< String^ >(2) {sys_name, sys_sold } , -1));
		temp[i]=listViewItem;
	}
	prodnum(0);
	this->listView1->Items->AddRange(temp);
	this->Manufacturer->AutoResize(ColumnHeaderAutoResizeStyle::ColumnContent);
	this->listView1->EndUpdate();

	statusReady();
}

//Filter
Void MyForm::filterFunc(){
	ProductList flist; //filtered list

	statusChange("Loading List",Color::IndianRed);

	if(radiobuttonName->Checked) //filter by name
	{
		string name;
		if(textBoxFName->Text == ""){
			statusReady();
			MessageBox::Show("Please enter name to filter by","Error");
			return;
		}
		MarshalString(textBoxFName->Text,name);
		if(!list->searchName(name , flist)){
			MessageBox::Show(gcnew String(list->getErrorString().c_str()),"Error");
			statusReady();
			return;
		}
	}
	else if(radiobuttonBar->Checked) //filter by barcode
	{
		if(textBoxFBar->Text == ""){
			statusReady();
			MessageBox::Show("Please enter barcode to filter by","Error");
			return;
		}
		int bar = Convert::ToInt32(textBoxFBar->Text);
		if(!list->searchBarCode(bar , flist))
		{
			statusReady();
			MessageBox::Show(gcnew String(list->getErrorString().c_str()),"Error");
			return;
		}
	}
	else if(radiobuttonCat->Checked) //filter by category
	{
		if(comboBoxCat->SelectedIndex < 0){
			statusReady();
			MessageBox::Show("Please enter category to filter by","Error");
			return;
		}
		Object^ selectedItem = comboBoxCat->SelectedItem;
		string str;
		MarshalString(selectedItem->ToString(),str);
		if(!list->searchCategory(str , flist))
		{
			statusReady();
			MessageBox::Show(gcnew String(list->getErrorString().c_str()),"Error");
			return;
		}
	}
	else if(radiobuttonManu->Checked) //filter by manufacturer
	{
		if(comboBoxManu->SelectedIndex < 0){
			statusReady();
			MessageBox::Show("Please enter manufacturer to filter by","Error");
			return;
		}

		Object^ selectedItem = comboBoxManu->SelectedItem;
		string str;
		MarshalString(selectedItem->ToString(),str);

		if(!list->searchManufacturer(str , flist))
		{
			MessageBox::Show(gcnew String(list->getErrorString().c_str()),"Error");
			statusReady();
			return;
		}
	}
	else
	{
		statusReady();
		MessageBox::Show("Please choose what you would like to filter by.","Error");
		return;
	}
	this->listView1->ListViewItemSorter = gcnew ListViewItemComparer2();
	printlist(&flist);
}


/*****************************/
/*      Other Functions      */
/*****************************/

//update status for batch processing - to be called by batchprocessor
Void MyForm::updateStatus(string stat){
	String^ sys_stat = gcnew String(stat.c_str());
	this->Cursor = Cursors::WaitCursor;
	statusChange(sys_stat,Color::Turquoise);
}

//initial set up of progressbar
Void MyForm::progSet(Color colour){
	statusbar->BackColor = SystemColors::Control;
	this->prodNumBar->Visible =false;
	this->progressBar->Visible = true;
	this->progressBar->BackColor = colour;
}

//Update text on progress bar
Void MyForm::statusProg(double perc, string str){
	String^ sys_status = gcnew String(str.c_str());
	double width =  perc*844;
	this->statbarStatus->Text = sys_status;
	this->progbarStatus->Text = sys_status;
	this->progressBar->Size = System::Drawing::Size(int(width), 21);
	this->Refresh();
}

//refresh combobox
Void MyForm::comboRefresh()
{
	//clear comboboxes
	comboBoxCat->Items->Clear();
	comboBoxManu-> Items->Clear();

	//refresh categories combobox
	this->Cursor = Cursors::WaitCursor;
	statusChange("Populating Categories...",SystemColors::Control);

	set<ProductList::Combo> arr;
	list->getCategories(arr,%(*this));

	//refresh manufacturers combobox
	statusChange("Populating Manufacturers...",SystemColors::Control);

	set<ProductList::Combo> arr2;
	list->getManufacturerInfo(arr2,%(*this));

	statusChange("Loading ComboBox...",Color::DarkOrange);
	//add items into category combobox
	for(set<ProductList::Combo>::iterator it = arr.begin(); it != arr.end(); it++)
		comboBoxCat->Items->Add(gcnew String(it->name.c_str()));
	//add items into manufacturer combobox
	for(set<ProductList::Combo>::iterator it = arr2.begin(); it != arr2.end(); it++)
		comboBoxManu->Items->Add(gcnew String(it->name.c_str()));

	this->progressBar->Visible = false;
}

//print out list in listview
Void MyForm::printlist (ProductList *list1)
{
	int size = list1->getSize();
	int j=0;
	bool largelist = size>1000;
	array<ListViewItem^>^ temp;

	//graphical feedback
	this->Cursor = Cursors::WaitCursor;
	statusChange("Writing List...", SystemColors::Control);

	this->listView1->BeginUpdate(); //prevents listview from repainting

	if(loaded)
		this->listView1->Items->Clear();

	if(largelist)
		Array::Resize(temp,1000);
	else
		Array::Resize(temp,100);

	progSet(Color::LightSeaGreen);

	for(int i=0; i<size; i++){
		Product p1 = list1->print();
		int bar = p1.getBarcode();
		ListViewItem^item = gcnew ListViewItem;

		//to avoid repetitive item entry
		if(largelist && i==(size-(size%1000)))
			Array::Resize(temp,size%1000);
		else if (!largelist && i==(size-(size%100)))
			Array::Resize(temp,size%100);

		list1->printItem(%(*item));
		temp[j] = item; //add item to array

		j++;

		if(largelist&&j==1000|| !largelist&&j==100){
			this->listView1->Items->AddRange(temp); //print out items from array to listview

			stringstream status;
			double perc = (i*1.00/size);
			status<<"Writing to list ";
			status<<(int)(perc*100);
			status<<"% done...";
			statusProg(perc,status.str());

			j=0;
		}
	}

	if(largelist && size%1000 || !largelist && size%100){
		this->listView1->Items->AddRange(temp); //print out items from array to listview
	}
	statusProg(1.0,"Writing to list 100% done...");

	//resize barcode column to fit longest barcode
	this->BarCode->AutoResize(ColumnHeaderAutoResizeStyle::ColumnContent); 

	loaded = true;
	this->listView1->EndUpdate(); //resumes drawing of listview

	prodnum(list1->getSize());

	clearDetails();
	statusReady();
}

//Accept only digits and the Backspace character
Void MyForm::Digitonly_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if(!Char::IsDigit(e->KeyChar) && e->KeyChar != 0x08)
		e->Handled = true;
}

//Accept only one decimal point and 2 digits after decimal
Void MyForm::priceKeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	// only allow digits and '.'
	if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar) && e->KeyChar != '.') {
		e->Handled = true;
	}	
	// only allow one decimal point
	if (e->KeyChar == '.' && textBoxPrice->Text->IndexOf('.') > -1){
		e->Handled = true;
	}
	// only allow 2 digits after '.'
	if (!Char::IsControl(e->KeyChar) && textBoxPrice->SelectionLength == 0) {
		if (textBoxPrice->Text->IndexOf('.') > -1 && textBoxPrice->Text->Substring(textBoxPrice->Text->IndexOf('.'))->Length >= 3) {
			e->Handled = true;
		}
	}
}

//Clear all product details from textboxes
Void MyForm::clearDetails(){
	this->textBoxBar->Text = "";
	this->textBoxName->Text = "";
	this->textBoxCat->Text = "";
	this->textBoxManu->Text = "";
	this->textBoxPrice->Text = "";
	this->textNoSold->Text = "";
	this->textBoxStock->Text = "";
}

//Change status bar text and colour
Void MyForm::statusChange(String^ str, Color colour){
	this->statbarStatus->Text = str;
	this->statusbar->BackColor = colour;
	this->prodNumBar->BackColor = colour;
	this->Refresh();
}

/*change number of products in status bar*/
Void MyForm::prodnum(int num){
	String^ sys_num = Convert::ToString(num);
	this->toolStripStatusLabel3->Text = sys_num;
}

//Set statusbar to ready
Void MyForm::statusReady(){
	statusChange("Ready",Color::CornflowerBlue);
	this->Cursor = Cursors::Arrow;
	this->prodNumBar->Visible = true;
	this->progressBar->Visible = false;
}

//Check if best manufacturer is displayed, if displayed, revert back to normal
Void MyForm::checkBestManu(){
	if(bManu){
		this->buttonShowAll->Location = System::Drawing::Point(626, 357);
		this->buttonShowAll->Size = System::Drawing::Size(211, 35);
		this->listView1->Size = System::Drawing::Size(608, 309);
		this->listView1->Location = System::Drawing::Point(12, 83);
		this->filterBox->Visible = true;
		this->stockBox->Visible = true;
		this->Details->Visible = true;
		bManu = false;
	}
}


/*****************************/
/*      Event Functions      */
/*****************************/

/*****file menu*****/
Void MyForm::clickAddNew(System::Object^  sender, System::EventArgs^  e) {addNew();}
Void MyForm::Load_Click(System::Object^  sender, System::EventArgs^  e) {loadFunc();}
Void MyForm::batchProcess(System::Object^  sender, System::EventArgs^  e) {batchFunc();}
Void MyForm::Save(System::Object^  sender, System::EventArgs^  e) {saveFunc();}
Void MyForm::SaveAs(System::Object^  sender, System::EventArgs^  e) {
	if(!loaded){
		MessageBox::Show("Please load a product list first","Error");
		return;
	}
	if(saveFileDialog1->ShowDialog() == Windows::Forms::DialogResult::OK){
		string Fname;
		MarshalString( saveFileDialog1->FileName, Fname);

		statusChange("Saving...",Color::DarkOrchid);

		if(!list->saveAs(Fname))
			MessageBox::Show(gcnew System::String(list->getErrorString().c_str()),"Error");

		statusReady();
	}
}
Void MyForm::BackUp(System::Object^  sender, System::EventArgs^  e) {backupFunc();}

/*****Statistics Menu*****/
Void MyForm::bestManu(System::Object^  sender, System::EventArgs^  e) { bestManuFunc(); }
Void MyForm::BestSelling(System::Object^  sender, System::EventArgs^  e) { bestSellingFunc(); }
Void MyForm::clearLowStkBox(System::Object^  sender, System::EventArgs^  e) { this->toolStripTextBox1->Text = ""; }
Void MyForm::lowStockPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	//only allow digits and backspace
	if(!Char::IsDigit(e->KeyChar) && e->KeyChar != 0x08)
		e->Handled = true;

	//if enter key pressed
	if(e->KeyChar == (char)13 ){
		checkBestManu();

		int num;
		num = Convert::ToInt32( toolStripTextBox1->Text);

		ProductList flist;

		statusChange("Loading List",Color::IndianRed);

		this->listView1->BeginUpdate();
		this->listView1->Clear();
		this->listView1->Columns->AddRange(gcnew cli::array< ColumnHeader^  >(7) {this->Items, this->BarCode, 
			this->Category, this->Manufacturer, this->Price, this->NoSold, this->Stock });
		this->listView1->EndUpdate();

		if(!list->searchLowStock(num,flist)){
			MessageBox::Show(gcnew String(list->getErrorString().c_str()),"Error");
			return;
		}
		printlist(&flist);
	}

	//if textbox empty and backspace pressed
	else if(e->KeyChar == (char)8 && toolStripTextBox1->Text == "")
		this->toolStripTextBox1->Text = "<Enter Upper Limit>";
}
Void MyForm::ShowAll(System::Object^  sender, System::EventArgs^  e) {
	//error if no product list loaded
	if(!loaded){
		MessageBox::Show("Please load product list","Error");
		return;
	}

	checkBestManu();

	this->listView1->BeginUpdate();
	this->listView1->Sorting = SortOrder::None;
	listView1->Clear();
	this->listView1->Columns->AddRange(gcnew cli::array< ColumnHeader^ >(7) {this->Items, this->BarCode, 
		this->Category, this->Manufacturer, this->Price, this->NoSold, this->Stock});
	this->listView1->EndUpdate();

	printlist(list);
}

/*****Filter Bar*****/
Void MyForm::filter_click(System::Object^  sender, System::EventArgs^  e) {filterFunc();}
Void MyForm::filterDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if(e->KeyCode == Keys::Enter)
		filterFunc();
}

/*****listview*****/
Void MyForm::listView1_ColumnClick(System::Object^  sender, System::Windows::Forms::ColumnClickEventArgs^  e) {
	clearDetails();

	if(column == e->Column && order){
		if(column == 1 || column >3) //for barcode, price, number sold and stock columns
			this->listView1->ListViewItemSorter = gcnew ListViewItemComparer1( e->Column, order );
		else //for name, category and manufacturer columns
			this->listView1->ListViewItemSorter = gcnew ListViewItemComparer( e->Column, order );

		order=false;
	}
	else{
		if(e->Column == 1 || e->Column >3) //for barcode, price, number sold and stock columns
			this->listView1->ListViewItemSorter = gcnew ListViewItemComparer1( e->Column, false );
		else //for name, category and manufacturer columns
			this->listView1->ListViewItemSorter = gcnew ListViewItemComparer( e->Column, false );

		order=true;
		column = e->Column;
	}
}
Void MyForm::listView1_ItemActivate(System::Object^  sender, System::EventArgs^  e) {
	if(bManu)
		return;

	ListView::SelectedListViewItemCollection^ pdt = this->listView1->SelectedItems;
	lastSelected = pdt[0]->Index;
	ListViewItem^ item = pdt[0];

	//display selected item in product details
	this->textBoxName->Text =item->SubItems[0]->Text->ToString();//name
	this->textBoxBar->Text =item->SubItems[1]->Text->ToString();//barcode
	this->textBoxCat->Text =item->SubItems[2]->Text->ToString();//category
	this->textBoxManu->Text =item->SubItems[3]->Text->ToString();//manufacturer
	this->textBoxPrice->Text =item->SubItems[4]->Text->ToString();//price
	this->textNoSold->Text =item->SubItems[5]->Text->ToString();//number sold
	this->textBoxStock->Text =item->SubItems[6]->Text->ToString();//stock
}

/*****Stockkeeping box*****/
Void MyForm::textBoxQty_Click(System::Object^  sender, System::EventArgs^  e) {	this->textBoxQty->Text = ""; }
Void MyForm::Restock(System::Object^  sender, System::EventArgs^  e) {
	if(textBoxQty->Text == "" || textBoxQty->Text == "<Enter amount to restock / sell>"){
		MessageBox::Show("Please enter quantity restocked","Error");
		return;
	}
	else if(lastSelected == -1 || textBoxBar->Text == ""){
		MessageBox::Show("Please select a product","Error");
		return;
	}

	//convert system string to integer
	int bar = Convert::ToInt32(this->textBoxBar->Text);
	int qty = Convert::ToInt32(this->textBoxQty->Text);

	if(list->reStock(bar,qty)){
		String^ sys_instock = (Convert::ToInt32(this->textBoxStock->Text) + qty).ToString();
		this->textBoxStock->Text = sys_instock; //update textbox
		this->listView1->Items[lastSelected]->SubItems[6]->Text = sys_instock; //update listview
	}
	else
		MessageBox::Show(gcnew String(list->getErrorString().c_str()),"Error");
}
Void MyForm::sell_click(System::Object^  sender, System::EventArgs^  e) {
	if(textBoxQty->Text == "" || textBoxQty->Text == "<Enter amount to restock / sell>"){
		MessageBox::Show("Please enter quantity sold","Error");
		return;
	}
	else if(lastSelected == -1 || textBoxBar->Text == ""){
		MessageBox::Show("Please select a product","Error");
		return;
	}

	//convert system string to integer
	int bar = Convert::ToInt32(this->textBoxBar->Text);
	int qty = Convert::ToInt32(this->textBoxQty->Text);

	if(list->specifySale(bar,qty)){
		String^ sys_sold = (Convert::ToInt32(this->textNoSold->Text) + qty).ToString();
		String^ sys_instock = (Convert::ToInt32(this->textBoxStock->Text) - qty).ToString();

		//update textboxes
		this->textBoxStock->Text = sys_instock;
		this->textNoSold->Text = sys_sold;

		//update listview
		this->listView1->Items[lastSelected]->SubItems[6]->Text = sys_instock;
		this->listView1->Items[lastSelected]->SubItems[5]->Text = sys_sold;
	}
	else
		MessageBox::Show(gcnew String(list->getErrorString().c_str()),"Error");
}

/*****Product Details box*****/
Void MyForm::removeClick(System::Object^  sender, System::EventArgs^  e) {
	if(addprod) //Add product mode (button == cancel)
	{
		//revert UI back to normal
		this->listView1->Size = System::Drawing::Size(608, 309);
		this->listView1->Location = System::Drawing::Point(12, 83);
		this->buttonUpdate->Text = L"Update";
		this->buttonRemove->Text = L"Remove";
		this->buttonRemove->Visible = true;
		this->buttonRemove->Enabled = true;
		this->filterBox->Visible = true;
		this->stockBox->Visible = true;
		this->textBoxBar->ReadOnly = true;
		this->textBoxBar->BackColor = SystemColors::Control;
		this->textBoxBar->Cursor = Cursors::No;
		clearDetails();

		addprod = false;
	}

	else //Remove product mode (button == Remove)
	{
		//Error if no item selected
		if(textBoxBar->Text == "" || lastSelected == -1){
			MessageBox::Show("Please select an item to remove","Error");
			return;
		}

		else {
			if (MessageBox::Show("Are you sure you want to remove the product?","Confirmation",MessageBoxButtons::YesNo) == Windows::Forms::DialogResult::Yes){
				int bar = Convert::ToInt32(this->textBoxBar->Text);

				//display error message if remove failed
				if(!list->removeProduct(bar)){
					MessageBox::Show(gcnew String(list->getErrorString().c_str()),"Error");
					return;
				}

				this->listView1->Items->RemoveAt(lastSelected); //remove selected item from list
				lastSelected = -1; //reset last selected
				prodnum(list->getSize()); //update number of products
				clearDetails();
				comboRefresh();

				statusChange("Successfully Removed",Color::Lime);
				Threading::Thread::Sleep(500);
				statusReady();
			}
		}
	}

}
Void MyForm::updateClick(System::Object^  sender, System::EventArgs^  e) {
	string name, manu, cat;
	double price;
	int bar;

	if(!addprod && (lastSelected == -1 || textBoxBar->Text == "")){
		MessageBox::Show("Please select an item to update","Error");
		return;
	}

	MarshalString( this->textBoxName->Text,name);//convert name to std string
	MarshalString( this->textBoxCat->Text,cat);//convert category to std string
	MarshalString( this->textBoxManu->Text,manu);//convert manufacturer to std string
	price = Convert::ToDouble(this->textBoxPrice->Text); //convert price to double
	bar = Convert::ToInt32(this->textBoxBar->Text); //convert barcode to int

	String^ sys_name = this->textBoxName->Text;
	String^ sys_cat = this->textBoxCat->Text;
	String^ sys_manu = this->textBoxManu->Text;
	String^ sys_price = this->textBoxPrice->Text;
	String^ sys_bar = this->textBoxBar->Text;
	String^ sys_nosold = this->textNoSold->Text;
	String^ sys_instock = this->textBoxStock->Text;

	if(!addprod) //Update mode
	{
		//if updated successfully
		if(list->updateProduct(name, cat, manu, price, bar)){
			comboRefresh();

			//edit listview accordingly
			this->listView1->Items[lastSelected]->SubItems[0]->Text = sys_name;
			this->listView1->Items[lastSelected]->SubItems[2]->Text = sys_cat;
			this->listView1->Items[lastSelected]->SubItems[3]->Text = sys_manu;
			this->listView1->Items[lastSelected]->SubItems[4]->Text = sys_price;

			statusChange("Successfully updated",Color::Lime);
			Threading::Thread::Sleep(500);
			statusReady();
		}
		//if not updated successfully
		else{
			MessageBox::Show(gcnew String(list->getErrorString().c_str()),"Error");
			return;
		}
	}

	else //Add product mode
	{
		bool add = list->addProduct(name, cat, manu, price, bar);

		if(add){
			ListViewItem^  listViewItem = (gcnew ListViewItem(gcnew cli::array<String^>(7) {sys_name, sys_bar, sys_cat,sys_manu, sys_price, "0", "0" } , -1));
			this->listView1->Items->Add(listViewItem);

			comboRefresh();

			statusChange("Product added",Color::Lime);
		}
		else
			MessageBox::Show(gcnew String(list->getErrorString().c_str()),"Error");

		addprod = false;

		//revert graphics to normal
		this->buttonUpdate->Text = L"Update";
		this->buttonRemove->Text = L"Remove";
		this->buttonRemove->Visible = true;
		this->buttonRemove->Enabled = true;
		this->textBoxBar->ReadOnly = true;
		this->textBoxBar->BackColor = SystemColors::Control;
		this->textBoxBar->Cursor = Cursors::No;
		this->filterBox->Visible = true;
		this->stockBox->Visible = true;
		this->buttonShowAll->Location = System::Drawing::Point(626, 357);
		this->buttonShowAll->Size = System::Drawing::Size(211, 35);
		this->listView1->Size = System::Drawing::Size(608, 309);
		this->listView1->Location = System::Drawing::Point(12, 83);
		clearDetails();
		this->Refresh();

		Threading::Thread::Sleep(500);
		prodnum(list->getSize()); //update product number
		statusReady();
	}
}
Void MyForm::clearBarBox(System::Object^  sender, System::EventArgs^  e) {
	if(addprod)
		this->textBoxBar->Text = "";
}
Void MyForm::clearNameBox(System::Object^  sender, System::EventArgs^  e) {
	if(addprod)
		this->textBoxName->Text = "";
}
Void MyForm::clearCatBox(System::Object^  sender, System::EventArgs^  e) {
	if(addprod)
		this->textBoxCat->Text = "";
}
Void MyForm::clearManuBox(System::Object^  sender, System::EventArgs^  e) {
	if(addprod)
		this->textBoxManu->Text = "";
}
Void MyForm::clearPriceBox(System::Object^  sender, System::EventArgs^  e) {
	if(addprod)
		this->textBoxPrice->Text = "";
}

/*****Shortcut keys*****/
Void MyForm::shortcuts(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if(e->Control && e->KeyCode == Keys::S)
		saveFunc();
	if(e->Control && e->KeyCode == Keys::N)
		addNew();
	if(e->Control && e->KeyCode == Keys::L)
		loadFunc();
	if(e->Control && e->KeyCode == Keys::B)
		backupFunc();
	if(e->Control && e->KeyCode == Keys::J)
		batchFunc();
	if(e->Control && e->Alt && e->KeyCode == Keys::P)
		bestSellingFunc();
	if(e->Control && e->Alt && e->KeyCode == Keys::M)
		bestManuFunc();
}