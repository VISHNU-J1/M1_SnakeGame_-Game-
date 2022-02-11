#include "unity.h"
#include "snake_game.h"

void setUp(void){};

void tearDown(void){};
void test_mainMenu(void)
{
    TEST_ASSERT_GREATER_THAN_INT(0,mainMenu());
}
void test_mainMenu1(void)
{
    TEST_ASSERT_LESS_OR_EQUAL_INT(1,mainMenu());
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_mainMenu);
    RUN_TEST(test_mainMenu);
    return UNITY_END();
}