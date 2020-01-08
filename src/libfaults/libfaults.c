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
#include <calls.h>
#include <configuration.h>

#define ZF_LOG_TAG "libfaults"
#include <zf_log.h>

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

__attribute__((constructor))
static void
init()
{
   char homedir[128];
   struct passwd *pw = getpwuid(getuid());

   memset(&homedir, 0, sizeof(homedir));
   snprintf(&homedir[0], sizeof(homedir), "%s/libfaults.conf", pw->pw_dir);

   real_accept = dlsym(RTLD_NEXT, "accept");
   real_socket = dlsym(RTLD_NEXT, "socket");
   real_bind = dlsym(RTLD_NEXT, "bind");
   real_listen = dlsym(RTLD_NEXT, "listen");
   real_connect = dlsym(RTLD_NEXT, "connect");
   real_setsockopt = dlsym(RTLD_NEXT, "setsockopt");
   real_read = dlsym(RTLD_NEXT, "read");
   real_write = dlsym(RTLD_NEXT, "write");

   libfaults_init_configuration();

   if (libfaults_read_configuration(&homedir[0]))
   {
      if (libfaults_read_configuration("/tmp/libfaults.conf"))
      {
         fprintf(stderr, "libfaults configuration not found");
         exit(1);
      }
   }

   ZF_LOGD("Configuration loaded");
}

__attribute__((destructor))
static void
destroy()
{
}
