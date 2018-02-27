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

	//��մ�������
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
	//�ж�ջ�Ƿ�Ϊ��
	if (m_stackToRedo.empty())
	{
		return;
	}

	//��ͼ�δӴ��������ó�,ִ������,Ȼ�󱣴浽��������
	IOperator* pOperator = m_stackToRedo.top();
	m_stackToRedo.pop();
	pOperator->Redo();
	m_stackToUndo.push(pOperator);

	m_pDoc->UpdateAllViews(NULL);
}

void OperatorManager::Undo()
{
	//�ж�ջ�Ƿ�Ϊ��
	if (m_stackToUndo.empty())
	{
		return;
	}

	//��ͼ�δӴ��������ó�,ִ�г���,Ȼ�󱣴浽��������
	IOperator* pOperator = m_stackToUndo.top();
	m_stackToUndo.pop();
	pOperator->Undo();
	m_stackToRedo.push(pOperator);
	m_pDoc->UpdateAllViews(NULL);
}
