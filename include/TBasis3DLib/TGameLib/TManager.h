#pragma once
#include "TStd.h"
template <class T>
class TManager
{
	// 외부에서는 private 동일하지만 
	// 자식은 사용할 수 있다.
protected:
	ID3D11Device*			m_pd3dDevice; //생성
	ID3D11DeviceContext*    m_pd3dContext;//관리
public:
	std::map<std::wstring, T*> m_Map;
	std::wstring   m_strDefaultPath;
	typedef typename std::map<std::wstring, T*>::iterator ITER;
	std::vector<std::wstring>  m_fileList;
public:
	virtual bool    Init(
		ID3D11Device* pd3dDevice, 
		ID3D11DeviceContext* pd3dContext) 
	{
		m_pd3dDevice = pd3dDevice;
		m_pd3dContext = pd3dContext;
		return true;
	};
	virtual bool    Add(std::wstring);
	virtual bool    Release();
	virtual T*		GetPtr(std::wstring);
	virtual void	LoadDir(std::wstring path);
public:
	TManager();
	virtual ~TManager();
};
template <class T>
bool    TManager<T>::Add(std::wstring key)
{
	T* pData = GetPtr(key);
	if (pData != nullptr)
	{
		return true;
	}
	T* pNewData = new T(key);
	pNewData->Init(m_pd3dDevice, m_pd3dContext);
	bool bLoad = pNewData->Load(nullptr, key);
	if (bLoad==true)
	{		
		std::pair<ITER, bool> ret;
		ret = m_Map.insert(std::make_pair(key, pNewData));
		return ret.second;
	}
	return  false;
}
template <class T>
T* TManager<T>::GetPtr(std::wstring key)
{	
	ITER iter = m_Map.find(key);
	if (iter != m_Map.end())
	{
		T* pData = (T*)iter->second;
		return pData;
	}
	return nullptr;
}
template <class T>
bool	TManager<T>::Release()
{
	for (auto data : m_Map)
	{
		T* pData = data.second;
		pData->Release();
		delete pData;
	}
	m_Map.clear();
	return true;
}
template <class T>
void TManager<T>::LoadDir(std::wstring path)
{
	std::wstring dirPath = path + L"*.*";
	intptr_t handle; // fopen
	struct _wfinddata_t fd;
	handle = _wfindfirst(dirPath.c_str(), &fd);
	if (handle == -1L)
	{
		return;
	}
	do
	{
		// 디렉토리
		if ((fd.attrib & _A_SUBDIR) && fd.name[0] != '.')
		{
			LoadDir(path + fd.name + L"/");
		}
		else if (fd.name[0] != '.')// 파일, 
		{
			m_fileList.push_back(fd.name);
		}
	} while (_wfindnext(handle, &fd) == 0);
	_findclose(handle);

	for (std::wstring& data : m_fileList)
	{
		bool ret = Add(data);
		if (!ret)
		{
			OutputDebugString(L"중복\n");
		}
	}
}
template <class T>
TManager<T>::TManager()
{
	m_pd3dDevice = nullptr;
	m_pd3dContext = nullptr;
	m_strDefaultPath = L"../../data/";
}
template <class T>
TManager<T>::~TManager()
{
	m_fileList.clear();
}

