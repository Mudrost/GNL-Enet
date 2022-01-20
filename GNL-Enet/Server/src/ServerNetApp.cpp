
#include "ServerNetApp.h"
#include <Packet.h>
bool ServerNetApp::Start(uint16_t port) {


	if (enet_initialize() != 0)
	{
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		return EXIT_FAILURE;
	}

	// This runs inside a thread!!
	m_enet_addr.host = ENET_HOST_ANY;
	m_enet_addr.port = 3223;
	// This doesn't need to be free'd automatically, will be destroyed at the end.
	m_enet_host = enet_host_create(&m_enet_addr, 32, 2, 0, 0);

	if (m_enet_host == NULL)
	{
		fprintf(stderr,
			"An error occurred while trying to create an ENet server host.\n");
		exit(EXIT_FAILURE);
	}
	
}

void ServerNetApp::Run() {
	ENetEvent event;
	OutboundPkt out;
	int enet_return = 0;

	while (enet_return >= 0) {
		enet_return = enet_host_service(m_enet_host, &event, 0);
		if (enet_return > 0) {
			switch (event.type) {
				case ENET_EVENT_TYPE_CONNECT:
					m_mux.lock();
					m_peers.insert(std::make_pair(event.peer->connectID, event.peer));
					m_mux.unlock();
					break;
				case ENET_EVENT_TYPE_DISCONNECT:
					m_mux.lock();
					m_peers.erase(event.peer->connectID);
					m_mux.unlock();
					break;
				case ENET_EVENT_TYPE_RECEIVE:
					if(!m_inbound_queue.try_enqueue(event)) printf("couldnt enqueue");
					break;
			}
		}
		
		if (m_outbound_queue.try_dequeue(out)) {
			enet_peer_send(out.peer, 0, out.packet);
			// There are still outbound packets...
			if (m_peers.find(out.peer->connectID) != m_peers.end()); // Is this needed?
				
		}
	}

	enet_host_destroy(m_enet_host);
	enet_deinitialize();
}

