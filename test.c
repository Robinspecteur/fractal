#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <CUnit/Cunit.h>
#include <CUnit/Basic.h>
#include <CUnit/TestRun.h>
#include "libfractal/fractal.h"

void test_
struct fractal* f = fractal_new=("test_fractal", 800, 600, 0.5, -1);

void test_name_fractal(void){
  char *name = fractal_get_name(f);
  CU_ASSERT_PTR_EQUAL(name,f->name);
}

void test_height_fractal(void){
  int height = fractal_get_height(f);
  CU_ASSERT_PTR_EQUAL(height,f->height);
}

void test_width_fractal(void){
  int width = fractal_get_width(f);
  CU_ASSERT_PTR_EQUAL(width,f->width);
}

void test_a_fractal(void){
  double a = fractal_get_a(f);
  CU_ASSERT_PTR_EQUAL(a,f->a);
}

void test_b_fractal(void){
  double b = fractal_get_b(f);
  CU_ASSERT_PTR_EQUAL(b,f->b);
}


fractal_free(f);
write_fractal("test_fractal2 600 800 0.5 -1");

void test_name2_fractal(void){
  char *name = fractal_get_name(f);
  CU_ASSERT_PTR_EQUAL(name,f->name);
}

void test_height2_fractal(void){
  int height = fractal_get_height(f);
  CU_ASSERT_PTR_EQUAL(height,f->height);
}

void test_width2_fractal(void){
  int width = fractal_get_width(f);
  CU_ASSERT_PTR_EQUAL(width,f->width);
}

void test_a2_fractal(void){
  double a = fractal_get_a(f);
  CU_ASSERT_PTR_EQUAL(a,f->a);
}

void test_b2_fractal(void){
  double b = fractal_get_b(f);
  CU_ASSERT_PTR_EQUAL(b,f->b);
}







int setup(void)
{
  return 0;
}
int teardown(void)
{
  return 0;
}

int main()
{
    CU_pSuite pSuite = NULL;
    /* On initialise la suite de tests */
    if(CUE_SUCCESS != CU_initialize_registry())
    {
        return CU_get_error();
    }

    pSuite = CU_add_suite("ma_suite", setup, teardown);
    if(NULL == pSuite)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

    /* On ajoute les tests à la suite. L'ordre est important !
     * test_strlen1 sera exécuté en premier, puis test_strlen2, etc ...*/
    if(NULL == CU_add_test(pSuite, "test_name_fractal", test_name_fractal) ||
       NULL == CU_add_test(pSuite, "test_height_fractal", test_height_fractal)||
       NULL == CU_add_test(pSuite, "test_width_fractal", test_width_fractal)||
       NULL == CU_add_test(pSuite,"test_a_fractal", test_a_fractal)||
       NULL == CU_add_test(pSuite, "test_b_fractal", test_b_fractal)|| )
       NULL == CU_add_test(pSuite, "test_name2_fractal", test_name_fractal) ||
       NULL == CU_add_test(pSuite, "test_height2_fractal", test_height_fractal)||
       NULL == CU_add_test(pSuite, "test_width2_fractal", test_width_fractal)||
       NULL == CU_add_test(pSuite,"test_a2_fractal", test_a_fractal)||
       NULL == CU_add_test(pSuite, "test_b2_fractal", test_b_fractal)|| )
       {
        CU_cleanup_registry();
        return CU_get_error();
       }


    /* On exécute les tests et on vide ensuite la mémoire utilisée par CUnit */
    CU_basic_run_tests();
    CU_basic_show_failures(CU_get_failure_list());
}
