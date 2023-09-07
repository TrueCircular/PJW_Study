#include "Sample.h"
#include "TWriter.h"
#include "ICoreStd.h"
#include "TInput.h"
float g_fMapHalfSizeX = 800;
float g_fMapHalfSizeY = 450;

using std::shared_ptr;

void Sample::DebugMode()
{
	if (I_Input.GetInstance().m_dwKeyState[VK_NUMPAD4] == KEY_PUSH)
	{
		m_rsFillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	}
	if (I_Input.GetInstance().m_dwKeyState[VK_NUMPAD5] == KEY_PUSH)
	{
		m_rsFillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
	}
}

bool Sample::Init()
{
	//Create Camera
	m_pMainCamera->Create({ 0,0,0 }, { (float)g_dwWindowWidth, (float)g_dwWindowHeight });
	return true;
}

bool Sample::Frame()
{

	DebugMode();
	return true;
}

bool Sample::Render()
{
	return true;
}

bool Sample::Release()
{
	return true;
}


TGAME("ssda", 1600, 900)
