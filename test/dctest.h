#ifndef _DCTEST_H
#define _DCTEST_H

#include <stdio.h>
#include <dcmath.h>
#include <stdint.h>
#include <inttypes.h>


#define _print_type(type) _print_type_##type
#define _print_type_uint32_t PRIu32
#define _print_type_uint64_t PRIu64
#define _print_type_int8_t   PRId8
#define _print_type_int32_t  PRId32
#define _print_type_int64_t  PRId64
#define _print_type_size_t   "zu"

#define _scan_type(type) _scan_type_##type
#define _scan_type_uint32_t  SCNu32
#define _scan_type_uint64_t  SCNu64
#define _scan_type_int8_t    SCNd8
#define _scan_type_int32_t   SCNd32
#define _scan_type_int64_t   SCNd64
#define _scan_type_size_t    "zu"


/* 	Sequence tests. Has a number of input values
	and expected output values.						*/
#define SEQUENCE_TEST(OUTPUT_TYPE, FUNC, INPUT_TYPE) \
	SEQUENCE_TEST_F(OUTPUT_TYPE, FUNC, INPUT_TYPE, FUNC)

#define SEQUENCE_TEST_A(OUTPUT_TYPE, FUNC) \
	SEQUENCE_TEST_AF(OUTPUT_TYPE, FUNC, FUNC)

#define SEQUENCE_TEST_F(OUTPUT_TYPE, FUNC, INPUT_TYPE, FILENAME) \
	SEQUENCE_TEST_GENERAL(OUTPUT_TYPE, FUNC, INPUT_TYPE, FILENAME, FUNC(input), )

#define SEQUENCE_TEST_AF(OUTPUT_TYPE, FUNC, FILENAME) \
	SEQUENCE_TEST_GENERAL(OUTPUT_TYPE, FUNC, size_t, FILENAME, array[input], OUTPUT_TYPE *array)

#define SEQUENCE_TEST_GENERAL(OUTPUT_TYPE, FUNC, INPUT_TYPE, FILENAME, SEQ_CALL, ARGUMENT) \
	void FUNC##_sequence_test (ARGUMENT) { \
		int i, passed; \
		INPUT_TYPE input; \
		OUTPUT_TYPE ret_val, calc_val; \
		FILE *test_fp = fopen(_to_string(data/FILENAME.txt), "r"); \
		if (test_fp == NULL) { \
			perror(_to_string(Failed to open FILENAME.txt)); \
			return; \
		} \
		for (i = 0, passed = 0;; i++) { \
			if (fscanf(test_fp, \
				"%" _scan_type(INPUT_TYPE) "%" _scan_type(OUTPUT_TYPE), \
				&input, &ret_val) == EOF) break; \
			calc_val = SEQ_CALL; \
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
	}


/* 	Set tests. Has a list of numbers and expects 
	output 1 if the number is in the list, otherwise 0 */
#define SET_TEST_F(FUNC, INPUT_TYPE, FILENAME) \
	SET_TEST_FNS(FUNC, INPUT_TYPE, FILENAME, set, 0)

#define SET_TEST_FNS(FUNC, INPUT_TYPE, FILENAME, TEST_NAME, START) \
	void FUNC##_##TEST_NAME##_test () { \
		int i, passed, output, expected; \
		INPUT_TYPE input, next; \
		FILE *test_fp = fopen(_to_string(data/FILENAME.txt), "r"); \
		if (test_fp == NULL) { \
			perror(_to_string(Failed to open FILENAME.txt)); \
			return; \
		} \
		if (fscanf(test_fp, \
					"%" _scan_type(INPUT_TYPE), &next) == EOF) { \
			fprintf(stderr, _to_string(FILENAME.txt is empty\n)); \
			return; \
		} \
		input = START; \
		for (i = 0, passed = 0;; i++, input++) { \
			if (input > next) { \
				if (fscanf(test_fp, \
					"%" _scan_type(INPUT_TYPE), &next) == EOF) break; \
			} \
			if (input == next) expected = 1; \
			else expected = 0; \
			output = FUNC(input); \
			if (expected != output) { \
				printf("at input %" _print_type(INPUT_TYPE) \
						": expected %d, got %d\n", input, expected, output); \
			} else { \
				passed++; \
			} \
		} \
		fclose(test_fp); \
		printf(_to_string(FUNC TEST_NAME test result: %d\\%d), passed, i); \
		if (passed == i) { \
			puts("  \033[32mPassed\033[39m"); \
		} else { \
			puts("  \033[31mFailed\033[39m"); \
		} \
	}


#define FALSE_TEST_FN(FUNC, INPUT_TYPE, FILENAME, TEST_NAME) \
	EXPECTED_TEST_FN(0, FUNC, INPUT_TYPE, FILENAME, TEST_NAME)

#define TRUE_TEST_FN(FUNC, INPUT_TYPE, FILENAME, TEST_NAME) \
	EXPECTED_TEST_FN(1, FUNC, INPUT_TYPE, FILENAME, TEST_NAME)

#define EXPECTED_TEST_FN(VALUE, FUNC, INPUT_TYPE, FILENAME, TEST_NAME) \
	void FUNC##_##TEST_NAME##_test () { \
		int i, passed, output; \
		INPUT_TYPE input; \
		FILE *test_fp = fopen(_to_string(data/FILENAME.txt), "r"); \
		if (test_fp == NULL) { \
			perror(_to_string(Failed to open FILENAME.txt)); \
			return; \
		} \
		for (i = 0, passed = 0;; i++) { \
			if (fscanf(test_fp, \
				"%" _scan_type(INPUT_TYPE), &input) == EOF) break; \
			output = FUNC(input); \
			if (output != VALUE) { \
				printf("at input %" _print_type(INPUT_TYPE) \
					_to_string(: expected VALUE, got %d\n), input, output); \
			} else { \
				passed++; \
			} \
		} \
		fclose(test_fp); \
		printf(_to_string(FUNC TEST_NAME test result: %d\\%d), passed, i); \
		if (passed == i) { \
			puts("  \033[32mPassed\033[39m"); \
		} else { \
			puts("  \033[31mFailed\033[39m"); \
		} \
	}


#endif // _DCTEST_H
