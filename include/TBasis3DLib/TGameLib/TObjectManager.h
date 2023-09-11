#pragma once
#include "TPawn.h"
using CollisionFunction = std::function<void (TPawn*, DWORD)>;
using SelectFunction = std::function<void(POINT, DWORD)>;
class TObjectManager : public TSingleton<TObjectManager>
{
	int  m_iExecuteSelectID = 0;
	int	 m_iExecuteCollisionID=0;
public:
	bool		m_bSelectUI=false;
public:
	bool		Frame();
public :
	friend class TSingleton<TObjectManager>;
	std::map<int, TPawn*>   m_SelectObjectList;
	std::map<int, SelectFunction> m_fnSelectExecute;
	void AddSelectExecute(TPawn* owner, SelectFunction func);
	void DeleteSelect(int iID);
public:
	std::map<int, TPawn*>   m_CollisionObjectList;	
	std::map<int, CollisionFunction> m_fnNoneExecute;
	std::map<int, CollisionFunction> m_fnBeginExecute;
	std::map<int, CollisionFunction> m_fnStayExecute;
	std::map<int, CollisionFunction> m_fnEndExecute;	
	void AddCollisionExecute(TPawn* owner, CollisionFunction func);
	void AddBeginExecute(TPawn* owner, CollisionFunction func);
	void AddStayExecute(TPawn* owner, CollisionFunction func);
	void AddEndExecute(TPawn* owner, CollisionFunction func);
	void DeleteCollision(int iID);
public:
	TObjectManager();
public:
	~TObjectManager();
};
#define I_ObjMgr TObjectManager::GetInstance()
