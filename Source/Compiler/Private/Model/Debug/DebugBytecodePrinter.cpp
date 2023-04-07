//
// Created by raman.chakhouski on 3/24/2023.
//

#include "DebugBytecodePrinter.h"

using Bytecode::COpcode;
using Bytecode::COpcodes;

using Compiler::CConstantInfo;
using Compiler::CConstantFieldRefInfo;

namespace Util
{
    void PrintInvokeInfo(const char* InvokeName, const DebugBytecodePrinter::CDebugPrinterContext& Context, const u2 MethodRefInfo)
    {
        const CConstantInfo& ConstantMethodRefInfo = Context.ConstantPool->GetChecked<CConstantInfo>(MethodRefInfo);

        ASSERT_MSG
        (
            ConstantMethodRefInfo.IsA<Compiler::CConstantMethodRefInfo>() ||
            ConstantMethodRefInfo.IsA<Compiler::CConstantInterfaceMethodRefInfo>(),
            "Expected a method ref info (class or interface)"
        );

        Context.stream << InvokeName << ' ' <<  ConstantMethodRefInfo.ToResolvedString(*Context.ConstantPool) << std::endl;
    }

    void PrintFieldOperationInfo(const char* OperationName, const DebugBytecodePrinter::CDebugPrinterContext& Context)
    {
        const u2 FieldRefInfoIndex = Context.NextU2();

        const CConstantFieldRefInfo& FieldRefInfo = Context.ConstantPool->GetChecked<CConstantFieldRefInfo>(FieldRefInfoIndex);

        Context.stream << OperationName << ' ' << FieldRefInfo.ToResolvedString(*Context.ConstantPool) << std::endl;
    }

    void PrintLDC(const char* InvokeName, const DebugBytecodePrinter::CDebugPrinterContext& Context, const usz ConstaintPoolIndex, bool bAllow8Byte = false)
    {
        const CConstantInfo& Const = Context.ConstantPool->GetChecked<CConstantInfo>(ConstaintPoolIndex);
        Context.stream << InvokeName << " (" << Const.GetTagString() << ") " << Const.ToResolvedString(*Context.ConstantPool) << std::endl;
    }
}

#define DEFINE_OPCODE_PRINTER(_Opcode) void DebugBytecodePrinter::Print_##_Opcode(const DebugBytecodePrinter::CDebugPrinterContext& Context)

// 0 - 9
DEFINE_OPCODE_PRINTER(NOP)
{
    Context.stream << "NOP" << std::endl;
}
DEFINE_OPCODE_PRINTER(ACONST_NULL)
{
    Context.stream << "ACONST_NULL" << std::endl;
}
DEFINE_OPCODE_PRINTER(ICONST_M1)
{
    Context.stream << "ICONST_M1" << std::endl;
}
DEFINE_OPCODE_PRINTER(ICONST_0)
{
    Context.stream << "ICONST_0" << std::endl;
}
DEFINE_OPCODE_PRINTER(ICONST_1)
{
    Context.stream << "ICONST_1" << std::endl;
}
DEFINE_OPCODE_PRINTER(ICONST_2)
{
    Context.stream << "ICONST_2" << std::endl;
}
DEFINE_OPCODE_PRINTER(ICONST_3)
{
    Context.stream << "ICONST_3" << std::endl;
}
DEFINE_OPCODE_PRINTER(ICONST_4)
{
    Context.stream << "ICONST_4" << std::endl;
}
DEFINE_OPCODE_PRINTER(ICONST_5)
{
    Context.stream << "ICONST_5" << std::endl;
}
DEFINE_OPCODE_PRINTER(LCONST_0)
{
    Context.stream << "LCONST_0" << std::endl;
}

// 10 - 19
DEFINE_OPCODE_PRINTER(LCONST_1)
{
    Context.stream << "LCONST_1" << std::endl;
}
DEFINE_OPCODE_PRINTER(FCONST_0)
{
    Context.stream << "FCONST_0" << std::endl;
}
DEFINE_OPCODE_PRINTER(FCONST_1)
{
    Context.stream << "FCONST_1" << std::endl;
}
DEFINE_OPCODE_PRINTER(FCONST_2)
{
    Context.stream << "FCONST_2" << std::endl;
}
DEFINE_OPCODE_PRINTER(DCONST_0)
{
    Context.stream << "DCONST_0" << std::endl;
}
DEFINE_OPCODE_PRINTER(DCONST_1)
{
    Context.stream << "DCONST_1" << std::endl;
}
DEFINE_OPCODE_PRINTER(BIPUSH)
{
    const u1 Arg = Context.NextByte();
    Context.stream << "BIPUSH " << (s4)Arg << std::endl;
}
DEFINE_OPCODE_PRINTER(SIPUSH)
{
    const u2 Arg = Context.NextU2();

    Context.stream << "SIPUSH " << (s4)Arg << std::endl;
}
DEFINE_OPCODE_PRINTER(LDC)
{
    Util::PrintLDC("LDC", Context, (usz)Context.NextByte());
}
DEFINE_OPCODE_PRINTER(LDC_W)
{
    Util::PrintLDC("LDC_W", Context, (usz)Context.NextU2());
}

// 20 - 29
DEFINE_OPCODE_PRINTER(LDC2_W)
{
    Util::PrintLDC("LDC2_W", Context, (usz)Context.NextU2(), true);
}
DEFINE_OPCODE_PRINTER(ILOAD)
{
    const u1 Arg = Context.NextByte();
    Context.stream << "ILOAD Locals[" << (int)Arg << "]" << std::endl;
}
DEFINE_OPCODE_PRINTER(LLOAD)
{
    const u1 Arg = Context.NextByte();
    Context.stream << "LLOAD Locals[" << (int)Arg << "]" << std::endl;
}
DEFINE_OPCODE_PRINTER(FLOAD)
{
    const u1 Arg = Context.NextByte();
    Context.stream << "FLOAD Locals[" << (int)Arg << "]" << std::endl;
}
DEFINE_OPCODE_PRINTER(DLOAD)
{
    const u1 Arg = Context.NextByte();
    Context.stream << "DLOAD Locals[" << (int)Arg << "]" << std::endl;
}
DEFINE_OPCODE_PRINTER(ALOAD)
{
    const u1 Arg = Context.NextByte();
    Context.stream << "ALOAD Locals[" << (int)Arg << "]" << std::endl;
}
DEFINE_OPCODE_PRINTER(ILOAD_0)
{
    Context.stream << "ILOAD_0" << std::endl;
}
DEFINE_OPCODE_PRINTER(ILOAD_1)
{
    Context.stream << "ILOAD_1" << std::endl;
}
DEFINE_OPCODE_PRINTER(ILOAD_2)
{
    Context.stream << "ILOAD_2" << std::endl;
}
DEFINE_OPCODE_PRINTER(ILOAD_3)
{
    Context.stream << "ILOAD_3" << std::endl;
}

