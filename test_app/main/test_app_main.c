#include <stdio.h>
#include <stdlib.h>

#include "unity.h"
#include "unity_test_runner.h"

/*
 * Entry point for the Unity-based test runner.
 *
 * When built for a real ESP target this is the usual FreeRTOS app_main; when
 * built for the `linux` host target (IDF_TARGET=linux) it is invoked as a
 * normal function at process startup, which lets CI run the tests natively
 * without any hardware.
 */
void app_main(void)
{
    UNITY_BEGIN();
    unity_run_all_tests();
    int failures = UNITY_END();

    /*
     * Make sure the host-target binary exits with a non-zero status when a
     * test case fails. On a real chip this is a no-op because the function
     * never returns there (FreeRTOS scheduler is already running).
     */
    exit(failures == 0 ? 0 : 1);
}
