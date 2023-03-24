//
// Created by raman.chakhouski on 3/24/2023.
//

#include "DebugBytecodePrinter.h"

#define DEFINE_OPCODE_PRINTER(_Opcode) void DebugBytecodePrinter::Print_##_Opcode(const DebugBytecodePrinter::CDebugPrinterContext& Context)

// 0 - 9
DEFINE_OPCODE_PRINTER(NOP)
{
}
DEFINE_OPCODE_PRINTER(ACONST_NULL)
{
}
DEFINE_OPCODE_PRINTER(ICONST_0)
{
}
DEFINE_OPCODE_PRINTER(ICONST_1)
{
}
DEFINE_OPCODE_PRINTER(ICONST_2)
{
}
DEFINE_OPCODE_PRINTER(ICONST_3)
{
}
DEFINE_OPCODE_PRINTER(ICONST_4)
{
}
DEFINE_OPCODE_PRINTER(ICONST_5)
{
}
DEFINE_OPCODE_PRINTER(LCONST_0)
{
}

// 10 - 19
DEFINE_OPCODE_PRINTER(LCONST_1)
{
}
DEFINE_OPCODE_PRINTER(FCONST_0)
{
}
DEFINE_OPCODE_PRINTER(FCONST_1)
{
}
DEFINE_OPCODE_PRINTER(FCONST_2)
{
}
DEFINE_OPCODE_PRINTER(DCONST_0)
{
}
DEFINE_OPCODE_PRINTER(DCONST_1)
{
}
DEFINE_OPCODE_PRINTER(BIPUSH)
{
}
DEFINE_OPCODE_PRINTER(SIPUSH)
{
}
DEFINE_OPCODE_PRINTER(LDC)
{
}
DEFINE_OPCODE_PRINTER(LDC_W)
{
}

// 20 - 29
DEFINE_OPCODE_PRINTER(LDC2_W)
{
}
DEFINE_OPCODE_PRINTER(ILOAD)
{
}
DEFINE_OPCODE_PRINTER(LLOAD)
{
}
DEFINE_OPCODE_PRINTER(FLOAD)
{
}
DEFINE_OPCODE_PRINTER(DLOAD)
{
}
DEFINE_OPCODE_PRINTER(ALOAD)
{
}
DEFINE_OPCODE_PRINTER(ILOAD_0)
{
}
DEFINE_OPCODE_PRINTER(ILOAD_1)
{
}
DEFINE_OPCODE_PRINTER(ILOAD_2)
{
}
DEFINE_OPCODE_PRINTER(ILOAD_3)
{
}

// 30 - 39
DEFINE_OPCODE_PRINTER(LLOAD_0)
{
}
DEFINE_OPCODE_PRINTER(LLOAD_1)
{
}
DEFINE_OPCODE_PRINTER(LLOAD_2)
{
}
DEFINE_OPCODE_PRINTER(LLOAD_3)
{
}
DEFINE_OPCODE_PRINTER(FLOAD_0)
{
}
DEFINE_OPCODE_PRINTER(FLOAD_1)
{
}
DEFINE_OPCODE_PRINTER(FLOAD_2)
{
}
DEFINE_OPCODE_PRINTER(FLOAD_3)
{
}
DEFINE_OPCODE_PRINTER(DLOAD_0)
{
}
DEFINE_OPCODE_PRINTER(DLOAD_1)
{
}

// 40 - 49
DEFINE_OPCODE_PRINTER(DLOAD_2)
{
}
DEFINE_OPCODE_PRINTER(DLOAD_3)
{
}
DEFINE_OPCODE_PRINTER(ALOAD_0)
{
}
DEFINE_OPCODE_PRINTER(ALOAD_1)
{
}
DEFINE_OPCODE_PRINTER(ALOAD_2)
{
}
DEFINE_OPCODE_PRINTER(ALOAD_3)
{
}
DEFINE_OPCODE_PRINTER(IALOAD)
{
}
DEFINE_OPCODE_PRINTER(LALOAD)
{
}
DEFINE_OPCODE_PRINTER(FALOAD)
{
}
DEFINE_OPCODE_PRINTER(DALOAD)
{
}

