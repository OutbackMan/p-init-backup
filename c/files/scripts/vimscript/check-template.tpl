m4_changecom()m4_dnl
m4_define(`M4_LPROJECT_NAME_M4', `m4_esyscmd(echo -n $(basename $(cat ~/.working-on)))')m4_dnl
m4_define(`M4_UPROJECT_NAME_M4', `m4_esyscmd((echo -n $(basename $(cat ~/.working-on))) | tr [a-z] [A-Z])')m4_dnl
m4_define(`M4_DATE_M4', `m4_esyscmd(echo -n $(date +"%B %d, %Y (%Z)"))')m4_dnl
m4_define(`M4_GIT_USER_NAME_M4', `m4_esyscmd(echo -n $(git config user.name))')m4_dnl
m4_define(`M4_GIT_USER_EMAIL_M4', `m4_esyscmd(echo -n $(git config user.email))')m4_dnl
/*******************************************************************************

Name: checks/`'M4_LPROJECT_NAME_M4`'-check.c	Date of Creation: M4_DATE_M4

Maintainer: M4_GIT_USER_NAME_M4 <`'M4_GIT_USER_EMAIL_M4`'>

Developer Notes:


Credits:


*******************************************************************************/

#include "filename.h"

#include <check.h>
#include <stdlib.h>

START_TEST(test_name)
{
	
}
END_TEST

Suite* filename_suite(void)
{
	Suite* suite = suite_create("Filename");
	TCase* core_test_case = tcase_create("Core");

	tcase_add_test(core_test_case, test_name);

	suite_add_tcase(suite, core_test_case);

	return suite;
}

int main(void)
{
	int num_tests_failed = 0;

	Suite* filename_suite = filename_suite();
	SRunner* filename_suite_runner = srunner_create();

	srunner_run_all(filename_suite_runner, CK_NORMAL);
	
	num_tests_failed = srunner_ntests_failed(filename_suite_runner);

	srunner_free(filename_suite_runner);

	return (num_tests_failed == 0) ? EXIT_SUCESS : EXIT_FAILURE;
}
