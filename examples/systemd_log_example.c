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

#include "linux/sclog_systemd_sink.h"
#include "sclog.h"

int main(void)
{
	struct sc_log systemd_log;
	struct sc_log_sink systemd_sink;
	if (sc_log_systemd_sink_init(&systemd_sink) != 0) {
		return EXIT_FAILURE;
	}

	if (sc_log_init(&systemd_log, "systemd_log_example", SC_LOG_WARNING, &systemd_sink) != 0) {
		return EXIT_FAILURE;
	}

	int ret = sc_log_message(&systemd_log, SC_LOG_ERROR, "Hello error!");
	if (ret < 0) {
		goto err;
	}

	ret = sc_log_message(&systemd_log, SC_LOG_WARNING, "Hello warning!");
	if (ret < 0) {
		goto err;
	}

	ret = sc_log_message(&systemd_log, SC_LOG_INFO, "Hello info!");
	if (ret < 0) {
		goto err;
	}

	ret = sc_log_message(&systemd_log, SC_LOG_DEBUG, "Hello debug!");
	if (ret < 0) {
		goto err;
	}

	sc_log_close(&systemd_log);
	return EXIT_SUCCESS;

err:
	sc_log_close(&systemd_log);
	return EXIT_FAILURE;
}
