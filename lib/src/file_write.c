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

#include "sclog/file_write.h"
#include "sclog/time.h"

enum {MAX_TIME_STRING_LENGTH = 21};

static void get_time(char *buffer, size_t buffer_size)
{
	time_t t = time(NULL);
	if (t == (time_t)-1) {
		buffer[0] = '\0';
		return;
	}

	struct tm result;
	int ret = sclog_gmtime(&t, &result);
	if (ret < 0) {
		buffer[0] = '\0';
		return;
	}

	buffer[strftime(buffer, buffer_size, "%FT%H:%M:%SZ", &result)] = '\0';
}

static const char *get_level_string(enum sclog_level level)
{
	switch (level) {
	case SCLOG_NONE:
		return "NONE";
	case SCLOG_ERROR:
		return "ERROR";
	case SCLOG_WARNING:
		return "WARNING";
	case SCLOG_INFO:
		return "INFO";
	case SCLOG_DEBUG:
		return "DEBUG";
	default:
		return "UNKNOWN";
	}
}

enum { EXTRA_LOG_CHARACTERS = 6}; // white spaces and ":"

long sclog_log_get_log_message_length(const char *application, const char *message)
{
	return (long)(MAX_TIME_STRING_LENGTH + strlen(application) + strlen("UNKNOWN") + strlen(message) + EXTRA_LOG_CHARACTERS);
}

int sclog_log_message_to_file(FILE *fp, enum sclog_level level, const char *application, const char *message)
{
	char timestamp_buffer[MAX_TIME_STRING_LENGTH];

	const char *level_string = get_level_string(level);

	get_time(timestamp_buffer, sizeof(timestamp_buffer));

	int ret = fprintf(fp, "%s %s: %s: %s\n", timestamp_buffer, application, level_string, message);
	if (ret < 0) {
		return -1;
	}

	fflush(fp);
	return 0;
}

