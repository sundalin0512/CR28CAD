#include "stdafx.h"
#include "OperatorManager.h"


OperatorManager::OperatorManager(CCR28CADDoc * pDoc)
{
	m_pDoc = pDoc;
}


OperatorManager::~OperatorManager()
{
	while (!m_stackToRedo.empty())
	{
		IOperator* pOperator = m_stackToRedo.top();
		if (pOperator != NULL)
		{
			delete pOperator;
		}
		m_stackToRedo.pop();
	}
	while (!m_stackToUndo.empty())
	{
		IOperator* pOperator = m_stackToUndo.top();
		if (pOperator != NULL)
		{
			delete pOperator;
		}
		m_stackToUndo.pop();
	}
}

void OperatorManager::AddOperator(IOperator* pOperator)
{
	m_stackToUndo.push(pOperator);

	//清空待重做表
	while (!m_stackToRedo.empty())
	{
		IOperator* pOperator = m_stackToRedo.top();
		if (pOperator != NULL)
		{
			delete pOperator;
		}
		m_stackToRedo.pop();
	}
	m_pDoc->UpdateAllViews(NULL);
}

void OperatorManager::Redo()
{
	//判断栈是否为空
	if (m_stackToRedo.empty())
	{
		return;
	}

	//将图形从待重做表拿出,执行重做,然后保存到待撤销表
	IOperator* pOperator = m_stackToRedo.top();
	m_stackToRedo.pop();
	pOperator->Redo();
	m_stackToUndo.push(pOperator);

	m_pDoc->UpdateAllViews(NULL);
}

void OperatorManager::Undo()
{
	//判断栈是否为空
	if (m_stackToUndo.empty())
	{
		return;
	}

	//将图形从待撤销表拿出,执行撤销,然后保存到待重做表
	IOperator* pOperator = m_stackToUndo.top();
	m_stackToUndo.pop();
	pOperator->Undo();
	m_stackToRedo.push(pOperator);
	m_pDoc->UpdateAllViews(NULL);
}
