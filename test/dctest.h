#ifndef _DCTEST_H
#define _DCTEST_H

#include <stdio.h>
#include <dcmath.h>
#include <stdint.h>
#include <inttypes.h>


#define _print_type(type) _print_type_##type
#define _print_type_uint32_t PRIu32
#define _print_type_uint64_t PRIu64
#define _print_type_int32_t  PRId32
#define _print_type_int64_t  PRId64

/* 	Series tests. Has a number of input values
	and an expected output values.				 */
#define SERIES_TEST(OUTPUT_TYPE, FUNC, INPUT_TYPE) \
	void FUNC##_series_test () { \
		int test_error = 0; \
		FILE *test_fp = fopen(_to_string(FUNC.txt), "r"); \
		INPUT_TYPE input; \
		OUTPUT_TYPE ret_val, calc_val; \
		for (;;) { \
			if (fscanf(test_fp, \
				"%" _print_type(INPUT_TYPE) "%" _print_type(OUTPUT_TYPE), \
				&input, &ret_val) == EOF) break; \
			calc_val = FUNC(input); \
			if (ret_val != calc_val) { \
				printf("at input %" _print_type(INPUT_TYPE) \
						": expected %" _print_type(OUTPUT_TYPE) \
						", got %" _print_type(OUTPUT_TYPE) "\n", \
					input, ret_val, calc_val); \
				test_error = 1; \
			} \
		} \
		fclose(test_fp); \
		if (!test_error) { \
			puts(_to_string(Series test on FUNC finished without errors!)); \
		} \
	} \


#endif // _DCTEST_H
