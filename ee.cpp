#include "ee.h"
#include <stdio.h>

EE_Interpreter::EE_Interpreter() {
    Reset();
}

void EE_Interpreter::Reset() {
    // Zera todos os registradores ao ligar o "PS2"
    for (int i = 0; i < 32; i++) {
        state.gpr[i] = 0;
    }
    state.hi = 0;
    state.lo = 0;
    state.pc = 0x00100000; // Endereço padrão onde os ELFs de PS2 começam a rodar
}

void EE_Interpreter::Step(uint32_t instruction) {
    // O registrador R0 no MIPS é sempre ZERO. Forçamos isso a cada ciclo.
    state.gpr[0] = 0;

    // Decodificação básica de campos MIPS
    uint8_t opcode = (instruction >> 26) & 0x3F;      // 6 bits superiores
    uint8_t rs     = (instruction >> 21) & 0x1F;      // Registrador Origem 1
    uint8_t rt     = (instruction >> 16) & 0x1F;      // Registrador Origem 2 / Destino
    uint8_t rd     = (instruction >> 11) & 0x1F;      // Registrador Destino (tipo-R)
    uint16_t imm   = instruction & 0xFFFF;            // Valor imediato de 16 bits
    uint8_t funct  = instruction & 0x3F;              // Função específica para tipo-R

    // Extensão de sinal para o valor imediato (essencial para contas matemáticas)
    int64_t simm = (int16_t)imm; 

    switch (opcode) {
        case 0x00: // SPECIAL Opcodes (Instruções do tipo-R, dependem do campo 'funct')
            switch (funct) {
                case 0x21: // ADDU (Add Unsigned) -> rd = rs + rt
                    state.gpr[rd] = state.gpr[rs] + state.gpr[rt];
                    break;
                default:
                    printf("[EE] Instrucao SPECIAL desconhecida: funct 0x%02X\n", funct);
                    break;
            }
            break;

        case 0x09: // ADDIU (Add Immediate Unsigned) -> rt = rs + simm
            state.gpr[rt] = state.gpr[rs] + simm;
            break;

        case 0x0D: // ORI (Bitwise OR Immediate) -> rt = rs | imm
            state.gpr[rt] = state.gpr[rs] | imm;
            break;

        default:
            printf("[EE] Opcode desconhecido: 0x%02X (Instrucao completa: 0x%08X)\n", opcode, instruction);
            break;
    }

    // Avança o Program Counter para a próxima instrução (4 bytes adiante)
    state.pc += 4;
}