// 30 - 39
DEFINE_OPCODE_PRINTER(LLOAD_0)
{
    Context.stream << "LLOAD_0" << std::endl;
}
DEFINE_OPCODE_PRINTER(LLOAD_1)
{
    Context.stream << "LLOAD_1" << std::endl;
}
DEFINE_OPCODE_PRINTER(LLOAD_2)
{
    Context.stream << "LLOAD_2" << std::endl;
}
DEFINE_OPCODE_PRINTER(LLOAD_3)
{
    Context.stream << "LLOAD_3" << std::endl;
}
DEFINE_OPCODE_PRINTER(FLOAD_0)
{
    Context.stream << "FLOAD_0" << std::endl;
}
DEFINE_OPCODE_PRINTER(FLOAD_1)
{
    Context.stream << "FLOAD_1" << std::endl;
}
DEFINE_OPCODE_PRINTER(FLOAD_2)
{
    Context.stream << "FLOAD_2" << std::endl;
}
DEFINE_OPCODE_PRINTER(FLOAD_3)
{
    Context.stream << "FLOAD_3" << std::endl;
}
DEFINE_OPCODE_PRINTER(DLOAD_0)
{
    Context.stream << "DLOAD_0" << std::endl;
}
DEFINE_OPCODE_PRINTER(DLOAD_1)
{
    Context.stream << "DLOAD_1" << std::endl;
}

// 40 - 49
DEFINE_OPCODE_PRINTER(DLOAD_2)
{
    Context.stream << "DLOAD_2" << std::endl;
}
DEFINE_OPCODE_PRINTER(DLOAD_3)
{
    Context.stream << "DLOAD_3" << std::endl;
}
DEFINE_OPCODE_PRINTER(ALOAD_0)
{
    Context.stream << "ALOAD_0" << std::endl;
}
DEFINE_OPCODE_PRINTER(ALOAD_1)
{
    Context.stream << "ALOAD_1" << std::endl;
}
DEFINE_OPCODE_PRINTER(ALOAD_2)
{
    Context.stream << "ALOAD_2" << std::endl;
}
DEFINE_OPCODE_PRINTER(ALOAD_3)
{
    Context.stream << "ALOAD_3" << std::endl;
}
DEFINE_OPCODE_PRINTER(IALOAD)
{
    Context.stream << "IALOAD" << std::endl;
}
DEFINE_OPCODE_PRINTER(LALOAD)
{
    Context.stream << "LALOAD" << std::endl;
}
DEFINE_OPCODE_PRINTER(FALOAD)
{
    Context.stream << "FALOAD" << std::endl;
}
DEFINE_OPCODE_PRINTER(DALOAD)
{
    Context.stream << "DALOAD" << std::endl;
}

// 50 - 59
DEFINE_OPCODE_PRINTER(AALOAD)
{
    Context.stream << "AALOAD" << std::endl;
}
DEFINE_OPCODE_PRINTER(BALOAD)
{
    Context.stream << "BALOAD" << std::endl;
}
DEFINE_OPCODE_PRINTER(CALOAD)
{
    Context.stream << "CALOAD" << std::endl;
}
DEFINE_OPCODE_PRINTER(SALOAD)
{
    Context.stream << "SALOAD" << std::endl;
}
DEFINE_OPCODE_PRINTER(ISTORE)
{
    const u1 Arg = Context.NextByte();
    Context.stream << "ISTORE Locals[" << (int)Arg << "]" << std::endl;
}
DEFINE_OPCODE_PRINTER(LSTORE)
{
    const u1 Arg = Context.NextByte();
    Context.stream << "LSTORE Locals[" << (int)Arg << "]" << std::endl;
}
DEFINE_OPCODE_PRINTER(FSTORE)
{
    const u1 Arg = Context.NextByte();
    Context.stream << "FSTORE Locals[" << (int)Arg << "]" << std::endl;
}
DEFINE_OPCODE_PRINTER(DSTORE)
{
    const u1 Arg = Context.NextByte();
    Context.stream << "DSTORE Locals[" << (int)Arg << "]" << std::endl;
}
DEFINE_OPCODE_PRINTER(ASTORE)
{
    const u1 Arg = Context.NextByte();
    Context.stream << "ASTORE Locals[" << (int)Arg << "]" << std::endl;
}
DEFINE_OPCODE_PRINTER(ISTORE_0)
{
    Context.stream << "ISTORE_0" << std::endl;
}

// 60 - 69
DEFINE_OPCODE_PRINTER(ISTORE_1)
{
    Context.stream << "ISTORE_1" << std::endl;
}
DEFINE_OPCODE_PRINTER(ISTORE_2)
{
    Context.stream << "ISTORE_2" << std::endl;
}
DEFINE_OPCODE_PRINTER(ISTORE_3)
{
    Context.stream << "ISTORE_3" << std::endl;
}
DEFINE_OPCODE_PRINTER(LSTORE_0)
{
    Context.stream << "LSTORE_0" << std::endl;
}
DEFINE_OPCODE_PRINTER(LSTORE_1)
{
    Context.stream << "LSTORE_1" << std::endl;
}
DEFINE_OPCODE_PRINTER(LSTORE_2)
{
    Context.stream << "LSTORE_2" << std::endl;
}
DEFINE_OPCODE_PRINTER(LSTORE_3)
{
    Context.stream << "LSTORE_3" << std::endl;
}
DEFINE_OPCODE_PRINTER(FSTORE_0)
{
    Context.stream << "FSTORE_0" << std::endl;
}
DEFINE_OPCODE_PRINTER(FSTORE_1)
{
    Context.stream << "FSTORE_1" << std::endl;
}
DEFINE_OPCODE_PRINTER(FSTORE_2)
{
    Context.stream << "FSTORE_2" << std::endl;
}

