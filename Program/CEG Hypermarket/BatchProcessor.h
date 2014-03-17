/************************************************************************************************
 * This file defines all the functions involved in batch processing such as reading the file,	*
 * executing the jobs and logging encountered any error during the process						*
 *
 * Done by: Thyageesh, Jia Yi, Rupali Roy Choudhury												*
 ************************************************************************************************/

#ifndef _H_BATCH
#define _H_BATCH
#include<string>
#include<stack>
#include<queue>
//#include "ProductList.h"

namespace CEGHypermarket
{
	ref class MyForm;
}

class ProductList;

using namespace std;

class BatchProcessor
{
	public:
		bool batchProcess(string filename,ProductList& pdtlist,CEGHypermarket::MyForm^ form);
		enum JobType{ADD,DELETE,RESTOCK,SALE};
		struct Job
		{
			JobType jType;
			int barcode, amt;
			double price;
			string name,category,manufacturer,transId;
		};
	private:
			bool Load(string filename, stack<queue<Job>>& transactions);
			bool executeJob(Job j, ProductList& pdt);
			bool logError(Job j);
};
#endif