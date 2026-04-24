#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "faetter_BR";

void app_main(void)
{
    ESP_LOGI(TAG, "Application started on ESP32-H2");

    uint32_t count = 0;
    while (true) {
        ESP_LOGI(TAG, "Heartbeat #%lu", (unsigned long)count++);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