// 70 - 79
DEFINE_OPCODE_PRINTER(FSTORE_3)
{
    Context.stream << "FSTORE_3" << std::endl;
}
DEFINE_OPCODE_PRINTER(DSTORE_0)
{
    Context.stream << "DSTORE_0" << std::endl;
}
DEFINE_OPCODE_PRINTER(DSTORE_1)
{
    Context.stream << "DSTORE_1" << std::endl;
}
DEFINE_OPCODE_PRINTER(DSTORE_2)
{
    Context.stream << "DSTORE_2" << std::endl;
}
DEFINE_OPCODE_PRINTER(DSTORE_3)
{
    Context.stream << "DSTORE_3" << std::endl;
}
DEFINE_OPCODE_PRINTER(ASTORE_0)
{
    Context.stream << "ASTORE_0" << std::endl;
}
DEFINE_OPCODE_PRINTER(ASTORE_1)
{
    Context.stream << "ASTORE_1" << std::endl;
}
DEFINE_OPCODE_PRINTER(ASTORE_2)
{
    Context.stream << "ASTORE_2" << std::endl;
}
DEFINE_OPCODE_PRINTER(ASTORE_3)
{
    Context.stream << "ASTORE_3" << std::endl;
}
DEFINE_OPCODE_PRINTER(IASTORE)
{
    Context.stream << "IASTORE" << std::endl;
}

// 80 - 89
DEFINE_OPCODE_PRINTER(LASTORE)
{
    Context.stream << "LASTORE" << std::endl;
}
DEFINE_OPCODE_PRINTER(FASTORE)
{
    Context.stream << "FASTORE" << std::endl;
}
DEFINE_OPCODE_PRINTER(DASTORE)
{
    Context.stream << "DASTORE" << std::endl;
}
DEFINE_OPCODE_PRINTER(AASTORE)
{
    Context.stream << "AASTORE" << std::endl;
}
DEFINE_OPCODE_PRINTER(BASTORE)
{
    Context.stream << "BASTORE" << std::endl;
}
DEFINE_OPCODE_PRINTER(CASTORE)
{
    Context.stream << "CASTORE" << std::endl;
}
DEFINE_OPCODE_PRINTER(SASTORE)
{
    Context.stream << "SASTORE" << std::endl;
}
DEFINE_OPCODE_PRINTER(POP)
{
    Context.stream << "POP" << std::endl;
}
DEFINE_OPCODE_PRINTER(POP2)
{
    Context.stream << "POP2" << std::endl;
}
DEFINE_OPCODE_PRINTER(DUP)
{
    Context.stream << "DUP" << std::endl;
}

// 90 - 99
DEFINE_OPCODE_PRINTER(DUP_X1)
{
    Context.stream << "DUP_X1" << std::endl;
}
DEFINE_OPCODE_PRINTER(DUP_X2)
{
    Context.stream << "DUP_X2" << std::endl;
}
DEFINE_OPCODE_PRINTER(DUP2)
{
    Context.stream << "DUP2" << std::endl;
}
DEFINE_OPCODE_PRINTER(DUP2_X1)
{
    Context.stream << "DUP2_X1" << std::endl;
}
DEFINE_OPCODE_PRINTER(DUP2_X2)
{
    Context.stream << "DUP2_X2" << std::endl;
}
DEFINE_OPCODE_PRINTER(SWAP)
{
    Context.stream << "SWAP" << std::endl;
}
DEFINE_OPCODE_PRINTER(IADD)
{
    Context.stream << "IADD" << std::endl;
}
DEFINE_OPCODE_PRINTER(LADD)
{
    Context.stream << "LADD" << std::endl;
}
DEFINE_OPCODE_PRINTER(FADD)
{
    Context.stream << "FADD" << std::endl;
}
DEFINE_OPCODE_PRINTER(DADD)
{
    Context.stream << "DADD" << std::endl;
}

// 100 - 109
DEFINE_OPCODE_PRINTER(ISUB)
{
    Context.stream << "ISUB" << std::endl;
}
DEFINE_OPCODE_PRINTER(LSUB)
{
    Context.stream << "LSUB" << std::endl;
}
DEFINE_OPCODE_PRINTER(FSUB)
{
    Context.stream << "FSUB" << std::endl;
}
DEFINE_OPCODE_PRINTER(DSUB)
{
    Context.stream << "DSUB" << std::endl;
}
DEFINE_OPCODE_PRINTER(IMUL)
{
    Context.stream << "IMUL" << std::endl;
}
DEFINE_OPCODE_PRINTER(LMUL)
{
    Context.stream << "LMUL" << std::endl;
}
DEFINE_OPCODE_PRINTER(FMUL)
{
    Context.stream << "FMUL" << std::endl;
}
DEFINE_OPCODE_PRINTER(DMUL)
{
    Context.stream << "DMUL" << std::endl;
}
DEFINE_OPCODE_PRINTER(IDIV)
{
    Context.stream << "IDIV" << std::endl;
}
DEFINE_OPCODE_PRINTER(LDIV)
{
    Context.stream << "LDIV" << std::endl;
}

// 110 - 119
DEFINE_OPCODE_PRINTER(FDIV)
{
    Context.stream << "FDIV" << std::endl;
}
DEFINE_OPCODE_PRINTER(DDIV)
{
    Context.stream << "DDIV" << std::endl;
}
DEFINE_OPCODE_PRINTER(IREM)
{
    Context.stream << "IREM" << std::endl;
}
DEFINE_OPCODE_PRINTER(LREM)
{
    Context.stream << "LREM" << std::endl;
}
DEFINE_OPCODE_PRINTER(FREM)
{
    Context.stream << "FREM" << std::endl;
}
DEFINE_OPCODE_PRINTER(DREM)
{
    Context.stream << "DREM" << std::endl;
}
DEFINE_OPCODE_PRINTER(INEG)
{
    Context.stream << "INEG" << std::endl;
}
DEFINE_OPCODE_PRINTER(LNEG)
{
    Context.stream << "LNEG" << std::endl;
}
DEFINE_OPCODE_PRINTER(FNEG)
{
    Context.stream << "FNEG" << std::endl;
}
DEFINE_OPCODE_PRINTER(DNEG)
{
    Context.stream << "DNEG" << std::endl;
}

