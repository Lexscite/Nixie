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

#ifndef VOODOO_CONNECTION_H_
#define VOODOO_CONNECTION_H_

#include "packet.h"

#include <windows.h>
#include <string>
#include <iostream>

namespace voodoo {
class Connection {
 public:
  bool Establish(std::string ip, int port);
  void Release();
  bool Kill();

  bool SendPacketType(PacketType data);
  bool SendString(std::string &data);

  static Connection *GetSingleton();

 private:
  Connection();

  bool ProcessPacket(PacketType packetType);
  bool Send(char *data, int totalBytes);
  bool Recieve(char *data, int totalBytes);
  bool SendInt32(int32_t data);
  bool GetInt32(int32_t &data);
  bool GetPacketType(PacketType &data);
  bool GetString(std::string &data);

  static void Thread();

 private:
  SOCKET m_Socket;
  SOCKADDR_IN m_Address;
  int m_AddressSize;

  static Connection *s_singleton;
};
}  // namespace voodoo

#endif