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
	void VerticalFlip(bool isFlip);
	void HorizontalFlip(bool isFlip);
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};

enum E_SpriteType
{
	SPRITE_TYPE_NOMAL,
	SPRITE_TYPE_UV,
	SPRITE_TYPE_UVMASK,
	SPRTIE_TYPE_NONE
};
class SpriteComponent : public GameComponent
{
private:
	std::shared_ptr<TSpriteTexture> _nomalSprite;
	std::shared_ptr<TSpriteUV>		_uvSprite;
	std::shared_ptr<TSpriteObj>		_uvMaskSprite;

	E_SpriteType					_sType;
	bool							_isRender;
	bool							_isLoad;
public:
	SpriteComponent() {}
	~SpriteComponent() override {}
public:
	E_SpriteType	GetSpriteType() const;
	void			SetSpriteType(E_SpriteType sType);
	bool			GetLoadState() const;
	bool			GetRenderState() const;
	void			SetRender(bool render);

	std::shared_ptr<TSpriteTexture> GetNomalSprite();
	std::shared_ptr<TSpriteUV>		GetUVSprite();
	std::shared_ptr<TSpriteObj>		GetUVMaskSprtie();
public:
	bool LoadSpriteImage(TSpriteInfo desc);
	bool LoadSpriteImage(E_SpriteType sType, TSpriteInfo desc);

	void HorizontalFlip(bool isFlip);
	void VerticalFlip(bool isFlip);
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};

class AnimationControllerComponent : public GameComponent
{
	using NomalSprtieVec = std::vector<const TTexture*>;
	using NomalAnimVec = std::vector<NomalSprtieVec>;

	using UVSpriteVec = std::vector<TUVRect>;
	using UVAnimVec = std::vector<UVSpriteVec>;

	using UVMaskSpriteVec = std::vector<TUVRect>;
	using UVMaskAnimVec = std::vector<UVMaskSpriteVec>;

protected:
	std::shared_ptr<SpriteComponent> _SpriteCom;

	std::shared_ptr<TSpriteTexture>	 _nomalSprite;
	NomalAnimVec					 _nomalAnimation;
	std::shared_ptr<TSpriteUV>		 _uvSprite;
	UVAnimVec						 _uvAnimation;
	std::shared_ptr<TSpriteObj>		 _uvMaskSprite;
	UVMaskAnimVec					 _uvMaskAnimation;

	E_SpriteType					 _sType;
	bool							 _isLoop;
	int								 _AnimSize;
public:
	AnimationControllerComponent(){}
	~AnimationControllerComponent() override {}
public:
	void AddAnimation(int start, int end);
	void SetAnimationState(int state);
	void HorizontalFlip(bool isFlip);
	void VerticalFlip(bool isFlip);
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
class PlayerAnimControllerComponent : public AnimationControllerComponent
{
private:

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
class UnitAnimControllerComponent : public AnimationControllerComponent
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