#include "GameScene.h"
#include "ICoreStd.h"

bool GameScene::Init()
{
    return true;
}

bool GameScene::Frame()
{
    return true;
}

bool GameScene::Render()
{
    _backGround->SetMatrix(nullptr, &ICore::g_pMainCamera->m_matView, &ICore::g_pMainCamera->m_matOrthoProjection);
    _backGround->Render();
    return true;
}

bool GameScene::Release()
{
    _backGround->Release();
    _bgm->Release();
    return true;
}
