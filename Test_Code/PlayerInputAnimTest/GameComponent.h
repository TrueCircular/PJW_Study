#pragma once
#include "TSpriteObj.h"
#pragma region F_declaration
class GameObject;
#pragma endregion

class GameComponent
{
protected:
	std::shared_ptr<GameObject> _owner = nullptr;
public:
	GameComponent() {}
	virtual ~GameComponent() {}
public:
	void SetOwner(std::shared_ptr<GameObject> owner);
public:
	virtual bool Init() = 0;
	virtual bool Frame() = 0;
	virtual bool Render() = 0;
	virtual bool Release() = 0;
};

class ImageComponent : public GameComponent
{
private:
	std::unique_ptr<TPlaneObj> _image;
public:
	ImageComponent() {}
	~ImageComponent() override {}
public:
	void Imageload(S_TOBJECT_DESC desc);
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};

enum E_SpriteType
{
	SPRITE_TYPE_MASK,
	SPRITE_TYPE_NOMAL,
	SPRITE_TYPE_UV,
	SPRTIE_TYPE_NONE
};
class SpriteComponent : public GameComponent
{
private:
	std::shared_ptr<TSpriteTexture> _nomalSprite;
	std::shared_ptr<TSpriteUV>		_uvSprite;
	std::shared_ptr<TSpriteObj>		_uvMaskSprite;
	E_SpriteType					_sType;
public:
	SpriteComponent() {}
	~SpriteComponent() override {}
public:
	E_SpriteType	GetSpriteType();
	void			SetSpriteType(E_SpriteType sType);

	std::shared_ptr<TSpriteTexture> GetNomalSprite();
	std::shared_ptr<TSpriteUV>		GetUVSprite();
	std::shared_ptr<TSpriteObj>		GetUVMaskSprtie();
public:
	bool LoadSpriteImage(TSpriteInfo desc);
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};

enum E_PlayerAnimationState
{
	P_ANIM_IDLE,
	P_ANIM_FORWARD,
	P_ANIM_BACK,
	P_ANIM_LEFT,
	P_ANIM_RIGHT,
	P_ANIM_NONE
};	
class PlayerAnimControllerComponent : public GameComponent
{
public:
	PlayerAnimControllerComponent() {}
	~PlayerAnimControllerComponent() override {}
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};

enum E_UnitAnimationState
{
	U_ANIM_IDLE,
	U_ANIM_DEATH,
	U_ANIM_ATTACK,
	U_ANIM_SKILL1,
	U_ANIM_SKILL2
};
class UnitAnimControllerComponent : public GameComponent
{
public:
	UnitAnimControllerComponent() {}
	~UnitAnimControllerComponent() override {}
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};