#pragma once
#pragma once
#ifndef GDNATIVE_H
#define GDNATIVE_H
#endif

#include <core/Godot.hpp>
#include <gen/Node.hpp>
#include <core/Ref.hpp>
#include "Client.h"
#include <gen/Object.hpp>
#include <enet/enet.h>

namespace godot {
	class NetNode : public Node {
		GODOT_CLASS(NetNode, Node);
	public:
		static void _register_methods();

		NetNode();
		~NetNode();

		void _init();
		void _process(float delta);

		void Connect(String host, uint16_t port);
	
	private:
		ENetHost*			enet_host;
	};
}