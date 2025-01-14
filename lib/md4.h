/* Declarations of functions and data types used for MD4 sum
   library functions.
   Copyright (C) 2000-2001, 2003, 2005, 2008-2025 Free Software Foundation,
   Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

#ifndef MD4_H
# define MD4_H 1

# include <stdio.h>
# include <stdint.h>

# ifdef __cplusplus
extern "C" {
# endif

# define MD4_DIGEST_SIZE 16

/* Structure to save state of computation between the single steps.  */
struct md4_ctx
{
  uint32_t A;
  uint32_t B;
  uint32_t C;
  uint32_t D;

  uint32_t total[2];
  uint32_t buflen;
  uint32_t buffer[32];
};


/* Initialize structure containing state of computation. */
extern void md4_init_ctx (struct md4_ctx *ctx);

/* Starting with the result of former calls of this function (or the
   initialization function update the context for the next LEN bytes
   starting at BUFFER.
   It is necessary that LEN is a multiple of 64!!! */
extern void md4_process_block (const void *buffer, size_t len,
                               struct md4_ctx *ctx);

/* Starting with the result of former calls of this function (or the
   initialization function update the context for the next LEN bytes
   starting at BUFFER.
   It is NOT required that LEN is a multiple of 64.  */
extern void md4_process_bytes (const void *buffer, size_t len,
                               struct md4_ctx *ctx);

/* Process the remaining bytes in the buffer and put result from CTX
   in first 16 bytes following RESBUF.  The result is always in little
   endian byte order, so that a byte-wise output yields to the wanted
   ASCII representation of the message digest.  */
extern void *md4_finish_ctx (struct md4_ctx *ctx, void *restrict resbuf);


/* Put result from CTX in first 16 bytes following RESBUF.  The result is
   always in little endian byte order, so that a byte-wise output yields
   to the wanted ASCII representation of the message digest.  */
extern void *md4_read_ctx (const struct md4_ctx *ctx, void *restrict resbuf);


/* Compute MD4 message digest for LEN bytes beginning at BUFFER.  The
   result is always in little endian byte order, so that a byte-wise
   output yields to the wanted ASCII representation of the message
   digest.  */
extern void *md4_buffer (const char *buffer, size_t len,
                         void *restrict resblock);


/* Compute MD4 message digest for bytes read from STREAM.  The
   resulting message digest number will be written into the 16 bytes
   beginning at RESBLOCK.  */
extern int md4_stream (FILE * stream, void *resblock);


# ifdef __cplusplus
}
# endif

#endif
