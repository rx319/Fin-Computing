#ifndef STOCKv401_H
#define STOCKv401_H

#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;
typedef vector<string> StrVec;
typedef vector<double> Vector1;

class Date
{
private:
	string Day;
	string Month;
	string Year;
public:

	void setDay(string day){Day=day;}
	void setMonth(string month){Month=month;}
	void setYear(string year){Year=year;}
	string getDay(){return Day;}
	string getMonth(){return Month;}
	string getYear(){return Year;}

};

class Stock
{
private:
	//string Group;
	string Ticker;
	double EstimatedEPS;
	double ActualEPS;
	string Day0;
	string DayPrior;
	string DayAfter;
	string URL;
	string spyURL;
	Vector1 Price;
	Vector1 spyPrice;
	Vector1 stockReturn;
	Vector1 spyReturn;
	Vector1 abnormalReturn;
	Date startDate;
	Date endDate;

public:
	//void setGroup (string group){Group=group;}
	void setTicker (string ticker){Ticker=ticker;}
	void setEstimatedEPS (double estimatedEPS){EstimatedEPS=estimatedEPS;};
	void setActualEPS (double actualEPS){ActualEPS=actualEPS;}
	void setDay0(string day0){Day0=day0;}
	void setDayPrior(string dayPrior){DayPrior=dayPrior;}
	void setDayAfter(string dayAfter){DayAfter=dayAfter;}
	void setURL(string uRL){URL=uRL;}
	void setSpyURL(string uRL){spyURL=uRL;}
//	void setStock(string group,string ticker,double estimatedEPS,double actualEPS,string day0,string dayPrior,string dayAfter,string uRL);
	void setStock(string ticker,double estimatedEPS,double actualEPS,string day0,string dayPrior,string dayAfter);
	void setPrice(const Vector1 &price);
	void setSpyPrice(const Vector1 &price);

	void setStartDate(string day, string month,string year);
	void setEndDate(string day, string month,string year);

	Vector1 Return(const Vector1 &a);
	void setStockReturn(){stockReturn=Return(Price);}
	void setSpyReturn(){spyReturn=Return(spyPrice);}
	void setAbnormalReturn();

	void split(string str,StrVec &dateVec,string pattern);
	void splitStartDay(string str,string pattern);
	void splitEndDay(string str,string pattern);
	double str2num(string s);
	string num2str(double i);
	void adjust(string &s);
	string convert2url(string ticker,string beginyear,string &beginmonth,string beginday,string endyear,string &endmonth,string endday);

	//string getGroup (){return Group;}
	string getTicker (){return Ticker;}
	double getEstimatedEPS() {return EstimatedEPS;}
	double getActualEPS () {return ActualEPS;}
	string getDay0 () {return Day0;}
	string getDayPrior () {return DayPrior;}
	string getDayAfter () {return DayAfter;}
	string getURL() {return URL;}
	string getSpyURL() {return spyURL;}
	Date getStartDate(){return startDate;}
	Date getEndDate(){return endDate;}
	Vector1 getPrice(){return Price;}
	Vector1 getSpyPrice(){return spyPrice;}
	Vector1 getAbnormalReturn(){return abnormalReturn;};
	double getAbnormalReturn(int i){return abnormalReturn[i];}
	Vector1 getStockReturn(){return stockReturn;}
	Vector1 getSpyReturn(){return spyReturn;}
};

#endif