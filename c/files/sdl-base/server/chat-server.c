#include <uv.h>
#include <stdio.h>
#include <stdlib.h>

// uv_queue_work() to operate with thread pool

void chat_server_new_connection(uv_stream_t* chat_server, int status)
{
	if (status < 0) {
		fprintf(stderr, "New connection error: %s\n", uv_strerror(listen_status_code));		
		return;
	}

	uv_tcp_t* client = malloc(sizeof(uv_tcp_t));
	uv_tcp_init(&loop, client);
	if (uv_accept(server, (uv_stream_t *)client == 0)) {
		uv_read_start((uv_stream_t *)client, alloc_buffer, echo_read);	
	}
}

// args: port, max clients
int main(void)
{
	uv_loop_t* chat_server_event_loop = malloc(sizeof(uv_loop_t));
	uv_loop_init(chat_server_event_loop);

	uv_tcp_t chat_server_instance = {0};
	uv_tcp_init(chat_server_event_loop, &chat_server_instance);

	struct sockaddr_in chat_server_addr = {0};
	// 7000 -> port
	uv_ipv4_addr("0.0.0.0", 7000, &chat_server_addr);

	// 0 -> flags
	uv_tcp_bind(&chat_server_instance, (const struct sockaddr *)&chat_server_addr, 0);

	// 128 -> backlog: number of pending connections able to queue
	int chat_server_listen_status = uv_listen((uv_stream_t *)&chat_server_instance, 128, on_new_connection);
	if (chat_server_listen_status == 0) {
		fprintf(stderr, "Chat server listen error: %s\n", uv_strerror(chat_server_listen_status));		
		return 1;
	}

	// This will run until no events
	uv_run(loop, UV_RUN_DEFAULT);


	uv_loop_close(loop);
	free(loop);

	return 0;	
}
