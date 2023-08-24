#pragma once
#include "TObject.h"

class EffectObj : public TObject
{
private:
	EffectObj*						_effect;
	std::vector<std::wstring>		_spAdress;
	std::vector<const TTexture*>	_spriteList;
	bool _isPlay = false;
	bool _isSet = false;
	float indexTime = 0;
	float prevTime = 0;
	int _begin = 0;
	int _current = 0;
	int _last = 0;
public:
	void AddSpriteAddress(std::wstring address, int count);
	void  PlayEffect(bool flag) { _isPlay = flag; }

private:
	void CreateSpriteList();
public:
	bool		 Init(ID3D11Device* device, ID3D11DeviceContext* context, TVector3 pos, TVector3 scale);
	virtual bool CreateVertexBuffer() override;
	virtual bool Frame() override;
	virtual bool Render() override;
};

