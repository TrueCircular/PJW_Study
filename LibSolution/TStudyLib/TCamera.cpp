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
	// ¿ùµåÁÂÇ¥ ¹üÀ§(-10 ~ +10)  camera (0,0)
	// -10 ~ +10 camera (-5,0)°¡ ¿øÁ¡ÀÌ µÈ´Ù.
	// ºä ÁÂÇ¥ -> -5 ~ 15
	// Åõ¿µÁÂÇ¥ -> 9 ~ 10 ~ 11
	// Åõ¿µÁÂÇ¥ -> -1 ~ 0 ~ +1
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