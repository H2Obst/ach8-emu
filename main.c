#include <emulator.h>
#include <stdio.h>

int main(void)
{
    // struct emulator emulator;
    // setup_emulator(&emulator);
    // launch(&emulator);
    uint16_t op_code = 0x3faa;
    uint8_t v_register = op_code >> 8;
    v_register &= 0x0f;
    uint8_t value_to_compare = op_code & 0x00ff;
    printf("%u\n", v_register);
    return 0;
}
