#include "packet.hpp"

void sendPacket(ENetPeer *peer, char* data) {
    ENetPacket *enetPacket = enet_packet_create(data, strlen(data)+1, ENET_PACKET_FLAG_RELIABLE);
    if (!enetPacket)
        return;
	
    if (enet_peer_send(peer, 0, enetPacket) != 0)
        enet_packet_destroy(enetPacket);
}