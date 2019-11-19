#ifndef _ENDIANNESS_H_
# define _ENDIANNESS_H_

# include <stdint.h>
# include <stddef.h>

/*
 * # include <stdint.h>
 *
 * # define SWAPENDIAN_16(value)	(((value & 0xFF00) >> 8) | \
 *				((value & 0x00FF) << 8))
 *
 * # define SWAPENDIAN_32(value)	(((value & 0xFF000000ul) >> 24) | \
 *				((value & 0x00FF0000ul) >>  8) | \
 *				((value & 0x0000FF00ul) <<  8) | \
 *				((value & 0x000000FFul) << 24))
 *
 * # define SWAPENDIAN_64(value)	(((value & 0xFF00000000000000ULL) >> 56) | \
 *				((value & 0x00FF000000000000ULL) >> 40) | \
 *				((value & 0x0000FF0000000000ULL) >> 24) | \
 *				((value & 0x000000FF00000000ULL) >>  8) | \
 *				((value & 0x00000000FF000000ULL) <<  8) | \
 *				((value & 0x0000000000FF0000ULL) << 24) | \
 *				((value & 0x000000000000FF00ULL) << 40) | \
 *				((value & 0x00000000000000FFULL) << 56))
 */

# define SWAPENDIAN(value)	_swap_endian((char *)(&value), sizeof(value))

/**
 * union _endian_u - Used to test endianness
 *
 * @value: 32-bit value
 * @bytes: 4 bytes array
 */
typedef union _endian_u
{
	uint32_t value;
	uint8_t bytes[4];
} _endian_t;

uint8_t	_get_endianness(void);
void _swap_endian(void *p, size_t size);

#endif /* ! _ENDIANNESS_H_ */
