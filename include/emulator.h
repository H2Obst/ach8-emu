#ifndef EMULATOR_H
#define EMULATOR_H

#include <stdint.h>

#define MAX_STACK_SIZE 16
#define MEM_START_PROGRAM 0x200

struct address_stack {
    uint16_t funcs[MAX_STACK_SIZE];
    uint8_t top;
};

struct emulator {
    uint8_t ram[4096];
    uint16_t pc;
    uint16_t index_register;
    struct address_stack stack;
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint8_t variables[16];
};

void print_emulator(const struct emulator* emulator);
void load_font_in_mem(struct emulator* emulator);
void load_instructions_in_ram(struct emulator* emulator);
uint16_t get_op_code(const struct emulator* emulator);
void run_op_code(struct emulator* emulator, uint16_t op_code);

#endif //EMULATOR_H
