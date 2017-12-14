#pragma once
class IOperator
{
	public:
	IOperator();
	virtual ~IOperator();

	virtual void Redo() = 0;
	virtual void Undo() = 0;
};

