#ifndef EMULATOR_H
#define EMULATOR_H

#include <stdint.h>

#define MAX_STACK_SIZE 16
#define MEM_START_PROGRAM 0x200
#define RAM_SIZE 4096

#define CHIP8_WIDTH 64
#define CHIP8_HEIGHT 32
#define PIXEL_SCALE 10

struct address_stack {
    uint16_t funcs[MAX_STACK_SIZE];
    uint8_t top;
};

struct emulator {
    uint8_t ram[RAM_SIZE];
    uint16_t pc;
    uint16_t index_register;
    struct address_stack stack;
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint8_t variables[16];
    uint8_t display[CHIP8_WIDTH * CHIP8_HEIGHT];
    uint8_t draw_screen : 1;
};

void print_emulator(const struct emulator* emulator);
void load_font_in_mem(struct emulator* emulator);
void load_instructions_in_ram(struct emulator* emulator);
uint16_t get_op_code(struct emulator* emulator);
void run_op_code(struct emulator* emulator, uint16_t op_code);
void setup_emulator(struct emulator* emulator);
void launch();

#endif //EMULATOR_H
