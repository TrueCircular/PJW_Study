#pragma once
#include "TStd.h"
#include "GameObject.h"

#define MYLOCALPTH_SAVE (const char*) "data/SaveData/"

namespace GameTile
{
	enum TileType
	{
		TILE_FLOOR,
		TILE_WALL,
		TILE_POTAL,
		TILE_NONE
	};
}
struct TIndex
{
	int x, y;
	bool operator == (const TIndex& pos)
	{
		return (x == pos.x && y == pos.y);
	}
	TIndex operator + (const TIndex& right_)
	{
		return{ x + right_.x, y + right_.y };
	}
	TIndex(int fX, int fY)
	{
		x = fX;
		y = fY;
	}
	TIndex()
	{
		x = y = 0;
	}
};


class RectTile :public TObject
{
	using TileType = GameTile::TileType;
public:
	int		 _tileIndex = -1;
	TileType _tileType = TileType::TILE_FLOOR;
public:
	virtual bool  CreateVertexBuffer()override;
	virtual bool  Create(S_TOBJECT_DESC oDesc)override;
	void		  RectInCheck();
public:
	bool    Init() override;
	bool    Frame()override;
	bool    PreRender() override;
	bool    Render()override;
	bool    PostRender() override;
	bool    Release()override;
};

struct PointTile
{
	using TileType = GameTile::TileType;

	int			 _tileIndex;
	TIndex		 _tileCoordinates;
	TileType	 _tileType;
	UINT         _g;
	UINT         _h;
	PointTile*	 _parent;

	PointTile()
	{
		_tileCoordinates.x = 0;
		_tileCoordinates.y = 0;
		_tileIndex = -1;
		_tileType = TileType::TILE_FLOOR;
		_parent = nullptr;
		_g = 0;
		_h = 0;
	}
	PointTile(TIndex coord, PointTile* parent)
	{
		_tileCoordinates = coord;
		_parent = parent;
		_g = _h = 0;
		_tileType = TileType::TILE_FLOOR;
		_tileIndex = -1;
	}
	UINT GetScore()
	{
		return _g + _h;
	}

};

class TileManager
{
	using wifstream = std::wifstream;
	using wofstream = std::wofstream;
	using wstring = std::wstring;
private:
	int								_tileIndexCount = -1;
	TIndex							_coordinateOffset;
	std::vector<RectTile*>			_rectTileList;
	std::vector<PointTile>			_pointTileList;

	wifstream*						_inFile;
	wofstream*						_outFile;
private:
	TileManager() {}
public:
	~TileManager();
public:
	static TileManager& GetInstance() { static TileManager ins; return ins; }
public:
	void CreateRectTileMap(TVector3 mapScale, int widthCount, int heightCount);
	void CreatePointTileMap(TVector3 mapScale, int widthCount, int heightCount);
private:
	void RectTileRelease();
	void PointTileRelease();
private:
	bool LoadData(const wstring& path);
	bool SaveData(const wstring& path);
public:
	bool SaveTileData();
	bool LoadTileData(std::wstring lPath);
public:
	void Frame();
	void Render();
	void Release();
};