// 120 - 129
DEFINE_OPCODE_PRINTER(ISHL)
{
    Context.stream << "ISHL" << std::endl;
}
DEFINE_OPCODE_PRINTER(LSHL)
{
    Context.stream << "LSHL" << std::endl;
}
DEFINE_OPCODE_PRINTER(ISHR)
{
    Context.stream << "ISHR" << std::endl;
}
DEFINE_OPCODE_PRINTER(LSHR)
{
    Context.stream << "LSHR" << std::endl;
}
DEFINE_OPCODE_PRINTER(IUSHR)
{
    Context.stream << "IUSHR" << std::endl;
}
DEFINE_OPCODE_PRINTER(LUSHR)
{
    Context.stream << "LUSHR" << std::endl;
}
DEFINE_OPCODE_PRINTER(IAND)
{
    Context.stream << "IAND" << std::endl;
}
DEFINE_OPCODE_PRINTER(LAND)
{
    Context.stream << "LAND" << std::endl;
}
DEFINE_OPCODE_PRINTER(IOR)
{
    Context.stream << "IOR" << std::endl;
}
DEFINE_OPCODE_PRINTER(LOR)
{
    Context.stream << "LOR" << std::endl;
}

// 130 - 139
DEFINE_OPCODE_PRINTER(IXOR)
{
    Context.stream << "IXOR" << std::endl;
}
DEFINE_OPCODE_PRINTER(LXOR)
{
    Context.stream << "LXOR" << std::endl;
}
DEFINE_OPCODE_PRINTER(IINC)
{
    const u2 Arg = Context.NextU2();

    Context.stream << "IINC " << Arg << std::endl;
}
DEFINE_OPCODE_PRINTER(I2L)
{
    Context.stream << "I2L" << std::endl;
}
DEFINE_OPCODE_PRINTER(I2F)
{
    Context.stream << "I2F" << std::endl;
}
DEFINE_OPCODE_PRINTER(I2D)
{
    Context.stream << "I2D" << std::endl;
}
DEFINE_OPCODE_PRINTER(L2I)
{
    Context.stream << "L2I" << std::endl;
}
DEFINE_OPCODE_PRINTER(L2F)
{
    Context.stream << "L2F" << std::endl;
}
DEFINE_OPCODE_PRINTER(L2D)
{
    Context.stream << "L2D" << std::endl;
}
DEFINE_OPCODE_PRINTER(F2I)
{
    Context.stream << "F2I" << std::endl;
}

// 140 - 149
DEFINE_OPCODE_PRINTER(F2L)
{
    Context.stream << "F2L" << std::endl;
}
DEFINE_OPCODE_PRINTER(F2D)
{
    Context.stream << "F2D" << std::endl;
}
DEFINE_OPCODE_PRINTER(D2I)
{
    Context.stream << "D2I" << std::endl;
}
DEFINE_OPCODE_PRINTER(D2L)
{
    Context.stream << "D2L" << std::endl;
}
DEFINE_OPCODE_PRINTER(D2F)
{
    Context.stream << "D2F" << std::endl;
}
DEFINE_OPCODE_PRINTER(I2B)
{
    Context.stream << "I2B" << std::endl;
}
DEFINE_OPCODE_PRINTER(I2C)
{
    Context.stream << "I2C" << std::endl;
}
DEFINE_OPCODE_PRINTER(I2S)
{
    Context.stream << "I2S" << std::endl;
}
DEFINE_OPCODE_PRINTER(LCMP)
{
    Context.stream << "LCMP" << std::endl;
}
DEFINE_OPCODE_PRINTER(FCMPL)
{
    Context.stream << "FCMPL" << std::endl;
}

// 150 - 159
DEFINE_OPCODE_PRINTER(FCMPG)
{
    Context.stream << "FCMPG" << std::endl;
}
DEFINE_OPCODE_PRINTER(DCMPL)
{
    Context.stream << "DCMPL" << std::endl;
}
DEFINE_OPCODE_PRINTER(DCMPG)
{
    Context.stream << "DCMPG" << std::endl;
}
DEFINE_OPCODE_PRINTER(IFEQ)
{
    const u2 Arg = Context.NextU2();

    Context.stream << "IFEQ " << Arg << std::endl;
}
DEFINE_OPCODE_PRINTER(IFNE)
{
    const u2 Arg = Context.NextU2();

    Context.stream << "IFNE " << Arg << std::endl;
}
DEFINE_OPCODE_PRINTER(IFLT)
{
    const u2 Arg = Context.NextU2();

    Context.stream << "IFLT " << Arg << std::endl;
}
DEFINE_OPCODE_PRINTER(IFGE)
{
    const u2 Arg = Context.NextU2();

    Context.stream << "IFGE " << Arg << std::endl;
}
DEFINE_OPCODE_PRINTER(IFGT)
{
    const u2 Arg = Context.NextU2();

    Context.stream << "IFGT " << Arg << std::endl;
}
DEFINE_OPCODE_PRINTER(IFLE)
{
    const u2 Arg = Context.NextU2();

    Context.stream << "IFLE " << Arg << std::endl;
}
DEFINE_OPCODE_PRINTER(IF_ICMPEQ)
{
    const u2 Arg = Context.NextU2();

    Context.stream << "IF_ICMPEQ " << Arg << std::endl;
}

