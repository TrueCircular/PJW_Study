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

void SpriteComponent::VerticalFlip(bool isFlip)
{
	if (_owner != nullptr)
	{
		float temp = fabsf(_owner->m_vScale.y);
		if (isFlip)
		{
			_owner->m_vScale.y = temp * -1.0f;
		}
		else
		{
			_owner->m_vScale.y = temp;
		}
	}
}

void SpriteComponent::HorizontalFlip(bool isFlip)
{
	if (_owner != nullptr)
	{
		float temp = fabsf(_owner->m_vScale.x);
		if (isFlip)
		{
			_owner->m_vScale.x = temp * -1.0f;
		}
		else
		{
			_owner->m_vScale.x = temp;
		}
	}
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
			_nomalSprite->m_vScale = _owner->m_vScale;
			_nomalSprite->m_vRotation = _owner->m_vRotation;
			_nomalSprite->Frame();
		}
		break;
	}
	case SPRITE_TYPE_UV:
	{
		if (_owner != nullptr)
		{
			_uvSprite->m_vPos = _owner->m_vPos;
			_uvSprite->m_vScale = _owner->m_vScale;
			_uvSprite->m_vRotation = _owner->m_vRotation;
			_uvSprite->Frame();
		}
		break;
	}
	case SPRITE_TYPE_UVMASK:
	{
		if (_owner != nullptr)
		{
			_uvMaskSprite->m_vPos = _owner->m_vPos;
			_uvMaskSprite->m_vScale = _owner->m_vScale;
			_uvMaskSprite->m_vRotation = _owner->m_vRotation;

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
	if (_owner != nullptr)
	{
		float temp = fabsf(_owner->m_vScale.x);
		if (isFlip)
		{
			_owner->m_vScale.x = temp * -1.0f;
		}
		else
		{
			_owner->m_vScale.x = temp;
		}
	}
}

void ImageComponent::VerticalFlip(bool isFlip)
{
	if (_owner != nullptr)
	{
		float temp = fabsf(_owner->m_vScale.y);
		if (isFlip)
		{
			_owner->m_vScale.y = temp * -1.0f;
		}
		else
		{
			_owner->m_vScale.y = temp;
		}
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
		_image->m_vScale = _owner->m_vScale;
		_image->m_vRotation = _owner->m_vRotation;
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

void AnimationControllerComponent::AddAnimation(int start, int end)
{
	switch (_sType)
	{
	case E_SpriteType::SPRITE_TYPE_NOMAL:
	{
		if (_nomalSprite != nullptr && _SpriteCom->GetLoadState())
		{
			NomalSprtieVec temp(_nomalSprite->m_pTexList);
			NomalSprtieVec temp2;

			for (int i = start; i <= end; i++)
			{
				temp2.push_back(temp[i]);
			}

			_nomalAnimation.push_back(temp2);
		}
		break;
	}
	case E_SpriteType::SPRITE_TYPE_UV:
	{
		if (_uvSprite != nullptr && _SpriteCom->GetLoadState())
		{
			UVSpriteVec temp(_uvSprite->m_pUVList);
			UVSpriteVec temp2;

			for (int i = start; i <= end; i++)
			{
				temp2.push_back(temp[i]);
			}

			_uvAnimation.push_back(temp2);
		}
		break;
	}
	case E_SpriteType::SPRITE_TYPE_UVMASK:
	{
		if (_uvMaskSprite != nullptr && _SpriteCom->GetLoadState())
		{
			UVMaskSpriteVec temp(_uvMaskSprite->m_pUVList);
			UVMaskSpriteVec temp2;

			for (int i = start; i <= end; i++)
			{
				temp2.push_back(temp[i]);
			}

			_uvMaskAnimation.push_back(temp2);
		}
		break;
	}
	default:
		break;
	}
}

void AnimationControllerComponent::SetAnimationState(int state)
{
	switch (_sType)
	{
	case E_SpriteType::SPRITE_TYPE_NOMAL:
	{
		if (_nomalAnimation.size() > 0)
		{
			if (_nomalSprite != nullptr)
			{
				_nomalSprite->m_pTexList = _nomalAnimation[state];
				_nomalSprite->m_iCurrentAnimIndex = 0;
			}
		}
		break;
	}
	case E_SpriteType::SPRITE_TYPE_UV:
	{
		if (_uvAnimation.size() > 0)
		{
			if (_uvSprite != nullptr)
			{
				_uvSprite->m_pUVList = _uvAnimation[state];
				_uvSprite->m_iCurrentAnimIndex = 0;
			}
		}
		break;
	}
	case E_SpriteType::SPRITE_TYPE_UVMASK:
	{
		if (_uvMaskAnimation.size() > 0)
		{
			if (_uvMaskSprite != nullptr)
			{
				_uvMaskSprite->m_pUVList = _uvMaskAnimation[state];
				_uvMaskSprite->m_iCurrentAnimIndex = 0;
			}
		}
		break;
	}
	default:
		break;
	}
}

void AnimationControllerComponent::HorizontalFlip(bool isFlip)
{
	if (_owner != nullptr)
	{
		float temp = fabsf(_owner->m_vScale.x);
		if (isFlip)
		{
			_owner->m_vScale.x = temp * -1.0f;
		}
		else
		{
			_owner->m_vScale.x = temp;
		}
	}
}

void AnimationControllerComponent::VerticalFlip(bool isFlip)
{
	if (_owner != nullptr)
	{
		float temp = fabsf(_owner->m_vScale.y);
		if (isFlip)
		{
			_owner->m_vScale.y = temp * -1.0f;
		}
		else
		{
			_owner->m_vScale.y = temp;
		}
	}
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