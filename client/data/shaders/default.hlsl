cbuffer MatrixBuffer
{
    matrix world_matrix;
    matrix view_matrix;
    matrix projection_matrix;
};

struct VertexInput
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
    float4 color : COLOR;
};

struct VertexOutput
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float4 color : COLOR;
};

VertexOutput DefaultVertexShader(VertexInput input)
{
    VertexOutput output;
    
    input.position.w = 1.0f;

    output.position = mul(input.position, world_matrix);
    output.position = mul(output.position, view_matrix);
    output.position = mul(output.position, projection_matrix);
    
    output.tex = input.tex;
    output.color = input.color;
    
    return output;
}

struct PixelInput
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float4 color : COLOR;
};

Texture2D shaderTexture;
SamplerState SampleType;

float4 DefaultPixelShader(PixelInput input) : SV_TARGET
{
    return shaderTexture.Sample(SampleType, input.tex);
}