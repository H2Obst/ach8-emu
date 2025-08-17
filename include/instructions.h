#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <emulator.h>

/**
 * Clear the display.
 * @param emulator
 */
void clear_screen(struct emulator* emulator);

/**
 * Return from a subroutine.
 *
 * The interpreter sets the program counter to the address at the top of the stack, then subtracts 1 from the stack pointer.
 * @param emulator
 */
void return_from_subroutine(struct emulator* emulator);

/**
 * Jump to location nnn.
 *
 * The interpreter sets the program counter to nnn.
 * @param emulator
 * @param op_code
 */
void jump_to_location(struct emulator* emulator, uint16_t op_code);

/**
 * Call subroutine at nnn.
 *
 * The interpreter increments the stack pointer, then puts the current PC on the top of the stack. The PC is then set to nnn.
 * @param emulator
 * @param op_code
 */
void call_subroutine(struct emulator* emulator, uint16_t op_code);

/**
 * Skip next instruction if Vx = kk.
 *
 * The interpreter compares register Vx to kk, and if they are equal, increments the program counter by 2.
 * @param emulator
 * @param op_code
 */
void skip_next_instruction(struct emulator* emulator, uint16_t op_code);

#endif //INSTRUCTIONS_H
