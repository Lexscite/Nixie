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

#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace voodoo {
// Fundamentals
typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned long ulong;
typedef ulong dword;

// STD
typedef std::string string;
typedef std::wstring wstring;

template <class T>
using vector = std::vector<T>;

template <class Key_T, class Value_T>
using map = std::map<Key_T, Value_T>;

template <class Key_T, class Value_T>
using multimap = std::multimap<Key_T, Value_T>;

template <class Key_T, class Value_T>
using unordered_map = std::unordered_map<Key_T, Value_T>;

template <class T>
using shared_ptr = std::shared_ptr<T>;

template <class T>
using unique_ptr = std::unique_ptr<T>;

template <class T>
using EnableSharedFromThis = std::enable_shared_from_this<T>;
}  // namespace voodoo