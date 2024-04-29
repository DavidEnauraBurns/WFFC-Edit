#include "CameraController.h"
#include <SimpleMath.h>


CameraController::CameraController(Vector3 position, Vector3 lookAt, int width, int height) :

	m_position(position),
	m_lookAt(lookAt),
	m_width(width),
	m_height(height),

	m_prevMousePos(Vector2::Zero),
	m_orientation(Vector3::Zero),
	m_lookDirection(lookAt),
	m_right(Vector3::Zero),
	m_up(Vector3::UnitY),

	m_rotRate(50),
	m_rotSensitivity(0.5),
	m_moveSpeed(10.f)
{
}

void CameraController::HandleInput(const InputCommands& input, const float dt)
{
	if (!input.allowCamera_movement) {
		m_prevMousePos = Vector2(input.mouse_X, input.mouse_Y);
		return;
	}

	Vector2 delta = Vector2(input.mouse_X, input.mouse_Y) - m_prevMousePos;
	m_prevMousePos = Vector2(input.mouse_X, input.mouse_Y);

	m_orientation.y += delta.x * m_rotRate * dt;
	m_orientation.x -= delta.y * m_rotRate * dt;

	m_orientation.x = std::min(std::max(m_orientation.x, -89.f), 89.f);

	Vector3 moveDirection = Vector3::Zero;

	Vector3 planarMoveDir = m_lookDirection;
	planarMoveDir.y = 0;
	planarMoveDir.Normalize();

	if (input.forward)
	{
		moveDirection += planarMoveDir;
	}
	if (input.back)
	{
		moveDirection -= planarMoveDir;
	}
	if (input.right)
	{
		moveDirection += m_right;
	}
	if (input.left)
	{
		moveDirection -= m_right;
	}
	if (input.up)
	{
		moveDirection += Vector3::Up;
	}
	if (input.down)
	{
		moveDirection -= Vector3::Up;
	}

	moveDirection.Normalize();
	m_position += (moveDirection * m_moveSpeed * dt);
}


void CameraController::Update(const float dt)
{
	auto Rad = [](float x) { return x * 3.1415 / 180; };

	// sphere equation
	m_lookDirection.x = cos(Rad(m_orientation.y)) * cos(Rad(m_orientation.x));
	m_lookDirection.y = sin(Rad(m_orientation.x));
	m_lookDirection.z = sin(Rad(m_orientation.y)) * cos(Rad(m_orientation.x));
	m_lookDirection.Normalize();

	//create right vector from look Direction
	m_lookDirection.Cross(Vector3::UnitY, m_right);

	//update lookat point
	m_lookAt = m_position + m_lookDirection;

	//apply camera vectors
	m_view = Matrix::CreateLookAt(m_position, m_lookAt, Vector3::UnitY);

}
