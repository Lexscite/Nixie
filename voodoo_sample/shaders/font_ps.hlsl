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
// along with Foobar.  If not, see <https://www.gnu.org/licenses/>.

Texture2D shader_texture;
SamplerState sample_type;

cbuffer Color { float4 pixel_color; };

struct PixelInput {
  float4 position : SV_POSITION;
  float2 tex : TEXCOORD0;
};

float4 main(PixelInput input) : SV_TARGET {
  float4 color;

  color = shader_texture.Sample(sample_type, input.tex);

  if (color.r == 0.0f) {
    color.a = 0.0f;
  } else {
    color.rgb = pixel_color.rgb;
    color.a = 1.0f;
  }

  return color;
}