// CLIENT
// first byte of stream determines packet type
// 1. CON-REQUEST (0) <-- unique player identifier

// PER FRAME
// 1. SEND-DATA (server sends to all other clients)

typedef struct {
  UDPsocket socket;
  u32 timeout;
  int id;
} PlayerData;

int create_player_data(PlayerData* player_data, u32 timeout, int id)
{
  player_data->socket = SDLNet_UDP_Open(0);
  if (player_data->socket == NULL) {
    GAME_LOG_WARN("Unable to create client udp socket. Status %s", SDLNet_GetError());
    return FAILURE;
  }
  player_data->timeout = timeout;
  player_data->id = id;
  
  return SUCCESS;
}

void destroy_player_data(PlayerData* player_data)
{
  SDLNet_UDP_Close(player_data->socket);
  player_data->socket = NULL;
}

int main(int argc, char* argv[argc + 1])
{
	SDLNet_Init();
	int current_player_id = 0;
	int players_connected = 0;
	SDL_Event event = {0};

	IPaddress ip = {0};
	// NULL to signify server
	if (SDLNet_ResolveHost(&ip, NULL, 1234) < 0) {
		GAME_LOG_WARN("Unable to resolve ip %s", SDLNet_GetError());		
	}
	UDPsocket server_socket = SDLNet_UDP_Open(&ip);

	PlayerData* socket_vector = NULL;
	BUF_PUSH(socket_vector, (PlayerData)({...}));

	bool server_is_running = true;
	char data_buffer[1400] = {0};
	SDLNet_SocketSet sockets = {0}; // allow to check if waiting to prevent blocking on recv() 

	while (running) {
		// handle new connections
		UDPsocket tmp_socket = SDLNet_UDP_Accept(server_socket); // on new connection
		if (players_connected < 30) {
			/// getticks() - 5000 to handle timeout 
			BUF_PUSH(socket_vector, (PlayerData){tmp_socket, SDL_GetTicks(), current_player_id});
			++players_connected;
			// 0 signifying connection recieved (have protocol handle success and failure for each option)
			// \n necessary to identify message termination
			sprintf(data_buffer, "0 %d\n", current_player_id);
			++current_player_id;
			SDLNet_UDP_Send(tmp_socket, data_buffer, strlen(data_buffer) + 1); 
		}
		// check for new data	
		while (SDLNet_CheckSockets(sockets, 0) > 0) {
			for (size_t data_index = 0; data_index < BUF_LEN(socket_vector); ++data_index) {
				socket_vector.payload[data_index].timeout = SDL_GetTicks();			
				SDLNet_UDP_Recv(socket_vector.payload[data_index], data_buffer, 1400);
				int num = 0;
				while (isnum(*data_buffer)) {
					num *= 10;
					num += *data_buffer - '0';
					++data_buffer;
				}
				
				// 1.  broadcast position message
				// 2.  broadcast disconnection message
				if (num == 1) {
					for (size_t data_index2 = 0; data_index2 < BUF_LEN(socket_vector); ++data_index2) {
						if (data_index2 == data_index) continue;		
						SDLNet_UDP_Send(socket_vector.payload[data_index2], data_buffer, strlen(data_buffer) + 1);
					}
				} else if (num == 2) {
					for (size_t data_index2 = 0; data_index2 < BUF_LEN(socket_vector); ++data_index2) {
						if (data_index2 == data_index) continue;		
						SDLNet_UDP_Send(socket_vector.payload[data_index2], data_buffer, strlen(data_buffer) + 1);
						SDLNet_UDP_Close(socket_vector.payload[data_index2]);
						BUF_DEL(socket_vector, data_index2);

					}
					
				}
			}		
		}
	}



	SDLNet_Quit();
	return 0;	
}
