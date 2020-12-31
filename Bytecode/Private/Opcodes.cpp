//
// Created by ASUS on 31/12/2020.
//

#include "Opcodes.h"

namespace Bytecode
{
    constexpr size_t GetNumOpcodes()
    {
        const size_t NumOpcodes = sizeof(G_OpcodesArray) / sizeof(*G_OpcodesArray);
        static_assert((NumOpcodes - 1) == (G_OpcodesArray[NumOpcodes - 1].GetOperation()),
                "Check opcode table: ");

        return NumOpcodes;
    }

    const Opcode& GetOpcodeForByte(const u1 Byte)
    {
        const Opcode& OpcodeForByte = G_OpcodesArray[(size_t)Byte];
        ASSERT(Byte == OpcodeForByte.GetOperation());

        return OpcodeForByte;
    }
}
