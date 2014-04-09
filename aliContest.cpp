// aliContest.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "SparseMatrix.h"
#include "DataLoder.h"
#include "Recomend.h"
using namespace wx;
using namespace std;
using namespace XY;

int _tmain(int argc, _TCHAR* argv[])
{
	//locale china("chs");//use china character  
	//wcin.imbue(china);//use locale object  
	//wcout.imbue(china);
	//wchar_t t ;
	//while (wcin >>t)
	//{
	//wcout << t << endl;

	//}
	//cout << "hahaha" << "\r" << "xixi" <<endl; 
	
	DataLoder dataloder;                               //                     DataPrimer
	//vector<DataLoder::UserDataPrimer> userDatasPrimer;
	//string dataSrc = "E:/CWorkspace/aliContest/aliContest/t_alibaba_data.csv";
	//dataloder.readCSV(dataSrc,userDatasPrimer);           
	//dataloder.scoresProcess( userDatasPrimer,list);
	//cout << userDatasPrimer.size()<<endl;


	                                //----------------------------------tripleTuple
	string tripleSrc = "E:/CWorkspace/aliContest/aliContest/UBS.csv";
	vector<TripleNode> _list;
	dataloder.readCSV(tripleSrc,_list);
	cout << _list.size() <<endl;
	 //-------------------------------------------------------------------manual data
	/*vector<TripleNode> _list;
	TripleNode node1(100,1008,1);
	TripleNode node2(101,1008,2);
	TripleNode node3(1000,2016,4);
	TripleNode node4(9888,45,4);
	_list.push_back(node1);
	_list.push_back(node2);
	_list.push_back(node3);
	_list.push_back(node4);
	*/
	SparseMatrix sm(_list);
	cout <<"ratio:" << sm.sparseRatio<< endl;;
	Recomend rcmd;
	/*int userRec = 19500 ; */
	vector<pair<int,float>> recs;
	int j = 0 ;
	for(set<int>::iterator it = sm.users.begin(); it!= sm.users.end(); it++ )
	{
    rcmd.userBasedRecomend(sm,*it,recs,0);
	j++;
	}

	system("pause");
	return 0;
}

