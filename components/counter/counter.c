#include "counter.h"

#include <stddef.h>

void counter_init(counter_t *c)
{
    if (c == NULL) {
        return;
    }
    c->value = 0;
}

uint32_t counter_value(const counter_t *c)
{
    if (c == NULL) {
        return 0;
    }
    return c->value;
}

uint32_t counter_next(counter_t *c)
{
    if (c == NULL) {
        return 0;
    }
    /* Deliberately allow natural wraparound at UINT32_MAX. */
    c->value += 1u;
    return c->value;
}

void counter_reset(counter_t *c)
{
    counter_init(c);
}
