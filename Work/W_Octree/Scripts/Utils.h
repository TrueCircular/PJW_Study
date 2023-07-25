#pragma once
#include<Windows.h>
#include<iostream>
#include<string>
#include<queue>
#include<vector>
#include<set>
#include<math.h>
#include"MyEnums.h"
#pragma comment(lib, "winmm.lib") //timeGetTime()

#define randstep(fmin, fmax) ((float)fmin+((float)fmax-(float)fmin)* rand() / RAND_MAX)

using namespace std;

struct TPoint2
{
    float x = 0.0f;
    float y = 0.0f;
    bool operator == (TPoint2& p)
    {
        if (fabs(x - p.x) > 0.0001f)
        {
            if (fabs(y - p.y) > 0.0001f)
            {
                return true;
            }
        }
        return false;
    }
    bool operator != (TPoint2& p)
    {
        return !(*this == p);
    }
    TPoint2 operator + (TPoint2& p)
    {
        return TPoint2(x + p.x, y + p.y);
    }
    TPoint2 operator - (TPoint2& p)
    {
        return TPoint2(x - p.x, y - p.y);
    }
    TPoint2 operator * (float fValue)
    {
        return TPoint2(x * fValue, y * fValue);
    }
    TPoint2 operator / (float fValue)
    {
        return TPoint2(x / fValue, y / fValue);
    }
    TPoint2& operator /= (float fValue)
    {
        x = x / fValue;
        y = y / fValue;
        return *this;
    }
    float GetDistance()
    {
        float fDistance = sqrt(x * x + y * y);
        return fDistance;
    }
    static float GetDistance(TPoint2& p)
    {
        float fDistance = sqrt(p.x * p.x + p.y * p.y);
        return fDistance;
    }
    TPoint2() {}
    TPoint2(float fx, float fy) : x(fx), y(fy)
    {
    }
};
struct TPoint3
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    bool operator == (TPoint3& p)
    {
        if (fabs(x - p.x) > 0.0001f)
        {
            if (fabs(y - p.y) > 0.0001f)
            {
                if (fabs(z - p.z) > 0.0001f)
                    return true;
            }
        }
        return false;
    }
    bool operator != (TPoint3& p)
    {
        return !(*this == p);
    }
    TPoint3 operator + (TPoint3& p)
    {
        return TPoint3(x + p.x, y + p.y, z + p.z);
    }
    TPoint3 operator - (TPoint3& p)
    {
        return TPoint3(x - p.x, y - p.y, z - p.z);
    }
    TPoint3 operator * (float fValue)
    {
        return TPoint3(x * fValue, y * fValue, z * fValue);
    }
    TPoint3 operator / (float fValue)
    {
        return TPoint3(x / fValue, y / fValue, z / fValue);
    }
    TPoint3& operator /= (float fValue)
    {
        x = x / fValue;
        y = y / fValue;
        z = z / fValue;
        return *this;
    }
    TPoint3& operator+= (TPoint3& p)
    {
        *this = *this + p;
        return *this;
    }
    float GetDistance()
    {
        float fDistance = sqrt(x * x + y * y + z * z);
        return fDistance;
    }
    static float GetLength(TPoint3& p)
    {
        float fDistance = sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
        return fDistance;
    }
    TPoint3() {}
    TPoint3(float fx, float fy, float fz) : x(fx), y(fy), z(fz)
    {
    }
};
struct TFloat2
{
    union
    {
        struct
        {
            float m_fx;
            float m_fy;
        };
        float v[2];
    };
};
struct TRect : TFloat2
{
    bool  m_bEnable = true;
    float m_fWidth = 0.0f;
    float m_fHeight = 0.0f;
    TPoint2 m_Point[4];
    TPoint2 m_Center;
    TPoint2 m_Half;
    TPoint2 m_Min;
    TPoint2 m_Max;
    TPoint2 v;
    TPoint2 s;
    bool Intersect(TRect& p, TRect& ret)
    {
        return false;
    }
    bool operator == (TRect& p)
    {
        if (fabs(m_fx - p.m_fx) > 0.0001f)
        {
            if (fabs(m_fy - p.m_fy) > 0.0001f)
            {
                if (fabs(m_fWidth - p.m_fWidth) > 0.0001f)
                {
                    if (fabs(m_fHeight - p.m_fHeight) > 0.0001f)
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    bool operator != (TRect& p)
    {
        return !(*this == p);
    }
    TRect operator + (TRect& p)
    {
        TRect rt;
        float fMinX = min(m_fx, p.m_fx);
        float fMinY = min(m_fy, p.m_fy);
        float fMaxX = max(m_Point[2].x, p.m_Point[2].x);
        float fMaxY = max(m_Point[2].y, p.m_Point[2].y);
        TPoint2 pos = { fMinX, fMinY };
        rt.Set(pos, fMaxX - fMinX, fMaxY - fMinY);
        return rt;
    }
    TRect operator - (TRect& p)
    {
        TRect rt;
        rt.m_bEnable = false;
        if (ToRect(p))
        {
            //left, top          right
            //      bottom
            float fx = (m_Min.x > p.m_Min.x) ? m_Min.x : p.m_Min.x;
            float fy = (m_Min.y > p.m_Min.y) ? m_Min.y : p.m_Min.y;
            float right = (m_Max.x < p.m_Max.x) ? m_Max.x : p.m_Max.x;
            float bottom = (m_Max.y < p.m_Max.y) ? m_Max.y : p.m_Max.y;
            rt.Set(fx, fy, right - fx, bottom - fy);
            rt.m_bEnable = true;
        }
        return rt;
    }
    TRect operator - (TPoint2& p)
    {
        m_fx -= p.x;
        m_fy -= p.y;
        return TRect(m_fx, m_fy, m_fWidth, m_fHeight);
    }
    TRect operator * (float fValue)
    {
        if (fValue <= 0.0f)
        {
            return *this;
        }
        m_fWidth *= fValue;
        m_fHeight *= fValue;
        return TRect(m_fx, m_fy, m_fWidth, m_fHeight);
    }
    TRect operator / (float fValue)
    {
        if (fValue <= 0.0f)
        {
            return *this;
        }
        m_fWidth /= fValue;
        m_fHeight /= fValue;
        return TRect(m_fx, m_fy, m_fWidth, m_fHeight);
    }
    void Set(TPoint2 p)
    {
        v = { p.x, p.y };
        s = { m_fWidth, m_fHeight };
        m_fx = m_fx;
        m_fy = m_fy;
        Set(m_fWidth, m_fHeight);
    }
    void Set(float fw, float fh)
    {
        m_fWidth = fw;
        m_fHeight = fh;
        m_Half = { m_fWidth * 0.5f,m_fHeight * 0.5f };
        m_Point[0] = { m_fx, m_fy };
        m_Point[1] = { m_fx + m_fWidth, m_fy };
        m_Point[2] = { m_fx + m_fWidth, m_fy + m_fHeight };
        m_Point[3] = { m_fx, m_fy + m_fHeight };
        m_Center = (m_Point[0] + m_Point[2]) * 0.5f;
        m_Min = m_Point[0];
        m_Max = m_Point[2];
    }
    void Set(TPoint2 p, float fw, float fh)
    {
        v = { p.x, p.y };
        s = { fw, fh };
        m_fx = p.x;
        m_fy = p.y;
        Set(fw, fh);
    }
    void Set(float fx, float fy, float fw, float fh)
    {
        v = { fx, fy };
        s = { fw, fh };

        m_fx = fx;
        m_fy = fy;
        Set(fw, fh);
    }

    bool ToRect(TRect& rt)
    {
        TRect sum = (*this) + rt;
        float fX = m_fWidth + rt.m_fWidth;
        float fY = m_fHeight + rt.m_fHeight;
        if (sum.m_fWidth <= fX)
        {
            if (sum.m_fHeight <= fY)
            {
                return true;
            }
        }
        return false;
    }
    bool ToPoint(TPoint2& p)
    {
        if (m_Min.x <= p.x && m_Max.x >= p.x &&
            m_Min.y <= p.y && m_Max.y >= p.y)
        {
            return true;
        }
        return false;
    }
    TRect() : m_bEnable(true) {}


    TRect(float fx, float fy, float fw, float fh)
    {
        m_bEnable = true;
        Set(fx, fy, fw, fh);
    }
};
struct TFloat3
{
    union
    {
        struct
        {
            float m_fx;
            float m_fy;
            float m_fz;
        };
        float v[3];
    };
};
struct TBox : public TFloat3
{
    bool  m_bEnable = true;
    float m_fWidth = 0.0f;
    float m_fHeight = 0.0f;
    float m_fDepth = 0.0f;
    TPoint3 m_Point[8];
    TPoint3 m_Center;
    TPoint3 m_Half;
    TPoint3 m_Min;
    TPoint3 m_Max;
    TPoint3 v;
    TPoint3 s;

    bool operator == (TBox& box)
    {
        if (fabs(m_fx - box.m_fx) > 0.0001f)
        {
            if (fabs(m_fy - box.m_fy) > 0.0001f)
            {
                if (fabs(m_fz - box.m_fz) > 0.0001f)
                {
                    if (fabs(m_fWidth - box.m_fWidth) > 0.0001f)
                    {
                        if (fabs(m_fHeight - box.m_fHeight) > 0.0001f)
                        {
                            if (fabs(m_fDepth - box.m_fDepth) > 0.0001f)
                            {
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }
    bool operator != (TBox& box)
    {
        return !(*this == box);
    }
    TBox operator + (TBox& p)
    {
        TBox temp;

        float minX = min(m_fx, p.m_fx);
        float minY = min(m_fy, p.m_fy);
        float minZ = min(m_fz, p.m_fz);
        float maxX = max(m_Max.x, p.m_Max.x);
        float maxY = max(m_Max.y, p.m_Max.y);
        float maxZ = max(m_Max.z, p.m_Max.z);

        TPoint3 ptemp = { minX,minY,minZ };
        TPoint3 ptemp2 = { maxX - minX, maxY - minY, maxZ - minZ };

        temp.Set(ptemp, ptemp2);
        return temp;
    }

    void Set(float fSizeX, float fSizeY, float fSizeZ)
    {
        m_fWidth = fSizeX;
        m_fHeight = fSizeY;
        m_fDepth = fSizeZ;
        m_Half = { m_fWidth * 0.5f,m_fHeight * 0.5f, m_fDepth * 0.5f };

        m_Point[0] = { m_fx, m_fy, m_fz };
        m_Point[1] = { m_fx + m_fWidth, m_fy, m_fz };
        m_Point[2] = { m_fx + m_fWidth, m_fy + m_fHeight, m_fz };
        m_Point[3] = { m_fx, m_fy + m_fHeight, m_fz };

        m_Point[4] = { m_fx, m_fy, m_fz + fSizeZ };
        m_Point[5] = { m_fx + m_fWidth, m_fy, m_fz + fSizeZ };
        m_Point[6] = { m_fx + m_fWidth, m_fy + m_fHeight, m_fz + fSizeZ };
        m_Point[7] = { m_fx, m_fy + m_fHeight, m_fz + fSizeZ };

        m_Min = m_Point[0];
        m_Max = m_Point[6];
        m_Center = (m_Min + m_Max) * 0.5f;
    }
    void Set(TPoint3 p, TPoint3 surface)
    {
        v = { p.x, p.y, p.z };
        s = { surface.x, surface.y, surface.z };
        m_fx = p.x;
        m_fy = p.y;
        m_fz = p.z;
        Set(surface.x, surface.y, surface.z);
    }
    void Set(float fx, float fy, float fz, float fw, float fh, float fd)
    {
        v = { fx, fy, fz };
        s = { fw, fh, fd };

        m_fx = fx;
        m_fy = fy;
        m_fz = fz;
        Set(fw, fh, fd);
    }

    TBox() : m_bEnable(true) {}

    TBox(float fx, float fy, float fz,
        float fw, float fh, float fd)
    {
        m_bEnable = true;
        Set(fx, fy, fz, fw, fh, fz);
    }
    TBox(TPoint3 pos, TPoint3 surface)
    {
        m_bEnable = true;
        Set(pos, surface);
    }
};
class TTimer
{
public:
    float	m_fGameTimer;
    float   m_fSecondPerFrame;
    DWORD	m_dwBeforeTime;
    float   m_fFramePerSecond;
    int     m_iFPS;
public:
    int		GetFPS();
public:
    bool	Init();		// 초기화 작업
    bool	Frame();	// 실시간 계산
    bool	Render();	// 실시간 랜더링, 드로우
    bool	Release();	// 객체의 소멸 작업
};
class Util
{
private:
    static Util*    _instance;
    TTimer* _timer;
    Util() : _timer(new TTimer()) {}
    ~Util() { delete _timer; }

public:
    Util(Util const&) = delete;
    Util& operator=(Util const&) = delete;

	static Util* GetInstance()
	{
        if (_instance == nullptr)
            _instance = new Util();

		return _instance;
	}
    TTimer* GetTimer() { if (_timer == nullptr) _timer = new TTimer(); return _timer; }
public:
    bool BoxToBox(TBox& bx1, TBox& bx2)
    {
        TBox temp = bx1 + bx2;
        float wi = bx1.m_fWidth + bx2.m_fWidth;
        float he = bx1.m_fHeight + bx2.m_fHeight;
        float de = bx1.m_fDepth + bx2.m_fDepth;

        if (temp.m_fWidth <= wi)
        {
            if (temp.m_fHeight <= he)
            {
                if (temp.m_fDepth <= de)
                {
                    return true;
                }
            }
        }
        return false;
    }
    bool RectToRect(TRect& rt1, TRect& rt2)
    {
        TRect sum = rt1 + rt2;
        float fX = rt1.m_fWidth + rt2.m_fWidth;
        float fY = rt1.m_fHeight + rt2.m_fHeight;
        if (sum.m_fWidth <= fX)
        {
            if (sum.m_fHeight <= fY)
            {
                return true;
            }
        }
        return false;
    }
    bool RectToPoint(TRect& rt, TPoint2& p)
    {
        if (rt.m_Min.x <= p.x && rt.m_Max.x >= p.x
            &&
            rt.m_Min.y <= p.y && rt.m_Max.y >= p.y)
        {
            return true;
        }
        return false;
    }

    TPoint3 Normalize(TPoint3& vec3)
    {
        float xtemp = vec3.x / sqrt(vec3.x * vec3.x + vec3.y * vec3.y + vec3.z * vec3.z);
        float ytemp = vec3.y / sqrt(vec3.x * vec3.x + vec3.y * vec3.y + vec3.z * vec3.z);
        float ztemp = vec3.z / sqrt(vec3.x * vec3.x + vec3.y * vec3.y + vec3.z * vec3.z);

        TPoint3 nomal = { xtemp, ytemp, ztemp };

        return nomal;
    }
    float GetLength(TPoint3& vec3)
    {
        float temp = sqrt(vec3.x * vec3.x + vec3.y * vec3.y + vec3.z * vec3.z);
        return temp;
    }
};

