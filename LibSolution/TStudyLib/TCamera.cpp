#include "TCamera.h"
#include "TInput.h"

TMatrix TCamera::CreateLookAt(TVector3 pos, TVector3 target, TVector3 up)
{
	TVector3 dir = target - pos;
	dir = dir.NormalVector();
	float dot = up | dir;

	TVector3 vP = dir * dot;
	TVector3 vUp = up - vP;
	vUp = vUp.NormalVector();
	TVector3 vRight = vUp ^ dir;

	TMatrix tMt;
	tMt._11 = vRight.x; tMt._12 = vUp.x; tMt._13 = dir.x;
	tMt._21 = vRight.x; tMt._22 = vUp.y; tMt._23 = dir.y;
	tMt._31 = vRight.x; tMt._32 = vUp.z; tMt._33 = dir.z;
	tMt._41 = -(pos.x * tMt._11 + pos.y * tMt._21 + pos.z * tMt._31);
	tMt._42 = -(pos.x * tMt._11 + pos.y * tMt._21 + pos.z * tMt._31);
	tMt._43 = -(pos.x * tMt._11 + pos.y * tMt._21 + pos.z * tMt._31);

	return tMt;
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
	return true;
}
bool  TCamera::Init()
{
	m_vTargetPos = { 0,0,0 };
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
