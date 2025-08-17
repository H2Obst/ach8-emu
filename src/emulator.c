#include <emulator.h>
#include <instructions.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <SDL3/SDL.h>

void load_font_in_mem(struct emulator* const emulator)
{
    const int fonts_start = 0x50;
    const uint16_t fonts[] = {
        0xf0, 0x90, 0x90, 0x90, 0xf0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xf0, 0x10, 0xf0, 0x80, 0xf0, // 2
        0xf0, 0x10, 0x70, 0x10, 0xf0, // 3
        0x90, 0x90, 0xf0, 0x10, 0x10, // 4
        0xf0, 0x80, 0xf0, 0x10, 0xf0, // 5
        0xf0, 0x80, 0xf0, 0x90, 0xf0, // 6
        0xf0, 0x10, 0x20, 0x40, 0x40, // 7
        0xf0, 0x90, 0xf0, 0x90, 0xf0, // 8
        0xf0, 0x90, 0xf0, 0x10, 0xf0, // 9
        0xf0, 0x90, 0xf0, 0x90, 0x90, // A
        0xe0, 0x90, 0xe0, 0x90, 0xe0, // B
        0xf0, 0x80, 0x80, 0x80, 0xf0, // C
        0xe0, 0x90, 0x90, 0x90, 0xe0, // D
        0xf0, 0x80, 0xf0, 0x80, 0xf0, // E
        0xf0, 0x80, 0xf0, 0x80, 0x80  // F
    };
    memcpy(emulator->ram + 0x50, fonts, fonts_start);
}

void load_instructions_in_ram(struct emulator* const emulator)
{
    FILE *rom = fopen("/home/alex/CLionProjects/pipicap/IBM_logo.ch8", "rb");
    if(!rom) {
        fprintf(stderr, "Failed to open ROM");
        return;
    }
    fread(&emulator->ram[MEM_START_PROGRAM], 1, RAM_SIZE - MEM_START_PROGRAM, rom);
    fclose(rom);
}

uint16_t get_op_code(struct emulator* const emulator)
{
    uint16_t op_code = emulator->ram[emulator->pc] << 8 | emulator->ram[emulator->pc + 1];
    emulator->pc += 2;
    if(emulator->pc >= RAM_SIZE) {  // TODO verify if that is necessary
        emulator->pc = MEM_START_PROGRAM;
    }
    return op_code;
}

void run_op_code(struct emulator* const emulator, const uint16_t op_code)
{
    uint8_t function_nibble;
    switch(op_code & 0xf000) {
        case 0x0000:
            switch(op_code) {
                case 0x00e0:
                    clear_screen(emulator);
                    break;
                case 0x00ee:
                    return_from_subroutine(emulator);
                    break;
                default:
                    printf("SYS addr\n");
                    break;
            }
            break;
        case 0x1000:
            jump_to_location(emulator, op_code);
            break;
        case 0x2000:
            printf("CALL\n");
            break;
        case 0x3000:
            printf("SE Vx, byte\n");
            break;
        case 0x4000:
            printf("SNE Vx, byte\n");
            break;
        case 0x5000:
            printf("SE Vx, Vy\n");
            break;
        case 0x6000:
            printf("LD Vx, byte\n");
            break;
        case 0x7000:
            printf("ADD Vx, byte\n");
            break;
        case 0x8000:
            function_nibble = op_code & 0x0001;
            switch(function_nibble) {
                case 0x0:
                    printf("LD Vx, Vy\n");
                    break;
                case 0x1:
                    printf("OR Vx, Vy\n");
                    break;
                case 0x2:
                    printf("AND Vx, Vy\n");
                    break;
                case 0x3:
                    printf("XOR Vx, Vy\n");
                    break;
                case 0x4:
                    printf("ADD Vx, Vy\n");
                    break;
                case 5:
                    printf("SUB Vx, Vy\n");
                    break;
                case 0x6:
                    printf("SHR Vx {, Vy}\n");
                    break;
                case 0x7:
                    printf("SUBN Vx, Vy\n");
                    break;
                case 0xe:
                    printf("SHL Vx {, Vy}\n");
                    break;
                default:
                    printf("ASDF\n");
                    break;
            }
            break;
        case 0x9000:
            printf("SNE Vx, Vy\n");
            break;
        case 0xa000:
            printf("LD I, addr\n");
            break;
        case 0xb000:
            printf("JP V0, addr\n");
            break;
        case 0xc000:
            printf("RND Vx, byte\n");
            break;
        case 0xd000:
            printf("DRW Vx, Vy, nibble\n");
            break;
        case 0xe000:
            switch(op_code) {
                case 0xe09e:
                    printf("SKP Vx\n");
                    break;
                case 0xe0a1:
                    printf("SKNP Vx\n");
                    break;
                default:
                    break;
            }
            break;
        case 0xf000:
            function_nibble = op_code & 0x00ff;
            switch(function_nibble) {
                case 0x07:
                    printf("LD Vx, DT\n");
                    break;
                case 0x0a:
                    printf("LD Vx, K\n");
                    break;
                case 0x15:
                    printf("LD DT, Vx\n");
                    break;
                case 0x18:
                    printf("LD ST, Vx\n");
                    break;
                case 0x1e:
                    printf("ADD I, Vx\n");
                    break;
                case 0x29:
                    printf("LD F, Vx\n");
                    break;
                case 0x33:
                    printf("LD B, Vx\n");
                    break;
                case 0x55:
                    printf("LD [I], Vx\n");
                    break;
                case 0x65:
                    printf("LD Vx, [I]\n");
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void setup_emulator(struct emulator* emulator)
{
    load_font_in_mem(emulator);
    load_instructions_in_ram(emulator);
    emulator->pc = MEM_START_PROGRAM;
    emulator->draw_screen = 0;
}

void launch(struct emulator* emulator)
{
    int running = 1;
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Texture* texture;
    SDL_Event event;
    uint32_t pixels[CHIP8_WIDTH * CHIP8_HEIGHT];

    if(!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return;
    }
    if(!SDL_CreateWindowAndRenderer(
        "Chip8",
        CHIP8_WIDTH * PIXEL_SCALE,
        CHIP8_HEIGHT * PIXEL_SCALE,
        SDL_WINDOW_RESIZABLE,
        &window,
        &renderer
    )) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return;
    }
    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        CHIP8_WIDTH,
        CHIP8_HEIGHT
    );
    for(int i = 0; i < CHIP8_WIDTH * CHIP8_HEIGHT; i++) {
        pixels[i] = 0xffffffff;
    }
    SDL_UpdateTexture(texture, NULL, pixels, CHIP8_WIDTH * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    while(running) {
        while (SDL_PollEvent(&event)) {
            if(event.type == SDL_EVENT_QUIT) {
                running = 0;
            }
        }
        get_op_code(emulator);
        //run_op_code(emulator, op_code);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}
