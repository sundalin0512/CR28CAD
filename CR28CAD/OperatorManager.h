#pragma once
#include <stack>
#include "IOperator.h"
#include "CR28CADDoc.h"

class OperatorManager
{
	public:
	OperatorManager(CCR28CADDoc * pDoc);
	~OperatorManager();
	void AddOperator(IOperator* pOperator);
	void Redo();
	void Undo();

	CCR28CADDoc * m_pDoc;

	private:
	std::stack<IOperator*> m_stackToUndo; //待撤销表
	std::stack<IOperator*> m_stackToRedo; //待重做表
};

