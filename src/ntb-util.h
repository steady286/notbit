/*
 * Notbit - A Bitmessage client
 * Copyright (C) 2013  Neil Roberts
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef NTB_UTIL_H
#define NTB_UTIL_H

#include <stdlib.h>
#include <stdint.h>

#ifdef __GNUC__
#define NTB_NO_RETURN __attribute__((noreturn))
#define NTB_PRINTF_FORMAT(string_index, first_to_check) \
  __attribute__((format(printf, string_index, first_to_check)))
#else
#define NTB_NO_RETURN
#define NTB_PRINTF_FORMAT(string_index, first_to_check)
#endif

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define NTB_ALIGNOF(x) ALIGNOF_NAME(x)

#define NTB_STRUCT_OFFSET(container, member) \
  ((size_t) &((container *) 0)->member)

#define NTB_SWAP_UINT16(x)                      \
  ((uint16_t)                                   \
   (((uint16_t) (x) >> 8) |                     \
    ((uint16_t) (x) << 8)))
#define NTB_SWAP_UINT32(x)                              \
  ((uint32_t)                                           \
   ((((uint32_t) (x) & UINT32_C(0x000000ff)) << 24) |   \
    (((uint32_t) (x) & UINT32_C(0x0000ff00)) << 8) |    \
    (((uint32_t) (x) & UINT32_C(0x00ff0000)) >> 8) |    \
    (((uint32_t) (x) & UINT32_C(0xff000000)) >> 24)))
#define NTB_SWAP_UINT64(x)                                              \
  ((uint64_t)                                                           \
   ((((uint64_t) (x) & (uint64_t) UINT64_C(0x00000000000000ff)) << 56) | \
    (((uint64_t) (x) & (uint64_t) UINT64_C(0x000000000000ff00)) << 40) | \
    (((uint64_t) (x) & (uint64_t) UINT64_C(0x0000000000ff0000)) << 24) | \
    (((uint64_t) (x) & (uint64_t) UINT64_C(0x00000000ff000000)) << 8) | \
    (((uint64_t) (x) & (uint64_t) UINT64_C(0x000000ff00000000)) >> 8) | \
    (((uint64_t) (x) & (uint64_t) UINT64_C(0x0000ff0000000000)) >> 24) | \
    (((uint64_t) (x) & (uint64_t) UINT64_C(0x00ff000000000000)) >> 40) | \
    (((uint64_t) (x) & (uint64_t) UINT64_C(0xff00000000000000)) >> 56)))

#if defined(HAVE_BIG_ENDIAN)
#define NTB_UINT16_FROM_BE(x) (x)
#define NTB_UINT32_FROM_BE(x) (x)
#define NTB_UINT64_FROM_BE(x) (x)
#define NTB_UINT16_FROM_LE(x) NTB_SWAP_UINT16(x)
#define NTB_UINT32_FROM_LE(x) NTB_SWAP_UINT32(x)
#define NTB_UINT64_FROM_LE(x) NTB_SWAP_UINT64(x)
#elif defined(HAVE_LITTLE_ENDIAN)
#define NTB_UINT16_FROM_LE(x) (x)
#define NTB_UINT32_FROM_LE(x) (x)
#define NTB_UINT64_FROM_LE(x) (x)
#define NTB_UINT16_FROM_BE(x) NTB_SWAP_UINT16(x)
#define NTB_UINT32_FROM_BE(x) NTB_SWAP_UINT32(x)
#define NTB_UINT64_FROM_BE(x) NTB_SWAP_UINT64(x)
#else
#error Platform is neither little-endian nor big-endian
#endif

#define NTB_UINT16_TO_LE(x) NTB_UINT16_FROM_LE(x)
#define NTB_UINT16_TO_BE(x) NTB_UINT16_FROM_BE(x)
#define NTB_UINT32_TO_LE(x) NTB_UINT32_FROM_LE(x)
#define NTB_UINT32_TO_BE(x) NTB_UINT32_FROM_BE(x)
#define NTB_UINT64_TO_LE(x) NTB_UINT64_FROM_LE(x)
#define NTB_UINT64_TO_BE(x) NTB_UINT64_FROM_BE(x)

void *
ntb_alloc(size_t size);

void
ntb_free(void *ptr);

NTB_NO_RETURN NTB_PRINTF_FORMAT(1, 2) void
ntb_fatal(const char *format, ...);

NTB_PRINTF_FORMAT(1, 2) void
ntb_warning(const char *format, ...);

#endif /* NTB_UTIL_H */
