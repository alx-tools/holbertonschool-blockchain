#include <stdint.h>
#include <stddef.h>

/**
 * _get_endianness - Get current endianness
 *
 * Return: 1 for little endian, 2 for big endian, 0 for unknown
 */
uint8_t _get_endianness(void)
{
	union {
		uint32_t value;
		uint8_t bytes[4];
	} order = { 1 };

	if (order.bytes[0] == 1)
		return (1); /* Little endian */
	if (order.bytes[0] == 0)
		return (2); /* Big endian */

	return (0); /* Should not happen */
}

void _swap_endian(char *n, size_t size)
{
	size_t i;

	for (i = 0; i < size / 2; i++)
	{
		n[i] ^= n[size - (i + 1)];
		n[size - (i + 1)] ^= n[i];
		n[i] ^= n[size - (i + 1)];
	}
}
