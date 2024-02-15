#pragma once

struct InputCommands
{
	bool forward;
	bool back;
	bool right;
	bool left;
	bool rotRight;
	bool rotLeft;
	bool rotUp;
	bool rotDown;

	//
	float mouse_X;
	float mouse_Y;
	long mouseDX;
	long mouseDY;
	bool mouseLB;
	bool mouseRB;
	bool mouseSW;
};
