// This file is part of Voodoo Engine.
//
// Voodoo Engine is free software : you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Voodoo Engine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Voodoo Engine.  If not, see <https://www.gnu.org/licenses/>.

cbuffer MatrixBuffer {
  matrix world_matrix;
  matrix view_matrix;
  matrix projection_matrix;
};

struct VertexInput {
  float4 position : POSITION;
  float2 tex : TEXCOORD0;
  float3 normal : NORMAL;
};

struct VertexOutput {
  float4 position : SV_POSITION;
  float2 tex : TEXCOORD0;
  float3 normal : NORMAL;
};

VertexOutput main(VertexInput input) {
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