// 160 - 169
DEFINE_OPCODE_PRINTER(IF_ICMPNE)
{
    const u2 Arg = Context.NextU2();

    Context.stream << "IF_ICMPNE " << Arg << std::endl;
}
DEFINE_OPCODE_PRINTER(IF_ICMPLT)
{
    const u2 Arg = Context.NextU2();

    Context.stream << "IF_ICMPLT " << Arg << std::endl;
}
DEFINE_OPCODE_PRINTER(IF_ICMPGE)
{
    const u2 Arg = Context.NextU2();

    Context.stream << "IF_ICMPGE " << Arg << std::endl;
}
DEFINE_OPCODE_PRINTER(IF_ICMPGT)
{
    const u2 Arg = Context.NextU2();

    Context.stream << "IF_ICMPGT " << Arg << std::endl;
}
DEFINE_OPCODE_PRINTER(IF_ICMPLE)
{
	const u2 Arg = Context.NextU2();

    Context.stream << "IF_ICMPLE " << Arg << std::endl;
}
DEFINE_OPCODE_PRINTER(IF_ACMPEQ)
{
	const u2 Arg = Context.NextU2();

    Context.stream << "IF_ACMPEQ " << Arg << std::endl;
}
DEFINE_OPCODE_PRINTER(IF_ACMPNE)
{
	const u2 Arg = Context.NextU2();

    Context.stream << "IF_ACMPNE " << Arg << std::endl;
}
DEFINE_OPCODE_PRINTER(GOTO)
{
	const u2 Arg = Context.NextU2();

    Context.stream << "GOTO " << Arg << std::endl;
}
DEFINE_OPCODE_PRINTER(JSR)
{
	const u2 Arg = Context.NextU2();

    Context.stream << "JSR " << Arg << std::endl;
}
DEFINE_OPCODE_PRINTER(RET)
{
    const u1 Arg = Context.NextByte();
    Context.stream << "RET Locals[" << Arg << "]" << std::endl;
}

// 170 - 179
DEFINE_OPCODE_PRINTER(TABLESWITCH)
{
	const usz BeginPos = Context.Tell();
	const usz BeginPosAligned = Util::CMathUtils::Align(BeginPos, 4);

	usz NumPadBytes = BeginPosAligned - BeginPos;
	ASSERT(NumPadBytes < 4);

	while(NumPadBytes-- > 0)
	{
		const u1 UselessByte = Context.NextByte();
	}

	const u4 Default = Context.NextU4();
	const u4 Low = Context.NextU4();
	const u4 High = Context.NextU4();

	ASSERT(High > Low);

	const s4 NumJumpOffsets = (High - Low) + 1;

	std::vector<s4> JumpOffsets{};
	for (s4 Index = 0; Index < NumJumpOffsets; ++Index)
	{
		const s4 JumpOffset = Context.NextS4();
		JumpOffsets.push_back(JumpOffset);
	}

	Context.stream << "TABLESWITCH" << std::endl;
}
DEFINE_OPCODE_PRINTER(LOOKUPSWITCH)
{
	const usz BeginPos = Context.Tell();
	const usz BeginPosAligned = Util::CMathUtils::Align(BeginPos, 4);

	usz NumPadBytes = BeginPosAligned - BeginPos;
	ASSERT(NumPadBytes < 4);

	while(NumPadBytes-- > 0)
	{
		const u1 UselessByte = Context.NextByte();
	}

	const u4 Default = Context.NextU4();
	const u4 NumPairs = Context.NextU4();

	struct CLookupSwitchPair
	{
		s4 Match;
		s4 Offset;
	};

	std::vector<CLookupSwitchPair> Pairs{};
	Pairs.reserve(NumPairs);

	for (u4 Index = 0; Index < NumPairs; ++Index)
	{
		const s4 Match = Context.NextS4();
		const s4 Offset = Context.NextS4();
		Pairs.push_back(CLookupSwitchPair{ Match, Offset });
	}

	Context.stream << "LOOKUPSWITCH" << std::endl;
}
DEFINE_OPCODE_PRINTER(IRETURN)
{
    Context.stream << "IRETURN" << std::endl;
}
DEFINE_OPCODE_PRINTER(LRETURN)
{
    Context.stream << "LRETURN" << std::endl;
}
DEFINE_OPCODE_PRINTER(FRETURN)
{
    Context.stream << "FRETURN" << std::endl;
}
DEFINE_OPCODE_PRINTER(DRETURN)
{
    Context.stream << "DRETURN" << std::endl;
}
DEFINE_OPCODE_PRINTER(ARETURN)
{
    Context.stream << "ARETURN" << std::endl;
}
DEFINE_OPCODE_PRINTER(RETURN)
{
    Context.stream << "RETURN" << std::endl;
}
DEFINE_OPCODE_PRINTER(GETSTATIC)
{
    Util::PrintFieldOperationInfo("GETSTATIC", Context);
}
DEFINE_OPCODE_PRINTER(PUTSTATIC)
{
    Util::PrintFieldOperationInfo("PUTSTATIC", Context);
}