// 50 - 59
DEFINE_OPCODE_PRINTER(AALOAD)
{
}
DEFINE_OPCODE_PRINTER(BALOAD)
{
}
DEFINE_OPCODE_PRINTER(CALOAD)
{
}
DEFINE_OPCODE_PRINTER(SALOAD)
{
}
DEFINE_OPCODE_PRINTER(ISTORE)
{
}
DEFINE_OPCODE_PRINTER(LSTORE)
{
}
DEFINE_OPCODE_PRINTER(FSTORE)
{
}
DEFINE_OPCODE_PRINTER(DSTORE)
{
}
DEFINE_OPCODE_PRINTER(ASTORE)
{
}
DEFINE_OPCODE_PRINTER(ISTORE_0)
{
}

// 60 - 69
DEFINE_OPCODE_PRINTER(ISTORE_1)
{
}
DEFINE_OPCODE_PRINTER(ISTORE_2)
{
}
DEFINE_OPCODE_PRINTER(ISTORE_3)
{
}
DEFINE_OPCODE_PRINTER(LSTORE_0)
{
}
DEFINE_OPCODE_PRINTER(LSTORE_1)
{
}
DEFINE_OPCODE_PRINTER(LSTORE_2)
{
}
DEFINE_OPCODE_PRINTER(LSTORE_3)
{
}
DEFINE_OPCODE_PRINTER(FSTORE_0)
{
}
DEFINE_OPCODE_PRINTER(FSTORE_1)
{
}
DEFINE_OPCODE_PRINTER(FSTORE_2)
{
}

// 70 - 79
DEFINE_OPCODE_PRINTER(FSTORE_3)
{
}
DEFINE_OPCODE_PRINTER(DSTORE_0)
{
}
DEFINE_OPCODE_PRINTER(DSTORE_1)
{
}
DEFINE_OPCODE_PRINTER(DSTORE_2)
{
}
DEFINE_OPCODE_PRINTER(DSTORE_3)
{
}
DEFINE_OPCODE_PRINTER(ASTORE_0)
{
}
DEFINE_OPCODE_PRINTER(ASTORE_1)
{
}
DEFINE_OPCODE_PRINTER(ASTORE_2)
{
}
DEFINE_OPCODE_PRINTER(ASTORE_3)
{
}
DEFINE_OPCODE_PRINTER(IASTORE)
{
}

// 80 - 89
DEFINE_OPCODE_PRINTER(LASTORE)
{
}
DEFINE_OPCODE_PRINTER(FASTORE)
{
}
DEFINE_OPCODE_PRINTER(DASTORE)
{
}
DEFINE_OPCODE_PRINTER(AASTORE)
{
}
DEFINE_OPCODE_PRINTER(BASTORE)
{
}
DEFINE_OPCODE_PRINTER(CASTORE)
{
}
DEFINE_OPCODE_PRINTER(SASTORE)
{
}
DEFINE_OPCODE_PRINTER(POP)
{
}
DEFINE_OPCODE_PRINTER(POP2)
{
}
DEFINE_OPCODE_PRINTER(DUP)
{
}

// 90 - 99
DEFINE_OPCODE_PRINTER(DUP_X1)
{
}
DEFINE_OPCODE_PRINTER(DUP_X2)
{
}
DEFINE_OPCODE_PRINTER(DUP2)
{
}
DEFINE_OPCODE_PRINTER(DUP2_X1)
{
}
DEFINE_OPCODE_PRINTER(DUP2_X2)
{
}
DEFINE_OPCODE_PRINTER(SWAP)
{
}
DEFINE_OPCODE_PRINTER(IADD)
{
}
DEFINE_OPCODE_PRINTER(LADD)
{
}
DEFINE_OPCODE_PRINTER(FADD)
{
}
DEFINE_OPCODE_PRINTER(DADD)
{
}

