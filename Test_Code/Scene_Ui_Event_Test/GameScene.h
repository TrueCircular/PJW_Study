#pragma once
#include "TStd.h"
#include "TPlaneObj.h"
#include "TSoundMgr.h"

enum E_SceneType
{
	SCENE_MAIN,
	SCENE_TOWN,
	SCENE_WORLD,
	SCENE_FIELD,
	SCENE_BATTLE,
	SCENE_NONE
};

using UPTR_BackGround = std::unique_ptr<TPlaneObj>;
using UPTR_BackMusic = std::unique_ptr<TSound>;

class GameScene
{
protected:
	UPTR_BackGround _backGround;
	UPTR_BackMusic	_bgm;
	E_SceneType     _sType = E_SceneType::SCENE_NONE;
public:
	E_SceneType GetSceneType() { return _sType; }
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
public:
	virtual void In() {};
	virtual void Update() {};
	virtual void Out() {};
};

class MainScene : public GameScene
{
public:
	bool Init()override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
public:
	void In()override;
	void Update()override;
	void Out()override;
};

class TownScene : public GameScene
{
public:
	bool Init()override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
public:
	void In()override;
	void Update()override;
	void Out()override;
};

