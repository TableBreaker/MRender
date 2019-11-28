#pragma once

#include "resource.h"
#include "framework.h"

class MRender
{
public:
	MRender();
	~MRender();
	bool Initialize();
	bool UpdateFrame();
	void Shutdown();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:

};

