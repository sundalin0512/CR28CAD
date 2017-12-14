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
	CList<IShape*, IShape*>* m_pLstShapes;//ͼ������
	IShape* m_pShape; //��Ҫ��ӵ������ͼ��
};