// 180 - 189
DEFINE_OPCODE_PRINTER(GETFIELD)
{
    Util::PrintFieldOperationInfo("GETFIELD", Context);
}
DEFINE_OPCODE_PRINTER(PUTFIELD)
{
    Util::PrintFieldOperationInfo("PUTFIELD", Context);
}
DEFINE_OPCODE_PRINTER(INVOKEVIRTUAL)
{
    Util::PrintInvokeInfo("INVOKEVIRTUAL", Context, Context.NextU2());
}
DEFINE_OPCODE_PRINTER(INVOKESPECIAL)
{
    Util::PrintInvokeInfo("INVOKESPECIAL", Context, Context.NextU2());
}
DEFINE_OPCODE_PRINTER(INVOKESTATIC)
{
    Util::PrintInvokeInfo("INVOKESTATIC", Context, Context.NextU2());
}
DEFINE_OPCODE_PRINTER(INVOKEINTERFACE)
{
    Util::PrintInvokeInfo("INVOKEINTERFACE", Context, Context.NextU2());
}
DEFINE_OPCODE_PRINTER(INVOKEDYNAMIC)
{
    Util::PrintInvokeInfo("INVOKEDYNAMIC", Context, Context.NextU2());
}
DEFINE_OPCODE_PRINTER(NEW)
{
	const u2 Arg = Context.NextU2();

    const Compiler::CConstantClassInfo& ClassInfo =
            Context.ConstantPool->GetChecked<Compiler::CConstantClassInfo>(Arg);

    const Compiler::CConstantUtf8Info& ClassName =
            Context.ConstantPool->GetChecked<Compiler::CConstantUtf8Info>(ClassInfo.GetNameIndex());

    Context.stream << "NEW " << ClassName.GetStringUtf8() << std::endl;
}
DEFINE_OPCODE_PRINTER(NEWARRAY)
{
    const u1 Arg = Context.NextByte();

    enum class ENewArrayElementType
    {
        T_BOOLEAN   = 4,
        T_CHAR      = 5,
        T_FLOAT     = 6,
        T_DOUBLE    = 7,
        T_BYTE      = 8,
        T_SHORT     = 9,
        T_INT       = 10,
        T_LONG      = 11,
    };

    const char* ArrayElementName = [Arg = (ENewArrayElementType)Arg]
    {
        switch(Arg)
        {
            case ENewArrayElementType::T_BOOLEAN:   return "T_BOOLEAN";
            case ENewArrayElementType::T_CHAR:      return "T_CHAR";
            case ENewArrayElementType::T_FLOAT:     return "T_FLOAT";
            case ENewArrayElementType::T_DOUBLE:    return "T_DOUBLE";
            case ENewArrayElementType::T_BYTE:      return "T_BYTE";
            case ENewArrayElementType::T_SHORT:     return "T_SHORT";
            case ENewArrayElementType::T_INT:       return "T_INT";
            case ENewArrayElementType::T_LONG:      return "T_LONG";

            default: return "<Unknown>";
        }
    }();

    Context.stream << "NEWARRAY " << ArrayElementName << std::endl;
}
DEFINE_OPCODE_PRINTER(ANEWARRAY)
{
    const u2 Arg = Context.NextU2();

    const Compiler::CConstantClassInfo& ClassInfo =
            Context.ConstantPool->GetChecked<Compiler::CConstantClassInfo>(Arg);

    const Compiler::CConstantUtf8Info& ClassName =
            Context.ConstantPool->GetChecked<Compiler::CConstantUtf8Info>(ClassInfo.GetNameIndex());

    Context.stream << "ANEWARRAY " << ClassName.GetStringUtf8() << std::endl;
}

// 190 - 199
DEFINE_OPCODE_PRINTER(ARRAYLENGTH)
{
    Context.stream << "ARRAYLENGTH " << std::endl;
}
DEFINE_OPCODE_PRINTER(ATHROW)
{
    Context.stream << "ATHROW " << std::endl;
}
DEFINE_OPCODE_PRINTER(CHECKCAST)
{
	const u2 Arg = Context.NextU2();

    const Compiler::CConstantClassInfo& ClassInfo =
            Context.ConstantPool->GetChecked<Compiler::CConstantClassInfo>(Arg);

    const Compiler::CConstantUtf8Info& ClassName =
            Context.ConstantPool->GetChecked<Compiler::CConstantUtf8Info>(ClassInfo.GetNameIndex());

    Context.stream << "CHECKCAST " << ClassName.GetStringUtf8() << std::endl;
}
DEFINE_OPCODE_PRINTER(INSTANCEOF)
{
	const u2 Arg = Context.NextU2();

    const Compiler::CConstantClassInfo& ClassInfo =
            Context.ConstantPool->GetChecked<Compiler::CConstantClassInfo>(Arg);

    const Compiler::CConstantUtf8Info& ClassName =
            Context.ConstantPool->GetChecked<Compiler::CConstantUtf8Info>(ClassInfo.GetNameIndex());

    Context.stream << "INSTANCEOF " << ClassName.GetStringUtf8() << std::endl;
}
DEFINE_OPCODE_PRINTER(MONITORENTER)
{
    Context.stream << "MONITORENTER" << std::endl;
}
DEFINE_OPCODE_PRINTER(MONITOREXIT)
{
    Context.stream << "MONITOREXIT" << std::endl;
}
DEFINE_OPCODE_PRINTER(WIDE)
{
    const u1 B1 = Context.NextByte();

    const COpcode& OpcodeToWide = COpcode::GetOpcodeForByte(B1);

    if (OpcodeToWide == COpcodes::IINC)
    {
        const u4 Arg = Context.NextU4();
	    Context.stream << "WIDE (32) " << Arg <<  std::endl;
    }
    else
    {
        const u2 Arg = Context.NextU2();
	    Context.stream << "WIDE (16) " << Arg << std::endl;
    }
}
DEFINE_OPCODE_PRINTER(MULTIANEWARRAY)
{
	const u2 Arg = Context.NextU2();
    const u1 B3 = Context.NextByte();

    Context.stream << "MULTIANEWARRAY " << Arg << std::endl;
}
DEFINE_OPCODE_PRINTER(IFNULL)
{
	const u2 Arg = Context.NextU2();

    Context.stream << "IFNULL " << Arg << std::endl;
}
DEFINE_OPCODE_PRINTER(IFNONNULL)
{
	const u2 Arg = Context.NextU2();

    Context.stream << "IFNONNULL " << Arg << std::endl;
}

// 200 - 201
DEFINE_OPCODE_PRINTER(GOTO_W)
{
	const u4 Arg = Context.NextU4();

    Context.stream << "GOTO_W " << Arg << std::endl;
}
DEFINE_OPCODE_PRINTER(JSR_W)
{
	const u4 Arg = Context.NextU4();

    Context.stream << "JSR_W " << Arg << std::endl;
}

#undef DEFINE_OPCODE_PRINTER



typedef void (*CPrintOpcodePtr)(const DebugBytecodePrinter::CDebugPrinterContext& Context);


#pragma region PrintOpcodeFunctions

#define OPCODE_PRINTER_REF(_Opcode) DebugBytecodePrinter::Print_##_Opcode

