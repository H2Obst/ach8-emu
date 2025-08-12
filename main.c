#include <emulator.h>
#include <stdio.h>

int main(void)
{
    struct emulator emu;
    load_font_in_mem(&emu);
    load_instructions_in_ram(&emu);
    emu.pc = MEM_START_PROGRAM;
    uint8_t a = 0xff;
    a+=2;
    printf("%u\n", a);
    return 0;
}
