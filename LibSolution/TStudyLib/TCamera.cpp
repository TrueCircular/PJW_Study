#include "TCamera.h"
#include "TInput.h"
bool  TCamera::Create(TVector3 vPos, TVector2 size)
{
	m_vCameraPos = vPos;
	m_dwWindowWidth = size.x;
	m_dwWindowHeight = size.y;
	m_matView._41 = -m_vCameraPos.x;
	m_matView._42 = -m_vCameraPos.y;
	m_matView._43 = -m_vCameraPos.z;
	m_matOrthoProjection._11 = 2.0f / ((float)m_dwWindowWidth);
	m_matOrthoProjection._22 = 2.0f / ((float)m_dwWindowHeight);
	m_povNear = 1.0f;
	m_povFar = 1000.0f;
	return true;
}
std::pair<float, float> TCamera::ZoomInOut(float halfWidth, float halfHeight)
{
	std::pair<float, float> temp;
	temp.first = halfWidth;
	temp.second = halfHeight;

	TVector3 mouse = I_Input.GetWorldPos({ (float)g_dwWindowWidth, (float)g_dwWindowHeight }, m_vCameraPos);
	TVector2 mouse2 = I_Input.GetWorldPosVec2({ (float)g_dwWindowWidth, (float)g_dwWindowHeight }, m_vCameraPos);

	if (m_rt.ToPoint(mouse2))
	{
		_isCamMove = false;
	}
	else
	{
		_isCamMove = true;
	}

	if (_isCamMove)
	{
		TVector3 mDir = mouse - m_vCameraPos;
		mDir.Normalize();
		TVector3 velo = mDir * 400.f * g_fSecondPerFrame;
		m_vCameraPos += velo;
	}

	if (I_Input.GetInstance().m_dwKeyState[VK_NUMPAD1] == KEY_PUSH)
	{
		m_zoomState = E_CameraZoomState::CAMERA_ZOOM_ONCE;
	}
	if (I_Input.GetInstance().m_dwKeyState[VK_NUMPAD2] == KEY_PUSH)
	{
		m_zoomState = E_CameraZoomState::CAMERA_ZOOM_TWICE;
	}
	if (I_Input.GetInstance().m_dwKeyState[VK_NUMPAD3] == KEY_PUSH)
	{
		m_zoomState = E_CameraZoomState::CAMERA_ZOOM_TRIPLE;
	}

	switch (m_zoomState)
	{
	case CAMERA_ZOOM_ONCE:
	{
		m_vCameraPos.x = 0.f;
		m_vCameraPos.y = 0.f;
		m_vCameraPos.z = 0.f;

		return  temp;
	}
	case CAMERA_ZOOM_TWICE:
	{
		if (m_vCameraPos.x > g_fMapHalfSizeX - (halfWidth * 0.5f))
		{
			m_vCameraPos.x = g_fMapHalfSizeX - (halfWidth * 0.5f);
		}
		if (m_vCameraPos.x < -(g_fMapHalfSizeX)+(halfWidth * 0.5f))
		{
			m_vCameraPos.x = -(g_fMapHalfSizeX)+(halfWidth * 0.5f);
		}
		if (m_vCameraPos.y > g_fMapHalfSizeY - (halfHeight * 0.5f))
		{
			m_vCameraPos.y = g_fMapHalfSizeY - (halfHeight * 0.5f);
		}
		if (m_vCameraPos.y < -g_fMapHalfSizeY + (halfHeight * 0.5f))
		{
			m_vCameraPos.y = -g_fMapHalfSizeY + (halfHeight * 0.5f);
		}

		temp.first = halfWidth * 0.5f;
		temp.second = halfHeight * 0.5f;

		return  temp;
	}
	case CAMERA_ZOOM_TRIPLE:
	{
		if (m_vCameraPos.x > g_fMapHalfSizeX - (halfWidth * 0.33375f))
		{
			m_vCameraPos.x = g_fMapHalfSizeX - (halfWidth * 0.33375f);
		}
		if (m_vCameraPos.x < -(g_fMapHalfSizeX)+(halfWidth * 0.33375f))
		{
			m_vCameraPos.x = -(g_fMapHalfSizeX)+(halfWidth * 0.33375f);
		}
		if (m_vCameraPos.y > g_fMapHalfSizeY - (halfHeight * 0.33375f))
		{
			m_vCameraPos.y = g_fMapHalfSizeY - (halfHeight * 0.33375f);
		}
		if (m_vCameraPos.y < -(g_fMapHalfSizeY)+(halfHeight * 0.33375f))
		{
			m_vCameraPos.y = -(g_fMapHalfSizeY)+(halfHeight * 0.33375f);
		}

		temp.first = halfWidth * 0.33375f;
		temp.second = halfHeight * 0.33375f;

		return  temp;
	}
	default:
		return  temp;
	}
}
bool  TCamera::Frame()
{
	float fHalfWidth = m_dwWindowWidth;
	float fHalfHeight = m_dwWindowHeight;

	ProjecPair = ZoomInOut(g_dwWindowWidth/2, g_dwWindowHeight/2);

	m_rt.Set(m_vCameraPos, 1250.f, 550.f);

	m_matView._41 = -m_vCameraPos.x;
	m_matView._42 = -m_vCameraPos.y;
	m_matView._43 = -m_vCameraPos.z;

	m_matViewinverse._41 = -m_matView._41;
	m_matViewinverse._42 = -m_matView._42;
	m_matViewinverse._43 = -m_matView._43;

	m_matOrthoProjection._11 = 2.0f / ProjecPair.first;
	m_matOrthoProjection._22 = 2.0f / ProjecPair.second;
	m_matOrthoProjection._33 = 2.0f / (m_povFar - m_povNear);
	m_matOrthoProjection._43 = - m_povNear / (m_povFar - m_povNear);

	m_matOrthoProjectionInverse._11 = ProjecPair.first;
	m_matOrthoProjectionInverse._22 = ProjecPair.second;

	return true;
}
bool  TCamera::Init()
{
	return true;
}
bool  TCamera::Render()
{
#ifdef _DEBUG
	//std::wstring mousePos = std::to_wstring(m_vCameraPos.x);
	//mousePos += L",";
	//mousePos += std::to_wstring(m_vCameraPos.y);
	//mousePos += L"\n";
	//T_Debug(mousePos.c_str());
#endif

	return true;
}
bool  TCamera::Release()
{
	return true;
}
