/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>
#include <metal/pmp.h>

#define CONFIG_TO_INT(_config) (*((char *)&(_config)))

extern void switch_to_user_mode();

void set_pmp() {
    
    struct metal_pmp_config cfg = {
        .R=1,
        .W=1,
        .X=1,
        .A=METAL_PMP_NAPOT,
        .L=METAL_PMP_UNLOCKED
    };

    uint32_t address = 0xFFFFFFFF;
    unsigned int region = 0;
    size_t cfgmask = (0xFF << (8 * (region % 4)));
    size_t pmpcfg = (CONFIG_TO_INT(cfg) << (8 * (region % 4)));
    
    __asm__("csrw pmpaddr0, %[addr]" ::[addr] "r"(address) :);
    __asm__("csrc pmpcfg0, %[mask]" ::[mask] "r"(cfgmask) :);
    __asm__("csrs pmpcfg0, %[cfg]" ::[cfg] "r"(pmpcfg) :);
}

int main() {

    printf("Setting the PMP configuration...\n");
    set_pmp();

    printf("Trying to switch to user mode...\n");
    switch_to_user_mode();

    printf("Hello, World!\n");
}
