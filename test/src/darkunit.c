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
/**
 * DarkUnit TDD
 * 
 */
static void sighandler(int signum);
static void resethandlers();
typedef struct test_stats {
    int total;
    int failed;
    int passed;
} test_stats;
test_stats tests;

int TestCountInc() { return tests.total++; }
int TestFailInc()  { return tests.failed++; }
int TestPassInc()  { return tests.passed++; }

/**
 * Describe
 * @param desc title of section
 * @lambda the section code
 * 
 * print a section title & execute
 */
void Describe(char* desc, void (^lambda)()) {
	DSLog("%s\n======================================\n", desc);
	lambda();
}

/**
 * It
 * @param desc title of test
 * @lambda the test code
 * 
 * print a test title & execute
 */
void It(char* desc, void (^lambda)()) {
    fprintf(stdout, "%s - ", desc);
	fflush(stdout);
	lambda();
}

/**
 * print summary info
 */
int Summary() {
    DSLog("Tests run: %d", tests.total);
    DSLog("Tests passed: %d", tests.passed);
    DSLog("Tests failed: %d", tests.failed);
	return tests.failed;
}

/**
 * Handle fatal errors
 */
static void resethandlers() {
	signal(SIGABRT, sighandler);
	signal(SIGFPE, sighandler);
	signal(SIGILL, sighandler);
	signal(SIGINT, sighandler);
	signal(SIGSEGV, sighandler);
	signal(SIGTERM, sighandler);
}
/**
 * Handled fatal error
 */
static void sighandler(int signum) {
	switch(signum) {
		case SIGABRT: 	DSLog("Program Aborted");		break;
		case SIGFPE: 	DSLog("Division by Zero");		break;
		case SIGILL: 	DSLog("Illegal Instruction"); 	break;
		case SIGINT: 	DSLog("Program Interrupted"); 	break;
		case SIGSEGV: 	DSLog("Segmentation fault"); 	break;
		case SIGTERM:	DSLog("Program Terminated"); 	break;
	}
	resethandlers();
	exit(0);
}
/**
 * Set some fatal error traps
 */
void __attribute__((constructor)) DarkUnit() {
	resethandlers();
}

