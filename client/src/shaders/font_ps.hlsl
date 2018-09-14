Texture2D shader_texture;
SamplerState sample_type;

cbuffer Color
{
	float4 pixel_color;
};

struct PixelInput
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};

float4 main(PixelInput input) : SV_TARGET
{
	float4 color;

	color = shader_texture.Sample(sample_type, input.tex);

	if (color.r == 0.0f)
	{
		color.a = 0.0f;
	}
	else
	{
		color.rgb = pixel_color.rgb;
		color.a = 1.0f;
	}

	return color;
}
