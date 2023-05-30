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

/* 	Sequence tests. Has a number of input values
	and expected output values.				 */
#define SEQUENCE_TEST(OUTPUT_TYPE, FUNC, INPUT_TYPE) \
	SEQUENCE_TEST_F(OUTPUT_TYPE, FUNC, INPUT_TYPE, FUNC)

#define SEQUENCE_TEST_F(OUTPUT_TYPE, FUNC, INPUT_TYPE, FILENAME) \
	void FUNC##_sequence_test () { \
		int i, passed; \
		FILE *test_fp = fopen(_to_string(FILENAME.txt), "r"); \
		if (test_fp == NULL) { \
			perror(_to_string(Failed to open FUNC.txt)); \
			return; \
		} \
		INPUT_TYPE input; \
		OUTPUT_TYPE ret_val, calc_val; \
		for (i = 0, passed = 0;; i++) { \
			if (fscanf(test_fp, \
				"%" _print_type(INPUT_TYPE) "%" _print_type(OUTPUT_TYPE), \
				&input, &ret_val) == EOF) break; \
			calc_val = FUNC(input); \
			if (ret_val != calc_val) { \
				printf("at input %" _print_type(INPUT_TYPE) \
						": expected %" _print_type(OUTPUT_TYPE) \
						", got %" _print_type(OUTPUT_TYPE) "\n", \
					input, ret_val, calc_val); \
			} else { \
				passed++; \
			} \
		} \
		fclose(test_fp); \
		printf(_to_string(FUNC sequence test result: %d\\%d), passed, i); \
		if (passed == i) { \
			puts("  \033[32mPassed\033[39m"); \
		} else { \
			puts("  \033[31mFailed\033[39m"); \
		} \
	} \


#endif // _DCTEST_H
