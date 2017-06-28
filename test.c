// (c) Copyright 2017, Sean Connelly (@voidqk), http://syntheti.cc
// MIT License
// Project Home: https://github.com/voidqk/nvqm

//
// This file is used to run tests against the NVQM C library, specifically the fixed-point functions
//
// It includes "nvqm.c" directly, so it's easy to compile:
//
// $ clang      \
//     -O2      \ # optimization level 2
//     -Wall    \ # warn on anything
//     -fwrapv  \ # wrap overflow
//     -o test  \ # output to `test`
//     test.c     # the single file that needs to be compiled
//

#include "nvqm.c"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

static int err_rang(const char *hint, xang (*est_func)(xint v), float (*ans_func)(float v),
	xint min, xint max){
	int max_err = -1;
	int64_t dot = ((int64_t)max - (int64_t)min) / 75;
	printf("_________________________________ Progress ________________________________\n");
	for (int64_t i = min; i <= max; i++){
		if (i % dot == 0){
			printf(".");
			fflush(stdout);
		}
		xint x = (xint)i;
		xang est = est_func(x);
		xang ans = xang_fromfloat(ans_func(xint_tofloat(x)));
		ans = ((ans % XANG360) + XANG360) % XANG360;
		int diff = est - ans;
		if (diff < 0)
			diff = -diff;
		if (diff > XANG180)
			diff = XANG360 - diff;
		if (diff > max_err)
			max_err = diff;
	}
	printf("\n\n"
		"Results\n"
		"-----------------------------------\n"
		"Error Test   : %s(i)\n"
		"Range `i`    : %f to %f\n"
		"Maximum Error: +-%f radians\n"
		"               +-%d / %d units\n",
		hint, xint_tofloat(min), xint_tofloat(max),
		xang_todouble(max_err), max_err, XANG360
	);
	return 0;
}

static int err_aang(const char *hint, xint (*est_func)(xang v), float (*ans_func)(float v),
	int32_t min, int32_t max){
	int max_err = -1;
	int64_t dot = ((int64_t)max - (int64_t)min) / 75;
	printf("_________________________________ Progress ________________________________\n");
	for (int64_t i = min; i <= max; i++){
		if (i % dot == 0){
			printf(".");
			fflush(stdout);
		}
		xang x = (xang)i;
		xint est = est_func(x);
		xint ans = xint_fromfloat(ans_func(xang_tofloat(x)));
		int diff = est - ans;
		if (diff < 0)
			diff = -diff;
		if (diff > max_err)
			max_err = diff;
	}
	printf("\n\n"
		"Results\n"
		"-----------------------------------\n"
		"Error Test   : %s(i)\n"
		"Range `i`    : %f to %f radians\n"
		"               %d to %d units\n"
		"Maximum Error: +-%f radians\n"
		"               +-%d / %d units\n",
		hint, xang_tofloat(min), xang_tofloat(max), min, max,
		xang_todouble(max_err), max_err, XANG360
	);
	return 0;
}

static int err_xint(const char *hint, xint (*est_func)(xint v), float (*ans_func)(float v),
	xint min, xint max){
	int max_err = -1;
	int64_t dot = ((int64_t)max - (int64_t)min) / 75;
	printf("_________________________________ Progress ________________________________\n");
	for (int64_t i = min; i <= max; i++){
		if (i % dot == 0){
			printf(".");
			fflush(stdout);
		}
		xint x = (xint)i;
		xint est = est_func(x);
		xint ans = xint_fromfloat(ans_func(xint_tofloat(x)));
		int diff = est - ans;
		if (diff < 0)
			diff = -diff;
		if (diff > max_err)
			max_err = diff;
	}
	printf("\n\n"
		"Results\n"
		"-----------------------------------\n"
		"Error Test   : %s(i)\n"
		"Range `i`    : %f to %f\n"
		"Maximum Error: +-%f\n"
		"               +-%d / %d\n",
		hint, xint_tofloat(min), xint_tofloat(max),
		xang_todouble(max_err), max_err, XINT1
	);
	return 0;
}

