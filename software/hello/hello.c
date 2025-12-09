/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>
#include <metal/pmp.h>

extern void switch_to_user_mode();

void set_pmp() {
    struct metal_pmp *pmp = metal_pmp_get_device();
    if(!pmp) {
        printf("No PMP device found\n");
        return;
    }
    metal_pmp_init(pmp);
    
    // Set PMP to allow all access to all memory regions
    metal_pmp_set_region(
        pmp,
        0,
        (struct metal_pmp_config){
            .R=1,
            .W=1,
            .X=1,
            .A=METAL_PMP_NAPOT,
            .L=METAL_PMP_UNLOCKED
        },
        0xFFFFFFFF
    );
}

int main() {

    printf("Setting the PMP configuration...\n");
    // set_pmp();

    printf("Trying to switch to user mode...\n");
    switch_to_user_mode();

    printf("Hello, World!\n");
}
