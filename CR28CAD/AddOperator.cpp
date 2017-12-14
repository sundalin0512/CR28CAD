#include "stdafx.h"
#include "AddOperator.h"


AddOperator::AddOperator()
{
}

AddOperator::AddOperator(CList<IShape*, IShape*>* pList, IShape* pShape):
	m_pLstShapes(pList), m_pShape(pShape)
{
}


AddOperator::~AddOperator()
{
}

void AddOperator::Redo()
{
	m_pLstShapes->AddTail(m_pShape);
}

void AddOperator::Undo()
{
	m_pLstShapes->RemoveAt(m_pLstShapes->Find(m_pShape));
}
