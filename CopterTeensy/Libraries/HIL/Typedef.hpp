#ifndef TYPEDEF_HPP_
#define TYPEDEF_HPP_

#include <Math.hpp>
#include <stdint.h>
#include <Arduino.h>
#include <arm_math.h>

// read something the size of a byte, far version
inline uint8_t pgm_read_one_byte(const void *s)
{
	return *(const uint8_t *) s;
}

// read something the size of a word
inline uint16_t pgm_read_short_word(const void *s)
{
	return *(const uint16_t *) s;
}

// read something the size of a dword
inline uint32_t pgm_read_long_word(const void *s)
{
	return *(const uint32_t *) s;
}

inline float pgm_read_fl(const void *s)
{
	return *(const float *) s;
}

// read something the size of a pointer. This makes the menu code more
// portable
static inline uintptr_t pgm_read_pointer(const void *s)
{
	return *(const uintptr_t *) s;
}

#define PGM_UINT8(addr) pgm_read_one_byte((const prog_char *)addr)
#define PGM_UINT16(addr) pgm_read_short_word((const uint16_t *)addr)
#define PGM_FLOAT(addr) pgm_read_fl((const float *)addr)
#define PGM_POINTER(addr) pgm_read_pointer((const void *)addr)

typedef char prog_char;

#endif /* TYPEDEF_HPP_ */
