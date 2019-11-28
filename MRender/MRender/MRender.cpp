#include "MRender.h"
#include "framework.h"

MRender::MRender()
{
}

MRender::~MRender()
{
}

bool MRender::Initialize()
{
	return true;
}

bool MRender::UpdateFrame()
{
	return true;
}

void MRender::Shutdown()
{

}

LRESULT CALLBACK MRender::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
		// Check if a key has been pressed on the keyboard.
	case WM_KEYDOWN:
	{
		// If a key is pressed send it to the input object so it can record that state.
		// m_Input->KeyDown((unsigned int)wparam);
		return 0;
	}

	// Check if a key has been released on the keyboard.
	case WM_KEYUP:
	{
		// If a key is released then send it to the input obejct so it can unset the state for that key.
		// m_Input->KeyUp((unsigned int)wparam);
		return 0;
	}

	// Any other messages send to the default message handler as our application won't make use of them.
	default:
	{
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
	}
}