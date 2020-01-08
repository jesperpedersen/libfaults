/*
 * Copyright (C) 2020 Red Hat
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this list
 * of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or other
 * materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its contributors may
 * be used to endorse or promote products derived from this software without specific
 * prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* libfaults */
#include <libfaults.h>
#include <configuration.h>
#include <logging.h>

/* system */
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 256

struct configuration config;

static void apply_call(char* section, struct call* call);
static void extract_key_value(char* str, char** key, char** value);
static int as_int(char* str);
static bool as_bool(char* str);
static int as_logging_type(char* str);
static int as_logging_level(char* str);
static int as_error_code(char* str);

/**
 *
 */
int
libfaults_init_configuration()
{
   memset(&config, 0, sizeof(struct configuration));

   config.log_type = LIBFAULTS_LOGGING_TYPE_CONSOLE;
   config.log_level = LIBFAULTS_LOGGING_LEVEL_INFO;

   return 0;
}

/**
 *
 */
int
libfaults_read_configuration(char* filename)
{
   FILE* file;
   char section[LINE_LENGTH];
   char line[LINE_LENGTH];
   char* key = NULL;
   char* value = NULL;
   char* ptr = NULL;
   size_t max;
   struct call call;

   file = fopen(filename, "r");

   if (!file)
      return 1;
    
   memset(&section, 0, LINE_LENGTH);
   memset(&call, 0, sizeof(struct call));

   while (fgets(line, sizeof(line), file))
   {
      if (strcmp(line, ""))
      {
         if (line[0] == '[')
         {
            ptr = strchr(line, ']');
            if (ptr)
            {
               memset(&section, 0, LINE_LENGTH);
               max = ptr - line - 1;
               if (max > MISC_LENGTH - 1)
                  max = MISC_LENGTH - 1;
               memcpy(&section, line + 1, max);
               if (strcmp(section, "libfaults"))
               {
                  apply_call(section, &call);
                  memset(&call, 0, sizeof(struct call));
               }
            }
         }
         else if (line[0] == '#' || line[0] == ';')
         {
            /* Comment, so ignore */
         }
         else
         {
            extract_key_value(line, &key, &value);

            if (key && value)
            {
               bool unknown = false;

               if (!strcmp(key, "log_type"))
               {
                  if (!strcmp(section, "libfaults"))
                  {
                     config.log_type = as_logging_type(value);
                  }
                  else
                  {
                     unknown = true;
                  }
               }
               else if (!strcmp(key, "log_level"))
               {
                  if (!strcmp(section, "libfaults"))
                  {
                     config.log_level = as_logging_level(value);
                  }
                  else
                  {
                     unknown = true;
                  }
               }
               else if (!strcmp(key, "log_path"))
               {
                  if (!strcmp(section, "libfaults"))
                  {
                     max = strlen(value);
                     if (max > MISC_LENGTH - 1)
                        max = MISC_LENGTH - 1;
                     memcpy(config.log_path, value, max);
                  }
                  else
                  {
                     unknown = true;
                  }
               }
               else if (!strcmp(key, "enable"))
               {
                  if (strcmp(section, "libfaults"))
                  {
                     call.enable = as_bool(value);
                  }
                  else
                  {
                     unknown = true;
                  }
               }
               else if (!strcmp(key, "return_value"))
               {
                  if (strcmp(section, "libfaults"))
                  {
                     call.return_value = as_int(value);
                  }
                  else
                  {
                     unknown = true;
                  }
               }
               else if (!strcmp(key, "error_code"))
               {
                  if (strcmp(section, "libfaults"))
                  {
                     call.error_code = as_error_code(value);
                  }
                  else
                  {
                     unknown = true;
                  }
               }

               if (unknown)
               {
                  fprintf(stderr, "Unknown: Section=%s, Key=%s, Value=%s\n", strlen(section) > 0 ? section : "<unknown>", key, value);
               }

               free(key);
               free(value);
               key = NULL;
               value = NULL;
            }
         }
      }
   }

   if (strlen(section) > 0)
   {
      apply_call(section, &call);
   }

   fclose(file);

   return 0;
}

/**
 *
 */
int
libfaults_validate_configuration(void* shmem)
{
   return 0;
}

