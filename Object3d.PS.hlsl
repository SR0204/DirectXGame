#include "object3d.hlsli"

struct Material
{
    float4 color;
    int enableLIghting;
    float3 shininess;
};

struct DirectionalLight
{
    float4 color; ///!<ライトの色
    float3 direction; ///!<ライトの向き
    float intensity; ///!<輝度
};

ConstantBuffer<Material> gMaterial : register(b0);
Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);
ConstantBuffer<DirectionalLight> gDirectionalLight : register(b1);
struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};


struct Camera
{
    float3 worldPosition;
};
ConstantBuffer<Camera> gCamera : register(b2);



PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    float4 textureColor = gTexture.Sample(gSampler, input.texcoord);
    output.color = gMaterial.color * textureColor;
    if (gMaterial.enableLIghting != 0)
    { //Lightingする場合
        float NdotL = dot(normalize(input.normal), -gDirectionalLight.direction);
        float cos = pow(NdotL * 0.5f + 0.5f, 2.0f);
        output.color = gMaterial.color * textureColor * gDirectionalLight.color * cos * gDirectionalLight.intensity;
    }
    else
    {
        output.color = gMaterial.color * textureColor;
    }
    
    
    
    float3 toEye = normalize(gCamera.worldPosition - input.worldPosition);  
    float3 reflectLight = reflect(gDirectionalLight.direction, normalize(input.normal));
    float RdotE = dot(reflectLight, toEye);
    float specularPow = pow(saturate(RdotE), gMaterial.shininess);
    
    //拡散反射
    float3 diffuse = gMaterial.color.rgb * textureColor.rgb * gDirectionalLight.color.rgb * cos * gDirectionalLight.intensity;
    //鏡面反射
    float3 specular = gDirectionalLight.color.rgb * gDirectionalLight.intensity * specularPow * float3(1.0f, 1.0f, 1.0f);   
    //拡散反射*鏡面反射
    output.color.rgb = diffuse + specular;
    //アルファは今まで道理
    output.color.a = gMaterial.color.a * textureColor.a;
    
    
    return output;
}