#include "ChatMessage.h"

namespace NixieServer
{
	ChatMessage::ChatMessage(string message)
	{
		m_Message = message;
	}

	ChatMessage::~ChatMessage()
	{
	}

	Packet ChatMessage::ToPacket()
	{
		const int packetSize = (int)sizeof(int32_t) * 2 + (int)m_Message.size() * (int)sizeof(char*);
		char * buffer = new char[packetSize];

		int32_t packetType = htonl((int32_t)PacketType::ChatMessage);
		int32_t messageSize = htonl((u_long)m_Message.size());

		memcpy(buffer, &packetType, sizeof(int32_t));
		memcpy(buffer + sizeof(int32_t), &messageSize, sizeof(int32_t));
		memcpy(buffer + sizeof(int32_t) * 2, m_Message.c_str(), m_Message.size() * sizeof(char));

		Packet packet(buffer, packetSize);

		return packet;
	}
}