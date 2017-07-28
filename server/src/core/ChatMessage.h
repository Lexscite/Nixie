#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include "Packet.h"

namespace NixieServer
{
	class ChatMessage
	{
	public:
		ChatMessage(string message);
		~ChatMessage();
		Packet ToPacket();

		string m_Message;
	};
}

#endif // !CHATMESSAGE_H