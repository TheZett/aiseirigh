/*
 * Copyright (c) 2023 Davee Morgan
 *
 * Use of this source code is governed by a MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT
 */

// dynamically generated by LK
#include <lk_loader_lk.h>
#include <config.h>

#include <cpu.h>
#include <emcddr.h>
#include <gpio.h>
#include <sysreg.h>
#include <syscon.h>
#include <uart.h>

#define LK_BINARY_START (MEMBASE)

void memset(void *dst, int val, unsigned int len)
{
    for (unsigned int i = 0; i < len; ++i) {
        ((unsigned char *)dst)[i] = val;
    }
}

void memcpy(void *dst, void *src, unsigned int len)
{
    for (unsigned int i = 0; i < len; ++i) {
        ((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
    }
}

int memcmp(void *s1, void *s2, unsigned int len)
{
    int diff = 0;

    for (unsigned int i = 0; i < len; ++i) {
        diff = ((unsigned char *)s1)[i] - ((unsigned char *)s2)[i];

        if (diff != 0) {
            break;
        }
    }

    return diff;
}

int main(void)
{
    // we want to perform the minimal setup possible in order to load the lk app
    // into DDR and hand over execution. once we've handed over execution then
    // lk can initialise the rest of the hardware.
    sysreg_busclk_enable(BUSCLK_APB);
    gpio_init();
    gpio_set_port_mode(GPIO_PORT_LCD_RESET, GPIO_MODE_OUTPUT);
    gpio_clear(GPIO_PORT_LCD_RESET);

    // initialise syscon and perform the handshake routine to unlock additional
    // functionality on newer models. 
    syscon_init();
    syscon_handshake_unlock();

    // power up the headphone remote and setup UART through it.
	syscon_ctrl_hr_power(1);
	uart_init(UART_HPREMOTE, 115200);
	uart_puts(UART_HPREMOTE, "lk loader start...\n");

    // initialise the DDR as a 32 MB source. if the LK app wants to support the
    // 64 MB variants then it must do so itself.
    emcddr_init(DDR_TYPE_32MB);

    // the LK binary is stored as an array. it is expected to be loaded at the
    // address LK_BINARY_START. copy the binary there, writeback the dcache
    // and transition execution
    for (unsigned int offset = 0; offset < size_lk; offset += 4) {
        unsigned int *src = (unsigned int *)(&lk[offset]);
        unsigned int *dst = (unsigned int *)(LK_BINARY_START + offset);
        *dst = *src;
    }

    cpu_dcache_wb_inv_all();
    cpu_icache_inv_all();

    int (* lk_entry)(void) = (void *)LK_BINARY_START;
    return lk_entry();
}