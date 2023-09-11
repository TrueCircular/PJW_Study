#pragma once
// directx sdk  win10�� ��ġ �Ǿ� �ִ�.
#include <d3d11.h> // 2d, 3d �׷���
#pragma comment (lib,"d3d11.lib") // D3D11.DLL
class TGraphics
{
public:
	ID3D11Device*			m_pd3dDevice; //����
	ID3D11DeviceContext*    m_pd3dContext;//����
	IDXGISwapChain*			m_pSwapChain; //�����
	ID3D11RenderTargetView* m_pRTV;       //�����Ÿ��
	D3D11_VIEWPORT			m_ViewPort;   //ȭ�� ������� ������
	
	ID3D11SamplerState*		m_pSamplerState;
	// blend state
	ID3D11BlendState*		m_pAlphaBlend;
	bool					CreateBlendState();
	// depth-stencil state	
	ID3D11DepthStencilView*	 m_pDepthStencilView;
	ID3D11DepthStencilState* m_pDSSDepthEnable;
	ID3D11DepthStencilState* m_pDSSDepthDisable;
	HRESULT UpdateDepthStencilView(ID3D11Device* pDevice, UINT Width, UINT Height);
public:
	bool	Init(HWND hWnd,LONG w, LONG h);
	bool    PreRender();
	bool    PostRender(); 
	bool    Release();
public:
	TGraphics();
	virtual ~TGraphics();
};

