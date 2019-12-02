#pragma once

#include "resource.h"
#include "framework.h"

class MRender
{
public:
	MRender();
	~MRender();
	bool Initialize();

	bool Paint(HWND hWnd);
	bool UpdateFrame();
	bool UpdateFrame(HDC hdc);
	void Shutdown();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:

};

