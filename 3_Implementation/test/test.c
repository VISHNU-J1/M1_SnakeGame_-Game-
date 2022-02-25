#include "unity.h"
#include "snake_game.h"

void exitYN(void);
void test_inputScore(void);

void setUp(void){};

void tearDown(void){};


void test_inputScore(void){
    char highScoreName[20]="Vishnu"
    int scores[5] = 20;
    TEST_ASSERT_EQUAL("Vishnu", highScoreName);
    // TEST_ASSERT_EQUAL(20, scores);

    TEST_ASSERT_EQUAL_INT(20, scores);

}

void test_exitYN(void)
{
	char pressed;
	pressed == 'y';
    TEST_ASSERT_EACH_EQUAL_CHAR("y", pressed);

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_exitYN);
    RUN_TEST(test_inputScore);
    return UNITY_END();
}