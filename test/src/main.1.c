#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dark/Foundation.h>
#include <Block.h>
#include "darkunit.h"
#include "main.h"


Either* test_parseNumber(char* s) {
	if (strspn(s, "0123456789") != strlen(s)) {
		return Left($("Invalid Numeral"));
	}
	else {
		return Right($(DSParseLong(s, 10)));
	}
}

void test_parse_success() {
	Either* result = test_parseNumber("420");
	if (IsRight(result)) DSLog("pass"); else DSLog("fail");

	if (LongValue((DSLong*)GetRight(result)) == 420) 
		DSLog("success"); 
	else 
		DSLog("failed");	

}
void test_parse_fail() {
	Either* result = test_parseNumber("xxx");
	if (IsRight(result)) DSLog("pass"); else DSLog("fail");

	if (!strcmp(ToString(GetLeft(result)),"Invalid Numeral")) 
		DSLog("success"); 
	else 
		DSLog("failed");	
}


int main(int argc, char **argv) {

    DSLog("** DaRKSTEP Test** \n");
	Maybe* x = Just($("frodo"));

	test_parse_success();
	test_parse_fail();

	auto ss = NewOption(nullptr);

	auto Str = NewOption($("A String"));

	DSObject* val;// = Some(Str);

	if (!IsEmpty(Str)) {
		val = Some(Str);
		DSLog("val = %$", val);
	} else {
		DSLog("Not Found");
	}

    return 0;
}

