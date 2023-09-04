#include "GameComponent.h"
#include "GameObject.h"
#include "ICoreStd.h"

using std::shared_ptr;
using std::make_shared;

using std::unique_ptr;
using std::make_unique;

bool SpriteComponent::Init()
{
	_uvMaskSprite = make_shared<TSpriteObj>();
	_nomalSprite = make_shared<TSpriteTexture>();
	_uvSprite = make_shared<TSpriteUV>();

	_sType = E_SpriteType::SPRITE_TYPE_NOMAL;
	return true;
}

E_SpriteType SpriteComponent::GetSpriteType()
{
	return _sType;
}

void SpriteComponent::SetSpriteType(E_SpriteType sType)
{
	_sType = sType;
}

std::shared_ptr<TSpriteTexture> SpriteComponent::GetNomalSprite()
{
	return _nomalSprite;
}

std::shared_ptr<TSpriteUV> SpriteComponent::GetUVSprite()
{
	return _uvSprite;
}

std::shared_ptr<TSpriteObj> SpriteComponent::GetUVMaskSprtie()
{
	return _uvMaskSprite;
}

bool SpriteComponent::LoadSpriteImage(TSpriteInfo desc)
{
	switch (_sType)
	{
	case SPRITE_TYPE_MASK:
		break;
	case SPRITE_TYPE_NOMAL:
		break;
	case SPRITE_TYPE_UV:
		break;
	case SPRTIE_TYPE_NONE:
		break;
	}
	return true;
}

bool SpriteComponent::Frame()
{
	switch (_sType)
	{
	case SPRITE_TYPE_MASK:
		break;
	case SPRITE_TYPE_NOMAL:
		break;
	case SPRITE_TYPE_UV:
		break;
	case SPRTIE_TYPE_NONE:
		break;
	}
	return true;
}

bool SpriteComponent::Render()
{
	return true;
}

bool SpriteComponent::Release()
{
	if (_uvMaskSprite) _uvMaskSprite->Release();
	if (_nomalSprite) _nomalSprite->Release();
	if (_uvSprite) _uvSprite->Release();

	return true;
}

void GameComponent::SetOwner(std::shared_ptr<GameObject> owner)
{
	_owner = owner;
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
	_image = make_unique<TPlaneObj>();

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
