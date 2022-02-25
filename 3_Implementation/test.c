#include "unity.h"
#include "snake_game.h"

void test_mainMenu(void);
void test_mainMenu1(void);
void test_inputScore(void);

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
void test_inputScore(void){
    char highScoreName[20]="Vishnu"
    int scores[5] = 20;
    TEST_ASSERT_EQUAL("Vishnu", highScoreName);
    // TEST_ASSERT_EQUAL(20, scores);

    TEST_ASSERT_EQUAL_INT(20, scores);

}
int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_mainMenu);
    RUN_TEST(test_mainMenu);
    RUN_TEST(test_inputScore);
    return UNITY_END();
}