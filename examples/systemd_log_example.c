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

#include <stdlib.h>
#include <string.h>

#include "sclog/sclog.h"
#include "sclog/systemd_sink.h"

int main(void)
{
	struct sclog_sink systemd_sink;
	if (sclog_systemd_sink_init(&systemd_sink, SCLOG_WARNING) != 0) {
		return EXIT_FAILURE;
	}

	struct sclog_sink *sinks[] = {&systemd_sink};
	struct sclog systemd_log;
	if (sclog_init(&systemd_log, "systemd_log_example", sinks, 1) != 0) {
		return EXIT_FAILURE;
	}

	int ret = sclog_message(&systemd_log, SCLOG_ERROR, "Hello error!");
	if (ret < 0) {
		goto err;
	}

	ret = sclog_message(&systemd_log, SCLOG_WARNING, "Hello warning!");
	if (ret < 0) {
		goto err;
	}

	ret = sclog_message(&systemd_log, SCLOG_INFO, "Hello info!");
	if (ret < 0) {
		goto err;
	}

	ret = sclog_message(&systemd_log, SCLOG_DEBUG, "Hello debug!");
	if (ret < 0) {
		goto err;
	}

	sclog_close(&systemd_log);
	return EXIT_SUCCESS;

err:
	sclog_close(&systemd_log);
	return EXIT_FAILURE;
}
