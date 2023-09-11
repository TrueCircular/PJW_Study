#pragma once
#include "TEffect.h"
#include <functional>
struct cmp {
	bool operator()(int i, int j)
	{
		if (i > j) return true;
		else return false;
	}
};
class TObjectComposite : public TPawn
{
public:
	std::deque<TPawn*> m_Components;
public:
	TPawn* Clone();
};

using CollisionFunction = std::function<void(TPawn*, DWORD)>;
using SelectFunction = std::function<void(POINT, DWORD)>;

class TObjectManager : public TSingleton<TObjectManager>
{
public:
	friend  class TSingleton<TObjectManager>;
private:
	std::vector<TObjAttribute>  m_ObjAttribute;
	std::vector<TSpriteInfo>	m_rtSpriteList;
private:
	std::map<wstring, TPawn*>				m_List;
	std::map<wstring, TPawn*>::iterator	m_iter;
	std::wstring				m_szDefaultPath;
private:
	int		m_iExecuteSelectID = 0;
	int		m_iExecuteCollisionID = 0;
	std::map<int ,TPawn*>	      m_CollisionObjectList;
	std::map<int, TPawn*>	      m_SelectObjectList;

	typedef std::map<int, SelectFunction>::iterator SelectFuncIterator;
	std::map<int, SelectFunction>    m_fnSelectExecute;

	typedef std::map<int, CollisionFunction>::iterator CollisionFuncIterator;
	std::map<int, CollisionFunction>    m_fnCollisionExecute;
public:
	void		AddSelectExecute(TPawn* ownder, SelectFunction func);
	void		AddCollisionExecute(TPawn* ownder, CollisionFunction func);
	void		DeleteExecute(TPawn* owner);
public:
	TPawn*	Add(TPawn* pAddObject);
	bool		Load(const TCHAR* filename);
	TPawn*	GetPtr(wstring szName);
	TPawn*	Clone(wstring szName);
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
public:
	bool  LoadObjectFile(T_STR szFileName, std::vector<TObjAttribute>&);
	bool  LoadEffectFile(T_STR szFileName, std::vector<TSpriteInfo>&);
	void  CreateEffect(std::vector<TSpriteInfo>&	list);
	void  CreateObject(std::vector<TObjAttribute>&	list);
	void  GetBitmapLoad(FILE* fp, wstring& ret);
private:
	TObjectManager();
public:
	~TObjectManager();
};
#define g_ObjectMgr TObjectManager::GetInstance()

