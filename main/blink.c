/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>

#include "demo-led.h"
#include "demo-wifi.h"

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "sdkconfig.h"

TaskHandle_t fade_task = NULL;
static uint32_t s_led_state = 0;

void fade_task_work() {
    while(true) {
        if (s_led_state) {
            s_led_state = 0;
        } else {
            s_led_state = 4000;
        }
        fade_led(s_led_state, 500);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void  got_ip() {
    ESP_LOGI("tag", "Got IP");
    if(fade_task == NULL) {
        xTaskCreate(fade_task_work, "fader", 4096, NULL, 5, &fade_task);
    }
}

void  lost_ip() { 
    ESP_LOGI("tag", "lost IP");
    vTaskDelete(fade_task);
    fade_task = NULL;
}

callback_handler_t cb = {
    .got_ip = &got_ip,
    .lost_ip = &lost_ip
};

void app_main(void)
{
    configure_led();
    
    wifi_init("ssid", "password", &cb);

    while (1) {
        vTaskDelay(portMAX_DELAY);        
    }
}
