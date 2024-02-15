#pragma once

#include "DisplayChunk.h"

class InputCommands; 

class CameraController
{
public:
	CameraController();

public:
	// Functionality
	float m_movespeed;
	float m_camRotRate;

	DirectX::SimpleMath::Vector2 currentMousePos, previousMousePos;

	// Camera
	DirectX::SimpleMath::Vector3 m_camPosition;
	DirectX::SimpleMath::Vector3 m_camOrientation;
	DirectX::SimpleMath::Vector3 m_camLookAt;
	DirectX::SimpleMath::Vector3 m_camLookDirection;
	DirectX::SimpleMath::Vector3 m_camRight;

	DirectX::SimpleMath::Matrix m_view;

public:
	void Update(InputCommands* input_commands);
	void HandleMouseInput(InputCommands* input_commands);

	void CreateLookAt()
	{
		DirectX::SimpleMath::Matrix::CreateLookAt(m_camPosition, m_camLookAt, DirectX::SimpleMath::Vector3::UnitY);
	}

	DirectX::SimpleMath::Matrix const getView() { return m_view; };
	DirectX::SimpleMath::Vector3 const getPos() { return m_camPosition; };
};