// 100 - 109
DEFINE_OPCODE_PRINTER(ISUB)
{
}
DEFINE_OPCODE_PRINTER(LSUB)
{
}
DEFINE_OPCODE_PRINTER(FSUB)
{
}
DEFINE_OPCODE_PRINTER(DSUB)
{
}
DEFINE_OPCODE_PRINTER(IMUL)
{
}
DEFINE_OPCODE_PRINTER(LMUL)
{
}
DEFINE_OPCODE_PRINTER(FMUL)
{
}
DEFINE_OPCODE_PRINTER(DMUL)
{
}
DEFINE_OPCODE_PRINTER(IDIV)
{
}
DEFINE_OPCODE_PRINTER(LDIV)
{
}

// 110 - 119
DEFINE_OPCODE_PRINTER(FDIV)
{
}
DEFINE_OPCODE_PRINTER(DDIV)
{
}
DEFINE_OPCODE_PRINTER(IREM)
{
}
DEFINE_OPCODE_PRINTER(LREM)
{
}
DEFINE_OPCODE_PRINTER(FREM)
{
}
DEFINE_OPCODE_PRINTER(DREM)
{
}
DEFINE_OPCODE_PRINTER(INEG)
{
}
DEFINE_OPCODE_PRINTER(LNEG)
{
}
DEFINE_OPCODE_PRINTER(FNEG)
{
}
DEFINE_OPCODE_PRINTER(DNEG)
{
}

// 120 - 129
DEFINE_OPCODE_PRINTER(ISHL)
{
}
DEFINE_OPCODE_PRINTER(LSHL)
{
}
DEFINE_OPCODE_PRINTER(ISHR)
{
}
DEFINE_OPCODE_PRINTER(LSHR)
{
}
DEFINE_OPCODE_PRINTER(IUSHR)
{
}
DEFINE_OPCODE_PRINTER(LUSHR)
{
}
DEFINE_OPCODE_PRINTER(IAND)
{
}
DEFINE_OPCODE_PRINTER(LAND)
{
}
DEFINE_OPCODE_PRINTER(IOR)
{
}
DEFINE_OPCODE_PRINTER(LOR)
{
}

// 130 - 139
DEFINE_OPCODE_PRINTER(IXOR)
{
}
DEFINE_OPCODE_PRINTER(LXOR)
{
}
DEFINE_OPCODE_PRINTER(IINC)
{
}
DEFINE_OPCODE_PRINTER(I2L)
{
}
DEFINE_OPCODE_PRINTER(I2F)
{
}
DEFINE_OPCODE_PRINTER(I2D)
{
}
DEFINE_OPCODE_PRINTER(L2I)
{
}
DEFINE_OPCODE_PRINTER(L2F)
{
}
DEFINE_OPCODE_PRINTER(L2D)
{
}
DEFINE_OPCODE_PRINTER(F2I)
{
}

// 140 - 149
DEFINE_OPCODE_PRINTER(F2L)
{
}
DEFINE_OPCODE_PRINTER(F2D)
{
}
DEFINE_OPCODE_PRINTER(D2I)
{
}
DEFINE_OPCODE_PRINTER(D2L)
{
}
DEFINE_OPCODE_PRINTER(D2F)
{
}
DEFINE_OPCODE_PRINTER(I2B)
{
}
DEFINE_OPCODE_PRINTER(I2C)
{
}
DEFINE_OPCODE_PRINTER(I2S)
{
}
DEFINE_OPCODE_PRINTER(LCMP)
{
}
DEFINE_OPCODE_PRINTER(FCMPL)
{
}