CPrintOpcodePtr PrintOpcodeFunctions[]
{
    // 0 - 9
    OPCODE_PRINTER_REF(NOP),
    OPCODE_PRINTER_REF(ACONST_NULL),
    OPCODE_PRINTER_REF(ICONST_M1),
    OPCODE_PRINTER_REF(ICONST_0),
    OPCODE_PRINTER_REF(ICONST_1),
    OPCODE_PRINTER_REF(ICONST_2),
    OPCODE_PRINTER_REF(ICONST_3),
    OPCODE_PRINTER_REF(ICONST_4),
    OPCODE_PRINTER_REF(ICONST_5),
    OPCODE_PRINTER_REF(LCONST_0),

    // 10 - 19
    OPCODE_PRINTER_REF(LCONST_1),
    OPCODE_PRINTER_REF(FCONST_0),
    OPCODE_PRINTER_REF(FCONST_1),
    OPCODE_PRINTER_REF(FCONST_2),
    OPCODE_PRINTER_REF(DCONST_0),
    OPCODE_PRINTER_REF(DCONST_1),
    OPCODE_PRINTER_REF(BIPUSH),
    OPCODE_PRINTER_REF(SIPUSH),
    OPCODE_PRINTER_REF(LDC),
    OPCODE_PRINTER_REF(LDC_W),

    // 20 - 29
    OPCODE_PRINTER_REF(LDC2_W),
    OPCODE_PRINTER_REF(ILOAD),
    OPCODE_PRINTER_REF(LLOAD),
    OPCODE_PRINTER_REF(FLOAD),
    OPCODE_PRINTER_REF(DLOAD),
    OPCODE_PRINTER_REF(ALOAD),
    OPCODE_PRINTER_REF(ILOAD_0),
    OPCODE_PRINTER_REF(ILOAD_1),
    OPCODE_PRINTER_REF(ILOAD_2),
    OPCODE_PRINTER_REF(ILOAD_3),

    // 30 - 39
    OPCODE_PRINTER_REF(LLOAD_0),
    OPCODE_PRINTER_REF(LLOAD_1),
    OPCODE_PRINTER_REF(LLOAD_2),
    OPCODE_PRINTER_REF(LLOAD_3),
    OPCODE_PRINTER_REF(FLOAD_0),
    OPCODE_PRINTER_REF(FLOAD_1),
    OPCODE_PRINTER_REF(FLOAD_2),
    OPCODE_PRINTER_REF(FLOAD_3),
    OPCODE_PRINTER_REF(DLOAD_0),
    OPCODE_PRINTER_REF(DLOAD_1),

    // 40 - 49
    OPCODE_PRINTER_REF(DLOAD_2),
    OPCODE_PRINTER_REF(DLOAD_3),
    OPCODE_PRINTER_REF(ALOAD_0),
    OPCODE_PRINTER_REF(ALOAD_1),
    OPCODE_PRINTER_REF(ALOAD_2),
    OPCODE_PRINTER_REF(ALOAD_3),
    OPCODE_PRINTER_REF(IALOAD),
    OPCODE_PRINTER_REF(LALOAD),
    OPCODE_PRINTER_REF(FALOAD),
    OPCODE_PRINTER_REF(DALOAD),

    // 50 - 59
    OPCODE_PRINTER_REF(AALOAD),
    OPCODE_PRINTER_REF(BALOAD),
    OPCODE_PRINTER_REF(CALOAD),
    OPCODE_PRINTER_REF(SALOAD),
    OPCODE_PRINTER_REF(ISTORE),
    OPCODE_PRINTER_REF(LSTORE),
    OPCODE_PRINTER_REF(FSTORE),
    OPCODE_PRINTER_REF(DSTORE),
    OPCODE_PRINTER_REF(ASTORE),
    OPCODE_PRINTER_REF(ISTORE_0),

    // 60 - 69
    OPCODE_PRINTER_REF(ISTORE_1),
    OPCODE_PRINTER_REF(ISTORE_2),
    OPCODE_PRINTER_REF(ISTORE_3),
    OPCODE_PRINTER_REF(LSTORE_0),
    OPCODE_PRINTER_REF(LSTORE_1),
    OPCODE_PRINTER_REF(LSTORE_2),
    OPCODE_PRINTER_REF(LSTORE_3),
    OPCODE_PRINTER_REF(FSTORE_0),
    OPCODE_PRINTER_REF(FSTORE_1),
    OPCODE_PRINTER_REF(FSTORE_2),

    // 70 - 79
    OPCODE_PRINTER_REF(FSTORE_3),
    OPCODE_PRINTER_REF(DSTORE_0),
    OPCODE_PRINTER_REF(DSTORE_1),
    OPCODE_PRINTER_REF(DSTORE_2),
    OPCODE_PRINTER_REF(DSTORE_3),
    OPCODE_PRINTER_REF(ASTORE_0),
    OPCODE_PRINTER_REF(ASTORE_1),
    OPCODE_PRINTER_REF(ASTORE_2),
    OPCODE_PRINTER_REF(ASTORE_3),
    OPCODE_PRINTER_REF(IASTORE),

    // 80 - 89
    OPCODE_PRINTER_REF(LASTORE),
    OPCODE_PRINTER_REF(FASTORE),
    OPCODE_PRINTER_REF(DASTORE),
    OPCODE_PRINTER_REF(AASTORE),
    OPCODE_PRINTER_REF(BASTORE),
    OPCODE_PRINTER_REF(CASTORE),
    OPCODE_PRINTER_REF(SASTORE),
    OPCODE_PRINTER_REF(POP),
    OPCODE_PRINTER_REF(POP2),
    OPCODE_PRINTER_REF(DUP),

    // 90 - 99
    OPCODE_PRINTER_REF(DUP_X1),
    OPCODE_PRINTER_REF(DUP_X2),
    OPCODE_PRINTER_REF(DUP2),
    OPCODE_PRINTER_REF(DUP2_X1),
    OPCODE_PRINTER_REF(DUP2_X2),
    OPCODE_PRINTER_REF(SWAP),
    OPCODE_PRINTER_REF(IADD),
    OPCODE_PRINTER_REF(LADD),
    OPCODE_PRINTER_REF(FADD),
    OPCODE_PRINTER_REF(DADD),

    // 100 - 109
    OPCODE_PRINTER_REF(ISUB),
    OPCODE_PRINTER_REF(LSUB),
    OPCODE_PRINTER_REF(FSUB),
    OPCODE_PRINTER_REF(DSUB),
    OPCODE_PRINTER_REF(IMUL),
    OPCODE_PRINTER_REF(LMUL),
    OPCODE_PRINTER_REF(FMUL),
    OPCODE_PRINTER_REF(DMUL),
    OPCODE_PRINTER_REF(IDIV),
    OPCODE_PRINTER_REF(LDIV),

    // 110 - 119
    OPCODE_PRINTER_REF(FDIV),
    OPCODE_PRINTER_REF(DDIV),
    OPCODE_PRINTER_REF(IREM),
    OPCODE_PRINTER_REF(LREM),
    OPCODE_PRINTER_REF(FREM),
    OPCODE_PRINTER_REF(DREM),
    OPCODE_PRINTER_REF(INEG),
    OPCODE_PRINTER_REF(LNEG),
    OPCODE_PRINTER_REF(FNEG),
    OPCODE_PRINTER_REF(DNEG),

    // 120 - 129
    OPCODE_PRINTER_REF(ISHL),
    OPCODE_PRINTER_REF(LSHL),
    OPCODE_PRINTER_REF(ISHR),
    OPCODE_PRINTER_REF(LSHR),
    OPCODE_PRINTER_REF(IUSHR),
    OPCODE_PRINTER_REF(LUSHR),
    OPCODE_PRINTER_REF(IAND),
    OPCODE_PRINTER_REF(LAND),
    OPCODE_PRINTER_REF(IOR),
    OPCODE_PRINTER_REF(LOR),

    // 130 - 139
    OPCODE_PRINTER_REF(IXOR),
    OPCODE_PRINTER_REF(LXOR),
    OPCODE_PRINTER_REF(IINC),
    OPCODE_PRINTER_REF(I2L),
    OPCODE_PRINTER_REF(I2F),
    OPCODE_PRINTER_REF(I2D),
    OPCODE_PRINTER_REF(L2I),
    OPCODE_PRINTER_REF(L2F),
    OPCODE_PRINTER_REF(L2D),
    OPCODE_PRINTER_REF(F2I),

    // 140 - 149
    OPCODE_PRINTER_REF(F2L),
    OPCODE_PRINTER_REF(F2D),
    OPCODE_PRINTER_REF(D2I),
    OPCODE_PRINTER_REF(D2L),
    OPCODE_PRINTER_REF(D2F),
    OPCODE_PRINTER_REF(I2B),
    OPCODE_PRINTER_REF(I2C),
    OPCODE_PRINTER_REF(I2S),
    OPCODE_PRINTER_REF(LCMP),
    OPCODE_PRINTER_REF(FCMPL),

    // 150 - 159
    OPCODE_PRINTER_REF(FCMPG),
    OPCODE_PRINTER_REF(DCMPL),
    OPCODE_PRINTER_REF(DCMPG),
    OPCODE_PRINTER_REF(IFEQ),
    OPCODE_PRINTER_REF(IFNE),
    OPCODE_PRINTER_REF(IFLT),
    OPCODE_PRINTER_REF(IFGE),
    OPCODE_PRINTER_REF(IFGT),
    OPCODE_PRINTER_REF(IFLE),
    OPCODE_PRINTER_REF(IF_ICMPEQ),

    // 160 - 169
    OPCODE_PRINTER_REF(IF_ICMPNE),
    OPCODE_PRINTER_REF(IF_ICMPLT),
    OPCODE_PRINTER_REF(IF_ICMPGE),
    OPCODE_PRINTER_REF(IF_ICMPGT),
    OPCODE_PRINTER_REF(IF_ICMPLE),
    OPCODE_PRINTER_REF(IF_ACMPEQ),
    OPCODE_PRINTER_REF(IF_ACMPNE),
    OPCODE_PRINTER_REF(GOTO),
    OPCODE_PRINTER_REF(JSR),
    OPCODE_PRINTER_REF(RET),

    // 170 - 179
    OPCODE_PRINTER_REF(TABLESWITCH),
    OPCODE_PRINTER_REF(LOOKUPSWITCH),
    OPCODE_PRINTER_REF(IRETURN),
    OPCODE_PRINTER_REF(LRETURN),
    OPCODE_PRINTER_REF(FRETURN),
    OPCODE_PRINTER_REF(DRETURN),
    OPCODE_PRINTER_REF(ARETURN),
    OPCODE_PRINTER_REF(RETURN),
    OPCODE_PRINTER_REF(GETSTATIC),
    OPCODE_PRINTER_REF(PUTSTATIC),

    // 180 - 189
    OPCODE_PRINTER_REF(GETFIELD),
    OPCODE_PRINTER_REF(PUTFIELD),
    OPCODE_PRINTER_REF(INVOKEVIRTUAL),
    OPCODE_PRINTER_REF(INVOKESPECIAL),
    OPCODE_PRINTER_REF(INVOKESTATIC),
    OPCODE_PRINTER_REF(INVOKEINTERFACE),
    OPCODE_PRINTER_REF(INVOKEDYNAMIC),
    OPCODE_PRINTER_REF(NEW),
    OPCODE_PRINTER_REF(NEWARRAY),
    OPCODE_PRINTER_REF(ANEWARRAY),

    // 190 - 199
    OPCODE_PRINTER_REF(ARRAYLENGTH),
    OPCODE_PRINTER_REF(ATHROW),
    OPCODE_PRINTER_REF(CHECKCAST),
    OPCODE_PRINTER_REF(INSTANCEOF),
    OPCODE_PRINTER_REF(MONITORENTER),
    OPCODE_PRINTER_REF(MONITOREXIT),
    OPCODE_PRINTER_REF(WIDE),
    OPCODE_PRINTER_REF(MULTIANEWARRAY),
    OPCODE_PRINTER_REF(IFNULL),
    OPCODE_PRINTER_REF(IFNONNULL),

    // 200 - 201
    OPCODE_PRINTER_REF(GOTO_W),
    OPCODE_PRINTER_REF(JSR_W)
};

#undef OPCODE_PRINTER_REF

#pragma endregion

namespace DebugBytecodePrinter
{
    using Bytecode::COpcode;

    void PrintBytecode(CDebugPrinterContext& DebugPrinterContext)
    {
        while (!DebugPrinterContext.IsAtEnd())
        {
            const u1 RawByte = DebugPrinterContext.NextByte();

            CPrintOpcodePtr PrintOpcodePtr = PrintOpcodeFunctions[static_cast<usz>(RawByte)];

            PrintOpcodePtr(DebugPrinterContext);
        }
    }
}