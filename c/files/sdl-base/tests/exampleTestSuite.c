#include "tests/test-helpers.h"
// define TEST_SUCCESS = 0
// define TEST_FAILURE = !TEST_SUCCESS

int exampleTestSuite(int argc, char* argv[argc + 1])
{
	if (strcmp(argv[1], "example_test_age")) {
		return example_test_age();
	}

	return 0;
}

int example_test_age(void)
{
	
}
