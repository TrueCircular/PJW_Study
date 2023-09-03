#pragma once
#include "TStd.h"
#include "TSpriteObj.h"
#include "TSoundMgr.h"


#define MAX_SCENE_SIZE (int)E_SceneType::SCENE_END

 typedef enum 
{
	SCENE_TITLE = 0,
	SCENE_TOWN,
	SCENE_WORLD,
	SCENE_BATTLE,
	SCENE_SAVE_LOAD,
	SCENE_END
}E_SceneType;

 using Sprite = std::unique_ptr<TPlaneObj>;
class GameScene
{
protected:
	Sprite		_backGround;
	TSound*		_music;
public:
	GameScene(){}
	virtual ~GameScene(){}
public:
	virtual bool Init() = 0;
	virtual bool Frame() = 0;
	virtual bool Render() = 0;
	virtual bool Release() = 0;
};

class TitleScene : public GameScene
{
private:

private:
	void BirdMove();
	void MenuGradation();
public:
	bool Init()override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
};

class TownScene : public GameScene
{
public:
	bool Init()override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
};
class WorldScene : public GameScene
{
public:
	bool Init()override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
};
class BattleScene : public GameScene
{
public:
	bool Init()override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
};
class SaveLoadScene : public GameScene
{
public:
	bool Init()override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
};

class SceneFactory
{
public:
	static GameScene* CreateScene(E_SceneType type);
};

class SceneManager
{
private:
	GameScene*								_currentScene;
	E_SceneType								_currentSceneName;
	std::array<GameScene*, MAX_SCENE_SIZE>  _sceneList;
private:
	SceneManager();
	void Init();
public:
	~SceneManager();
	//GET
	static SceneManager& GetInstance();
	GameScene*			 GetCurrentScene();
	E_SceneType			 GetCurrentSceneName();
	//SET
	void				 SetCurrentScene(E_SceneType trans);
};

