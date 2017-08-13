#ifndef __CHATMESSAGE_H__
#define __CHATMESSAGE_H__

#include "Packet.h"

class CChatMessage
{
public:
	CChatMessage(string message);
	~CChatMessage();
	CPacket ToPacket();

public:
	string m_message;
};

#endif // !CHATMESSAGE_H