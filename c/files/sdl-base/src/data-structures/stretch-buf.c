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

#define buf_end(b) ((b) + buf_len(b))
#define buf_sizeof(b) ((b) ? buf_len(b)*sizeof(*b) : 0)

#define buf_free(b) ((b) ? (free(buf__hdr(b)), (b) = NULL) : 0)
#define buf_fit(b, n) ((n) <= buf_cap(b) ? 0 : ((b) = buf__grow((b), (n), sizeof(*(b)))))
#define buf_push(b, ...) (buf_fit((b), 1 + buf_len(b)), (b)[buf__hdr(b)->len++] = (__VA_ARGS__))
#define buf_printf(b, ...) ((b) = buf__printf((b), __VA_ARGS__))
#define buf_clear(b) ((b) ? buf__hdr(b)->len = 0 : 0)

void *buf__grow(const void *buf, size_t new_len, size_t elem_size) {
    assert(buf_cap(buf) <= (SIZE_MAX - 1)/2);
    size_t new_cap = CLAMP_MIN(2*buf_cap(buf), MAX(new_len, 16));
    assert(new_len <= new_cap);
    assert(new_cap <= (SIZE_MAX - offsetof(GameStretchyBufHdr, buf))/elem_size);
    size_t new_size = offsetof(GameStretchyBufHdr, buf) + new_cap*elem_size;
    GameStretchyBufHdr *new_hdr;
    if (buf) {
        new_hdr = xrealloc(buf__hdr(buf), new_size);
    } else {
        new_hdr = xmalloc(new_size);
        new_hdr->len = 0;
    }
    new_hdr->cap = new_cap;
    return new_hdr->buf;
}

char *buf__printf(char *buf, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    size_t cap = buf_cap(buf) - buf_len(buf);
    size_t n = 1 + vsnprintf(buf_end(buf), cap, fmt, args);
    va_end(args);
    if (n > cap) {
        buf_fit(buf, n + buf_len(buf));
        va_start(args, fmt);
        size_t new_cap = buf_cap(buf) - buf_len(buf);
        n = 1 + vsnprintf(buf_end(buf), new_cap, fmt, args);
        assert(n <= new_cap);
        va_end(args);
    }
    buf__hdr(buf)->len += n - 1;
    return buf;
}
