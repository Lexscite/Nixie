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
    float3 normal : NORMAL;
};

struct VertexOutput
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
};

VertexOutput main(VertexInput input)
{
    VertexOutput output;
    
    input.position.w = 1.0f;

    output.position = mul(input.position, world_matrix);
    output.position = mul(output.position, view_matrix);
    output.position = mul(output.position, projection_matrix);
    
    output.tex = input.tex;

    output.normal = mul(input.normal, (float3x3)world_matrix);
    output.normal = normalize(output.normal);
    
    return output;
}