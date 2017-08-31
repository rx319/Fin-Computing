#include "stdafx.h"
#include "Functions401.h"

//********************** Functions ****************************************************
//spilt string into pieces by pattern
//not using this function
StrVec split(std::string str,std::string pattern)
{
    std::string::size_type pos;
    StrVec result;
    str+=pattern;//expand string for convience
    int size=str.size();

    for(int i=0; i<size; i++)
    {
        pos=str.find(pattern,i);
        if(pos<size)
        {
            std::string s=str.substr(i,pos-i);
            result.push_back(s);
            i=pos+pattern.size()-1;
        }
    }
    return result;
}

//convert string to double
double str2num(string s)
 {   
        double num;
        stringstream ss(s);
        ss>>num;
        return num;
}
int write_data(void *ptr, int size, int nmemb, FILE *stream) 
{
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}


/*
//input the data from the internet url u  to "stock.txt"
int ImportURL(const string& u)
{ 
	//declaration of an object CURL
	CURL *handle;
	//file pointer to create file that store the data  
   

	//result of the whole process
	CURLcode result;
	//set up the program environment libcurl need
	curl_global_init(CURL_GLOBAL_ALL);
	//curl_easy_init() returns a CURL easy handle for resue in other easy functions
	handle = curl_easy_init();
	const char *url=u.data(); 
	const char outfilename[FILENAME_MAX]="Stock.txt"; 
	//if everything's all right with the easy handle...
	if (handle)
	{
        fp=fopen(outfilename,"wb");  
        //various options for curl   
        curl_easy_setopt(handle, CURLOPT_URL, url);  
        curl_easy_setopt(handle, CURLOPT_ENCODING, "");  
		curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);  
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, fp); 
        result = curl_easy_perform(handle);  
        
        fclose(fp);
		
		//check for errors
		if (result != CURLE_OK)
		{
			//if errors have occurred, tell us what is wrong with 'result'
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
			return 1;
		}
	}
	else //if sth's gone wrong with curl at the beginning
	{
		fprintf(stderr, "Curl init failed!\n");
		return 1;
	}

	//cleanup
	curl_easy_cleanup(handle);

	//releases resources acquired by curl_global_init()
	curl_global_cleanup();

	return 0;
}*/

//input the data from the internet url u  to "stock.txt"
int ImportURL(const string& u, Vector1 &price)
{ 
	struct MemoryStruct data;
    data.memory=NULL;
    data.size = 0;   
	
	//declaration of an object CURL
	CURL *curl;
	//file pointer to create file that store the data  
    FILE *fp=NULL;  

	//indiactor that can be used to judge if opening url success or not  
    CURLcode res;  
	
	//set up the program environment libcurl need
	curl_global_init(CURL_GLOBAL_ALL);
	//curl_easy_init() returns a CURL easy handle for resue in other easy functions
	curl = curl_easy_init();
	
	const char *url=u.data(); 
	//const char outfilename[FILENAME_MAX]="Stock.txt";  
	//if everything's all right with the easy handle...
	if (curl)
	{   
		curl_easy_setopt(curl, CURLOPT_URL, url);  
        curl_easy_setopt(curl, CURLOPT_ENCODING, "");  
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data2);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&data); 
        res = curl_easy_perform(curl);  
		
		stringstream sData; if(data.memory==NULL) cout<<"???"<<endl;
		sData.str(data.memory);
		string sValue;
		double dValue = 0;
		for (string line; getline(sData, line); ) {
			sValue = line.substr(line.find_last_of(',')+1);
			dValue = strtod (sValue.c_str(), NULL);
			price.push_back(dValue);
			//cout << sValue << " " << dValue << endl; 
		}
	price.erase(price.begin());
		//system("pause");
	}
	else //if sth's gone wrong with curl at the beginning
	{
		fprintf(stderr, "Curl init failed!\n");
		return 1;
	}

	//cleanup
	curl_easy_cleanup(curl);

	//releases resources acquired by curl_global_init()
	curl_global_cleanup();

	return 0;
}

