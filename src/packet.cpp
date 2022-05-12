#include "packet.hpp"

Packet::Packet(uint8_t type) {
    this->type = type;
    this->length = 0;
    this->data = nullptr;
}

Packet::Packet(uint8_t type, uint32_t length, uint8_t* data) {
    this->type = type;
    this->length = length;
    this->data = data;
}

const uint8_t& Packet::operator[](int index) {
    if (!index) {
        return this->type;
    }
    else if (index < 5) {
        return *((uint8_t*)&this->length)+index-1;
    }
    else if (index < this->length + 5) {
        return this->data[index - 5];
    }
    else {
        throw std::out_of_range("Out of packet range");
    }
}

void Packet::send(ENetPeer* peer) {
    int length = this->length + 5;
    ENetPacket* enetPacket = enet_packet_create(nullptr, length, ENET_PACKET_FLAG_RELIABLE);
    if (!enetPacket)
        return;


    uint8_t* data = new uint8_t[length];

    for (unsigned int i = 0; i < length; i++) {
        data[i] = this->operator[](i);
    }

    memcpy(enetPacket->data, data, length);

    delete[] data;

    if (enet_peer_send(peer, 0, enetPacket) != 0)
        enet_packet_destroy(enetPacket);
}