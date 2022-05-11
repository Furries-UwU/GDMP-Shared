#include "packet.hpp"

Packet::Packet(uint8_t type, uint8_t* data, unsigned int length) {
	this->type = type;
	this->data = data;
	this->length = length + 1;
}

const uint8_t& Packet::operator[](int index) const {
    if (!index) {
        return this->type;
    }
    else if (index < this->length) {
		return this->data[index - 1];
    }
    else {
        throw std::range_error("Out of packet range");
    }
}

void sendPacket(ENetPeer* peer, Packet packet, unsigned int packetLength) {
    ENetPacket* enetPacket = enet_packet_create(&packet, packetLength, ENET_PACKET_FLAG_RELIABLE);
    if (!enetPacket)
        return;

    uint8_t* data = new uint8_t[packet.length];

    for (unsigned int i = 0; i < packet.length; i++) {
        data[i] = packet[i];
    }

	memcpy(enetPacket->data, data, packet.length);

    delete[] data;

    if (enet_peer_send(peer, 0, enetPacket) != 0)
        enet_packet_destroy(enetPacket);
}