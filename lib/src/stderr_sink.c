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

#include <stddef.h>
#include <stdio.h>
#include <time.h>

#include "sclog/file_write.h"
#include "sclog/sclog.h"
#include "sclog/stderr_sink.h"

static int init(void *context)
{
	(void)context;
	return 0;
}

static void close(const void *context)
{
	(void)context;
}

static int log_message(void *context, enum sclog_level level, const char *application, const char *message)
{
	const struct sclog_sink *sink = (const struct sclog_sink *)context;
	if ((level == SCLOG_NONE) || (level > sink->guard_level)) {
		return -1;
	}

	return sclog_log_message_to_file(stderr, level, application, message);
}

int sclog_stderr_sink_init(struct sclog_sink *sink, enum sclog_level level)
{
	if (sink == NULL) {
		return -1;
	}

	sink->init = init;
	sink->close = close;
	sink->log_message = log_message;
	sink->guard_level = level;
	sink->context = sink;

	return 0;
}
