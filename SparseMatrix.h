#include <map>
#include<vector>
#include <assert.h>
#include <iostream>
#include "DataLoder.h"
#include <cassert>
using namespace XY;
using std::map;
using std::vector;
namespace wx{
class SparseMatrix{
private:
	int rows,cols;
	int numOfNodes;
	float sparseRatio;

	map<int,int> rowBegin;
	map<int,int> rowEnd;
	TripleNode *dataOfRowPri;

	map<int,int> colBegin;
	map<int,int> colEnd;
	TripleNode *dataOfColPri;
public:

	
	//friend RowIterator;  //to do
	class _ColIterator{
	public:
		_ColIterator(SparseMatrix *_sm,int _col,int _pos);
		/*_ColIterator(const _ColIterator &coI){
			sm = new SparseMatrix(coL);
		}*/
		_ColIterator & operator +=(int i)
		{
			pos += i;
			assert(sm->colBegin[col] <= pos && pos <= sm->colEnd[col] );
			return *this;
		}
		bool operator !=(const _ColIterator & rhs)
		{
			return pos!= rhs.pos;		
		}

		_ColIterator operator ++(int)
		{
			_ColIterator temp(*this);
			pos++;
			return temp;
		}
		TripleNode &operator *(){
			return  sm->dataOfColPri[pos];
		}
		/*TripleNode* operator ->(){
			return  sm->dataOfColPri[pos];
		}*/
	private:
		int col,pos;
		SparseMatrix *sm;
	};

	typedef _ColIterator ColIterator;
	                                          //typedef complete definition
	ColIterator BeginOfCol(int col){
		/*if(colBegin.find(col)== colBegin.end())
		{
		std::cout << " the col is invalid" <<std::endl;

		}*/
		assert(colBegin.find(col)!= colBegin.end());
		return ColIterator(this,col,colBegin[col]);	
	};
	ColIterator EndOfCol(int col){
		return ColIterator(this,col,colEnd[col]+1);	
	};
	SparseMatrix(vector<TripleNode> & scoreList);


	float getSparseRatio(){
		return numOfNodes/cols*rows ; 
	}
	TripleNode getElement(int i,int j);
	~SparseMatrix();

};

}
