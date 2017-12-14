#pragma once
#include "IOperator.h"
#include "IShape.h"

class MoveOperator :
	public IOperator
{
	public:
	MoveOperator();
	MoveOperator(IShape* pShape, POINT oldPt, POINT newPt):
		m_pShape(pShape), ptOld(oldPt),ptNew(newPt)
	{
		
	}
	virtual ~MoveOperator();
	void Redo() override;
	void Undo() override;
	private:
	IShape * m_pShape; //被移动的图形
	POINT ptOld; //移动之前的坐标
	POINT ptNew; //移动之后的坐标
};

