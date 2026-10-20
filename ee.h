#ifndef EE_H
#define EE_H

#include <stdint.h>

// Estrutura que representa o estado interno do Emotion Engine (EE)
struct EE_State {
    uint64_t gpr[32]; // 32 Registradores de Propósito Geral (General Purpose Registers)
    uint32_t pc;      // Program Counter (Ponteiro para a instrução atual na memória)
    uint64_t hi;      // Registrador HI para multiplicação/divisão
    uint64_t lo;      // Registrador LO para multiplicação/divisão
};

// Classe do Interpretador da CPU
class EE_Interpreter {
public:
    EE_State state;

    EE_Interpreter();
    void Reset();
    void Step(uint32_t instruction); // Executa uma única instrução binária de 32 bits
};

#endif
