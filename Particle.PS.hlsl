
#include"Particle.hlsli"

struct Pixelshaderoutput
{
    float4 color : SV_TARGET0;

};
Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);
struct Material
{
    float4 color;
};
ConstantBuffer<Material> gMaterial : register(b0);

struct Camera
{
    float3 worldPositon;
};
ConstantBuffer<Camera> gCamera : register(b2);

Pixelshaderoutput main(VertexShaderOutput input)
{
    Pixelshaderoutput output;
    
    //float4 transformedUV = mul(float4(input.texcoord, 0.0f, 1.0f), gMaterial.color);
    float4 textureColor = gTexture.Sample(gSampler, input.texcoord);
    output.color = gMaterial.color * textureColor;
    
    float3 toEye = normalize(gCamera.worldPositon - input.worldPosition);
    
	//output.colorのa値が0の時にPixelを棄却
    if (output.color.a == 0.0)
    {
        discard;
    }
    
    return output;
}
