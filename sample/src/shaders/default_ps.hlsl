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

Texture2D shader_texture;
SamplerState sample_type;

cbuffer LightBuffer {
  float4 diffuse_color;
  float4 ambient_color;
  float3 direction;
  float padding;
};

struct PixelInput {
  float4 position : SV_POSITION;
  float2 tex : TEXCOORD0;
  float3 normal : NORMAL;
};

float4 main(PixelInput input) : SV_TARGET {
  float4 texture_color;
  float3 light_dir;
  float light_intensity;
  float4 color;

  texture_color = shader_texture.Sample(sample_type, input.tex);

  color = ambient_color;

  light_dir = -direction;
  light_intensity = saturate(dot(input.normal, light_dir));

  if (light_intensity > 0.0f) {
    color += (diffuse_color * light_intensity);
  }

  color = saturate(color);
  color = color * texture_color;

  return color;
}