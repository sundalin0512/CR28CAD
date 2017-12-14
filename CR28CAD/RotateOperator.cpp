#include "stdafx.h"
#include "RotateOperator.h"


RotateOperator::RotateOperator()
{
}


RotateOperator::~RotateOperator()
{
}

void RotateOperator::Redo()
{
	m_pShape->AddRotate(m_rotate);
}

void RotateOperator::Undo()
{
	m_pShape->AddRotate(-m_rotate);
}
