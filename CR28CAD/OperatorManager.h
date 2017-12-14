#pragma once
#include <stack>
#include "IOperator.h"

class OperatorManager
{
	public:
	OperatorManager();
	~OperatorManager();
	void AddOperator(IOperator* pOperator);
	void Redo();
	void Undo();
	private:
	std::stack<IOperator*> m_stackToUndo; //��������
	std::stack<IOperator*> m_stackToRedo; //��������
};

