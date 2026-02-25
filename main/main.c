/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define LED_PIN   14
#define BOTAO_PIN 16

#define A 2
#define B 3
#define C 4
#define D 5

// Sequência full-step (como no guia HowToMechatronics)
const int passos[4][4] = {
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 1},
    {1, 0, 0, 1},
};

void girar_360() {
    for (int i = 0; i < 2048; i++) {  // 2048 passos = 360°
        gpio_put(A, passos[i % 4][0]);
        gpio_put(B, passos[i % 4][1]);
        gpio_put(C, passos[i % 4][2]);
        gpio_put(D, passos[i % 4][3]);
        sleep_ms(2);
    }
    // Desliga bobinas
    gpio_put(A, 0); gpio_put(B, 0);
    gpio_put(C, 0); gpio_put(D, 0);
}

int main() {
    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(BOTAO_PIN);
    gpio_set_dir(BOTAO_PIN, GPIO_IN);
    gpio_pull_up(BOTAO_PIN);

    gpio_init(A); gpio_set_dir(A, GPIO_OUT);
    gpio_init(B); gpio_set_dir(B, GPIO_OUT);
    gpio_init(C); gpio_set_dir(C, GPIO_OUT);
    gpio_init(D); gpio_set_dir(D, GPIO_OUT);

    while (true) {
        if (!gpio_get(BOTAO_PIN)) {
            while (!gpio_get(BOTAO_PIN)); 

            printf("Girando!\n");
            gpio_put(LED_PIN, 1);   
            girar_360();             
            gpio_put(LED_PIN, 0);   
        }
    }
}
