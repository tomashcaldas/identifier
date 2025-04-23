#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(comissao)
{
  RUN_TEST_CASE(comissao, TestComissao1);
  RUN_TEST_CASE(comissao, TestComissao2);
}
