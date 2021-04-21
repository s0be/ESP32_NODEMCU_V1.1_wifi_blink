#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

typedef struct callback_handler {
    void (*got_ip)();
    void (*lost_ip)();
} callback_handler_t;

void wifi_init(char *ssid, char *pass, callback_handler_t *cb);