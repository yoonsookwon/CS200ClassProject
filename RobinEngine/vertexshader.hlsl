cbuffer mycBuffer : register(b0) //second를 만들고 싶으면 b1이라고 한다
{
    //row_major & column_major
    float4x4 mat;
};

struct VS_INPUT 
{
    float3 inPos : POSITION;
    float2 inTexCoord : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 outPosition : SV_POSITION;
    float2 outTexCoord : TEXCOORD;
};

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;

    output.outPosition = mul(float4(input.inPos, 1.0f), mat);
    output.outTexCoord = input.inTexCoord;
    return output;
}
