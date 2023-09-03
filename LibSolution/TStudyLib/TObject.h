#pragma once
#include "TDxObject.h"

struct S_TOBJECT_DESC
{
	TVector3 pos;
	TVector3 scale;
	std::wstring texFileName;
	std::wstring shaderFileName;
};

class TObject : public TDxObject
{
public:
	bool            m_bDead = false;
	int             m_iCollisionID = -1;
	int             m_iSelectID = -1;
	bool            m_isFlip = false;
public:
	TVector3        m_vPos;
	TVector3        m_vScale;
	TVector3        m_vRotation;
	TRect	        m_tRT;
	TVector2		m_rtPos;
public:
	TMatrix         matScale, matRotation, matTranslate;
	TMatrix         m_matWorld;
	TMatrix         m_matView;
	TMatrix         m_matProj;
public:
	void          SetPos(TVector3 p);
	void          SetScale(TVector3 s);
	virtual void  SetRect(TVector2& c, float w, float h);
public:
	virtual bool  Create(std::wstring shaderFilename,
		std::wstring texFilename);
	virtual bool  Create(S_TOBJECT_DESC desc);
	virtual void  UpdateMatrix();
	virtual void  UpdateRect();
	virtual bool  Init() override;
	virtual bool  Frame()override;
	virtual bool  Render()override;
	virtual bool  Release()override;
	virtual void  SetMatrix(TMatrix* matWorld, TMatrix* matView, TMatrix* matProj);
	virtual void  Move(float fSecond) {};
public:
	TObject();
	virtual ~TObject() {}
};

