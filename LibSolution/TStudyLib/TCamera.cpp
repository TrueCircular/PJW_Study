#include "TCamera.h"
#include "TInput.h"

TMatrix TCamera::CreateLookAt(TVector3 pos, TVector3 target, TVector3 up)
{
	TVector3 dir = target - pos;
	D3DXVec3Normalize(&dir, &dir);
	float dot = D3DXVec3Dot(&up, &dir);
	TVector3 vP = dir * dot;
	TVector3 vUp = up - vP;
	D3DXVec3Normalize(&vUp, &vUp);
	TVector3 vRight;
	D3DXVec3Cross(&vRight, &vUp, &dir);

	m_matView._11 = vRight.x; m_matView._12 = vUp.x; m_matView._13 = dir.x;
	m_matView._21 = vRight.y; m_matView._22 = vUp.y; m_matView._23 = dir.y;
	m_matView._31 = vRight.z; m_matView._32 = vUp.z; m_matView._33 = dir.z;

	m_matView._41 = -(pos.x * m_matView._11 + pos.y * m_matView._21 + pos.z * m_matView._31);
	m_matView._42 = -(pos.x * m_matView._12 + pos.y * m_matView._22 + pos.z * m_matView._32);
	m_matView._43 = -(pos.x * m_matView._13 + pos.y * m_matView._23 + pos.z * m_matView._33);

	return m_matView;
}
TMatrix   TCamera::CreatePerspectiveFov(float fovy, float Aspect, float fNearPlane, float fFarPlane)
{
	m_far = fFarPlane;
	m_near = fNearPlane;

	float    h, w, Q;
	h = 1 / tan(fovy * 0.5f);
	w = h / Aspect;
	Q = fFarPlane / (fFarPlane - fNearPlane);

	m_matPerspectiveProj._44 = 0.0f;
	m_matPerspectiveProj._11 = w;
	m_matPerspectiveProj._22 = h;
	m_matPerspectiveProj._33 = Q;
	m_matPerspectiveProj._43 = -Q * fNearPlane;
	m_matPerspectiveProj._34 = 1;

	return m_matPerspectiveProj;
}

void   TCamera::UpdateVector()
{
	m_vLook.x = m_matView._13;
	m_vLook.y = m_matView._23;
	m_vLook.z = m_matView._33;
	m_vUp.x = m_matView._12;
	m_vUp.y = m_matView._22;
	m_vUp.z = m_matView._32;
	m_vSide.x = m_matView._11;
	m_vSide.y = m_matView._21;
	m_vSide.z = m_matView._31;
}

bool  TCamera::Frame()
{
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
