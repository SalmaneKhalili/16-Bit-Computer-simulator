#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "Assembler.h"


// Opcode Mask
#define MASK_OPCODE 0x8000  // Bit 15 instruction[15]
// Reg selection Mask
#define MASK_ACODE 0x1000 // Bit 12 instruction[12]
// Control Masks
#define MASK_ZX 0x0800 // Bit 11 instruction[11]
#define MASK_NX 0x0400 // Bit 10 instruction[10]
#define MASK_ZY 0x0200 // Bit 9 instruction[9]
#define MASK_NY 0x0100 // Bit 8 instruction[8]
#define MASK_F 0x0080 // Bit 7 instruction[7]
#define MASK_NO 0x0040 // Bit 6 instruction[6]
// Destination Masks (d1, d2, d3)
#define MASK_DEST_A 0x0020  // Bit 5 (0000 0000 0010 0000)
#define MASK_DEST_D 0x0010  // Bit 4 (0000 0000 0001 0000)
#define MASK_DEST_M 0x0008  // Bit 3 (0000 0000 0000 1000)
// Jump Masks (j1, j2, j3)
#define MASK_JUMP_LT 0x0004  // Bit 2
#define MASK_JUMP_EQ 0x0002  // Bit 1
#define MASK_JUMP_GT 0x0001  // Bit 0



int main() {

    // MEMORY
    uint16_t RAM[16384];    // 16K Data Memory
    uint16_t Screen[8192];
    uint16_t Keyboard = 0;
    uint16_t ROM[32768];   // 32K Instruction Memory

    // getting rid of garbage values
    memset(RAM, 0, sizeof(RAM));
    memset(Screen, 0, sizeof(Screen));
    memset(ROM, 0, sizeof(ROM));

    // CPU registers
    uint16_t pc = 0;         // Program Counter
    uint16_t A = 0;         // A-Register
    uint16_t D = 0;        // D-Register
    load(ROM);

    // test case following HACK ML Specifications //


    while (pc < 32768)
    {
        // Fetch & type instruction
        uint16_t instruction = ROM[pc];
        bool isC = (instruction & MASK_OPCODE);
        bool jump = false;


        uint16_t out;
        if (!isC)
        {
            A = instruction;
        } else
        {
            uint16_t inM;
            if (A < 16384) {
                inM = RAM[A];
            } else if (A >= 16384 && A <= 24575) {
                inM = Screen[A - 16384]; // Offset by the start address
            } else if (A == 24576) {
                inM = Keyboard; // A single 16-bit variable
            } else {
                inM = 0; // Out of bounds safety
            }

            //ALU

            // Inputs
            uint16_t x = D;
            uint16_t y = (instruction & MASK_ACODE) ? inM: A;

            // Control
            if (instruction & MASK_ZX) x = 0;
            if (instruction & MASK_NX) x = ~x;
            if (instruction & MASK_ZY) y = 0;
            if (instruction & MASK_NY) y = ~y;
            out = (instruction & MASK_F) ?  x + y : x & y;
            if (instruction & MASK_NO) out = ~out;

            // Comparators
            uint16_t zr = (out == 0) ? 1:0;
            uint16_t ng = (out & 0x8000) ? 1 : 0; // complement of 2 check for MSB to decide if negative or not

            // Destination bits
            if (instruction & MASK_DEST_A) A = out;
            if (instruction & MASK_DEST_D) D = out;

            if (instruction & MASK_DEST_M)
            {
                if (A < 16384) {
                    RAM[A] = out;
                } else if (A >= 16384 && A <= 24575) {
                    Screen[A - 16384] = out; // Offset by the start address
                } else if (A == 24576) {
                    // cant write to keyboard
                }
            }

            // Jump bits
            bool j1 = (instruction & MASK_JUMP_LT) && ng;
            bool j2 = (instruction & MASK_JUMP_EQ) && zr;
            bool j3 = (instruction & MASK_JUMP_GT) && (!zr && !ng);

            if (j1 || j2 || j3)
            {
                jump = true;
            }
        }
        printf("PC: %u | A: %u | D: %u | out: %u | jump: %d\n", pc, A, D, out, jump);
        (jump) ? pc = A : pc++;

    }


    return 0;
}

//TODO LOAD INTO ROM FUNCTION
//TODO ASSEMBLER FOR HACK ASSEMBLY
//TODO IO
