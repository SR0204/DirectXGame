#include"Object3d.hlsli"

struct PixelShaderOutput
{
    float32_t4 color : SV_TARGET0;
};

Texture2D<float32_t4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct Material
{
    float32_t4 color;
};
ConstantBuffer<Material> gMaterial : register(b0);


struct DirectionalLight
{
    
    float32_t4 color;//ライトの色
    float32_t3 direction;//ライトの向き
    float intensity;//光度
};
ConstantBuffer<DirectionalLight> gDirectionalLight : register(b1);

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    output.color = gMaterial.color;
    float32_t4 textureColor = gTexture.Sample(gSampler, input.texcoord);
    
    
    //if (gMaterial.enableLightting != 0)
    //{
        
    //    float cos = saturate(dot(normalize(input.normal), -gDirectionalLight.direction));
    //    output.color = gMaterial.color * textureColor * gDirectionalLight.color * cos * gDirectionalLight.intensity;
        
    //}
    
    
    output.color.rgb = gMaterial.color.rgb * textureColor.rgb * gDirectionalLight.color.rgb * cos * gDirectionalLight.intensity;
    output.color.a = gMaterial.color.a * textureColor.a;
    
    
    //output.color = gMaterial.color * textureColor;
    
    return output;
}


