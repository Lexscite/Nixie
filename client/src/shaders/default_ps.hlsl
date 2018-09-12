Texture2D shader_texture;
SamplerState sample_type;

cbuffer LightBuffer
{
    float4 diffuse_color;
    float4 ambient_color;
    float3 direction;
    float padding;
};

struct PixelInput
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
};

float4 main(PixelInput input) : SV_TARGET
{
    float4 texture_color;
    float3 light_dir;
    float light_intensity;
    float4 color;

    texture_color = shader_texture.Sample(sample_type, input.tex);

    color = ambient_color;

    light_dir = -direction;
    light_intensity = saturate(dot(input.normal, light_dir));

	if (light_intensity > 0.0f)
	{
        color += (diffuse_color * light_intensity);
	}

    color = saturate(color);
    color = color * texture_color;

    return color;
}