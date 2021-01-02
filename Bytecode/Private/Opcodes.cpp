//
// Created by ASUS on 31/12/2020.
//

#include "Opcodes.h"




namespace Bytecode
{
    static_assert((NumOpcodes - 1) == (G_OpcodesArray[NumOpcodes - 1]->GetOperation()),
                  "Check opcode table: inconsistency between opcode numbers and indices");

    const Opcode& GetOpcodeForByte(const u1 Byte)
    {
        return *G_OpcodesArray[(usz)Byte];
    }
}