void ImportAllURLandPrice(StockVec &stockVec)
{
	int terminate;
	for(int i=0;i<stockVec.size();i++)
	{  Vector1 price;
		terminate=ImportURL(stockVec[i].getURL(),price);
		if (terminate==1)
		{ 
			cout<<"URL error!Please correct it & Try again"<<endl;
			cout<<"Error URL: "<<stockVec[i].getURL()<<endl;
			system("Pause");
			exit (EXIT_FAILURE);
		} 
	
		stockVec[i].setPrice(price);	
		stockVec[i].setStockReturn(); //cout<<i<<" "<<stockVec[i].getTicker()<<" "<<stockVec[i].getPrice().size()<<endl;
	}
}

void ImportAllspyURLandPrice(StockVec &stockVec)
{
	int terminate;
	for(int i=0;i<stockVec.size();i++)
	{  Vector1 price;
		terminate=ImportURL(stockVec[i].getSpyURL(),price);
		if (terminate==1)
		{ 
			cout<<"URL error!Please correct it & Try again"<<endl;
			cout<<"Error URL: "<<stockVec[i].getSpyURL()<<endl;
			system("Pause");
			exit (EXIT_FAILURE);
		}
		//ifstream infile("Stock.txt");
		//Vector1 price;
		//price=Spilt2Price(infile);
		stockVec[i].setSpyPrice(price);	
		stockVec[i].setSpyReturn();
		stockVec[i].setAbnormalReturn();
	}
}
int readFile(ifstream &infile, StockVec &stockVec)
{
	//string group;
	string ticker;
	double estimatedEPS;
	double actualEPS;
	string day0;
	string day30Prior;
	string day30After;
	//string uRL;

	int count=0;

    if (infile.is_open())
    {
      while (!infile.eof() )
      { 
		  infile>>ticker>>estimatedEPS>>actualEPS>>day0>>day30Prior>>day30After;
		  //cout<<group<<" "<<ticker<<" "<<estimatedEPS<<" "<<actualEPS<<" "<<day0<<" "<<day30Prior<<" "<<day30After<<" "<<endl;
		  stockVec[count].setStock(ticker,estimatedEPS,actualEPS,day0,day30Prior,day30After);
		  //cout<<"Print file Ticker"<<stockVec[count].getTicker()<<endl;
		  count++; 
      }
      infile.close();
	  return count;
    }
    else {
	   cout << "Unable to open file"; 
	   exit (EXIT_FAILURE);
    }
}

void GroupStocks(Group &Missed, Group &Beat,Group &Met, StockVec stockVec)
{ 
	//string str; 
	int countBeat=0,countMet=0, countMissed=0;
	double diff;
	for (int i=0; i<stockVec.size();i++)
	{ 		
		diff=stockVec[i].getActualEPS()-stockVec[i].getEstimatedEPS();
		if(diff<0)
		{ 
			Missed.setStocks(stockVec[i],countMissed);
			countMissed++;
		}
		else if(diff>=0 && diff<H)
		{ 
			Met.setStocks(stockVec[i],countMet);
			countMet++;
		}
		else if(diff>=H)
		{
			Beat.setStocks(stockVec[i],countBeat);
			countBeat++;
		} 
	}
	Missed.Stocks.resize(countMissed); 
	Met.Stocks.resize(countMet);
	Beat.Stocks.resize(countBeat);
	Missed.setCAAR(); 
	Met.setCAAR(); 
	Beat.setCAAR(); 
}




Vector<double, long> v2V(Vector1 &V)
{   long n=V.size();
	Vector<double, long> Vec(n);
	for(int i=0;i<n;i++) Vec[i+1]=V[i];
	return Vec;
}

void Vectorlist(list<Vector<double, long> > &vectorList,Matrix1 &M)
{
	int n=M.size();
	for(int m=0;m<n;m++) vectorList.push_back(v2V(M[m]));		
}

Matrix<double,long> trans(Matrix1 &M)
{
	int n=M.size();
	int m=M[0].size();
	for(int i=1;i<n;i++)
	{if(M[i].size()>m) m=M[i].size();}
	Matrix<double,long> Mx(n,m);
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++) Mx(i+1,j+1)=M[i][j];
	return Mx;
}


