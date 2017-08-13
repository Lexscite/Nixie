#include "ChatMessage.h"

CChatMessage::CChatMessage(string message)
{
	m_message = message;
}

CChatMessage::~CChatMessage()
{
}

CPacket CChatMessage::ToPacket()
{
	const int packetSize = (int)sizeof(int32_t) * 2 + (int)m_message.size() * (int)sizeof(char*);
	char * buffer = new char[packetSize];

	int32_t packetType = htonl((int32_t)PacketType::ChatMessage);
	int32_t messageSize = htonl((u_long)m_message.size());

	memcpy(buffer, &packetType, sizeof(int32_t));
	memcpy(buffer + sizeof(int32_t), &messageSize, sizeof(int32_t));
	memcpy(buffer + sizeof(int32_t) * 2, m_message.c_str(), m_message.size() * sizeof(char));

	CPacket packet(buffer, packetSize);

	return packet;
}