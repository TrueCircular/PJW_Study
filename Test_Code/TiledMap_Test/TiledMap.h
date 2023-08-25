#pragma once
#include "TCore.h"
#include "TObject.h"


class Tile
{
	using TileList = std::vector<Tile*>;

private:
	INT64		_index = 0;
	INT64		_depth = 0;
	Tile*		_parent = nullptr;
	TRect		_rect;
	TileList	_child;
public:
	Tile() { _child.resize(8); }
	virtual ~Tile() {
		for (int i = 0; i < _child.size(); i++)
		{
			delete _child[i];
			_child[i] = nullptr;
		}
	}

public:
	//properties
	Tile*	GetParent() { return _parent; }
	void	SetParent(Tile* parent) { _parent = parent; _depth = parent->GetIndex() + 1; }
	TRect&	GetRect() { return _rect; }
	void	SetRect(TRect rect) { _rect = rect; }
	const INT64	GetDepth() { return _depth; }
	const INT64	GetIndex() { return _index; }
};


class TiledMap : public TObject
{
private:

private:

public:
	bool Init();
	bool PreRender();
	bool Render();
	bool PostRender();
	bool Release();
};

