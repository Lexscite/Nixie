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

#ifndef VOODOO_STD_MAPPINGS_H_
#define VOODOO_STD_MAPPINGS_H_

#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace voodoo {
// Fundamentals
typedef unsigned int uint;
typedef unsigned long ulong;
typedef long long llong;
typedef unsigned long long ullong;
typedef long double ldouble;
typedef unsigned char byte;
typedef ulong dword;

// STD
// Types
typedef std::string string;
typedef std::wstring wstring;

template <class T>
using vector = std::vector<T>;

template <class T1, class T2>
using pair = std::pair<T1, T2>;

template <class Key_T, class Value_T>
using map = std::map<Key_T, Value_T>;

template <class Key_T, class Value_T>
using multimap = std::multimap<Key_T, Value_T>;

template <class Key_T, class Value_T>
using unordered_map = std::unordered_map<Key_T, Value_T>;

template <class T>
using sptr = std::shared_ptr<T>;

template <class T>
using uptr = std::unique_ptr<T>;

template <class T>
using enable_shared_from_this = std::enable_shared_from_this<T>;

// Smart pointer casting
template <class T1, class T2>
inline sptr<T1> s_cast(const sptr<T2>& other) noexcept {
  return std::static_pointer_cast<T1>(other);
}

template <class T1, class T2>
inline sptr<T1> c_cast(const sptr<T2>& other) noexcept {
  return std::const_pointer_cast<T1>(other);
}

template <class T1, class T2>
inline sptr<T1> r_cast(const sptr<T2>& other) noexcept {
  return std::reinterpret_pointer_cast<T1>(other);
}

template <class T1, class T2>
inline sptr<T1> d_cast(const sptr<T2>& other) noexcept {
  return std::dynamic_pointer_cast<T1>(other);
}

// SFINAE
template <bool test, class T = void>
using enable_if = std::enable_if<test, T>;

template <bool test, class T = void>
using enable_if_t = typename enable_if<test, T>::type;

template <class Base, class Derived>
using is_base_of = std::is_base_of<Base, Derived>;

template <class Base, class Derived>
constexpr bool is_base_of_v = is_base_of<Base, Derived>::value;
}  // namespace voodoo

#endif  // VOODOO_STD_MAPPINGS_H_