#include "stdafx.h"
#include "Stockv401.h"
/*
void Stock::setStock(string group,string ticker,double estimatedEPS,double actualEPS,string day0,string dayPrior,string dayAfter,string uRL)
{
	Group=group;
	Ticker=ticker;
	EstimatedEPS=estimatedEPS;
	ActualEPS=actualEPS;
	Day0=day0;
	DayPrior=dayPrior;
	DayAfter=dayAfter;
	URL=uRL;
	splitStartDay(DayPrior,"/");
	splitEndDay(DayAfter,"/");
	URL=convert2url(Ticker,startDate.getYear(),startDate.getMonth(),startDate.getDay(),endDate.getYear(),endDate.getMonth(),endDate.getDay());
}*/

void Stock::setStock(string ticker,double estimatedEPS,double actualEPS,string day0,string dayPrior,string dayAfter)
{
	Ticker=ticker;
	EstimatedEPS=estimatedEPS;
	ActualEPS=actualEPS;
	Day0=day0;
	DayPrior=dayPrior;
	DayAfter=dayAfter;
	splitStartDay(DayPrior,"/");
	splitEndDay(DayAfter,"/");
	URL=convert2url(Ticker,startDate.getYear(),startDate.getMonth(),startDate.getDay(),endDate.getYear(),endDate.getMonth(),endDate.getDay());	
	spyURL=convert2url("SPY",startDate.getYear(),startDate.getMonth(),startDate.getDay(),endDate.getYear(),endDate.getMonth(),endDate.getDay());	

}

void Stock::setPrice(const Vector1 &price)
{
	int size=price.size();
	Price=Vector1(size); 
	for (int i=0;i<size;i++)
		Price[i]=price[size-i-1]; 
}

void Stock::setSpyPrice(const Vector1 &price)
{
	int size=price.size();
	spyPrice=Vector1(size);
	for (int i=0;i<size;i++)
		spyPrice[i]=price[size-i-1]; 
}


void Stock::setStartDate(string day, string month,string year)
{
	startDate.setDay(day);
	startDate.setMonth(month);
	startDate.setYear(year);
}

void Stock::setEndDate(string day, string month,string year)
{
	endDate.setDay(day);
	endDate.setMonth(month);
	endDate.setYear(year);
}

//spilt string into pieces by pattern
void Stock::split(string str,StrVec &dateVec, string pattern="/")
{
    std::string::size_type pos;
    str+=pattern;//expand string for convience
    int size=str.size();int j=0;
    for(int i=0; i<size; i++)
    {
        pos=str.find(pattern,i);
        if(pos<size)
        {
            std::string s=str.substr(i,pos-i);
			dateVec[j]=s;
            i=pos+pattern.size()-1;
			j++;
        } 
    }
}

void Stock::splitStartDay(string str,string pattern="/")
{
	StrVec dateVec (3);
	split(str,dateVec);
	startDate.setDay(dateVec[1]);
	startDate.setMonth(dateVec[0]);
	startDate.setYear(dateVec[2]);
}

void Stock::splitEndDay(string str,string pattern="/")
{
	StrVec dateVec (3);
	split(str,dateVec);
	endDate.setDay(dateVec[1]);
	endDate.setMonth(dateVec[0]);
	endDate.setYear(dateVec[2]); 
}

//convert elements to url strings
string Stock::convert2url(string ticker,string beginyear,string &beginmonth,string beginday,string endyear,string &endmonth,string endday)
{  
	adjust(beginmonth);
	adjust(endmonth);
	string url="http://real-chart.finance.yahoo.com/table.csv?s="+ticker+"&a="+beginmonth+"&b="+beginday+"&c="+beginyear+"&d="+endmonth+"&e="+endday+"&f="+endyear+"&g=d&ignore=.csv";    
	return url;
}

//convert string to double
double Stock::str2num(string s)
 {   
        double num;
        stringstream ss(s);
        ss>>num;
        return num;
}
//convert double to string
string Stock::num2str(double i)
{
        stringstream ss;
        ss<<i;
        return ss.str();
}
//adjust the month to accord with url rules(6->05)
void Stock::adjust(string &s)
{   
	if(str2num(s)-1<10)
     s="0"+num2str(str2num(s)-1);
	else s=num2str(str2num(s)-1);
	
}

Vector1 Stock::Return(const Vector1 &a)
{
	Vector1 R=Vector1(a.size()-1);
	for(int i=0;i<a.size()-1;i++) 
		R[i]=(a[i+1]/a[i])-1;
	return R;
}

//compute the abnormal return
void Stock::setAbnormalReturn()
{   
	if(stockReturn.size()!=spyReturn.size()) {cout<<"Wrong size";}
	for(int m=0;m<stockReturn.size();m++) abnormalReturn.push_back(stockReturn[m]-spyReturn[m]);
}

