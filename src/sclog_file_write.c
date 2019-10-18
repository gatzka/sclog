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
#include <string.h>
#include <time.h>

#include "sclog_file_write.h"

enum {MAX_TIME_STRING_LENGTH = 21};

static void get_time(char *buffer, size_t buffer_size)
{
	time_t t = time(NULL);
	if (t == (time_t)-1) {
		buffer[0] = '\0';
		return;
	}

	struct tm result;
	struct tm *lt = gmtime_r(&t, &result);
	if (lt == NULL) {
		buffer[0] = '\0';
		return;
	}

	buffer[strftime(buffer, buffer_size, "%FT%H:%M:%SZ", &result)] = '\0';
}

static const char *get_level_string(enum sc_log_level level)
{
	switch (level) {
	case SC_LOG_NONE:
		return "NONE";
	case SC_LOG_ERROR:
		return "ERROR";
	case SC_LOG_WARNING:
		return "WARNING";
	case SC_LOG_INFO:
		return "INFO";
	case SC_LOG_DEBUG:
		return "DEBUG";
	default:
		return "UNKNOWN";
	}
}

long sc_log_log_get_log_message_length(const char *application, const char *message)
{
	return (long)(MAX_TIME_STRING_LENGTH + strlen(application) + strlen("UNKNOWN") + strlen(message) + 6);
}

void sc_log_log_message_to_file(FILE *fp, enum sc_log_level level, const char *application, const char *message)
{
	char timestamp_buffer[MAX_TIME_STRING_LENGTH];

	const char *level_string = get_level_string(level);

	get_time(timestamp_buffer, sizeof(timestamp_buffer));

	fprintf(fp, "%s %s: %s: %s\n", timestamp_buffer, application, level_string, message);
	fflush(fp);
}

