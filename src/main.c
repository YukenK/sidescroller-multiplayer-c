#include <enet/enet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

#define COMPONENT_DEFAULT_SIZE 1024
#define ENTITIY_DEFAULT_SIZE 256
#define PEER_DEFAULT_SIZE 32;

enum ComponentType {
	NO_COMP,
};
enum EntityType {
	NO_PEER_ENTITY,
	PEER_ENTITY,
}
typedef struct {
	ComponentType type;
	void* comp;
	void* deinit;
	int has_deinit_function;
} ComponentContainer;
typedef struct {
	EntityType type;
	uint32_t id;
} Entity;
typedef struct {
	EntityType type;
	uint32_t id;
	uint32_t peer_id;
} PeerEntity;
typedef struct {
	Vector components;
	Vector entities;
	Vector peers;
} GameState;

int init_state(GameState* game_state) {
	init_vector(&game_state->components, COMPONENT_DEFAULT_SIZE, sizeof(ComponentContainer));
	init_vector(&game_state->entities, ENTITY_DEFAULT_SIZE, sizeof(PeerEntity));
	init_vector(&game_state->peers, PEER_DEFAULT_SIZE, sizeof(ENetPeer*));
	for (int i = 0; i < COMPONENT_DEFAULT_SIZE; i++) {
		ComponentContainer* comp = (ComponentContainer*)vec_get(&game_state->components, i);
		comp->comp = NULL;
		comp->deinit = NULL;
		comp->has_deinit_function = 0;
		comp->type = NO_COMP;
	}
	for (int i = 0; i < ENTITY_DEFAULT_SIZE; i++) {
		Entity* entity = (Entity*)vec_get(&game_state->entities, i);
		entity->id = i; // Entity IDs are sequential by default, or set to peer ID. 
		entity->type = NO_PEER_ENTITY;
	}
}
void deinit_state(GameState* game_state, ENetHost* server) {
	for (int i = 0; i < game_state->components->size; i++) {
		ComponentContainer* comp = (ComponentContainer*)vec_get(&game_state->components, i);
		if (comp->has_deinit_function) {
			comp->deinit(comp);
		}
	}
	int peers_left;
	for (peers_left = 0; peers_left < game_state->peers->size; peers_Left++) {
		Peer* peer = *(Peer**)vec_get(&game_state->peers, peers_left);
		enet_peer_disconnect(peer, 0);
		PeerEntity* entity = NULL;
		for (int i = 0; i < game_state->entities->size; i++) {
			entity = (PeerEntity*)vec_get(&game_state->entities, i);
			if (entity->ComponentType == PEER_ENTITY && entity->peer_id == peer->id) {
				entity->ComponentType = NO_PEER;
				entity->peer_id = 0;
				entity->id = 0;
				vec_remove(&game_state->entities, i);
				break;
			}
			entity = NULL;
		}
	}
	ENetEvent event;
	while (enet_host_service(host, &event, 5000)) {
		switch (event.type) {
			case ENET_EVENT_TYPE_RECEIVE:
				enet_packet_destroy(event.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				peers_left--;
			default:
				break;
		}
	}
	if (peers_left) {
		for (int i = 0; i < game_state->peers->size; i++) {
			Peer* peer = *(Peer**)vec_get(&game_state->peers, i);
			enet_peer_reset(peer);
		}
	}
	deinit_vector(&game_state->components);
	deinit_vector(&game_state->entities);
	deinit_vector(&game_state->peers);
}
void handle_packet(GameState* game_state, ENetPeer* peer, ENetPacket* packet) {
	uint16_t packet_type;
	if (packet->dataLength == 0) {
		fprintf(stderr, "Zero length packet received from peer: %s\n", peer->id);
	}
	else if (packet->dataLength == 1) {
		packet_type = get_u8(packet->data, 0);
	} else if (packet->dataLength > 1) {
		uint16_t packet_type = get_u16(packet->data, 0);
	}
}
int main(int argc, char** argv) {
	ENetAddress address;
	ENetHost* server;
	unsigned int port = 5515;
	char* host_address = "0.0.0.0";
	GameState game_state;
	init_state(&game_state);


	if (enet_initialize() != 0) {
		fprintf(stderr, "An error occured while initializing enet.\n");
		return EXIT_FAILURE;
	}
	atexit(enet_deinitialize);

	for (int i = 1; i < argc; i++) {
		char* arg = *(argv + i);
		if (strcmp(arg, "-p") == 0 || strcmp(arg, "--port") == 0) {
			i++;
			port = strtol(*(argv + i), NULL, 10);
			break;
		} else if (strcmp(arg, "--host") == 0) {
			i++;
			host_address = *(argv + i);
			enet_address_set_host(&address, host_address);
			break;
		}
		fprintf(stderr, "Unknown argument found: %s\n", arg);
	}

	printf("Listening on: %s:%d\n", host_address, port);

	int quit = 0;

	ENetEvent event;
	while (!quit) {
		while (enet_host_service(server, &event, 0) > 0) {
			switch (event.type) {
				case ENET_EVENT_TYPE_CONNECT:
					printf("Client joined: %x:%u\n", event.peer->address.host, event.peer->address.port);
					break;
				case ENET_EVENT_TYPE_RECEIVE:
					handle_packet(&game_state, event.peer, event.packet);
					enet_packet_destroy(event.packet);
					break;
				case ENET_EVENT_TYPE_DISCONNECT:
					printf("Client disconnected: %s\n", event.peer->data);
					event.peer->data = NULL;
					break;
				default:
					break;

			}
		}
	}
	
	enet_host_flush(host);

	deinit_state(&game_state, host);

	return 0;
}
