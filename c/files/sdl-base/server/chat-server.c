#include <uv.h>
#include <stdio.h>
#include <stdlib.h>

// uv_queue_work() to operate with thread pool

static uv_loop_t* chat_server_event_loop;		

typedef struct {
	uv_write_t req;
	uv_buf_t buf;
} write_req_t;

void chat_server_echo_read(uv_stream_t* chat_server_client, ssize_t nread, const uv_buf_t* buf)
{
	if (nread > 0) {
		write_req_t		
	}	
}

void chat_server_new_connection(uv_stream_t* chat_server, int status)
{
	if (status < 0) {
		fprintf(stderr, "Chat server new connection error: %s\n", uv_strerror(status));		
		return;
	}

	uv_tcp_t* chat_server_client = malloc(sizeof(uv_tcp_t));
	uv_tcp_init(&chat_server_event_loop, chat_server_client);

	if (uv_accept(chat_server, (uv_stream_t *)chat_server_client) == 0) {
		uv_read_start((uv_stream_t *)chat_server_client, alloc_buffer, echo_read);	
	} else {
		uv_close((uv_handle_t *)chat_server_client, chat_server_close_connection);		
	}
}

// args: port, max clients
int main(void)
{
	chat_server_event_loop = malloc(sizeof(uv_loop_t));
	uv_loop_init(chat_server_event_loop);

	uv_tcp_t chat_server_instance = {0};
	uv_tcp_init(chat_server_event_loop, &chat_server_instance);

	struct sockaddr_in chat_server_addr = {0};
	// 7000 -> port
	uv_ipv4_addr("0.0.0.0", 7000, &chat_server_addr);

	// 0 -> flags
	uv_tcp_bind(&chat_server_instance, (const struct sockaddr *)&chat_server_addr, 0);

	// 128 -> backlog: number of pending connections able to queue
	int chat_server_listen_status = uv_listen((uv_stream_t *)&chat_server_instance, 128, chat_server_new_connection);
	if (chat_server_listen_status == 0) {
		fprintf(stderr, "Chat server listen error: %s\n", uv_strerror(chat_server_listen_status));		
		return 1;
	}

	// This will run until no events
	uv_run(chat_server_event_loop, UV_RUN_DEFAULT);

	uv_loop_close(chat_server_event_loop);
	free(chat_server_event_loop);

	return 0;	
}
