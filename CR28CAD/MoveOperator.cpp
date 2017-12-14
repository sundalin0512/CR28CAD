#include "stdafx.h"
#include "MoveOperator.h"


MoveOperator::MoveOperator()
{
}


MoveOperator::~MoveOperator()
{
}

void MoveOperator::Redo()
{
	m_pShape->MoveShape(ptOld, ptNew);
}

void MoveOperator::Undo()
{
	m_pShape->MoveShape(ptNew, ptOld);
}
