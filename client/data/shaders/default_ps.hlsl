Texture2D shaderTexture;
SamplerState SampleType;

cbuffer LightBuffer
{
    float4 diffuse_color;
    float3 direction;
    float padding;
};

struct PixelInput
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
};

float4 DefaultPixelShader(PixelInput input) : SV_TARGET
{
    float4 textureColor;
    float3 lightDir;
    float lightIntensity;
    float4 color;

    textureColor = shaderTexture.Sample(SampleType, input.tex);

    lightDir = -direction;
    lightIntensity = saturate(dot(input.normal, lightDir));
    color = saturate(diffuse_color * lightIntensity);
    color = color * textureColor;

    return color;
}