static int err_pow(){
	int max_err = -1;
	int64_t a_min = 0;
	int64_t a_max = 512;
	int64_t b_min = -XINT1 + 1;
	int64_t b_max = -XINT1 + 1;
	int64_t step = 1;
	int64_t dot = (a_max - a_min) / (75 * step);
	printf("_________________________________ Progress ________________________________\n");
	for (int64_t i = a_min; i <= a_max; i += step){
		if (i % dot == 0){
			//printf(".");
			fflush(stdout);
		}
		xint x = (xint)i;
		for (int64_t j = b_min; j <= b_max; j += step){
			xint y = (xint)j;
			xint est = xint_pow(i, j);
			xint ans = xint_fromfloat(num_pow(xint_tofloat(x), xint_tofloat(j)));
			int diff = est - ans;
			if (diff < 0)
				diff = -diff;
			if (diff > max_err)
				max_err = diff;
		}
	}
	printf("\n\n"
		"Results\n"
		"-----------------------------------\n"
		"Error Test   : pow(i, j)\n"
		"Range `i`    : %f to %f\n"
		"Range `j`    : %f to %f\n"
		"Step         : %f\n"
		"Maximum Error: +-%f\n"
		"               +-%d / %d\n",
		xint_tofloat(a_min), xint_tofloat(a_max),
		xint_tofloat(b_min), xint_tofloat(b_max),
		xint_tofloat(step),
		xang_todouble(max_err), max_err, XINT1
	);
	return 0;
}

static float num_atan(float a){ return num_atan2(a, 1); }
static xint xint_atan(xint a){ return xint_atan2(a, XINT1); }

static int gen_sin_lut(){
	// generate the sin lookup table
	char buf[100];
	int pos = 4;
	printf("\t");
	for (int i = 0; i < XANG360; i++){
		xint x = xint_fromfloat(num_sin(xang_tofloat(i)));
		int sz = snprintf(buf, sizeof(buf), i == XANG360 - 1 ? "%d" : "%d, ", x);
		if (sz + pos > 101){
			printf("\n\t%s", buf);
			pos = sz + 4;
		}
		else{
			printf("%s", buf);
			pos += sz;
		}
	}
	return 0;
}

static int gen_tan_lut(){
	// generate the tan lookup table
	char buf[100];
	int pos = 4;
	printf("\t");
	for (int i = 0; i < XANG180; i++){
		xint x = xint_fromfloat(num_tan(xang_tofloat(i)));
		int sz = snprintf(buf, sizeof(buf), i == XANG180 - 1 ? "%d" : "%d, ", x);
		if (sz + pos > 101){
			printf("\n\t%s", buf);
			pos = sz + 4;
		}
		else{
			printf("%s", buf);
			pos += sz;
		}
	}
	return 0;
}

static void print_help(){
	printf(
		"NVQM test suite\n\n"
		"Please select a test via:\n"
		"  $ ./test <testname> [params...]\n\n"
		"Margin of Error Tests:\n\n"
		"  Test Name     Tested Function   Correct Function\n"
		"  ---------     ----------------  ----------------\n"
		"  err_acos  ->  xint_acos(i)      num_acos(i)\n"
		"  err_asin  ->  xint_asin(i)      num_asin(i)\n"
		"  err_atan  ->  xint_atan2(i, 1)  num_atan2(i, 1)\n"
		"  err_atan2 ->  xint_atan2(i, j)  num_atan2(i, j)\n"
		"  err_cos   ->  xint_cos(i)       num_cos(i)\n"
		"  err_exp   ->  xint_exp(i)       num_exp(i)\n"
		"  err_log   ->  xint_log(i)       num_log(i)\n"
		"  err_pow   ->  xint_pow(i, j)    num_pow(i, j)\n"
		"  err_sin   ->  xint_sin(i)       num_sin(i)\n"
		"  err_sqrt  ->  xint_sqrt(i)      num_sqrt(i)\n"
		"  err_tan   ->  xint_tan(i)       num_tan(i)\n"
	);
}

static const char *testname;
bool T(const char *test){ return strcmp(testname, test) == 0; }
int main(int argc, char **argv){
	testname = argv[1];
	if (T("err_acos" )) return err_rang("acos" , xint_acos, num_acos,       -XINT1,         XINT1);
	if (T("err_asin" )) return err_rang("asin" , xint_asin, num_asin,       -XINT1,         XINT1);
	if (T("err_atan" )) return err_rang("atan" , xint_atan, num_atan,      XINTMIN,       XINTMAX);
	//if (T("err_atan2")) return err_atan2();
	if (T("err_cos"  )) return err_aang("cos"  , xint_cos , num_cos ,            0,       XANG360);
	if (T("err_exp"  )) return err_xint("exp"  , xint_exp , num_exp ,      XINTMIN,    0x000A65AF);
	if (T("err_log"  )) return err_xint("log"  , xint_log , num_log ,            0,       XINTMAX);
	if (T("err_pow"  )) return err_pow();
	if (T("err_sin"  )) return err_aang("sin"  , xint_sin , num_sin ,            0,       XANG360);
	if (T("err_sqrt" )) return err_xint("sqrt" , xint_sqrt, num_sqrt,            0,       XINTMAX);
	if (T("err_tan"  )) return err_aang("tan"  , xint_tan , num_tan ,            0,       XANG180);
	print_help();
	fprintf(stderr, "Invalid test: %s\n", argv[1]);
	return 1;
}
