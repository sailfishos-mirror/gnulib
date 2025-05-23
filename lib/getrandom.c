/* Obtain a series of random bytes.

   Copyright 2020-2025 Free Software Foundation, Inc.

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

/* Written by Paul Eggert.  */

#include <config.h>

#include <sys/random.h>

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#if defined _WIN32 && ! defined __CYGWIN__
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# if HAVE_BCRYPT_H
#  include <bcrypt.h>
# else
#  define NTSTATUS LONG
typedef void * BCRYPT_ALG_HANDLE;
#  define BCRYPT_USE_SYSTEM_PREFERRED_RNG 0x00000002
#  if HAVE_LIB_BCRYPT
extern NTSTATUS WINAPI BCryptGenRandom (BCRYPT_ALG_HANDLE, UCHAR *, ULONG, ULONG);
#  endif
# endif
# if !HAVE_LIB_BCRYPT
#  include <wincrypt.h>
#  ifndef CRYPT_VERIFY_CONTEXT
#   define CRYPT_VERIFY_CONTEXT 0xF0000000
#  endif
# endif
#endif

#include "minmax.h"

#if defined _WIN32 && ! defined __CYGWIN__

/* Don't assume that UNICODE is not defined.  */
# undef LoadLibrary
# define LoadLibrary LoadLibraryA
# undef CryptAcquireContext
# define CryptAcquireContext CryptAcquireContextA

# if !HAVE_LIB_BCRYPT

/* Avoid warnings from gcc -Wcast-function-type.  */
#  define GetProcAddress \
    (void *) GetProcAddress

/* BCryptGenRandom with the BCRYPT_USE_SYSTEM_PREFERRED_RNG flag works only
   starting with Windows 7.  */
typedef NTSTATUS (WINAPI * BCryptGenRandomFuncType) (BCRYPT_ALG_HANDLE, UCHAR *, ULONG, ULONG);
static BCryptGenRandomFuncType BCryptGenRandomFunc = NULL;
static BOOL initialized = FALSE;

static void
initialize (void)
{
  HMODULE bcrypt = LoadLibrary ("bcrypt.dll");
  if (bcrypt != NULL)
    {
      BCryptGenRandomFunc =
        (BCryptGenRandomFuncType) GetProcAddress (bcrypt, "BCryptGenRandom");
    }
  initialized = TRUE;
}

# else

#  define BCryptGenRandomFunc BCryptGenRandom

# endif

#else
/* These devices exist on all platforms except native Windows.  */

/* Name of a device through which the kernel returns high quality random
   numbers, from an entropy pool.  When the pool is empty, the call blocks
   until entropy sources have added enough bits of entropy.  */
# ifndef NAME_OF_RANDOM_DEVICE
#  define NAME_OF_RANDOM_DEVICE "/dev/random"
# endif

/* Name of a device through which the kernel returns random or pseudo-random
   numbers.  It uses an entropy pool, but, in order to avoid blocking, adds
   bits generated by a pseudo-random number generator, as needed.  */
# ifndef NAME_OF_NONCE_DEVICE
#  define NAME_OF_NONCE_DEVICE "/dev/urandom"
# endif

#endif

/* Set BUFFER (of size LENGTH) to random bytes under the control of FLAGS.
   Return the number of bytes written (> 0).
   Upon error, return -1 and set errno.  */
ssize_t
getrandom (void *buffer, size_t length, unsigned int flags)
#undef getrandom
{
#if defined _WIN32 && ! defined __CYGWIN__
  /* BCryptGenRandom, defined in <bcrypt.h>
     <https://docs.microsoft.com/en-us/windows/win32/api/bcrypt/nf-bcrypt-bcryptgenrandom>
     with the BCRYPT_USE_SYSTEM_PREFERRED_RNG flag
     works in Windows 7 and newer.  */
  static int bcrypt_not_working /* = 0 */;
  if (!bcrypt_not_working)
    {
# if !HAVE_LIB_BCRYPT
      if (!initialized)
        initialize ();
# endif
      if (BCryptGenRandomFunc != NULL
          && BCryptGenRandomFunc (NULL, buffer, length,
                                  BCRYPT_USE_SYSTEM_PREFERRED_RNG)
             == 0 /*STATUS_SUCCESS*/)
        return length;
      bcrypt_not_working = 1;
    }
# if !HAVE_LIB_BCRYPT
  /* CryptGenRandom, defined in <wincrypt.h>
     <https://docs.microsoft.com/en-us/windows/win32/api/wincrypt/nf-wincrypt-cryptgenrandom>
     works in older releases as well, but is now deprecated.
     CryptAcquireContext, defined in <wincrypt.h>
     <https://docs.microsoft.com/en-us/windows/win32/api/wincrypt/nf-wincrypt-cryptacquirecontexta>  */
  {
    static int crypt_initialized /* = 0 */;
    static HCRYPTPROV provider;
    if (!crypt_initialized)
      {
        if (CryptAcquireContext (&provider, NULL, NULL, PROV_RSA_FULL,
                                 CRYPT_VERIFY_CONTEXT))
          crypt_initialized = 1;
        else
          crypt_initialized = -1;
      }
    if (crypt_initialized >= 0)
      {
        if (!CryptGenRandom (provider, length, buffer))
          {
            errno = EIO;
            return -1;
          }
        return length;
      }
  }
# endif
  errno = ENOSYS;
  return -1;
#elif HAVE_GETRANDOM
  return getrandom (buffer, length, flags);
#else
  static int randfd[2] = { -1, -1 };
  bool devrandom = (flags & GRND_RANDOM) != 0;
  int fd = randfd[devrandom];

  if (fd < 0)
    {
      static char const randdevice[][MAX (sizeof NAME_OF_NONCE_DEVICE,
                                          sizeof NAME_OF_RANDOM_DEVICE)]
        = { NAME_OF_NONCE_DEVICE, NAME_OF_RANDOM_DEVICE };
      int oflags = (O_RDONLY + O_CLOEXEC
                    + (flags & GRND_NONBLOCK ? O_NONBLOCK : 0));
      fd = open (randdevice[devrandom], oflags);
      if (fd < 0)
        {
          if (errno == ENOENT || errno == ENOTDIR)
            errno = ENOSYS;
          return -1;
        }
      randfd[devrandom] = fd;
    }

  return read (fd, buffer, length);
#endif
}
