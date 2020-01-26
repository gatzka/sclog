/*
 * SPDX-License-Identifier: MIT
 *
 *The MIT License (MIT)
 *
 * Copyright (c) <2019> <Stephan Gatzka>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef SC_LOG_H
#define SC_LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sclog_export.h"

#define SCLOG_BUFFER_SIZE 200

enum sc_log_level {
	SC_LOG_NONE,
	SC_LOG_ERROR,
	SC_LOG_WARNING,
	SC_LOG_INFO,
	SC_LOG_DEBUG
};

struct sc_log_sink {
	int (*init)(void *context);
	void (*close)(void *context);
	int (*log_message)(void *context, enum sc_log_level, const char *application, const char *message);
	void *context;
};

struct sc_log {
	const char *application;
	enum sc_log_level guard_level;
	char log_buffer[SCLOG_BUFFER_SIZE];
	struct sc_log_sink *sink;
};

SCLOG_EXPORT int sc_log_init(struct sc_log *log, const char *application, enum sc_log_level init_level, struct sc_log_sink *sink);
SCLOG_EXPORT void sc_log_close(struct sc_log *log);
SCLOG_EXPORT int sc_log_message(struct sc_log *log, enum sc_log_level level, const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif