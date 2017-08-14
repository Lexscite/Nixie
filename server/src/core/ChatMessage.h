#ifndef __CHATMESSAGE_H__
#define __CHATMESSAGE_H__

#pragma once

#include "Packet.h"

class CChatMessage
{
public:
	CChatMessage(std::string message);

	CPacket ToPacket();

public:
	std::string m_message;
};

#endif