#pragma once

#include "resource.h"
#include "framework.h"
#include "MInput.h"

const bool FULL_SCREEN = false;

class MRender
{
public:
	MRender();
	~MRender();
	bool Initialize(int screenWidth, int screenHeight);

	bool Paint(HWND hWnd);
	bool UpdateFrame(HDC hdc);
	void Shutdown();

	int GetScrWidth() { return m_screenWidth; }
	void SetScrWidth(int width) { m_screenWidth = width; }
	int GetScrHeight() { return m_screenHeight; }
	void SetScrHeight(int height) { m_screenHeight = height; }

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	int m_screenWidth;
	int m_screenHeight;

	MInput* m_input;
};

