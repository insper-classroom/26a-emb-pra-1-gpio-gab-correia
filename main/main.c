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

// Sequência half-step para o 28BYJ-48
const int passos[8][4] = {
    {1,0,0,0},
    {1,1,0,0},
    {0,1,0,0},
    {0,1,1,0},
    {0,0,1,0},
    {0,0,1,1},
    {0,0,0,1},
    {1,0,0,1},
};

void girar_360() {
    for (int i = 0; i < 4096; i++) {
        gpio_put(A, passos[i % 8][0]);
        gpio_put(B, passos[i % 8][1]);
        gpio_put(C, passos[i % 8][2]);
        gpio_put(D, passos[i % 8][3]);
        sleep_ms(2);
    }

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
