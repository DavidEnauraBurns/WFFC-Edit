#pragma once
#include <stack>
#include <vector>

#include "Action.h"

class ActionController
{
public:
	ActionController(int memory) : m_memory(memory), m_cachedAction(nullptr)
	{
		m_undoStack.reserve(memory);
		m_redoStack.reserve(memory);
	}
	void PushNewAction(Action* action)
	{
		if (action)
			m_undoStack.push_back(action);

		if(m_undoStack.size() > m_memory)
		{
			delete m_undoStack.front();
			m_undoStack.erase(m_undoStack.begin());
		}
		while(!m_redoStack.empty())
		{
			delete m_redoStack.back();
			m_redoStack.pop_back();
		}
	}

	void Undo()
	{
		if(!m_undoStack.empty())
		{
			m_undoStack.back()->undo();
			m_redoStack.push_back(m_undoStack.back());
			m_undoStack.pop_back();
		}
	}

	void Redo()
	{
		if (!m_redoStack.empty())
		{
			m_redoStack.back()->redo();
			m_undoStack.push_back(m_redoStack.back());
			m_redoStack.pop_back();
		}
	}

	Action* Top() { return m_undoStack.back(); }

	Action* m_cachedAction;

private:
	std::vector<Action*> m_undoStack;
	std::vector<Action*> m_redoStack;

	const int m_memory;
};
