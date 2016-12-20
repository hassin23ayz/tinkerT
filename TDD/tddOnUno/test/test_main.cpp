#include <Arduino.h>
#include <unity.h>

#ifdef UNIT_TEST

#define BLINKPIN 17

void test_led_builtin_pin_number(void) {
    TEST_ASSERT_EQUAL(BLINKPIN, 13);
}


void setup() {
    UNITY_BEGIN();    // IMPORTANT LINE!
    RUN_TEST(test_led_builtin_pin_number); //unit testing the Pin number
    UNITY_END();
}


void loop()
{}

#endif
