#include <stdint.h>

#define BYTE_SIZE CHAR_BIT

typedef struct {
	char* payload;
	size_t length;
	size_t capacity;
} BitArray;

size_t bits_to_bytes(size_t number_of_bits)
{
	size_t bytes_from_bits = number_of_bits / BYTE_SIZE;

	if (number_of_bits % BYTE_SIZE != 0) {
		bytes_from_bits += 1;		
	}

	return bytes_from_bits;
}

int bit_array_create(BitArray* bit_array, size_t number_of_bits)
{
	size_t bytes_from_bits = bits_to_bytes(number_of_bits);

	bit_array->payload = calloc(sizeof(char), number_of_bits);	
	bit_array->length = number_of_bits;
	bit_array->capacity = bytes_from_bits * BYTE_SIZE;
}

void bit_array_free(BitArray* bit_array)
{
	free(bit_array->base);
}

// bit number 0th indexed
void bit_array_set_bit(BitArray* bit_array, size_t bit_number)
{
	if (bit_number >= bit_array->capacity) {
		
	}
	// index checking
	size_t bit_base_index = bit_number / CHAR_BIT;
	size_t bit_remainder_index = bit_number % CHAR_BIT;

	unsigned char shift = 0x80U >> bit_remainder_index;
	bit_array->base[bit_base_index] |= shift;
}

void bit_array_clear_bit(BitArray* bit_array, size_t bit_number)
{
	size_t bit_base_index = bit_number / CHAR_BIT;
	size_t bit_remainder_index = bit_number % CHAR_BIT;
	
	unsigned char shift = (0x80U >> bit_remainder_index) ^ 0xFFU;
	bit_array->base[bit_base_index] &= shift;
}

unsigned char bit_array_get_bit(BitArray* bit_array, size_t bit_number)
{
	size_t bit_base_index = bit_number / CHAR_BIT;
	size_t bit_remainder_index = bit_number % CHAR_BIT;

	unsigned char shift = 0x80U >> bit_remainder_index;
	if (bit_array->payload[bit_base_index] & shift) {
		return 1;		
	} else {
		return 0;		
	}
}





