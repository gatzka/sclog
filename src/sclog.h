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

#ifndef SCLOG_H
#define SCLOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sclog_export.h"

#define SCLOG_BUFFER_SIZE 200

enum sclog_level {
	SCLOG_NONE,
	SCLOG_ERROR,
	SCLOG_WARNING,
	SCLOG_INFO,
	SCLOG_DEBUG
};

struct sclog_sink {
	int (*init)(const void *context);
	void (*close)(void *context);
	int (*log_message)(void *context, enum sclog_level, const char *application, const char *message);
	void *context;
};

struct sclog {
	const char *application;
	enum sclog_level guard_level;
	char log_buffer[SCLOG_BUFFER_SIZE];
	struct sclog_sink *sink;
};

SCLOG_EXPORT int sclog_init(struct sclog *log, const char *application, enum sclog_level init_level, struct sclog_sink *sink);
SCLOG_EXPORT void sclog_close(struct sclog *log);
SCLOG_EXPORT int sclog_message(struct sclog *log, enum sclog_level level, const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif
