#include "stdafx.h"
#include <algorithm>
#include <fstream>
#include "SparseMatrix.h"
using namespace std;
namespace wx{
SparseMatrix::_ColIterator ::_ColIterator(SparseMatrix *_sm,int _col,int _pos)
:sm(_sm),col(_col)
{
	pos = _pos ;
}

SparseMatrix::SparseMatrix(vector<TripleNode> & scoreList){
	//dataOfRowPri
	int row_id_old;
	if(!scoreList.empty())
	{
		 dataOfRowPri = new TripleNode[scoreList.size()];
		 row_id_old = -1;                                    //
	}
	assert(!scoreList.empty());
	for (size_t i = 0 ;i < scoreList.size() ; i++)
	{
		dataOfRowPri[i] = scoreList[i];             //defuat assignment constructor
		int row_id = scoreList[i].user_id;
		int col_id = scoreList[i].brand_id;
		int score = scoreList[i].score;
		if(row_id != row_id_old)
		{
			rowEnd[row_id_old] = i -1;
			row_id_old = row_id;	
			rowBegin[row_id] = i;
		}
	}
	rowEnd[row_id_old] = scoreList.size() - 1 ;
	rows = rowBegin.size();
	//dataOfColPri
	sort(scoreList.begin(),scoreList.end(),[](TripleNode & lhs,TripleNode & rhs){return lhs.brand_id < rhs.brand_id; });
    int col_id_old;
	if(!scoreList.empty())
	{
		dataOfColPri = new TripleNode[scoreList.size()];
		col_id_old = -1;                                    //
	}
	assert(!scoreList.empty());

	/*char lines[20];
	ofstream fileout("E:/CWorkspace/aliContest/aliContest/USB2.csv");*/
	for (size_t i = 0 ;i < scoreList.size() ; i++)
	{
		dataOfColPri[i] = scoreList[i];   
		int col_id = scoreList[i].brand_id;//defuat assignment constructor
		int row_id = scoreList[i].user_id;
		int score = scoreList[i].score;

		/*sprintf_s(lines,"%d,%d,%d\n",row_id,col_id,score);
		fileout << lines;*/

		if(col_id != col_id_old)
		{
			colEnd[col_id_old] = i -1;
			col_id_old = col_id;	
			colBegin[col_id] = i;

		}
	}
	colEnd[col_id_old] = scoreList.size() - 1 ;
	cols = colBegin.size();
	numOfNodes = scoreList.size();

}
TripleNode SparseMatrix::getElement(int i,int j){
	//int index = rowBegin[i];
	//return dataOfRowlPri[index];
	int index = colBegin[j];
	return dataOfColPri[index];
}

SparseMatrix::~SparseMatrix(){
	delete [] dataOfColPri;
	delete [] dataOfRowPri;
}


class Test{
private:
	Test(){};
	static Test * instance;
public:	
	static Test * getInstance(){
		if(instance == nullptr)
			instance = new Test();
		return instance;
	}
	~Test(){
		delete instance;
		instance = nullptr;
	}
};

}