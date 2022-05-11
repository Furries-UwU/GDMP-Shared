#include "packet.hpp"

void sendPacket(ENetPeer *peer, Packet packet) {
    ENetPacket *enetPacket = enet_packet_create(&packet, sizeof(packet), ENET_PACKET_FLAG_RELIABLE);
    if (!enetPacket)
        return;

	//memcpy(enetPacket->data, &packet, sizeof(packet));
	
    if (enet_peer_send(peer, 0, enetPacket) != 0)
        enet_packet_destroy(enetPacket);
}