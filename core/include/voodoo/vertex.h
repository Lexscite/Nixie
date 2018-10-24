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

#ifndef VOODOO_VERTEX_H_
#define VOODOO_VERTEX_H_

#include "math.h"

namespace voodoo {
// Potition
struct vertex_p {
  vertex_p() = default;

  vertex_p(const float3& position)
    : position(position) {}

  float3 position;
};

// Position, color
struct vertex_pc : public vertex_p {
  vertex_pc() = default;

  vertex_pc(const float3& position,
    const float4& color)
    : vertex_p(position),
    color(color) {}

  float4 color;
};

// Position, texture
struct vertex_pt : public vertex_p {
  vertex_pt() = default;

  vertex_pt(const float3& position,
    const float2& texture)
    : vertex_p(position),
    texture(texture) {}

  float2 texture;
};

// Position, color, texture
struct vertex_pct : public vertex_pc {
  vertex_pct() = default;

  vertex_pct(const float3& position,
    const float4& color,
    const float2& texture)
    : vertex_pc(position, color),
    texture(texture) {}

  float2 texture;
};

// Position, texture, normal
struct vertex_ptn : public vertex_pt {
  vertex_ptn() = default;

  vertex_ptn(const float3& position,
    const float2& texture,
    const float3& normal)
    : vertex_pt(position, texture),
    normal(normal) {}

  float3 normal;
};

// Position, color, texture, normal
struct vertex_pctn : public vertex_pct {
  vertex_pctn() = default;

  vertex_pctn(const float3& position,
    const float4& color,
    const float2& texture,
    const float3& normal)
    : vertex_pct(position, color, texture),
    normal(normal) {}

  float3 normal;
};

// Position, texture, normal, tangent
struct vertex_ptnt : public vertex_ptn {
  vertex_ptnt() = default;

  vertex_ptnt(const float3& position,
    const float2& texture,
    const float3& normal,
    const float4& tangent)
    : vertex_ptn(position, texture, normal),
    tangent(tangent) {}

  float4 tangent;
};

// Position, color, texture, normal, tangent
struct vertex_pctnt : public vertex_pctn {
  vertex_pctnt() = default;

  vertex_pctnt(const float3& position,
    const float4& color,
    const float2& texture,
    const float3& normal,
    const float4& tangent)
    : vertex_pctn(position, color, texture, normal),
    tangent(tangent) {}

  float4 tangent;
};
}  // namespace voodoo

#endif