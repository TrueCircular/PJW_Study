#pragma once
#include "THeroObject.h"
#include "TMap.h"
#include "TNpcObject.h"
#include "TUIObject.h"
#include "TEffectObject.h"
#include "TWriter.h"
#include "TObjectManager.h""
struct TDepthCmp
{
	bool operator() (TPawn* a, TPawn* b)
	{
		return a->m_iDepth > b->m_iDepth;
	}
};
class TScene 
{
public:
	enum TSceneID
	{
		TSCENE_NONE = 0,
		TCENE_INTRO,
		TSCENE_LOBBY,
		TSCENE_ZONE,
	};
	TObjectManager			m_CollisionMgr;
	ID3D11Device*			m_pd3dDevice;
	ID3D11DeviceContext*    m_pd3dContext;
	DWORD					m_dwScneID = TCENE_INTRO;
	bool					m_bGameEnding = false;
	static TScene*	m_pCurrentScene;
	virtual TPawn*		GetPlayer();
	std::map<std::wstring, TPawn*>	m_EffectObjList;
	std::map<std::wstring, TPawn*>	m_UIObjList;
	std::priority_queue<TPawn*, std::vector<TPawn*>, TDepthCmp>  m_UIObjDraw;
	std::map<std::wstring, TPawn*>	m_ItemObjList;
	std::map<std::wstring, TPawn*>	m_ObjList;
	std::map<std::wstring, TPawn*>	m_CharacterList;
	std::map<std::wstring, TPawn*>	m_MapList;
public:
	virtual bool   CreateScene(ID3D11Device* pd3dDevice,ID3D11DeviceContext*    pd3dContext);
	virtual RECT   GetClientCenter(int iWidth, int iHeight);
	virtual bool   Init();
	virtual bool   SceneFrame() final;
	virtual bool   SceneRender() final;
	virtual bool   PreFrame();
	virtual bool   Frame();
	virtual bool   PostFrame();
	virtual bool   PreRender();
	virtual bool   Render();
	virtual bool   PostRender();	
	virtual bool   Release();
	virtual bool   GetSelectUI();
public:
	TScene();
	virtual ~TScene();
};

