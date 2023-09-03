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
	ImageComponent();
	virtual~ImageComponent(){};
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
	std::unique_ptr<TSpriteTexture> _nomalSprite;
	std::unique_ptr<TSpriteUV>		_uvSprite;
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};
