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

#include <stdio.h>
#include <string.h>

#include "sclog_file_rotate.h"
#include "sclog_file_write.h"
#include "sclog_util.h"

enum { FILENAME_BUFFER_SIZE = 255 };

static struct sc_log_file_rotate_sink *get_rotate_sink(const void *context)
{
	const struct sc_log *log = (const struct sc_log *)context;
	struct sc_log_sink *sink = log->sink;
	return sc_log_container_of(sink, struct sc_log_file_rotate_sink, sink);
}

static int init(void *context)
{
	struct sc_log_file_rotate_sink *fr_sink = get_rotate_sink(context);

	fr_sink->fp = fopen(fr_sink->log_file_name, "ae");
	if (fr_sink->fp == NULL) {
		return -1;
	}

	fr_sink->current_file_size = ftell(fr_sink->fp);

	return 0;
}

static void close(void *context)
{
	const struct sc_log_file_rotate_sink *fr_sink = get_rotate_sink(context);
	if (fr_sink->fp != NULL) {
		fclose(fr_sink->fp);
	}
}

static int rotate_files(struct sc_log_file_rotate_sink *fr_sink)
{
	unsigned int rot_files = fr_sink->number_of_files - 1;
	char name_buffer[FILENAME_BUFFER_SIZE];
	if (rot_files > 0) {
		snprintf(name_buffer, sizeof(name_buffer), "%s.%d", fr_sink->log_file_name, fr_sink->number_of_files - 1);
		int ret = remove(name_buffer);
		if (ret < 0) {
			return -1;
		}
	}

	for (unsigned int i = rot_files; i > 1; i--) {
		char name_buffer_to[FILENAME_BUFFER_SIZE];
		snprintf(name_buffer_to, sizeof(name_buffer_to), "%s.%d", fr_sink->log_file_name, i);
		snprintf(name_buffer, sizeof(name_buffer), "%s.%d", fr_sink->log_file_name, i - 1);
		int ret = rename(name_buffer, name_buffer_to);
		if (ret < 0) {
			return -1;
		}
	}

	fclose(fr_sink->fp);
	fr_sink->current_file_size = 0;
	if (rot_files > 0) {
		int ret = rename(fr_sink->log_file_name, name_buffer);
		if (ret < 0) {
			return -1;
		}
	}

	fr_sink->fp = fopen(fr_sink->log_file_name, "ae");
	if (fr_sink->fp == NULL) {
		return -1;
	}

	return 0;
}

static int log_message(void *context, enum sc_log_level level, const char *application, const char *message)
{
	struct sc_log_file_rotate_sink *fr_sink = get_rotate_sink(context);
	long message_length = sc_log_log_get_log_message_length(application, message);
	if (fr_sink->current_file_size + message_length > fr_sink->single_file_size) {
		int ret = rotate_files(fr_sink);
		if (ret < 0) {
			return -1;
		}
	}

	int ret = sc_log_log_message_to_file(fr_sink->fp, level, application, message);
	if (ret < 0) {
		return -1;
	}

	fr_sink->current_file_size = ftell(fr_sink->fp);
	return 0;
}

int sc_log_file_rotate_sink_init(struct sc_log_file_rotate_sink *fr_sink, struct sc_log *log)
{
	if ((fr_sink == NULL) || (fr_sink->number_of_files < 1)) {
		return -1;
	}

	fr_sink->sink.init = init;
	fr_sink->sink.close = close;
	fr_sink->sink.log_message = log_message;
	fr_sink->sink.context = log;
	return 0;
}
