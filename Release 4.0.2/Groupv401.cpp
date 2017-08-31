#include "stdafx.h"
#include "Groupv401.h"


void Group::setAARt()
{ 
	AARt=Vector1(Stocks[0].getAbnormalReturn().size()); 
	for (int i=0; i<Stocks[0].getAbnormalReturn().size();i++)
	{ 
		AARt[i]=Stocks[0].getAbnormalReturn(i);
		for(int j=1;j<Stocks.size();j++) {
		AARt[i]=AARt[i]+Stocks[j].getAbnormalReturn(i);}

		AARt[i]=AARt[i]/Stocks.size();
	}
}

void Group::setCAAR()
{  
	setAARt(); 
	CAAR=Vector1(Stocks[0].getAbnormalReturn().size());
	CAAR[0]=AARt[0];
	for(int i=1; i<AARt.size(); i++)
		CAAR[i]=CAAR[i-1]+AARt[i]; 
}


