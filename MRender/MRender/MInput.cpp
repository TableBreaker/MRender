#include "MInput.h"

MInput::MInput()
{
	
}

MInput::MInput(const MInput& other)
{

}

MInput::~MInput()
{

}

void MInput::Initialize()
{
	for (int i = 0; i < 256; i++)
	{
		m_keys[i] = false;
	}

	return;
}

void MInput::KeyDown(unsigned int input)
{
	m_keys[input] = true;
	return;
}

void MInput::KeyUp(unsigned int input)
{
	m_keys[input] = false;
	return;
}

bool MInput::IsKeyDown(unsigned int input)
{
	return m_keys[input];
}