static void
apply_call(char* section, struct call* call)
{
   if (!strcmp("accept", section))
   {
      memcpy(&config.accept, call, sizeof(struct call));
   }
   else if (!strcmp("socket", section))
   {
      memcpy(&config.socket, call, sizeof(struct call));
   }
   else if (!strcmp("bind", section))
   {
      memcpy(&config.bind, call, sizeof(struct call));
   }
   else if (!strcmp("listen", section))
   {
      memcpy(&config.listen, call, sizeof(struct call));
   }
   else if (!strcmp("connect", section))
   {
      memcpy(&config.connect, call, sizeof(struct call));
   }
   else if (!strcmp("setsockopt", section))
   {
      memcpy(&config.setsockopt, call, sizeof(struct call));
   }
   else if (!strcmp("read", section))
   {
      memcpy(&config.read, call, sizeof(struct call));
   }
   else if (!strcmp("write", section))
   {
      memcpy(&config.write, call, sizeof(struct call));
   }
   else
   {
      fprintf(stderr, "Unknown call: %s\n", strlen(section) > 0 ? section : "<unknown>");
   }
}

static void
extract_key_value(char* str, char** key, char** value)
{
   int c = 0;
   int offset = 0;
   int length = strlen(str);
   char* k;
   char* v;

   while (str[c] != ' ' && str[c] != '=' && c < length)
      c++;

   if (c < length)
   {
      k = malloc(c + 1);
      memset(k, 0, c + 1);
      memcpy(k, str, c);
      *key = k;

      while ((str[c] == ' ' || str[c] == '\t' || str[c] == '=') && c < length)
         c++;

      offset = c;

      while (str[c] != ' ' && str[c] != '\r' && str[c] != '\n' && c < length)
         c++;

      if (c < length)
      {
         v = malloc((c - offset) + 1);
         memset(v, 0, (c - offset) + 1);
         memcpy(v, str + offset, (c - offset));
         *value = v;
      }
   }
}

static int
as_int(char* str)
{
   return atoi(str);
}

static bool
as_bool(char* str)
{
   if (!strcasecmp(str, "true"))
      return true;

   if (!strcasecmp(str, "on"))
      return true;

   if (!strcasecmp(str, "1"))
      return true;

   if (!strcasecmp(str, "false"))
      return false;

   if (!strcasecmp(str, "off"))
      return false;

   if (!strcasecmp(str, "0"))
      return false;

   return false;
}

static int
as_logging_type(char* str)
{
   if (!strcasecmp(str, "console"))
      return LIBFAULTS_LOGGING_TYPE_CONSOLE;

   if (!strcasecmp(str, "file"))
      return LIBFAULTS_LOGGING_TYPE_FILE;

   if (!strcasecmp(str, "syslog"))
      return LIBFAULTS_LOGGING_TYPE_SYSLOG;

   return 0;
}

static int
as_logging_level(char* str)
{
   if (!strcasecmp(str, "debug5"))
      return LIBFAULTS_LOGGING_LEVEL_DEBUG5;

   if (!strcasecmp(str, "debug4"))
      return LIBFAULTS_LOGGING_LEVEL_DEBUG4;

   if (!strcasecmp(str, "debug3"))
      return LIBFAULTS_LOGGING_LEVEL_DEBUG3;

   if (!strcasecmp(str, "debug2"))
      return LIBFAULTS_LOGGING_LEVEL_DEBUG2;

   if (!strcasecmp(str, "debug1"))
      return LIBFAULTS_LOGGING_LEVEL_DEBUG1;

   if (!strcasecmp(str, "info"))
      return LIBFAULTS_LOGGING_LEVEL_INFO;

   if (!strcasecmp(str, "warn"))
      return LIBFAULTS_LOGGING_LEVEL_WARN;

   if (!strcasecmp(str, "error"))
      return LIBFAULTS_LOGGING_LEVEL_ERROR;

   if (!strcasecmp(str, "fatal"))
      return LIBFAULTS_LOGGING_LEVEL_FATAL;

   return LIBFAULTS_LOGGING_LEVEL_INFO;
}

