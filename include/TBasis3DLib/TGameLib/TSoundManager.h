#pragma once
#include <windows.h>
#include "TManager.h"
#include <fmod.h>
#include <fmod.hpp>
#include <fmod_errors.h>
#pragma comment (lib,"fmod_vc.lib") // fmod.dll 로드
class TSound
{
public:
	std::wstring m_csName;
	FMOD::Sound*   m_pSound = nullptr;
	FMOD::Channel* m_pChannel = nullptr;
public:
	bool    Init(ID3D11Device* pd3dDevice,	ID3D11DeviceContext* pd3dContext)
	{
		return true;
	};
	bool	Load(std::wstring path, std::wstring key);
	bool	Play();
	bool	Stop();
	bool	Paused();
	void    Volume(float fVolume);
	bool	Release();
	TSound()
	{		
	}
	TSound(std::wstring name)
	{
		m_csName = name;
	}
};
class TSoundManager : public TManager<TSound>
{
	// 단일객체 생성(싱글톤)
	static TSoundManager g_SoundManager;
public:
	static FMOD::System* m_pSystem;
	static TSoundManager* Get()
	{
		return &g_SoundManager;
	}
public:
	/*
	FMod 시스템 초기화 작업
	*/
	bool    Init(ID3D11Device* pd3dDevice, 
				 ID3D11DeviceContext* pd3dContext) override; // 
	/*
	FMod 시스템 초기화 소멸
	*/
	bool	Release();
	bool	Frame();
	void    Volume(std::wstring playfile, float fVolume);
	bool	Play(std::wstring);
	bool	Paused(std::wstring);
	bool	Stop(std::wstring);
private:
	TSoundManager();
public:
	virtual ~TSoundManager();
};
