/****************************************************************
 *This file defines the functions used for sorting in the GUI	*
 *																*
 * Done by Wen Yao Koh											*
 ****************************************************************/
#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;


//String comparer
ref class ListViewItemComparer: public System::Collections::IComparer
{
private:
	int col;
	bool _order;

public:
	ListViewItemComparer();

	ListViewItemComparer( int column, bool order );

	virtual int Compare( Object^ y, Object^ x )
	{
		if(_order)
			return String::Compare( (dynamic_cast<ListViewItem^>(x))->SubItems[ col ]->Text,(dynamic_cast<ListViewItem^>(y))->SubItems[ col ]->Text );
		else
			return String::Compare( (dynamic_cast<ListViewItem^>(y))->SubItems[ col ]->Text,(dynamic_cast<ListViewItem^>(x))->SubItems[ col ]->Text );
	}
};

//Number comparer
ref class ListViewItemComparer1: public System::Collections::IComparer
{
private:
	int col;
	bool _order;

public:
	ListViewItemComparer1();
	ListViewItemComparer1( int column, bool order );
	virtual int Compare( Object^ y, Object^ x ){
		//sort in descending order
		if(_order)
			return Convert::ToDouble((dynamic_cast<ListViewItem^>(x))->SubItems[ col ]->Text).Double::CompareTo(System::Convert::ToDouble(dynamic_cast<ListViewItem^>(y)->SubItems[ col ]->Text));
		//sort in ascending order
		else
			return Convert::ToDouble((dynamic_cast<ListViewItem^>(y))->SubItems[ col ]->Text).Double::CompareTo(System::Convert::ToDouble(dynamic_cast<ListViewItem^>(x)->SubItems[ col ]->Text));
	}
};

//To set item compare to NULL
ref class ListViewItemComparer2: public System::Collections::IComparer
{
public:
	virtual int Compare( Object^ y, Object^ x ){
		return false;
	}
};