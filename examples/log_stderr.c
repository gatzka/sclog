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

#include "sclog.h"
#include "sclog_stderr_sink.h"

int main(int argc, char* argv[])
{
	(void)argc;

	struct sc_log_sink stderr_sink;
	if (sc_log_stderr_sink_init(&stderr_sink) == false) {
		return EXIT_FAILURE;
	}

	struct sc_log log;
	if (sc_log_init(&log, argv[0], SC_LOG_WARNING, &stderr_sink) == false) {
		return EXIT_FAILURE;
	}

	sc_log_message(&log, SC_LOG_ERROR, "Hello error!");
	sc_log_message(&log, SC_LOG_WARNING, "Hello warning!");
	sc_log_message(&log, SC_LOG_INFO, "Hello info!");
	sc_log_message(&log, SC_LOG_DEBUG, "Hello debug!");

	return EXIT_SUCCESS;
}
