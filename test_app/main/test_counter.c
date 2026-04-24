#include <limits.h>
#include <stdint.h>

#include "unity.h"

#include "counter.h"

TEST_CASE("counter_init sets value to zero", "[counter]")
{
    counter_t c;
    c.value = 0xDEADBEEFu; /* Pre-poison to ensure init actually writes. */
    counter_init(&c);
    TEST_ASSERT_EQUAL_UINT32(0u, counter_value(&c));
}

TEST_CASE("counter_next returns a monotonically increasing value", "[counter]")
{
    counter_t c;
    counter_init(&c);

    TEST_ASSERT_EQUAL_UINT32(1u, counter_next(&c));
    TEST_ASSERT_EQUAL_UINT32(2u, counter_next(&c));
    TEST_ASSERT_EQUAL_UINT32(3u, counter_next(&c));
    TEST_ASSERT_EQUAL_UINT32(3u, counter_value(&c));
}

TEST_CASE("counter_reset brings the counter back to zero", "[counter]")
{
    counter_t c;
    counter_init(&c);
    for (int i = 0; i < 42; ++i) {
        counter_next(&c);
    }
    TEST_ASSERT_EQUAL_UINT32(42u, counter_value(&c));

    counter_reset(&c);
    TEST_ASSERT_EQUAL_UINT32(0u, counter_value(&c));
}

TEST_CASE("counter_next wraps around at UINT32_MAX", "[counter]")
{
    counter_t c;
    counter_init(&c);
    c.value = UINT32_MAX;

    /* One more increment should wrap to zero (defined unsigned behavior). */
    TEST_ASSERT_EQUAL_UINT32(0u, counter_next(&c));
    TEST_ASSERT_EQUAL_UINT32(0u, counter_value(&c));
}

TEST_CASE("counter APIs tolerate NULL input", "[counter]")
{
    /* These must not crash and must return sensible sentinel values. */
    counter_init(NULL);
    TEST_ASSERT_EQUAL_UINT32(0u, counter_value(NULL));
    TEST_ASSERT_EQUAL_UINT32(0u, counter_next(NULL));
    counter_reset(NULL);
}

TEST_CASE("multiple counters are independent of each other", "[counter]")
{
    /*
     * Regression guard: confirms that counter_t instances carry their own
     * state and that the API never relies on hidden/global storage. Mutating
     * one counter must not affect another, even when they're interleaved.
     */
    counter_t a;
    counter_t b;
    counter_init(&a);
    counter_init(&b);

    TEST_ASSERT_EQUAL_UINT32(1u, counter_next(&a));
    TEST_ASSERT_EQUAL_UINT32(0u, counter_value(&b));

    TEST_ASSERT_EQUAL_UINT32(1u, counter_next(&b));
    TEST_ASSERT_EQUAL_UINT32(2u, counter_next(&b));
    TEST_ASSERT_EQUAL_UINT32(3u, counter_next(&b));

    /* a is still at 1 even though b advanced three times. */
    TEST_ASSERT_EQUAL_UINT32(1u, counter_value(&a));
    TEST_ASSERT_EQUAL_UINT32(3u, counter_value(&b));

    /* Resetting one must not reset the other. */
    counter_reset(&a);
    TEST_ASSERT_EQUAL_UINT32(0u, counter_value(&a));
    TEST_ASSERT_EQUAL_UINT32(3u, counter_value(&b));
}
