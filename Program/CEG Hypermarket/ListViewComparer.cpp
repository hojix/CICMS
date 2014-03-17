/******************************************************************
 * This file implements functions defined in ListViewComparer.h   *
 *                                                                *
 * Done by Wen Yao Koh                                            *
 ******************************************************************/
#include "ListViewComparer.h"

ListViewItemComparer::ListViewItemComparer(){
	col = 0;
	_order=false;
}

ListViewItemComparer::ListViewItemComparer( int column, bool order ){
	col = column;
	_order = order;
}

ListViewItemComparer1::ListViewItemComparer1(){
	col = 0;
	_order=false;
}

ListViewItemComparer1::ListViewItemComparer1( int column, bool order ){
	col = column;
	_order = order;
}