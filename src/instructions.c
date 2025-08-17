#include <instructions.h>
#include <emulator.h>

void clear_screen(struct emulator* emulator)
{
    emulator->draw_screen = 1;
    for(int i = 0; i < CHIP8_HEIGHT * CHIP8_WIDTH; i++) {
        emulator->display[i] = 0x00;
    }
}

void return_from_subroutine(struct emulator* emulator)
{
    emulator->pc = emulator->stack.funcs[emulator->stack.top];
    emulator->stack.top -= 1;
}

void jump_to_location(struct emulator* emulator, const uint16_t op_code)
{
    const uint16_t address_to_jump_to = op_code & 0x0fff;
    emulator->pc = address_to_jump_to;
}

void call_subroutine(struct emulator* emulator, const uint16_t op_code)
{
    const uint16_t subroutine = op_code & 0x0fff;
    emulator->stack.top++;
    emulator->stack.funcs[emulator->stack.top] = emulator->pc;
    emulator->pc = subroutine;
}

void skip_next_instruction(struct emulator* emulator, const uint16_t op_code)
{
    uint8_t v_register = op_code >> 8;
    v_register &= 0x0f;
    const uint8_t value_to_compare = op_code & 0x00ff;
}
