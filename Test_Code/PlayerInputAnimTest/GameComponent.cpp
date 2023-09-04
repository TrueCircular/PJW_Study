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
	_isRender = true;
	_isLoad = false;

	return true;
}

E_SpriteType SpriteComponent::GetSpriteType() const
{
	return _sType;
}

void SpriteComponent::SetSpriteType(E_SpriteType sType)
{
	_sType = sType;
}

bool SpriteComponent::GetLoadState() const
{
	return _isLoad;
}

bool SpriteComponent::GetRenderState() const
{
	return _isRender;
}

void SpriteComponent::SetRender(bool render)
{
	_isRender = render;
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
	case SPRITE_TYPE_NOMAL:
	{
		_nomalSprite->Load(desc);
		_isLoad = true;
		break;
	}
	case SPRITE_TYPE_UV:
	{
		_uvSprite->Load(desc);
		_isLoad = true;
		break;
	}
	case SPRITE_TYPE_UVMASK:
	{
		_uvMaskSprite->Load(desc);
		_isLoad = true;
		break;
	}
	case SPRTIE_TYPE_NONE:
		break;
	}
	return true;
}

bool SpriteComponent::Frame()
{
	switch (_sType)
	{
	case SPRITE_TYPE_NOMAL:
	{
		if (_owner != nullptr)
		{
			_nomalSprite->m_vPos = _owner->m_vPos;
			_nomalSprite->Frame();
		}
		break;
	}
	case SPRITE_TYPE_UV:
	{
		if (_owner != nullptr)
		{
			_uvSprite->m_vPos = _owner->m_vPos;
			_uvSprite->Frame();
		}
		break;
	}
	case SPRITE_TYPE_UVMASK:
	{
		if (_owner != nullptr)
		{
			_uvMaskSprite->m_vPos = _owner->m_vPos;
			_uvMaskSprite->Frame();
		}
		break;
	}
	case SPRTIE_TYPE_NONE:
		break;
	}
	return true;
}

bool SpriteComponent::Render()
{
	if (_isRender)
	{
		switch (_sType)
		{
		case SPRITE_TYPE_NOMAL:
		{
			_nomalSprite->SetMatrix(nullptr, &ICore::g_pMainCamera->m_matView, &ICore::g_pMainCamera->m_matOrthoProjection);
			_nomalSprite->Render();
			break;
		}
		case SPRITE_TYPE_UV:
		{
			_uvSprite->SetMatrix(nullptr, &ICore::g_pMainCamera->m_matView, &ICore::g_pMainCamera->m_matOrthoProjection);
			_uvSprite->Render();
			break;
		}
		case SPRITE_TYPE_UVMASK:
		{
			_uvMaskSprite->SetMatrix(nullptr, &ICore::g_pMainCamera->m_matView, &ICore::g_pMainCamera->m_matOrthoProjection);
			_uvMaskSprite->Render();
			break;
		}
		case SPRTIE_TYPE_NONE:
			break;
		}
	}

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

void ImageComponent::HorizontalFlip(bool isFlip)
{
	float temp = fabsf( _image->m_vScale.x);
	if (isFlip)
	{
		_image->m_vScale.x = temp * -1.0f;
		_image->UpdateMatrix();
		_image->UpdateRect();
	}
	else
	{
		_image->m_vScale.x = temp;
		_image->UpdateMatrix();
		_image->UpdateRect();
	}
}

void ImageComponent::VerticalFlip(bool isFlip)
{
	float temp = fabsf(_image->m_vScale.y);
	if (isFlip)
	{
		_image->m_vScale.y = temp * -1.0f;
		_image->UpdateMatrix();
		_image->UpdateRect();
	}
	else
	{
		_image->m_vScale.y = temp;
		_image->UpdateMatrix();
		_image->UpdateRect();
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

bool AnimationControllerComponent::Init()
{
	if (_owner != nullptr)
	{
		if (_SpriteCom = std::dynamic_pointer_cast<SpriteComponent>(_owner->GetComponent(L"Sprite")))
		{
			_sType = _SpriteCom->GetSpriteType();

			_nomalSprite = _SpriteCom->GetNomalSprite();
			_uvSprite = _SpriteCom->GetUVSprite();
			_uvMaskSprite = _SpriteCom->GetUVMaskSprtie();

			_nomalSprite->
		}
	}

	return true;
}
bool AnimationControllerComponent::Frame()
{
	return true;
}
bool AnimationControllerComponent::Render()
{
	return true;
}
bool AnimationControllerComponent::Release()
{
	return true;
}