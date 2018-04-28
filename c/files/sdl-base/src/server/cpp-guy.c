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
    GAME_WARN("Unable to create client udp socket. Status %s", SDLNet_GetError());
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
