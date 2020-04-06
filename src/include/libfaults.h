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

#ifndef LIBFAULTS_H
#define LIBFAULTS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define VERSION "0.1.0"

#define MISC_LENGTH 128
   
/* Setup zf_log to include DEBUG support even for release builds */
#ifdef DEBUG
#define ZF_LOG_LEVEL ZF_LOG_VERBOSE
#else
#define ZF_LOG_LEVEL ZF_LOG_DEBUG
#endif

/** @struct
 * Defines a call
 */
struct call
{
   bool enable;        /**< Enable the call */
   int return_value;   /**< The return value */
   int error_code;     /**< The error */
   int percentage;     /**< The percentage */

} __attribute__ ((aligned (64)));

/** @struct
 * Defines the configuration and state of libfaults
 */
struct configuration
{
   int log_type;               /**< The logging type */
   int log_level;              /**< The logging level */
   char log_path[MISC_LENGTH]; /**< The logging path */

   struct call accept;         /**< accept() */
   struct call socket;         /**< socket() */
   struct call bind;           /**< bind() */
   struct call listen;         /**< listen() */
   struct call connect;        /**< connect() */
   struct call setsockopt;     /**< setsockopt() */
   struct call read;           /**< read() */
   struct call write;          /**< write() */

} __attribute__ ((aligned (64)));

/**
 * Is the call enabled
 * @param call The call
 * @return True if enabled, otherwise false
 */
bool
libfaults_call_enabled(struct call* call);

/**
 * Invoke call
 * @param call The call
 * @return The return value
 */
int
libfaults_invoke_call(struct call* call);

#ifdef __cplusplus
}
#endif

#endif
