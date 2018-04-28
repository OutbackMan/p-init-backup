typedef struct GameStretchyBufHdr {
    size_t len;
    size_t cap;
    char payload[0];
} GameStretchyBufHdr;

void* game__stretchy_buf_grow(
	const void* buf_payload, 
	size_t buf_new_len, 
	size_t buf_payload_elem_size
);

#define GAME_STRETCHY_BUF__HDR(buf) \
	((GameStretchyBufHdr *)((char *)(buf) - offsetof(GameStretchyBufHdr, buf)))

#define GAME_STRETCHY_BUF_LEN(buf) \
	((buf != NULL) ? GAME_STRETCHY_BUF__HDR(buf)->len : 0)

#define GAME_STRETCHY_BUF_CAP(buf) \
	((buf != NULL) ? buf__hdr(b)->cap : 0)

#define GAME_STRETCHY_BUF_FREE(buf) \
	((buf != NULL) ? (free(GAME_STRETCHY_BUF__HDR(buf)), (buf) = NULL) : 0)

#define GAME_STRETCHY_BUF__FITS(buf, num_to_fit) \
	((num_to_fit) <= GAME_STRETCHY_BUF_CAP(buf) ? true : false)

#define GAME_STRETCHY_BUF__FIT(buf, num_to_fit) \
	if (!GAME_STRETCHY_BUF__FITS(buf, num_to_fit)) { \
		if (game_stretchy_buf__grow(buf, num_to_fit, sizeof(*buf)) != SUCCESS) { \
			GAME_LEAVE(FAILURE) \
		} \
	}

#define GAME_STRETCHY_BUF_PUSH(buf, elem) \
	do { \
		GAME_STRETCHY_BUF__FIT(buf, 1 + GAME_STRETCHY_BUF_LEN(buf)) \
		(buf)[GAME_STRETCHY_BUF__HDR(buf)->len++] = (elem); \
	} while (0);

int GAME_CLAMP_MIN(int val, int min)
{
	return GAME_MAX(val, min);	
}

int game_stretchy_buf__grow(const void *buf, size_t new_len, size_t elem_size)
{
    size_t new_cap = CLAMP_MIN(2 * buf_cap(buf), MAX(new_len, 16));
    size_t new_size = offsetof(GameStretchyBufHdr, buf) + new_cap*elem_size;
    GameStretchyBufHdr* new_hdr = NULL;
    if (buf) {
		new_hdr = calloc(sizeof(GameStretchyBufHdr, new_size));
		if (new_hdr == NULL) {
			return FAILURE;	
		}
    } else {
		new_hdr = calloc(sizeof(GameStretchyBufHdr, new_size));
		if (new_hdr == NULL) {
			return FAILURE;	
		}
        new_hdr->len = 0;
    }

    new_hdr->cap = new_cap;

	return SUCCESS;
}
