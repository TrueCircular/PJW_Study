#include "GameComponent.h"
#include "GameObject.h"
#include "ICoreStd.h"

bool SpriteComponent::Init()
{
    return true;
}

bool SpriteComponent::Frame()
{
    return true;
}

bool SpriteComponent::Render()
{
    return true;
}

bool SpriteComponent::Release()
{
    return true;
}

void GameComponent::SetOwner(std::shared_ptr<GameObject> owner)
{
    _owner = owner;
}

ImageComponent::ImageComponent()
{
    _image = std::make_shared<TPlaneObj>();
}

void ImageComponent::Imageload(S_TOBJECT_DESC desc)
{
    if (_image != nullptr)
    {
        _image->Set(ICore::g_pDevice, ICore::g_pContext);
        _image->Create(desc);
    }
}

bool ImageComponent::Init()
{
    return true;
}

bool ImageComponent::Frame()
{
    if (_owner != nullptr)
    {
        _image->m_vPos = _owner->m_vPos;
    }
    _image->Frame();
    return true;
}

bool ImageComponent::Render()
{
    _image->SetMatrix(nullptr, &ICore::g_pMainCamera->m_matView, &ICore::g_pMainCamera->m_matOrthoProjection);
    _image->Render();
    return true;
}

bool ImageComponent::Release()
{
    _image->Release();
    return true;
}
