#pragma once
#include <map>
#include<vector>
#include <assert.h>
#include <iostream>
#include "DataLoder.h"
#include <cassert>
#include <set>
using namespace XY;
using std::map;
using std::vector;
using std::set;
namespace wx{
class SparseMatrix{
public:
	int rows,cols;
	int numOfNodes;
	double sparseRatio;
	set<int> items;
	set<int> users;
private:
	

	map<int,int> rowBegin;
	map<int,int> rowEnd;
	TripleNode *dataOfRowPri;

	map<int,int> colBegin;
	map<int,int> colEnd;
	TripleNode *dataOfColPri;

public:
	SparseMatrix(vector<TripleNode> & scoreList);         //Constructor
	
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
	ColIterator BeginOfCol(int col)  {
		/*if(colBegin.find(col)== colBegin.end())
		{
		std::cout << " the col is invalid" <<std::endl;

		}*/
		assert(colBegin.find(col)!= colBegin.end());
		return ColIterator(this,col,colBegin[col]);	
	};
	ColIterator EndOfCol(int col) {
		return ColIterator(this,col,colEnd[col]+1);	
	};

	class _RowIterator{
	public:
		_RowIterator(SparseMatrix *_sm,int _Row,int _pos);
		/*_RowIterator(const _RowIterator &coI){
			sm = new SparseMatrix(Row);
		}*/
		_RowIterator & operator +=(int i)
		{
			pos += i;
			assert(sm->rowBegin[row] <= pos && pos <= sm->rowEnd[row]+1);
			return *this;
		}
		bool operator !=(const _RowIterator & rhs)
		{
			return pos!= rhs.pos;		
		}

		TripleNode * operator ->()
		{
			return &sm->dataOfRowPri[pos] ;
		}
		_RowIterator operator ++(int)
		{
			_RowIterator temp(*this);
			pos++;
			return temp;
		}
		TripleNode &operator *(){
			return  sm->dataOfRowPri[pos];
		}
		/*TripleNode* operator ->(){
			return  sm->dataOfRowPri[pos];
		}*/
	private:
		int row,pos;
	    SparseMatrix *sm;
	};
	typedef _RowIterator RowIterator;
		RowIterator BeginOfRow(int _row) {

		assert(rowBegin.find(_row)!= rowBegin.end());
		return RowIterator(this,_row,rowBegin[_row]);	
	};
	RowIterator EndOfRow(int Row) {
		return RowIterator(this,Row,rowEnd[Row]+1);	
	};

	int getElement(int i,int j) ;


	int innerProduct(int _row1,int _row2);
	int norm(int row);

	~SparseMatrix();

};

}
