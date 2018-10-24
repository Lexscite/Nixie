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

#include "../include/voodoo/connection.h"

namespace voodoo {
Connection::Connection() {}

Connection* Connection::s_singleton;

Connection* Connection::GetSingleton() {
  if (s_singleton == 0) s_singleton = new Connection;

  return s_singleton;
}

bool Connection::Establish(std::string ip, int port) {
  m_AddressSize = sizeof(m_Address);
  WSADATA wsaData;
  WORD dllVersion = MAKEWORD(2, 2);

  if (WSAStartup(dllVersion, &wsaData) != 0) {
    std::cerr << "WSAStartup failed. Error code: " << WSAGetLastError()
              << std::endl;
    return false;
  }

  m_Address.sin_addr.s_addr = inet_addr(ip.c_str());
  m_Address.sin_port = htons(port);
  m_Address.sin_family = AF_INET;

  m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (connect(m_Socket, (SOCKADDR*)&m_Address, m_AddressSize) != 0) {
    std::cerr << "Unable to connect. Error code: " << WSAGetLastError()
              << std::endl;
    return false;
  }

  CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Thread, NULL, NULL, NULL);

  return true;
}

void Connection::Release() {
  bool done = Kill();

  while (!done) done = Kill();
}

bool Connection::Kill() {
  if (closesocket(m_Socket) == SOCKET_ERROR) {
    if (WSAGetLastError() == WSAENOTSOCK) {
      return true;
    }

    std::cerr << "Failed to close the connection. Error code: "
              << WSAGetLastError() << std::endl;
    return false;
  }

  return true;
}

bool Connection::Send(char* data, int totalBytes) {
  int sentBytes = 0;
  while (sentBytes < totalBytes) {
    int result = send(m_Socket, data + sentBytes, totalBytes - sentBytes, NULL);
    if (result == SOCKET_ERROR) {
      std::cerr << "Failed to send data. Error code: " << WSAGetLastError()
                << std::endl;
      return false;
    } else if (result == 0) {
      int iError = WSAGetLastError();
      if (iError == WSAEWOULDBLOCK)
        std::cerr << "Failed to send data. Error: WSAEWOULDBLOCK" << std::endl;
      else
        std::cerr << "Failed to send data. Error code: " << iError << std::endl;

      return false;
    }

    sentBytes += result;
  }

  return true;
}

bool Connection::Recieve(char* data, int totalBytes) {
  int recievedBytes = 0;
  while (recievedBytes < totalBytes) {
    int result =
        recv(m_Socket, data + recievedBytes, totalBytes - recievedBytes, NULL);
    if (result == SOCKET_ERROR) {
      std::cerr << "Failed to send data. Error code: " << WSAGetLastError()
                << std::endl;
      return false;
    } else if (result == 0) {
      int iError = WSAGetLastError();
      if (iError == WSAEWOULDBLOCK)
        std::cerr << "Failed to send data. Error: WSAEWOULDBLOCK" << std::endl;
      else
        std::cerr << "Failed to send data. Error code: " << iError << std::endl;

      return false;
    }

    recievedBytes += result;
  }

  return true;
}

bool Connection::SendInt32(int32_t data) {
  data = htonl(data);
  if (!Send((char*)&data, sizeof(int32_t))) return false;

  return true;
}

bool Connection::GetInt32(int32_t& data) {
  if (!Recieve((char*)&data, sizeof(int32_t))) return false;
  data = ntohl(data);

  return true;
}

bool Connection::SendPacketType(PacketType data) {
  if (!SendInt32((int32_t)data)) return false;

  return true;
}

bool Connection::GetPacketType(PacketType& data) {
  int32_t dataInt;
  if (!GetInt32(dataInt)) return false;
  data = (PacketType)dataInt;

  return true;
}

bool Connection::SendString(std::string& data) {
  int32_t bufferLength = (int32_t)data.size();

  if (!SendInt32(bufferLength)) return false;

  if (!Send((char*)data.c_str(), bufferLength)) return false;

  return true;
}

bool Connection::GetString(std::string& data) {
  int32_t bufferLength;

  if (!GetInt32(bufferLength)) return false;

  char* buffer = new char[bufferLength + 1];
  buffer[bufferLength] = '\0';

  if (!Recieve(buffer, bufferLength)) {
    delete[] buffer;
    return false;
  }

  data = buffer;
  delete[] buffer;

  return true;
}

bool Connection::ProcessPacket(PacketType packetType) {
  switch (packetType) {
    case PacketType::HelloMessage: {
      std::string message;
      if (!GetString(message)) return false;

      std::cout << "Message recieved: " << message << std::endl;
      break;
    }
    default:
      break;
  }

  return true;
}

void Connection::Thread() {
  PacketType packetType;

  while (true) {
    if (!Connection::GetSingleton()->GetPacketType(packetType)) break;

    if (!Connection::GetSingleton()->ProcessPacket(packetType)) break;
  }

  MessageBoxA(NULL, "Lost connection to the server", "Network Error",
              MB_OK | MB_ICONERROR);
  if (Connection::GetSingleton()->Kill())
    std::cout << "Socket to the server was closed successfuly" << std::endl;
  else
    std::cerr << "Socket is't able to be closed" << std::endl;
}
}  // namespace voodoo