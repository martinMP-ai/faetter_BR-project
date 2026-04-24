#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A tiny monotonically-increasing counter. Kept intentionally simple so that
 * it can serve as the subject of the project's example Unity tests.
 */
typedef struct {
    uint32_t value;
} counter_t;

/** Initialize @p c to zero. */
void counter_init(counter_t *c);

/** Return the current value of @p c without modifying it. */
uint32_t counter_value(const counter_t *c);

/**
 * Increment @p c and return the new value. Wraps at UINT32_MAX back to 0.
 */
uint32_t counter_next(counter_t *c);

/** Reset @p c back to zero. */
void counter_reset(counter_t *c);

#ifdef __cplusplus
}
#endif
