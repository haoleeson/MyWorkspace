#include<stdio.h>
#include<stdint.h>

#define width_msk(width) ((uint32_t)(((uint32_t)0xffffffff) >> (32 - width)))
#define fld_msk( bit, width ) (width_msk(width) << bit)


void test_bf_pltfm_chss_mgmt_port_mac_addr_get() {
    int i;
    uint16_t index, t;
    index = 1;
    uint8_t eeprom_bf_pltfm_mac_base[6] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
    uint8_t mac_info[6] = {0};

    printf("\nBefore\n");
    for (i = 0; i < 6; i++) {
        printf(" %x", eeprom_bf_pltfm_mac_base[i]);
    }

    for (i = 0; i < 6; i++) {
        mac_info[i] = eeprom_bf_pltfm_mac_base[i];
    }

    t = mac_info[5] | (mac_info[4] << 8);

    t = t + index;

    mac_info[5] = t & 0xFF;
    mac_info[4] = (t >> 8) & 0xFF;

    printf("\nAfter\n");
    for (i = 0; i < 6; i++) {
        printf(" %x", mac_info[i]);
    }
}


int main(void) {
    printf("hello word!");
    // uint32_t a = ~fld_msk( 0, 16 );
    // printf("~fld_msk( 0, 16 ) = %d", int(~fld_msk( 0, 16 )));
    test_bf_pltfm_chss_mgmt_port_mac_addr_get();
    return 0;
}