// 150 - 159
DEFINE_OPCODE_PRINTER(FCMPG)
{
}
DEFINE_OPCODE_PRINTER(DCMPL)
{
}
DEFINE_OPCODE_PRINTER(DCMPG)
{
}
DEFINE_OPCODE_PRINTER(IFEQ)
{
}
DEFINE_OPCODE_PRINTER(IFNE)
{
}
DEFINE_OPCODE_PRINTER(IFLT)
{
}
DEFINE_OPCODE_PRINTER(IFGE)
{
}
DEFINE_OPCODE_PRINTER(IFGT)
{
}
DEFINE_OPCODE_PRINTER(IFLE)
{
}
DEFINE_OPCODE_PRINTER(IF_ICMPEQ)
{
}

// 160 - 169
DEFINE_OPCODE_PRINTER(IF_ICMPNE)
{
}
DEFINE_OPCODE_PRINTER(IF_ICMPLT)
{
}
DEFINE_OPCODE_PRINTER(IF_ICMPGE)
{
}
DEFINE_OPCODE_PRINTER(IF_ICMPGT)
{
}
DEFINE_OPCODE_PRINTER(IF_ICMPLE)
{
}
DEFINE_OPCODE_PRINTER(IF_ACMPEQ)
{
}
DEFINE_OPCODE_PRINTER(IF_ACMPNE)
{
}
DEFINE_OPCODE_PRINTER(GOTO)
{
}
DEFINE_OPCODE_PRINTER(JSR)
{
}
DEFINE_OPCODE_PRINTER(RET)
{
}

// 170 - 179
DEFINE_OPCODE_PRINTER(TABLESWITCH)
{
}
DEFINE_OPCODE_PRINTER(LOOKUPSWITCH)
{
}
DEFINE_OPCODE_PRINTER(IRETURN)
{
}
DEFINE_OPCODE_PRINTER(LRETURN)
{
}
DEFINE_OPCODE_PRINTER(FRETURN)
{
}
DEFINE_OPCODE_PRINTER(DRETURN)
{
}
DEFINE_OPCODE_PRINTER(ARETURN)
{
}
DEFINE_OPCODE_PRINTER(RETURN)
{
}
DEFINE_OPCODE_PRINTER(GETSTATIC)
{
}
DEFINE_OPCODE_PRINTER(PUTSTATIC)
{
}

// 180 - 189
DEFINE_OPCODE_PRINTER(GETFIELD)
{
}
DEFINE_OPCODE_PRINTER(PUTFIELD)
{
}
DEFINE_OPCODE_PRINTER(INVOKEVIRTUAL)
{
}
DEFINE_OPCODE_PRINTER(INVOKESPECIAL)
{
}
DEFINE_OPCODE_PRINTER(INVOKESTATIC)
{
}
DEFINE_OPCODE_PRINTER(INVOKEINTERFACE)
{
}
DEFINE_OPCODE_PRINTER(INVOKEDYNAMIC)
{
}
DEFINE_OPCODE_PRINTER(NEW)
{
}
DEFINE_OPCODE_PRINTER(NEWARRAY)
{
}
DEFINE_OPCODE_PRINTER(ANEWARRAY)
{
}

// 190 - 199
DEFINE_OPCODE_PRINTER(ARRAYLENGTH)
{
}
DEFINE_OPCODE_PRINTER(ATHROW)
{
}
DEFINE_OPCODE_PRINTER(CHECKCAST)
{
}
DEFINE_OPCODE_PRINTER(INSTANCEOF)
{
}
DEFINE_OPCODE_PRINTER(MONITORENTER)
{
}
DEFINE_OPCODE_PRINTER(MONITOREXIT)
{
}
DEFINE_OPCODE_PRINTER(WIDE)
{
}
DEFINE_OPCODE_PRINTER(MULTIANEWARRAY)
{
}
DEFINE_OPCODE_PRINTER(IFNULL)
{
}
DEFINE_OPCODE_PRINTER(IFNONNULL)
{
}

// 200 - 201
DEFINE_OPCODE_PRINTER(GOTO_W)
{
}
DEFINE_OPCODE_PRINTER(JSR_W)
{
}

#undef DEFINE_OPCODE_PRINTER