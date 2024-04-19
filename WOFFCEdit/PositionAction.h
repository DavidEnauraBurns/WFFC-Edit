#pragma once
#include "Action.h"
#include <SimpleMath.h>

class PositionAction : public Action
{
public:
	PositionAction(DirectX::SimpleMath::Vector3& elementPosition)
		: m_oldPosition(elementPosition), m_elementPosition(elementPosition) {}

	void SetNewPosition(DirectX::SimpleMath::Vector3 newPosition) { m_newPosition = newPosition; }

	void undo() override { m_elementPosition = m_oldPosition; }
	void redo() override { m_elementPosition = m_newPosition; }

private:
	DirectX::SimpleMath::Vector3 m_oldPosition;
	DirectX::SimpleMath::Vector3 m_newPosition;
	DirectX::SimpleMath::Vector3& m_elementPosition;
};
