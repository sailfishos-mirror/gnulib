/* backupfile.h -- declarations for making Emacs style backup file names

   Copyright (C) 1990-1992, 1997-1999, 2003-2004, 2009-2025 Free Software
   Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

#ifndef BACKUPFILE_H_
#define BACKUPFILE_H_

/* This file uses _GL_ATTRIBUTE_MALLOC, _GL_ATTRIBUTE_RETURNS_NONNULL.  */
#if !_GL_CONFIG_H_INCLUDED
 #error "Please include config.h first."
#endif

/* Get AT_FDCWD, as a convenience for users of this file.  */
#include <fcntl.h>

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif


/* When to make backup files. */
enum backup_type
{
  /* Never make backups. */
  no_backups,

  /* Make simple backups of every file. */
  simple_backups,

  /* Make numbered backups of files that already have numbered backups,
     and simple backups of the others. */
  numbered_existing_backups,

  /* Make numbered backups of every file. */
  numbered_backups
};

#define VALID_BACKUP_TYPE(Type) \
  ((unsigned int) (Type) <= numbered_backups)

extern char const *simple_backup_suffix;

void set_simple_backup_suffix (char const *);
char *backup_file_rename (int, char const *, enum backup_type)
  _GL_ATTRIBUTE_MALLOC _GL_ATTRIBUTE_DEALLOC_FREE;
char *find_backup_file_name (int, char const *, enum backup_type)
  _GL_ATTRIBUTE_MALLOC _GL_ATTRIBUTE_DEALLOC_FREE
  _GL_ATTRIBUTE_RETURNS_NONNULL;
enum backup_type get_version (char const *context, char const *arg);
enum backup_type xget_version (char const *context, char const *arg);


#ifdef __cplusplus
}
#endif

#endif /* ! BACKUPFILE_H_ */
