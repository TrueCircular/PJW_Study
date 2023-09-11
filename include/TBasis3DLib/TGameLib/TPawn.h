#pragma once
#include "TDxObject.h"
#include "TCollision.h"
class TObjectManager;

static const int MAX_BTN_SIZE = 4;
enum TObjectType {
	BACKGROUND = 0,
	UICONTROL,
	MAP,	
	USER,
	NPC,
	ITEM,
};
enum TControlState {
	DEFAULT = 0,
	PUSH,
	SELECT,
	DISABLE,
};
enum TOverlapState {
	OVERLAP_NONE = 0,
	OVERLAP_BEGIN,
	OVERLAP_STAY,
	OVERLAP_END,
};
enum TCollisionType
{
	T_IGNORE = 0,		/// 무시한다.
	T_OVERLAP,			/// 겹칠 수 있다.
	T_BLOCKING			/// 중첩될 수 없고 블록킹 된다.
};
enum TSelectState
{
	T_DEFAULT = 0,  /// 마우스가 위에 없을 때( T_FOCUS상태에서 다른 곳이 T_ACTIVE 이후 상태가 되었을 때 전환된다.)
	T_HOVER = 1,	/// 마우스가 위에 있을 때	
	T_FOCUS = 2,	/// T_ACTIVE에서 마우스를 왼쪽 버튼을 다른 곳에서 놓았을 때( 또는 탭, 엔터키 적용 대상, 기타 경우)	
	T_ACTIVE = 4,	/// 마우스 좌측 버튼을 누르고 있을 때(키 상태의 KEY_HOLD와 같다)	
	T_SELECTED = 8, /// T_ACTIVE에서 마우스를 왼쪽 버튼을 위에서 놓았을 때( 이후에는 T_FOCUS가 된다.)
};
struct TObjectAttribute
{
	std::wstring szName;	// 이름
	int  iObjectType;		// TObjectType
	bool bEnable;			// 오브젝트 활성화 / 비활성화
	bool bSelectEnable;		// 선택 활성화 / 비활성화
	bool bCollisionEnable;  // 충돌 활성화 / 비활성화
	bool bVisible;		    // 드로우 활성화 / 비활성화
	RECT rtImage;			// 텍스처 클라이언트 좌표계(0~ 512)
	RECT rtClient;			// 클라이언트 좌표계
	std::wstring  maskImage;// 마스크 이미지
	//TSelectState 열거형 배열 인덱스 만큼(0번 디폴트이미지)
	std::vector<std::wstring> stateImage; // 마우스 선택 이미지들
	TObjectAttribute()
	{
		szName = L"none";
		bEnable = true;
		bVisible = true;
		bCollisionEnable = false;
		bSelectEnable = false;
		rtImage = { 0,0,0,0 };
		rtClient = { 0,0,0,0 };
		iObjectType = UICONTROL;
	}
};
static int g_iActiveDepth = 10000;
class TPawn : public TDxObject
{
public:
	int				 m_iObjectType = TObjectType::BACKGROUND;
	int				 m_iLifeCount=1;
	float			 m_fLifeTime = 10.0f;
	float			 m_fInvincible =false; // 무적상태
	//랜더링 순서를 정한다.(높은값이 나중에 렌더링)
	int				 m_iDepth=0;
	int				 m_iSaveDepth = 0;
	static TPawn*	 m_pActiveObject;

	void			 SetDepth(int depth)
	{
		m_iSaveDepth = m_iDepth = depth;
	}
	void			 TopActive()
	{
		if (m_pActiveObject != nullptr)
		{
			m_pActiveObject->InActive();
		}
		m_iSaveDepth = m_iDepth;
		m_iDepth = g_iActiveDepth;
		m_pActiveObject = this;
	}
	void			 InActive()
	{
		m_iDepth = m_iSaveDepth;
	}
	// 마우스 선택 활성화 및 비활성화
	bool			 m_bSelectEnable = false;
	// 충돌 활성화 및 비활성화
	bool			 m_bCollisionEnable = false;	
	// 보이기 활성화 및 비활성화
	bool			 m_bVisible = true;

	// 오브젝트 전체의 처리를 활성화 및 비활성화
	bool			 m_bEnable = true;
	void			 SetEnable(bool enable) {
		m_bEnable = enable;
	}
	TObjectAttribute m_ObjAttribute;
	int			m_iCollisionType = -1;
	FVector     m_rtPosition;
	FVector     m_Position;
	FVector     m_Direction;
	float		m_fSpeed;
	RECT		m_rtDraw;	// 클라이언트 영역
	RECT		m_rtTexture;// 텍스처 영역
	RECT		m_rtCollision;
	float		m_fAttackRadius;
	TShpere		m_Sphere;
	int			m_iSelectID=-1;
	int			m_iCollisionID = -1;
	DWORD		m_dwCollisionState = 0;
	DWORD		m_dwSelectState = 0;
	std::map<int, DWORD>   m_OtherObjectState;
public:
	bool		m_bDead = false;
	void		SetDead() { m_bDead = true; }
public:
	std::wstring	m_szTexList[MAX_BTN_SIZE];
	TImage*			m_pBtnState[MAX_BTN_SIZE];
public:
	std::vector<TPawn*>  m_pChildList;
public:
	bool		Init() override;
	bool		Release() override;
	virtual bool	SetCollisionMgr(TObjectManager& mgr);
	virtual bool	CreateLoad(ID3D11Device* pd3dDevice,
		ID3D11DeviceContext*    pd3dContext,
		TObjectAttribute& att);
public:
	virtual void    SetPos(FVector p);	
	virtual void    SetDir(FVector p);
	virtual void    SetPosUpdate(FVector p);
	virtual void    SetRectImage(RECT rt);
	virtual void    SetRectDraw(RECT rt);
	virtual void    UpdateVertexData();
	virtual void    Update(RECT rt);
	virtual void    Update();
	virtual bool	CreateVertexData() override;
	virtual void    MouseOverlap(POINT ptPos, DWORD dwState);
	virtual void    HitOverlap(TPawn* pDestObj, DWORD dwState);
	virtual void    NoneOverlap(TPawn* pDestObj, DWORD dwState);
	virtual void    BeginOverlap(TPawn* pDestObj, DWORD dwState);
	virtual void    StayOverlap(TPawn* pDestObj, DWORD dwState);
	virtual void    EndOverlap(TPawn* pDestObj, DWORD dwState);
public:
	TPawn();
	virtual ~TPawn();
};

