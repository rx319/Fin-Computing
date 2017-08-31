#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "curl.h"
#include "Stockv401.h"
#include "Groupv401.h"

const double H =0.05;//H is the threshold for differnt groups: Missed, Beat, Met.

#include "BitsAndPieces\StringConversions.hpp"
#include "ExcelDriver.hpp"
#include "ExcelMechanisms.hpp"
#include "VectorsAndMatrices\NumericMatrix.cpp" // Template
#include "ExceptionClasses\DatasimException.hpp"
using namespace std;

typedef vector<Stock> StockVec;
//typedef vector<string> StrVec;
typedef vector<StrVec> StrMrX ;
//typedef vector<double> Vector1;
typedef vector<Vector1> Matrix1;


int ImportURL(const string& u, Vector1 &price);
void ImportAllURLandPrice(StockVec &stockVec);
void ImportAllspyURLandPrice(StockVec &stockVec);
int readFile(ifstream &infile, StockVec &stockVec);
int write_data(void *ptr, int size, int nmemb, FILE *stream) ;
int write_data2(void *ptr, size_t size, size_t nmemb, void *data);
StrVec split(string str,string pattern);
double str2num(string s);


void GroupStocks(Group &Missed, Group &Beat,Group &Met, StockVec stockVec);



Vector<double, long> v2V(Vector1 &V);
void Vectorlist(list<Vector<double, long> > &vectorList,Matrix1 &M);
Matrix<double,long> trans(Matrix1 &M);
void printtoexcel(StockVec &stockVec,Group &Beat,Group &Met,Group &Missed);


 struct MemoryStruct {
    char *memory;
    size_t size;
	~MemoryStruct(){delete memory;}
 };

 void *myrealloc(void *ptr, size_t size);