
#include "driver/ledc.h"

ledc_timer_config_t ledc_timer = {
    .duty_resolution = LEDC_TIMER_13_BIT,
    .freq_hz = 5000,
    .speed_mode = LEDC_HIGH_SPEED_MODE,
    .timer_num = LEDC_TIMER_0,
    .clk_cfg = LEDC_AUTO_CLK,
};

ledc_channel_config_t ledc_channel = {.channel = LEDC_CHANNEL_0,
                                      .duty = 0,
                                      .gpio_num = 2,
                                      .speed_mode = LEDC_HIGH_SPEED_MODE,
                                      .hpoint = 0,
                                      .timer_sel = LEDC_TIMER_0};

void fade_led(uint32_t target, int fade_time) {
    ledc_set_fade_with_time(ledc_channel.speed_mode, ledc_channel.channel,
                            target, fade_time);
    ledc_fade_start(ledc_channel.speed_mode, ledc_channel.channel,
                    LEDC_FADE_WAIT_DONE);
}

void configure_led(void) {
    ledc_timer_config(&ledc_timer);
    ledc_channel_config(&ledc_channel);
    ledc_fade_func_install(0);
}