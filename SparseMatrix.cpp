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

SparseMatrix::_RowIterator ::_RowIterator (SparseMatrix *_sm,int _row,int _pos)
	:sm(_sm),row(_row)
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
		items.insert(col_id);
		users.insert(row_id);
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
	sparseRatio = (double)numOfNodes/(cols*rows);


}
int SparseMatrix::getElement(int i,int j){
	//int index = rowBegin[i];
	//return dataOfRowlPri[index];

	TripleNode *it = find_if(&dataOfRowPri[rowBegin[i]],&dataOfRowPri[rowEnd[i]]+1,[=](TripleNode &cur){ return cur.brand_id == j;}) ;

	if(it == &dataOfRowPri[rowEnd[i]] + 1 )
		{
			return 0;
	    }
	return it->score;



}


int SparseMatrix::innerProduct(int _row1,int _row2)
{
	int _innerProduct = 0 ;
	SparseMatrix::RowIterator it1 = BeginOfRow(_row1);
	SparseMatrix::RowIterator it2 = BeginOfRow(_row2);
	while (it1 !=EndOfRow(_row1) && it2!=EndOfRow(_row2))
	{
		if((*it1).brand_id == (*it2).brand_id)
		{
			_innerProduct += (*it1).score * (*it2).score;
			it1 ++ ;
			it2 ++ ;
		}
		else if((*it1).brand_id < (*it2).brand_id)
		{
			it1 ++ ;
		}
		else
		{
			it2 ++ ;
		}
	}
	return _innerProduct;
}



int SparseMatrix::norm(int _row){
	int sum_of_elems=0;
	std::for_each(&dataOfRowPri[rowBegin[_row]],&dataOfRowPri[rowEnd[_row]]+1,
		[&](TripleNode &t){
		sum_of_elems += t.score*t.score;  
	    }
	);
   return sum_of_elems;
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