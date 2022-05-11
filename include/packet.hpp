#pragma once
#include <enet/enet.h>
#include <stdexcept>
#include <stdint.h>

struct Packet {
	uint8_t type;
	unsigned int length;
	void* data;
};

void sendPacket(ENetPeer *peer, Packet packet, unsigned int packetLength);
