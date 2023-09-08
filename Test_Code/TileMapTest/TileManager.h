#pragma once
#include "TStd.h"
#include "GameObject.h"

namespace GameTile
{
	enum TileType
	{
		TILE_FLOOR,
		TILE_WALL,
		TILE_NONE
	};
}


class Debug_Tile :public TObject
{
	using TileType = GameTile::TileType;

public:
	int		 _tileIndex = -1;
	TileType _tileType = TileType::TILE_NONE;
public:
	bool  CreateVertexBuffer()override;
	bool  Create(S_TOBJECT_DESC oDesc)override;
	void  UpdateTile();
public:
	bool    Init() override;
	bool    Frame()override;
	bool    Render()override;
	bool    Release()override;
};

struct Tile
{
	using TileType = GameTile::TileType;

	int		 _tilePosX;
	int		 _tilePosY;
	int		 _tileIndex;
	TileType _tileType;

	Tile()
	{
		_tilePosX = 0;
		_tilePosY = 0;
		_tileIndex = -1;
		_tileType = TileType::TILE_NONE;
	}

};

class TileManager
{
private:
	int								_tileIndexCount = -1;
	int								_tileWidthCount = 0;
	int								_tileHeightCount = 0;
	std::vector<Debug_Tile*>		_debugTileList;
	std::vector<Tile>				_tileList;
private:
	TileManager() {}
public:
	~TileManager();
public:
	static TileManager& GetInstance() { static TileManager ins; return ins; }
public:
	void CreateDebugTileMap(TVector3 mapScale, int widthCount, int heightCount);
	void CreateTileMap(TVector3 mapScale, int widthCount, int heightCount);
public:
	bool SaveTileData();
	bool LoadTileData(std::wstring lPath);
public:
	void DebugTileFrame();
	void DebugTileRender();
private:
	void DebugTileRelease();
};
