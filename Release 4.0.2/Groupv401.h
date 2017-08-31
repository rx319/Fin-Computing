#ifndef GROUPv401_H
#define GROUPv401_H

#include "stdafx.h"
#include "Stockv401.h"
typedef vector<Stock> StockVec;
typedef vector<double> Vector1;

class Group
{
private:
	//static int count;
	Vector1 AARt;
	Vector1 CAAR;

public:	
	StockVec Stocks;
	Group(){ Stocks=StockVec (100);}
	void setStocks(Stock stock,int count){Stocks[count]=stock;}
	void setAARt();
	void setCAAR();
	Vector1 getAARt(){ return AARt;}
	Vector1 getCAAR() {return CAAR;}	
};



#endif
