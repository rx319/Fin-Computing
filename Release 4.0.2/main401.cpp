// Defines the entry point for the console application.
//
#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include "curl.h"
#include "Stockv401.h"
#include "Groupv401.h"
#include "Functions401.h" //this file contains all the functions used in main 

using namespace std;


int main(void)
{   
	clock_t start=clock();
	ifstream infile("StockInfo.txt");
	//ofstream outfile;
	//outfile.open( "test.csv", ios::out | ios::app );
	//outfile.open( "test.txt");
	StockVec stockVec (200);
	int count=readFile(infile,stockVec);
	stockVec.resize(count); 
	cout<<"Importing Data from URL, Please wait..."<<endl<<endl;
	ImportAllURLandPrice(stockVec);
	ImportAllspyURLandPrice(stockVec);
	
	cout<<"Data Import from URL Completed."<<endl<<endl;
	Group Missed, Beat, Met; 
	GroupStocks(Missed, Beat,Met,stockVec); //put the data into different group and do all the calculation automatically

	clock_t final=clock()-start;
    cout<<"Calculation Completed. Total run time(sec): "<<final/ (double) CLOCKS_PER_SEC<<endl<<endl;

	//print to excel	
	printtoexcel(stockVec,Beat,Met,Missed);
	final=clock()-start;
    cout<<"Excel Completed. Total run time(sec): "<<final/ (double) CLOCKS_PER_SEC<<endl<<endl;
	//make the program stop for avoiding the console closing before we can see anything 
	//outfile.close();

	system("PAUSE");
	return 0;
}




