#ifndef WAFEL_TYPES_H
#define WAFEL_TYPES_H

	#include <stdint.h>
	#include <stdbool.h>
	#include <stddef.h>

	#define U64_MAX	UINT64_MAX

	typedef uint8_t u8;
	typedef uint16_t u16;
	typedef uint32_t u32;
	typedef uint64_t u64;

	typedef int8_t s8;
	typedef int16_t s16;
	typedef int32_t s32;
	typedef int64_t s64;

	typedef volatile u8 vu8;
	typedef volatile u16 vu16;
	typedef volatile u32 vu32;
	typedef volatile u64 vu64;

	typedef volatile s8 vs8;
	typedef volatile s16 vs16;
	typedef volatile s32 vs32;
	typedef volatile s64 vs64;

	#define LINKABLE __attribute__ ((weak)) __attribute__((used))
	#define ALIGNED(x) __attribute__((aligned(x)))
	#define PACKED __attribute__((packed))

#endif // WAFEL_TYPES_H
