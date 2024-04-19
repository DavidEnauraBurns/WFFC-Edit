#pragma once

class Action
{
public:
	virtual ~Action() {}
	virtual void undo() = 0;
	virtual void redo() = 0;
};

