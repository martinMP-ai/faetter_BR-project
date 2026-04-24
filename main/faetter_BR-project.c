#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "counter.h"

static const char *TAG = "faetter_BR";

void app_main(void)
{
    ESP_LOGI(TAG, "Application started on ESP32-H2");

    counter_t heartbeat;
    counter_init(&heartbeat);

    while (true) {
        ESP_LOGI(TAG, "Heartbeat #%lu", (unsigned long)counter_next(&heartbeat));
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
