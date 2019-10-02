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

#include <stdbool.h>
#include <stddef.h>
#include <syslog.h>

#include "sclog.h"
#include "sclog_syslog_sink.h"

static bool init(void *context)
{
	struct sc_log *log = (struct sc_log*)context;
	openlog(log->application, 0, LOG_USER);
	return true;
}

static void close(void *context)
{
	(void)context;
	closelog();
}

static void log_message(void *context, enum sc_log_level level, const char *application, const char *message)
{
	(void)context;
	(void)application;

	int priority;

	switch (level) {
		case SC_LOG_NONE: priority = LOG_INFO; break;
		case SC_LOG_ERROR: priority = LOG_ERR; break;
		case SC_LOG_WARNING: priority = LOG_WARNING; break;
		case SC_LOG_INFO: priority = LOG_INFO; break;
		case SC_LOG_DEBUG: priority = LOG_DEBUG; break;
	}

	syslog(priority, "%s", message);
}

bool sc_log_syslog_sink_init(struct sc_log_sink *sink, struct sc_log *log)
{
	if (sink == NULL) {
		return false;
	}

	sink->init = init;
	sink->close = close;
	sink->log_message = log_message;
	sink->context = log;

	return true;
}


