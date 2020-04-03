/*
 * SPDX-License-Identifier: MIT
 *
 * The MIT License (MIT)
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

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

#include "sclog.h"
#include "sclog_compiler.h"

int sclog_init(struct sclog *log, const char *application, enum sclog_level init_level, struct sclog_sink *sink)
{
	if ((log == NULL) || (sink == NULL)) {
		return -1;
	}

	log->application = application;
	log->guard_level = init_level;
	log->sink = sink;

	return log->sink->init(log->sink->context);
}

void sclog_close(const struct sclog *log)
{
	log->sink->close(log->sink->context);
}

// clang-format off
__attribute__((format(printf, 3, 4)))
int sclog_message(struct sclog *log, enum sclog_level level, const char *format, ...)
// clang-format on
{
	if ((level == SCLOG_NONE) || (level > log->guard_level)) {
		return -1;
	}

	va_list args;
	va_start(args, format);
	vsnprintf(log->log_buffer, sizeof(log->log_buffer), format, args);
	va_end(args);

	return log->sink->log_message(log->sink->context, level, log->application, log->log_buffer);
}
