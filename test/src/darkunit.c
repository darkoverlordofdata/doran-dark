/*******************************************************************
** This code is part of the Dark Framework.
**
MIT License

Copyright (c) 2018 Dark Overlord of Data

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************/
#include "darkunit.h"

test_stats tests;

/**
 * print a section title
 */
void Describe(char* desc, void (^lambda)())
{
	printf("%s\n======================================\n\n", desc);
	lambda();
}

/**
 * Handle fatal errors
 */
static void sighandler(int signum) {
	switch(signum) {
		case SIGABRT: error("Program Aborted");	break;
		case SIGFPE: error("Division by Zero");	break;
		case SIGILL: error("Illegal Instruction"); break;
		case SIGINT: error("Program Interrupted"); break;
		case SIGSEGV: error("Segmentation fault"); break;
		case SIGTERM: error("Program Terminated"); break;
	}
	/* generate core dump */
	signal(signum, SIG_DFL);
	// kill(getpid(), signum);
}
/**
 * Set some fatal error traps
 */
void __attribute__((constructor)) DarkUnit()
{
	signal(SIGABRT, sighandler);
	signal(SIGFPE, sighandler);
	signal(SIGILL, sighandler);
	signal(SIGINT, sighandler);
	signal(SIGSEGV, sighandler);
	signal(SIGTERM, sighandler);

}

