struct VS_IN
{
    float3 p : POS;
    float4 c : COLOR0;
    float2 t : TEXTURE;
};

struct VS_OUT
{
    float4 p : SV_POSITION;
    float4 c : COLOR0;
    float2 t : TEXTURE;
};

// 상수버퍼(레지스터 단위로 저장되어야 한다.)
// 레지스터 단위란, float4(x,y,z,w) 
cbuffer cb0 
{
    matrix g_matWorld  : packoffset(c0);// float4x4 // 4개    
    matrix g_matView  : packoffset(c4);
    matrix g_matProj  : packoffset(c8);
};
VS_OUT VS(VS_IN vIn)
{
    VS_OUT vOut = (VS_OUT)0;
    // v * m ->(행->c0,c1,c2,c3)
    // v dot c0 = v.x
    // v dot c1 = v.y
    // v dot c2 = v.z
    // v dot c3 = v.w     
    float4 vWorld = mul(float4(vIn.p, 1.0f), g_matWorld);
    float4 vView = mul(vWorld, g_matView);
    float4 vProj = mul(vView, g_matProj);
    //vOut.p = float4(vIn.p.x, vIn.p.y, vIn.p.z, 1);
    vOut.p = vProj;
    vOut.t = vIn.t;
    vOut.c = vIn.c;

    return vOut;
}

Texture2D g_txDiffuse1 : register(t0);
SamplerState sample0 : register(s0);

struct PS_IN
{
    float4 p : SV_POSITION;
    float4 c : COLOR0;
    float2 t : TEXTURE;
};
float4 PS(PS_IN vIn) : SV_Target
{
    // 사각형 내부에 있는 경우 텍스쳐 샘플링을 통해 텍스쳐 픽셀을 반환합니다.
    return g_txDiffuse1.Sample(sample0, vIn.t);
}
float4 PS_RECT(PS_IN vIn) : SV_Target
{
    return  float4(1.0f, 0.0f, 0.0f, 0.1f);
}