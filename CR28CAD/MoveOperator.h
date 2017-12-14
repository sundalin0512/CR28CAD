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
	IShape * m_pShape; //���ƶ���ͼ��
	POINT ptOld; //�ƶ�֮ǰ������
	POINT ptNew; //�ƶ�֮�������
};

