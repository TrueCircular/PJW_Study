#include "SceneManager.h"
#include "ICoreStd.h"

SceneManager::SceneManager()
{
	Init();
	SetCurrentScene(E_SceneType::SCENE_TITLE);
}

SceneManager::~SceneManager()
{
	if (_currentScene)
	{
		delete _currentScene;
		_currentScene = nullptr;
	}
	if (_sceneList.size() > 0)
	{
		for (auto a : _sceneList)
		{
			delete a;
			a = nullptr;
		}
	}
}

SceneManager& SceneManager::GetInstance()
{
	static SceneManager instance;
	return instance;
}

void SceneManager::Init()
{
	for (int i = 0; i < _sceneList.size(); i++)
	{
		_sceneList[i] = SceneFactory::CreateScene((E_SceneType)i);
	}
}

void SceneManager::SetCurrentScene(E_SceneType trans)
{
	if (trans >= 0 && trans < MAX_SCENE_SIZE)
	{
		_currentScene = _sceneList[(int)trans];
		_currentSceneName = trans;
	}
	else
		throw std::out_of_range("Invalid scene type");
}

GameScene* SceneManager::GetCurrentScene()
{
	return _currentScene;
}

E_SceneType SceneManager::GetCurrentSceneName()
{
	return _currentSceneName;
}

GameScene* SceneFactory::CreateScene(E_SceneType type)
{
	switch (type)
	{
	case E_SceneType::SCENE_TITLE:
	{
		return new TitleScene();
	}
	case E_SceneType::SCENE_TOWN:
	{
		return new TownScene();
	}
	case E_SceneType::SCENE_WORLD:
	{
		return new WorldScene();
	}
	case E_SceneType::SCENE_BATTLE:
	{
		return new BattleScene();
	}
	case E_SceneType::SCENE_SAVE_LOAD:
	{
		return new SaveLoadScene();
	}
	default:
		return nullptr;
	}
}

bool TitleScene::Init()
{
	_backGround = std::make_unique<TPlaneObj>();

	//bakcground
	S_TOBJECT_DESC bDesc;
	ZeroMemory(&bDesc, sizeof(S_TOBJECT_DESC));
	bDesc.pos = { 0,0,0 };
	bDesc.scale = { g_fMapHalfSizeX, g_fMapHalfSizeY, 1.0f };
	bDesc.shaderFileName = L"../../resource/shader/Plane.hlsl";
	bDesc.texFileName = L"../../resource/Background/Main.png";
	_backGround->Create(bDesc);

	//music
	_music = I_Sound.Load(L"../../resource/Sound/Scene/Main.wav");
	_music->Play(true);
	_music->Volume(0.35f);

	return true;
}
bool TitleScene::Frame()
{
	I_Sound.Frame();
	_backGround->Frame();
	return true;
}
bool TitleScene::Render()
{
	_backGround->SetMatrix(nullptr, &ICore::g_pMainCamera->m_matView, &ICore::g_pMainCamera->m_matOrthoProjection);
	_backGround->Render();
	return true;
}
bool TitleScene::Release()
{
	return true;
}

bool TownScene::Init()
{
	return false;
}

bool TownScene::Frame()
{
	return false;
}

bool TownScene::Render()
{
	return false;
}

bool TownScene::Release()
{
	return false;
}

bool WorldScene::Init()
{
	return false;
}

bool WorldScene::Frame()
{
	return false;
}

bool WorldScene::Render()
{
	return false;
}

bool WorldScene::Release()
{
	return false;
}

bool BattleScene::Init()
{
	return false;
}

bool BattleScene::Frame()
{
	return false;
}

bool BattleScene::Render()
{
	return false;
}

bool BattleScene::Release()
{
	return false;
}

bool SaveLoadScene::Init()
{
	return false;
}

bool SaveLoadScene::Frame()
{
	return false;
}

bool SaveLoadScene::Render()
{
	return false;
}

bool SaveLoadScene::Release()
{
	return false;
}
