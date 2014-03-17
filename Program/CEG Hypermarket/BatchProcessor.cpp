/******************************************************************
 * The file implements the functions defined in BatchProcessor.h  *
 *                                                                *
 * Done by: Thyagesh M, Ho Jia Yi and Rupali Roychoudhury         *
 ******************************************************************/

#include<string>
#include<stack>
#include<queue>
#include<fstream>
#include<sstream>
#include "BatchProcessor.h"
#include "MyForm.h"
#include "ProductList.h"

using namespace std;

bool BatchProcessor::Load(string filename, stack<queue<Job>>& transactions)
{
	ifstream transfile(filename);
	int numtrans, numjob;
	string jobtype;
	BatchProcessor::Job job;
	
	//read the total number of transactions
	transfile>>numtrans;
	transfile.ignore(1,'\n');
	
	//loop until all transactions are done
	for(int i=0;i<numtrans;i++)
	{
		queue<BatchProcessor::Job> jobs;
		
		//read the transaction number
		transfile.ignore(1,'\n');
		getline(transfile,job.transId);
		
		//read the number of jobs in that transaction
		transfile>>numjob;
		transfile.ignore(1,'\n');
	
		//loop until all the jobs in that transaction are done
		for(int k=0;k<numjob;k++)
		{
			//read the job type
			transfile.ignore(1,'\n');
			getline(transfile,jobtype);
		
			//convert type to enum
			if(jobtype=="ADD")
				job.jType = ADD;
			else if(jobtype=="DELETE")
				job.jType = DELETE;
			else if(jobtype=="RESTOCK")
				job.jType = RESTOCK;
			else
				job.jType = SALE;

			//read file appropriately for different job types
			switch(job.jType)
			{
			case ADD:
				getline(transfile,job.name);
				getline(transfile,job.category);
				transfile>>job.barcode;
				transfile.ignore(1,'\n');
				transfile>>job.price;
				transfile.ignore(1,'\n');
				getline(transfile,job.manufacturer);
				transfile>>job.amt;
				transfile.ignore(1,'\n');
				break;

			case DELETE:
				transfile>>job.barcode;				
				transfile.ignore(1,'\n');
				break;

			case RESTOCK:
				transfile>>job.barcode;
				transfile.ignore(1,'\n');
				transfile>>job.amt;
				transfile.ignore(1,'\n');
				break;

			case SALE:
				transfile>>job.barcode;
				transfile.ignore(1,'\n');
				transfile>>job.amt;
				transfile.ignore(1,'\n');
				break;
			}
			//add job read to queue of jobs
			jobs.push(job);		
		}
		//add queue of jobs(a transaction) to stack of transactions
		transactions.push(jobs);
	}
	return true;
}

//function that does the changes to the productlist
bool BatchProcessor::executeJob(Job j,ProductList& pdtlist)
{
	switch(j.jType)
	{
		case ADD:
			return pdtlist.addProduct(j.name,j.category,j.manufacturer,j.price,j.barcode,j.amt,0);
		case DELETE:
			return pdtlist.removeProduct(j.barcode);
		case RESTOCK:
			return pdtlist.reStock(j.barcode,j.amt);
		case SALE:
			return pdtlist.specifySale(j.barcode,j.amt);
	}
	return false;
}

//goes through all transactions and make appropriate calls
bool BatchProcessor::batchProcess(string filename, ProductList& pdtlist,CEGHypermarket::MyForm^ form)
{
	stack<queue<Job>> transactions;
	form->updateStatus("Reading Transactions...");
	Load(filename,transactions);
	bool all_fine = true;
	int size = transactions.size();

	//keep loop until all transactions are done
	for(int i=1;(!transactions.empty());i++)
	{
		//read the transaction
		queue<Job> jq = transactions.top();
		if(i%2 == size%2)
		{
			stringstream status;
			status<<"Executing Transactions ";
			status<<((i*100.00)/size);
			status<<"% ...";
			form->updateStatus(status.str());
		}

		//remove the transaction
		transactions.pop();
		
		//loops through the entire transaction
		while(!jq.empty())
		{
			//execution failed, log the error
			if(!executeJob(jq.front(),pdtlist))
			{
				all_fine = false;
				logError(jq.front());
				
			}
			//remove the job after done
			jq.pop();
		}
	}
	return all_fine;
}

//jobs that are not completed successfully are logged here
bool BatchProcessor::logError(Job j)
{
	ofstream transErr("log.txt", ofstream::app);
	string type;
	
	//check what type of job
	switch(j.jType)
	{
		case ADD:
			type="ADD";
			break;
		case DELETE:
			type="DELETE";
			break;
		case RESTOCK:
			type="RESTOCK";
			break;
		case SALE:
			type="SALE";
			break;
	}

	//enter failed job
	transErr<<j.transId<<" "<<type<<" "<<j.barcode<<endl;
	return true;
}