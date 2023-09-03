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
	std::shared_ptr<TPlaneObj> _image;
public:
	ImageComponent();
	~ImageComponent() override {}
public:
	void Imageload(S_TOBJECT_DESC desc);
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};

class SpriteComponent : public GameComponent
{
private:
	std::shared_ptr<TSpriteObj>		_maskSprite;
	std::shared_ptr<TSpriteTexture> _nomalSprite;
	std::shared_ptr<TSpriteUV>		_uvSprite;
public:
	SpriteComponent() {}
	~SpriteComponent() override {}
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};
