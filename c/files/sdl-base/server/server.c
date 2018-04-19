#include <uv.h>
#include <stdio.h>
#include <stdlib.h>

// lua bindings
// uv_queue_work() to operate with thread pool

static uv_tcp_t server = {0};
static struct sockaddr_in addr = {0};

void on_new_connection(uv_stream_t* server, int status)
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

int main(void)
{
	uv_loop_t* loop = malloc(sizeof(uv_loop_t));
	uv_loop_init(loop);

	uv_tcp_init(loop, &server);
	uv_ipv4_addr("0.0.0.0", DEFAULT_PORT, &addr);
	uv_tcp_bind(&server, (const struct sockaddr *)&addr, 0);
	int listen_status_code = uv_listen((uv_stream_t *)&server, DEFAULT_BACKLOG, on_new_connection);
	if (listen_status_code == 0) {
		fprintf(stderr, "Listen error: %s\n", uv_strerror(listen_status_code));		
		return 1;
	}

	// This will run until no events
	uv_run(loop, UV_RUN_DEFAULT);


	uv_loop_close(loop);

	free(loop);

	return 0;	
}
