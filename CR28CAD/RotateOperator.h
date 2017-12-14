#pragma once
#include "IOperator.h"
#include "IShape.h"

class RotateOperator :
	public IOperator
{
	public:
	RotateOperator();
	RotateOperator(IShape* shape, float rotate)
		: m_pShape(shape),m_rotate(rotate)
	{
		
	}
	virtual ~RotateOperator();
	void Redo() override;
	void Undo() override;

	private:
	IShape * m_pShape; 
	float m_rotate; 
};

