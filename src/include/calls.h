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

#ifndef LIBFAULTS_CALLS_H
#define LIBFAULTS_CALLS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <sys/socket.h>

/**
 * accept
 */
int
(*real_accept)(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

/**
 * socket
 */
int
(*real_socket)(int domain, int type, int protocol);

/**
 * bind
 */
int
(*real_bind)(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
   
/**
 * listen
 */
int
(*real_listen)(int sockfd, int backlog);

/**
 * connect
 */
int
(*real_connect)(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

/**
 * setsockopt
 */
int
(*real_setsockopt)(int sockfd, int level, int optname, const void *optval, socklen_t optlen);

/**
 * read
 */
ssize_t
(*real_read)(int fd, void *buf, size_t count);

/**
 * write
 */
ssize_t
(*real_write)(int fd, const void *buf, size_t count);

#ifdef __cplusplus
}
#endif

#endif
