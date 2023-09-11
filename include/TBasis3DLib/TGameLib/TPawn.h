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
	T_IGNORE = 0,		/// �����Ѵ�.
	T_OVERLAP,			/// ��ĥ �� �ִ�.
	T_BLOCKING			/// ��ø�� �� ���� ���ŷ �ȴ�.
};
enum TSelectState
{
	T_DEFAULT = 0,  /// ���콺�� ���� ���� ��( T_FOCUS���¿��� �ٸ� ���� T_ACTIVE ���� ���°� �Ǿ��� �� ��ȯ�ȴ�.)
	T_HOVER = 1,	/// ���콺�� ���� ���� ��	
	T_FOCUS = 2,	/// T_ACTIVE���� ���콺�� ���� ��ư�� �ٸ� ������ ������ ��( �Ǵ� ��, ����Ű ���� ���, ��Ÿ ���)	
	T_ACTIVE = 4,	/// ���콺 ���� ��ư�� ������ ���� ��(Ű ������ KEY_HOLD�� ����)	
	T_SELECTED = 8, /// T_ACTIVE���� ���콺�� ���� ��ư�� ������ ������ ��( ���Ŀ��� T_FOCUS�� �ȴ�.)
};
struct TObjectAttribute
{
	std::wstring szName;	// �̸�
	int  iObjectType;		// TObjectType
	bool bEnable;			// ������Ʈ Ȱ��ȭ / ��Ȱ��ȭ
	bool bSelectEnable;		// ���� Ȱ��ȭ / ��Ȱ��ȭ
	bool bCollisionEnable;  // �浹 Ȱ��ȭ / ��Ȱ��ȭ
	bool bVisible;		    // ��ο� Ȱ��ȭ / ��Ȱ��ȭ
	RECT rtImage;			// �ؽ�ó Ŭ���̾�Ʈ ��ǥ��(0~ 512)
	RECT rtClient;			// Ŭ���̾�Ʈ ��ǥ��
	std::wstring  maskImage;// ����ũ �̹���
	//TSelectState ������ �迭 �ε��� ��ŭ(0�� ����Ʈ�̹���)
	std::vector<std::wstring> stateImage; // ���콺 ���� �̹�����
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
	float			 m_fInvincible =false; // ��������
	//������ ������ ���Ѵ�.(�������� ���߿� ������)
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
	// ���콺 ���� Ȱ��ȭ �� ��Ȱ��ȭ
	bool			 m_bSelectEnable = false;
	// �浹 Ȱ��ȭ �� ��Ȱ��ȭ
	bool			 m_bCollisionEnable = false;	
	// ���̱� Ȱ��ȭ �� ��Ȱ��ȭ
	bool			 m_bVisible = true;

	// ������Ʈ ��ü�� ó���� Ȱ��ȭ �� ��Ȱ��ȭ
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
	RECT		m_rtDraw;	// Ŭ���̾�Ʈ ����
	RECT		m_rtTexture;// �ؽ�ó ����
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

