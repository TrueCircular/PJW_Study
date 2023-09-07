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
		m_vCameraPos.x = 0;
		m_vCameraPos.y = 0;
		m_vCameraPos.z = 0;

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
	float fHalfWidth = m_dwWindowWidth / 2.0f;
	float fHalfHeight = m_dwWindowHeight / 2.0f;

	std::pair<float, float> ProjecPair = ZoomInOut(fHalfWidth, fHalfHeight);

	m_rt.Set(m_vCameraPos, 1250, 550);

	m_matView._41 = -m_vCameraPos.x;
	m_matView._42 = -m_vCameraPos.y;
	m_matView._43 = -m_vCameraPos.z;

	m_matOrthoProjection._11 = 1.0f / ProjecPair.first;
	m_matOrthoProjection._22 = 1.0f / ProjecPair.second;

	return true;
}
bool  TCamera::Init()
{
	return true;
}
bool  TCamera::Render()
{
	return true;
}
bool  TCamera::Release()
{
	return true;
}