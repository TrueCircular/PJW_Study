#include"Utils.h"
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
    if (this != nullptr)
    {
        delete this;
    }
    return true;
}