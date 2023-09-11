#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <io.h>
#include <d3d11.h>
#include "Matrix.h"
extern HWND		g_hWnd;
extern RECT		g_rtClient;
extern float	g_fSecPerFrame;
extern float    g_fGameTime;
extern FMatrix  g_matView;
extern FMatrix  g_matProj;

//////////////////////////////////////////////
//  ¸ÅÅ©·Î
//////////////////////////////////////////////
#define str(x) L#x
#define xstr(x) str(x)
#define randf(x) (x*rand()/(float)RAND_MAX)
#define randf2(x,off) (off+x*rand()/(float)RAND_MAX)
#define randstep(fMin,fMax) (fMin+((float)fMax-(float)fMin)*rand()/(float)RAND_MAX)
#define clamp(x,MinX,MaxX) if (x>MaxX) x=MaxX; else if (x<MinX) x=MinX;

template<class T>
class TSingleton
{
public:
	static T& GetInstance()
	{
		static T theSingle;
		return theSingle;
	}
};