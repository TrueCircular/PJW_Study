#pragma once
#include "TUserInterface.h"
#include "TGameUser.h"
#include "TNpcObject.h"
#include "TEffect.h"

struct TEnum
{
	enum  TGameType 
	{
		T_MAP = 0,
		T_USER = 100,
		T_NPC = 200,
		T_INTERFACE = 300,
		T_BUTTON,
		T_EDIT,
		T_DIALOGBOX,
		T_EFFECT = 400,
		T_OBJECT = 500,
	};
};


class TScene
{
public:
	enum TSceneID
	{
		TSCENE_LOADING = 0,
		TSCENE_LOBBY = 1,
		TSCENE_ZONE = 2,
	};
public:
	static TScene*				m_pCurrentScene;
	std::vector<TObjAttribute>  m_ObjAttribute;
	static TGameUser*			m_pGamePlayer;	
	std::vector<TSpriteInfo>	m_rtSpriteList;

	std::map<wstring, TPawn*>				m_UIObjList;
	std::map<wstring, TPawn*>				m_ItemObjList;
	std::map<wstring, TPawn*>				m_ObjList;
	std::map<wstring, TPawn*>				m_CharacterList;
	std::map<wstring, TPawn*>				m_MapList;
	std::map<wstring, TPawn*>::iterator	m_iter;

	std::vector<std::pair<wstring, TPawn*>>	m_UIDrawObjList;
public:
	virtual TPawn*	FindUI(std::wstring szName);
	virtual TPawn*	FindItem(std::wstring szName);
	virtual TPawn*	FindObject(std::wstring szName);
	virtual TPawn*	FindMap(std::wstring szName);
	virtual TPawn*	FindNpc(int iIndex);
	virtual TPawn*	FindParent(std::wstring szName);
	virtual bool		DelNpc(int iIndex);
public:
	std::map<int, TGameUser*>			m_UserList;
	std::map<int, TPawn*>				m_NpcList;
public:
	static int	m_iStageCounter;
	TPoint		m_ptInitHeroPos;
	int			m_iNextScene;
	int			m_iNpcCounter;
	int			m_iMaxCounter;
	bool		m_bGameFinish;
	int			m_iSceneID;
	bool		m_bSceneChange;
public:
	std::vector<TEffectInfo>	m_EffectList;
	virtual void  AddEffect(wstring name, TPoint pos, TPoint dir);
	virtual void  AddNpc(wstring name, TPoint pos, TPoint dir, int index);
	virtual bool  Reset();
	virtual void  SortZValue(	std::map<wstring, TPawn*>& srcList, 
								std::vector<std::pair<wstring, TPawn*>>& destList);
public:
	virtual LRESULT	 MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual bool  Load(const TCHAR* filename);
	virtual bool  Init();
	virtual bool  PreFrame();
	virtual bool  Frame();
	virtual bool  PostFrame();
	virtual bool  PreRender();
	virtual bool  Render();
	virtual bool  PostRender();
	virtual bool  RenderMap();
	virtual bool  RenderObject();
	virtual bool  RenderCharacter();
	virtual bool  RenderEffect();
	virtual bool  RenderUI();
	virtual bool  Release();
public:
	virtual TPawn*  NewObj(TObjAttribute& info);
	virtual bool  CreateScene();
	virtual bool  SetObject(TObjAttribute& iType, TPawn* pObj);
public:
	TScene();
	virtual ~TScene();

};

