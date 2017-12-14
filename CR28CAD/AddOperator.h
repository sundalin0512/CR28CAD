#pragma once
#include "IOperator.h"
#include "IShape.h"

class AddOperator :
	public IOperator
{
	public:
	AddOperator();
	AddOperator(CList<IShape*, IShape*>* pList, IShape* pShape);
	virtual ~AddOperator();
	void Redo() override;
	void Undo() override;
	CList<IShape*, IShape*>* m_pLstShapes;//图形链表
	IShape* m_pShape; //需要添加到链表的图形
};