static int
as_error_code(char* str)
{
   if (!strcasecmp(str, "EPERM"))
   {
      return EPERM;
   }
   if (!strcasecmp(str, "ENOENT"))
   {
      return ENOENT;
   }
   if (!strcasecmp(str, "ESRCH"))
   {
      return ESRCH;
   }
   if (!strcasecmp(str, "EINTR"))
   {
      return EINTR;
   }
   if (!strcasecmp(str, "EIO"))
   {
      return EIO;
   }
   if (!strcasecmp(str, "ENXIO"))
   {
      return ENXIO;
   }
   if (!strcasecmp(str, "E2BIG"))
   {
      return E2BIG;
   }
   if (!strcasecmp(str, "ENOEXEC"))
   {
      return ENOEXEC;
   }
   if (!strcasecmp(str, "EBADF"))
   {
      return EBADF;
   }
   if (!strcasecmp(str, "ECHILD"))
   {
      return ECHILD;
   }
   if (!strcasecmp(str, "EAGAIN"))
   {
      return EAGAIN;
   }
   if (!strcasecmp(str, "ENOMEM"))
   {
      return ENOMEM;
   }
   if (!strcasecmp(str, "EACCES"))
   {
      return EACCES;
   }
   if (!strcasecmp(str, "EFAULT"))
   {
      return EFAULT;
   }
   if (!strcasecmp(str, "ENOTBLK"))
   {
      return ENOTBLK;
   }
   if (!strcasecmp(str, "EBUSY"))
   {
      return EBUSY;
   }
   if (!strcasecmp(str, "EEXIST"))
   {
      return EEXIST;
   }
   if (!strcasecmp(str, "EXDEV"))
   {
      return EXDEV;
   }
   if (!strcasecmp(str, "ENODEV"))
   {
      return ENODEV;
   }
   if (!strcasecmp(str, "ENOTDIR"))
   {
      return ENOTDIR;
   }
   if (!strcasecmp(str, "EISDIR"))
   {
      return EISDIR;
   }
   if (!strcasecmp(str, "EINVAL"))
   {
      return EINVAL;
   }
   if (!strcasecmp(str, "ENFILE"))
   {
      return ENFILE;
   }
   if (!strcasecmp(str, "EMFILE"))
   {
      return EMFILE;
   }
   if (!strcasecmp(str, "ENOTTY"))
   {
      return ENOTTY;
   }
   if (!strcasecmp(str, "ETXTBSY"))
   {
      return ETXTBSY;
   }
   if (!strcasecmp(str, "EFBIG"))
   {
      return EFBIG;
   }
   if (!strcasecmp(str, "ENOSPC"))
   {
      return ENOSPC;
   }
   if (!strcasecmp(str, "ESPIPE"))
   {
      return ESPIPE;
   }
   if (!strcasecmp(str, "EROFS"))
   {
      return EROFS;
   }
   if (!strcasecmp(str, "EMLINK"))
   {
      return EMLINK;
   }
   if (!strcasecmp(str, "EPIPE"))
   {
      return EPIPE;
   }
   if (!strcasecmp(str, "EDOM"))
   {
      return EDOM;
   }
   if (!strcasecmp(str, "ERANGE"))
   {
      return ERANGE;
   }
   if (!strcasecmp(str, "EDEADLK"))
   {
      return EDEADLK;
   }
   if (!strcasecmp(str, "ENAMETOOLONG"))
   {
      return ENAMETOOLONG;
   }
   if (!strcasecmp(str, "ENOLCK"))
   {
      return ENOLCK;
   }
   if (!strcasecmp(str, "ENOSYS"))
   {
      return ENOSYS;
   }
   if (!strcasecmp(str, "ENOTEMPTY"))
   {
      return ENOTEMPTY;
   }
   if (!strcasecmp(str, "ELOOP"))
   {
      return ELOOP;
   }
   if (!strcasecmp(str, "EWOULDBLOCK"))
   {
      return EWOULDBLOCK;
   }
   if (!strcasecmp(str, "ENOMSG"))
   {
      return ENOMSG;
   }
   if (!strcasecmp(str, "EIDRM"))
   {
      return EIDRM;
   }
   if (!strcasecmp(str, "ECHRNG"))
   {
      return ECHRNG;
   }
   if (!strcasecmp(str, "EL2NSYNC"))
   {
      return EL2NSYNC;
   }
   if (!strcasecmp(str, "EL3HLT"))
   {
      return EL3HLT;
   }
   if (!strcasecmp(str, "EL3RST"))
   {
      return EL3RST;
   }
   if (!strcasecmp(str, "ELNRNG"))
   {
      return ELNRNG;
   }
   if (!strcasecmp(str, "EUNATCH"))
   {
      return EUNATCH;
   }
   if (!strcasecmp(str, "ENOCSI"))
   {
      return ENOCSI;
   }
   if (!strcasecmp(str, "EL2HLT"))
   {
      return EL2HLT;
   }
   if (!strcasecmp(str, "EBADE"))
   {
      return EBADE;
   }
   if (!strcasecmp(str, "EBADR"))
   {
      return EBADR;
   }
   if (!strcasecmp(str, "EXFULL"))
   {
      return EXFULL;
   }
   if (!strcasecmp(str, "ENOANO"))
   {
      return ENOANO;
   }
   if (!strcasecmp(str, "EBADRQC"))
   {
      return EBADRQC;
   }
   if (!strcasecmp(str, "EBADSLT"))
   {
      return EBADSLT;
   }
   if (!strcasecmp(str, "EDEADLOCK"))
   {
      return EDEADLOCK;
   }
   if (!strcasecmp(str, "EBFONT"))
   {
      return EBFONT;
   }
   if (!strcasecmp(str, "ENOSTR"))
   {
      return ENOSTR;
   }
   if (!strcasecmp(str, "ENODATA"))
   {
      return ENODATA;
   }
   if (!strcasecmp(str, "ETIME"))
   {
      return ETIME;
   }
   if (!strcasecmp(str, "ENOSR"))
   {
      return ENOSR;
   }
   if (!strcasecmp(str, "ENONET"))
   {
      return ENONET;
   }
   if (!strcasecmp(str, "ENOPKG"))
   {
      return ENOPKG;
   }
   if (!strcasecmp(str, "EREMOTE"))
   {
      return EREMOTE;
   }
   if (!strcasecmp(str, "ENOLINK"))
   {
      return ENOLINK;
   }
   if (!strcasecmp(str, "EADV"))
   {
      return EADV;
   }
   if (!strcasecmp(str, "ESRMNT"))
   {
      return ESRMNT;
   }
   if (!strcasecmp(str, "ECOMM"))
   {
      return ECOMM;
   }
   if (!strcasecmp(str, "EPROTO"))
   {
      return EPROTO;
   }
   if (!strcasecmp(str, "EMULTIHOP"))
   {
      return EMULTIHOP;
   }
   if (!strcasecmp(str, "EDOTDOT"))
   {
      return EDOTDOT;
   }
   if (!strcasecmp(str, "EBADMSG"))
   {
      return EBADMSG;
   }
   if (!strcasecmp(str, "EOVERFLOW"))
   {
      return EOVERFLOW;
   }
   if (!strcasecmp(str, "ENOTUNIQ"))
   {
      return ENOTUNIQ;
   }
   if (!strcasecmp(str, "EBADFD"))
   {
      return EBADFD;
   }
   if (!strcasecmp(str, "EREMCHG"))
   {
      return EREMCHG;
   }
   if (!strcasecmp(str, "ELIBACC"))
   {
      return ELIBACC;
   }
   if (!strcasecmp(str, "ELIBBAD"))
   {
      return ELIBBAD;
   }
   if (!strcasecmp(str, "ELIBSCN"))
   {
      return ELIBSCN;
   }
   if (!strcasecmp(str, "ELIBMAX"))
   {
      return ELIBMAX;
   }
   if (!strcasecmp(str, "ELIBEXEC"))
   {
      return ELIBEXEC;
   }
   if (!strcasecmp(str, "EILSEQ"))
   {
      return EILSEQ;
   }
   if (!strcasecmp(str, "ERESTART"))
   {
      return ERESTART;
   }
   if (!strcasecmp(str, "ESTRPIPE"))
   {
      return ESTRPIPE;
   }
   if (!strcasecmp(str, "EUSERS"))
   {
      return EUSERS;
   }
   if (!strcasecmp(str, "ENOTSOCK"))
   {
      return ENOTSOCK;
   }
   if (!strcasecmp(str, "EDESTADDRREQ"))
   {
      return EDESTADDRREQ;
   }
   if (!strcasecmp(str, "EMSGSIZE"))
   {
      return EMSGSIZE;
   }
   if (!strcasecmp(str, "EPROTOTYPE"))
   {
      return EPROTOTYPE;
   }
   if (!strcasecmp(str, "ENOPROTOOPT"))
   {
      return ENOPROTOOPT;
   }
   if (!strcasecmp(str, "EPROTONOSUPPORT"))
   {
      return EPROTONOSUPPORT;
   }
   if (!strcasecmp(str, "ESOCKTNOSUPPORT"))
   {
      return ESOCKTNOSUPPORT;
   }
   if (!strcasecmp(str, "EOPNOTSUPP"))
   {
      return EOPNOTSUPP;
   }
   if (!strcasecmp(str, "EPFNOSUPPORT"))
   {
      return EPFNOSUPPORT;
   }
   if (!strcasecmp(str, "EAFNOSUPPORT"))
   {
      return EAFNOSUPPORT;
   }
   if (!strcasecmp(str, "EADDRINUSE"))
   {
      return EADDRINUSE;
   }
   if (!strcasecmp(str, "EADDRNOTAVAIL"))
   {
      return EADDRNOTAVAIL;
   }
   if (!strcasecmp(str, "ENETDOWN"))
   {
      return ENETDOWN;
   }
   if (!strcasecmp(str, "ENETUNREACH"))
   {
      return ENETUNREACH;
   }
   if (!strcasecmp(str, "ENETRESET"))
   {
      return ENETRESET;
   }
   if (!strcasecmp(str, "ECONNABORTED"))
   {
      return ECONNABORTED;
   }
   if (!strcasecmp(str, "ECONNRESET"))
   {
      return ECONNRESET;
   }
   if (!strcasecmp(str, "ENOBUFS"))
   {
      return ENOBUFS;
   }
   if (!strcasecmp(str, "EISCONN"))
   {
      return EISCONN;
   }
   if (!strcasecmp(str, "ENOTCONN"))
   {
      return ENOTCONN;
   }
   if (!strcasecmp(str, "ESHUTDOWN"))
   {
      return ESHUTDOWN;
   }
   if (!strcasecmp(str, "ETOOMANYREFS"))
   {
      return ETOOMANYREFS;
   }
   if (!strcasecmp(str, "ETIMEDOUT"))
   {
      return ETIMEDOUT;
   }
   if (!strcasecmp(str, "ECONNREFUSED"))
   {
      return ECONNREFUSED;
   }
   if (!strcasecmp(str, "EHOSTDOWN"))
   {
      return EHOSTDOWN;
   }
   if (!strcasecmp(str, "EHOSTUNREACH"))
   {
      return EHOSTUNREACH;
   }
   if (!strcasecmp(str, "EALREADY"))
   {
      return EALREADY;
   }
   if (!strcasecmp(str, "EINPROGRESS"))
   {
      return EINPROGRESS;
   }
   if (!strcasecmp(str, "ESTALE"))
   {
      return ESTALE;
   }
   if (!strcasecmp(str, "EUCLEAN"))
   {
      return EUCLEAN;
   }
   if (!strcasecmp(str, "ENOTNAM"))
   {
      return ENOTNAM;
   }
   if (!strcasecmp(str, "ENAVAIL"))
   {
      return ENAVAIL;
   }
   if (!strcasecmp(str, "EISNAM"))
   {
      return EISNAM;
   }
   if (!strcasecmp(str, "EREMOTEIO"))
   {
      return EREMOTEIO;
   }
   if (!strcasecmp(str, "EDQUOT"))
   {
      return EDQUOT;
   }
   if (!strcasecmp(str, "ENOMEDIUM"))
   {
      return ENOMEDIUM;
   }
   if (!strcasecmp(str, "EMEDIUMTYPE"))
   {
      return EMEDIUMTYPE;
   }

   return 0;
}

