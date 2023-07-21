#pragma once
#include<Windows.h>
#include<iostream>
#include<math.h>
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
    float GetDistance()
    {
        float fDistance = sqrt(x * x + y * y + z * z);
        return fDistance;
    }
    static float GetDistance(TPoint3& p)
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

        m_Center = (m_Point[0] + m_Point[6]) * 0.5f;
        m_Min = m_Point[0];
        m_Max = m_Point[6];
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
    bool	Init();		// �ʱ�ȭ �۾�
    bool	Frame();	// �ǽð� ���
    bool	Render();	// �ǽð� ������, ��ο�
    bool	Release();	// ��ü�� �Ҹ� �۾�
};
#pragma region TimerFun
bool	TTimer::Init()
{
    m_fFramePerSecond = 0.0f;
    m_fGameTimer = 0.0f;
    m_fSecondPerFrame = 0.0f;
    m_dwBeforeTime = timeGetTime();// tick coounter 1000 => 1��
    return true;
}
bool	TTimer::Frame()
{
    DWORD dwCurrentTime = timeGetTime();
    DWORD dwElapseTime = dwCurrentTime - m_dwBeforeTime;
    m_fSecondPerFrame = dwElapseTime / 1000.0f;
    m_fGameTimer += m_fSecondPerFrame;
    m_dwBeforeTime = dwCurrentTime;

    m_fFramePerSecond += m_fSecondPerFrame;
    return true;
}
int   TTimer::GetFPS()
{
    static int iFPS = 0;
    if (m_fFramePerSecond >= 1.0f)
    {
        m_iFPS = iFPS;
        iFPS = 0;
        m_fFramePerSecond -= 1.0f;
    }
    iFPS++;
    return m_iFPS;
}
bool	TTimer::Render()
{
    std::cout << "[FPS]" << GetFPS() << " [GT]" << m_fGameTimer << " [SPF]" << m_fSecondPerFrame << std::endl;
    return true;
}
bool	TTimer::Release()
{
    return true;
}
#pragma endregion
class Util
{
private:
	static Util* _instance;
    TTimer* _timer;
	Util() : _timer(new TTimer()) {}
    ~Util(){}
public:
	static Util* GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new Util();
		}

		return _instance;
	}
    TTimer* GetTimer() { return _timer; }
public:
    inline bool BoxToBox()
    {
        return false;
    }

    inline bool RectToRect(TRect& rt1, TRect& rt2)
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
    inline bool RectToPoint(TRect& rt, TPoint2& p)
    {
        if (rt.m_Min.x <= p.x && rt.m_Max.x >= p.x
            &&
            rt.m_Min.y <= p.y && rt.m_Max.y >= p.y)
        {
            return true;
        }
        return false;

    }
};