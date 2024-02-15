#include "CameraController.h"
#include "InputCommands.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

CameraController::CameraController()
{
	// Functionality
	m_movespeed = 0.30;
	m_camRotRate = 3.0;

	// Camera
	m_camPosition.x = 0.0f;
	m_camPosition.y = 3.7f;
	m_camPosition.z = -3.5f;

	m_camOrientation.x = 0;
	m_camOrientation.y = 0;
	m_camOrientation.z = 0;

	m_camLookAt.x = 0.0f;
	m_camLookAt.y = 0.0f;
	m_camLookAt.z = 0.0f;

	m_camLookDirection.x = 0.0f;
	m_camLookDirection.y = 0.0f;
	m_camLookDirection.z = 0.0f;

	m_camRight.x = 0.0f;
	m_camRight.y = 0.0f;
	m_camRight.z = 0.0f;

	m_camOrientation.x = 0.0f;
	m_camOrientation.y = 0.0f;
	m_camOrientation.z = 0.0f;
}

void CameraController::Update(InputCommands* input_commands)
{
	Vector3 planarMotionVector = m_camLookDirection;
	planarMotionVector.y = 0.0;

	if (input_commands->rotRight)
	{
		m_camOrientation.y -= m_camRotRate;
	}
	if (input_commands->rotLeft)
	{
		m_camOrientation.y += m_camRotRate;
	}
	if (input_commands->rotUp)
	{
		m_camOrientation.x += m_camRotRate;
	}
	if (input_commands->rotDown)
	{
		m_camOrientation.x -= m_camRotRate;
	}

	m_camOrientation.y += input_commands->mouseDX;
	m_camOrientation.x += input_commands->mouseDY;

	// For avoiding Gimbal Lock
	m_camOrientation.x = std::min(m_camOrientation.x, +89.f);
	m_camOrientation.x = std::max(m_camOrientation.x, -89.f);

	//create look direction from Euler angles in m_camOrientation
	m_camLookDirection.x = sin((m_camOrientation.y) * 3.1415 / 180);
	m_camLookDirection.z = cos((m_camOrientation.y) * 3.1415 / 180);
	m_camLookDirection.y = cos((m_camOrientation.x) * 3.1415 / 180);
	m_camLookDirection.Normalize();

	//create right vector from look Direction
	m_camLookDirection.Cross(Vector3::UnitY, m_camRight);

	//process input and update stuff
	if (input_commands->forward)
	{
		m_camPosition += m_camLookDirection * m_movespeed;
	}
	if (input_commands->back)
	{
		m_camPosition -= m_camLookDirection * m_movespeed;
	}
	if (input_commands->right)
	{
		m_camPosition += m_camRight * m_movespeed;
	}
	if (input_commands->left)
	{
		m_camPosition -= m_camRight * m_movespeed;
	}

	m_camLookAt = m_camPosition + m_camLookDirection;

	//apply camera vectors
	m_view = Matrix::CreateLookAt(m_camPosition, m_camLookAt, Vector3::UnitY);
}

void CameraController::HandleMouseInput(InputCommands* input)
{
	if (input)
	{
		currentMousePos = DirectX::SimpleMath::Vector2(input->mouse_X, input->mouse_Y);

		if (input->mouseLB)
		{
			DirectX::SimpleMath::Vector2 Difference;

			Difference.x = currentMousePos.x - previousMousePos.x;
			Difference.y = currentMousePos.y - previousMousePos.y;

			Difference.Normalize();

			if (Difference.x != 0 || Difference.y != 0)
			{
				m_camOrientation.y += m_camRotRate * Difference.x;
				m_camOrientation.x -= m_camRotRate * Difference.y;
			}
			float cosR, cosP, cosY; //temp values for sin/cos from 
			float sinR, sinP, sinY;

			cosP = cosf(m_camOrientation.x * (3.1415 / 180));
			cosY = cosf(m_camOrientation.y * (3.1415 / 180));
			cosR = cosf(m_camOrientation.z * (3.1415 / 180));

			sinP = sinf(m_camOrientation.x * (3.1415 / 180));
			sinY = sinf(m_camOrientation.y * (3.1415 / 180));
			sinR = sinf(m_camOrientation.z * (3.1415 / 180));

			m_camLookDirection.x = sinY * cosP;
			m_camLookDirection.y = sinP;
			m_camLookDirection.z = cosP * -cosY;

			m_camLookAt = m_camPosition + m_camLookDirection;

			m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_camPosition, m_camLookAt, DirectX::SimpleMath::Vector3::UnitY);


		}
		previousMousePos = currentMousePos;
	}
}