void printtoexcel(StockVec &stockVec,Group &Beat,Group &Met,Group &Missed)
{  
	Matrix1 stockprice,spyprice;
	list<string> tickerlist;
	for(int n=0;n<stockVec.size();n++)
	{
		stockprice.push_back(stockVec[n].getPrice());
		spyprice.push_back(stockVec[n].getSpyPrice());
		tickerlist.push_back(stockVec[n].getTicker());
	}
	NumericMatrix<double,long> PstockNx(trans(stockprice));
	NumericMatrix<double,long> PspyNx(trans(spyprice));
	std::string Pstock("Pstock");
	std::string Pspy("Pspy");
	
	Matrix1 AAR,CAAR;
	AAR.push_back(Beat.getAARt());
	AAR.push_back(Met.getAARt());
	AAR.push_back(Missed.getAARt());
	CAAR.push_back(Beat.getCAAR());
	CAAR.push_back(Met.getCAAR());
	CAAR.push_back(Missed.getCAAR());
	NumericMatrix<double,long> AARNx(trans(AAR));
	NumericMatrix<double,long> CAARNx(trans(CAAR));
  	
	long N=60;
	Vector<double, long> xarr(N+1);
	
	double h1 = 1;
	xarr[xarr.MinIndex()] = -30;
	for (long i = xarr.MinIndex()+1; i <= xarr.MaxIndex(); i++)
	{
		xarr[i] = xarr[i-1] + h1;
	}
	Vector<double, long> xarr2(N);
	xarr2[xarr2.MinIndex()] = -29;
	for (long i = xarr2.MinIndex()+1; i <= xarr2.MaxIndex(); i++)
	{
		xarr2[i] = xarr2[i-1] + h1;
	}
	 
	//collables day-30 to day 30,for prices
	//collables day-29 to day 30,for returns
	list<std::string> collabels = convertToString(xarr);
	list<std::string> collabels2 = convertToString(xarr2);
	std::string sheetName("Pstock");
	std::string address("E:\VS\1.xlsx"); 
	list<string> grouplist;
	grouplist.push_back("Beat");
	grouplist.push_back("Meet");
	grouplist.push_back("Miss");
	string AARs("AAR");
	string CAARs("CAAR");

	
	ExcelDriver& excel = ExcelDriver::Instance();
	excel.MakeVisible(true);		// Default is INVISIBLE!
          //output the data for test purposes,can be customized
	//excel.AddMatrix(Pstock, PstockNx,tickerlist , collabels);
	///excel.AddMatrix(Pspy, PspyNx,tickerlist, collabels); 
	//excel.AddMatrix(AARs, AARNx,grouplist , collabels2);
	//excel.AddMatrix(CAARs, CAARNx,grouplist , collabels2);

	Vector<double, long> rowArr(3);
	rowArr[rowArr.MinIndex()] = 1;
	for (long i = rowArr.MinIndex()+1; i <= rowArr.MaxIndex(); i++)
	{
		rowArr[i] = rowArr[i-1] + h1;
	}

	list<Vector<double, long> > vectorList,vectorList2;
	Vectorlist(vectorList,CAAR);
	string xTitle("date");
	string yTitle("CAAR");
	string CAARChart("CAAR Chart");
	excel.CreateChart(xarr2, grouplist, vectorList, CAARChart, xTitle, yTitle);

	Vectorlist(vectorList2,AAR);
	string yTitle2("AAR");
	string AARChart("AAR Chart");
	excel.CreateChart(xarr2, grouplist, vectorList2, AARChart, xTitle, yTitle2);	
}


 int write_data2(void *ptr, size_t size, size_t nmemb, void *data)
 {
   size_t realsize = size * nmemb;
   struct MemoryStruct *mem = (struct MemoryStruct *)data;
 
   mem->memory = (char *)myrealloc(mem->memory, mem->size + realsize + 1);
   if (mem->memory) {
     memcpy(&(mem->memory[mem->size]), ptr, realsize);
     mem->size += realsize;
     mem->memory[mem->size] = 0;
   }
   return realsize;
 }

 
  void *myrealloc(void *ptr, size_t size)
 {
   /* There might be a realloc() out there that doesn't like reallocing
      NULL pointers, so we take care of it here */
   if(ptr)
     return realloc(ptr, size);
   else
     return malloc(size);
 }

