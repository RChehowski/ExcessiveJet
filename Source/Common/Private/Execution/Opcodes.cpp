//
// Created by ASUS on 31/12/2020.
//

#include "Common/Public/Execution/Opcodes.h"
#include "OpcodeExecutionTemplates.h"


#include <algorithm>


namespace Bytecode::OpcodeHandlers
{
#define DEFINE_OPCODE_HANDLER(Opcode) void Handle_##Opcode(VM::CExecutionContext& Context, const Util::CAllocationRef ConstantParameters)

#pragma region Opcode handler definition
    // 0 - 9
    DEFINE_OPCODE_HANDLER(NOP)
    {
        // Deliberately do nothing
    }
    DEFINE_OPCODE_HANDLER(ACONST_NULL)
    {
        Context.GetThreadStack().Push<oop>(Null);
    }
    DEFINE_OPCODE_HANDLER(ICONST_M1)
    {
        Context.GetThreadStack().Push<s4>(-1);
    }
    DEFINE_OPCODE_HANDLER(ICONST_0)
    {
        Context.GetThreadStack().Push<s4>(0);
    }
    DEFINE_OPCODE_HANDLER(ICONST_1)
    {
        Context.GetThreadStack().Push<s4>(1);
    }
    DEFINE_OPCODE_HANDLER(ICONST_2)
    {
        Context.GetThreadStack().Push<s4>(2);
    }
    DEFINE_OPCODE_HANDLER(ICONST_3)
    {
        Context.GetThreadStack().Push<s4>(3);
    }
    DEFINE_OPCODE_HANDLER(ICONST_4)
    {
        Context.GetThreadStack().Push<s4>(4);
    }
    DEFINE_OPCODE_HANDLER(ICONST_5)
    {
        Context.GetThreadStack().Push<s4>(5);
    }
    DEFINE_OPCODE_HANDLER(LCONST_0)
    {
        Context.GetThreadStack().Push<s8>(0);
    }

    // 10 - 19
    DEFINE_OPCODE_HANDLER(LCONST_1)
    {
        Context.GetThreadStack().Push<s8>(1);
    }
    DEFINE_OPCODE_HANDLER(FCONST_0)
    {
        Context.GetThreadStack().Push<float>(0.0f);
    }
    DEFINE_OPCODE_HANDLER(FCONST_1)
    {
        Context.GetThreadStack().Push<float>(1.0f);
    }
    DEFINE_OPCODE_HANDLER(FCONST_2)
    {
        Context.GetThreadStack().Push<float>(2.0f);
    }
    DEFINE_OPCODE_HANDLER(DCONST_0)
    {
        Context.GetThreadStack().Push<double>(0.0);
    }
    DEFINE_OPCODE_HANDLER(DCONST_1)
    {
        Context.GetThreadStack().Push<double>(1.0);
    }
    DEFINE_OPCODE_HANDLER(BIPUSH)
    {
        const s1 Value = ConstantParameters.template GetAsWhole<s1>();
        Context.GetThreadStack().template Push<s4>(static_cast<s4>(Value));
    }
    DEFINE_OPCODE_HANDLER(SIPUSH)
    {
        const s2 Value = ConstantParameters.template GetAsWhole<s2>();
        Context.GetThreadStack().template Push<s4>(static_cast<s4>(Value));
    }
    DEFINE_OPCODE_HANDLER(LDC)
    {
    }
    DEFINE_OPCODE_HANDLER(LDC_W)
    {
    }

    // 20 - 29
    DEFINE_OPCODE_HANDLER(LDC2_W)
    {
    }
    DEFINE_OPCODE_HANDLER(ILOAD)
    {
        const u1 Index = ConstantParameters.template GetAsWhole<u1>();
        Util::GenericLoadFromLocalVar<s4>(Context.GetThreadStack(), Context.GetLocalVariables(), Index);
    }
    DEFINE_OPCODE_HANDLER(LLOAD)
    {
        const u1 Index = ConstantParameters.template GetAsWhole<u1>();
        Util::GenericLoadFromLocalVar<s8>(Context.GetThreadStack(), Context.GetLocalVariables(), Index);
    }
    DEFINE_OPCODE_HANDLER(FLOAD)
    {
        const u1 Index = ConstantParameters.template GetAsWhole<u1>();
        Util::GenericLoadFromLocalVar<float>(Context.GetThreadStack(), Context.GetLocalVariables(), Index);
    }
    DEFINE_OPCODE_HANDLER(DLOAD)
    {
        const u1 Index = ConstantParameters.template GetAsWhole<u1>();
        Util::GenericLoadFromLocalVar<double>(Context.GetThreadStack(), Context.GetLocalVariables(), Index);
    }
    DEFINE_OPCODE_HANDLER(ALOAD)
    {
        const u1 Index = ConstantParameters.template GetAsWhole<u1>();
        Util::GenericLoadFromLocalVar<oop>(Context.GetThreadStack(), Context.GetLocalVariables(), Index);
    }
    DEFINE_OPCODE_HANDLER(ILOAD_0)
    {
        Util::GenericLoadFromLocalVar<s4>(Context.GetThreadStack(), Context.GetLocalVariables(), 0);
    }
    DEFINE_OPCODE_HANDLER(ILOAD_1)
    {
        Util::GenericLoadFromLocalVar<s4>(Context.GetThreadStack(), Context.GetLocalVariables(), 1);
    }
    DEFINE_OPCODE_HANDLER(ILOAD_2)
    {
        Util::GenericLoadFromLocalVar<s4>(Context.GetThreadStack(), Context.GetLocalVariables(), 2);
    }
    DEFINE_OPCODE_HANDLER(ILOAD_3)
    {
        Util::GenericLoadFromLocalVar<s4>(Context.GetThreadStack(), Context.GetLocalVariables(), 3);
    }

    // 30 - 39
    DEFINE_OPCODE_HANDLER(LLOAD_0)
    {
        Util::GenericLoadFromLocalVar<s8>(Context.GetThreadStack(), Context.GetLocalVariables(), 0);
    }
    DEFINE_OPCODE_HANDLER(LLOAD_1)
    {
        Util::GenericLoadFromLocalVar<s8>(Context.GetThreadStack(), Context.GetLocalVariables(), 1);
    }
    DEFINE_OPCODE_HANDLER(LLOAD_2)
    {
        Util::GenericLoadFromLocalVar<s8>(Context.GetThreadStack(), Context.GetLocalVariables(), 2);
    }
    DEFINE_OPCODE_HANDLER(LLOAD_3)
    {
        Util::GenericLoadFromLocalVar<s8>(Context.GetThreadStack(), Context.GetLocalVariables(), 3);
    }
    DEFINE_OPCODE_HANDLER(FLOAD_0)
    {
        Util::GenericLoadFromLocalVar<float>(Context.GetThreadStack(), Context.GetLocalVariables(), 0);
    }
    DEFINE_OPCODE_HANDLER(FLOAD_1)
    {
        Util::GenericLoadFromLocalVar<float>(Context.GetThreadStack(), Context.GetLocalVariables(), 1);
    }
    DEFINE_OPCODE_HANDLER(FLOAD_2)
    {
        Util::GenericLoadFromLocalVar<float>(Context.GetThreadStack(), Context.GetLocalVariables(), 2);
    }
    DEFINE_OPCODE_HANDLER(FLOAD_3)
    {
        Util::GenericLoadFromLocalVar<float>(Context.GetThreadStack(), Context.GetLocalVariables(), 3);
    }
    DEFINE_OPCODE_HANDLER(DLOAD_0)
    {
        Util::GenericLoadFromLocalVar<double>(Context.GetThreadStack(), Context.GetLocalVariables(), 0);
    }
    DEFINE_OPCODE_HANDLER(DLOAD_1)
    {
        Util::GenericLoadFromLocalVar<double>(Context.GetThreadStack(), Context.GetLocalVariables(), 1);
    }

    // 40 - 49
    DEFINE_OPCODE_HANDLER(DLOAD_2)
    {
        Util::GenericLoadFromLocalVar<double>(Context.GetThreadStack(), Context.GetLocalVariables(), 2);
    }
    DEFINE_OPCODE_HANDLER(DLOAD_3)
    {
        Util::GenericLoadFromLocalVar<double>(Context.GetThreadStack(), Context.GetLocalVariables(), 3);
    }
    DEFINE_OPCODE_HANDLER(ALOAD_0)
    {
        Util::GenericLoadFromLocalVar<oop>(Context.GetThreadStack(), Context.GetLocalVariables(), 0);
    }
    DEFINE_OPCODE_HANDLER(ALOAD_1)
    {
        Util::GenericLoadFromLocalVar<oop>(Context.GetThreadStack(), Context.GetLocalVariables(), 1);
    }
    DEFINE_OPCODE_HANDLER(ALOAD_2)
    {
        Util::GenericLoadFromLocalVar<oop>(Context.GetThreadStack(), Context.GetLocalVariables(), 2);
    }
    DEFINE_OPCODE_HANDLER(ALOAD_3)
    {
        Util::GenericLoadFromLocalVar<oop>(Context.GetThreadStack(), Context.GetLocalVariables(), 3);
    }
    DEFINE_OPCODE_HANDLER(IALOAD)
    {
    }
    DEFINE_OPCODE_HANDLER(LALOAD)
    {
    }
    DEFINE_OPCODE_HANDLER(FALOAD)
    {
    }
    DEFINE_OPCODE_HANDLER(DALOAD)
    {
    }

    // 50 - 59
    DEFINE_OPCODE_HANDLER(AALOAD)
    {
    }
    DEFINE_OPCODE_HANDLER(BALOAD)
    {
    }
    DEFINE_OPCODE_HANDLER(CALOAD)
    {
    }
    DEFINE_OPCODE_HANDLER(SALOAD)
    {
    }
    DEFINE_OPCODE_HANDLER(ISTORE)
    {
        const u1 Index = ConstantParameters.template GetAsWhole<u1>();
        Util::GenericStoreToLocalVar<s4>(Context.GetThreadStack(), Context.GetLocalVariables(), Index);
    }
    DEFINE_OPCODE_HANDLER(LSTORE)
    {
        const u1 Index = ConstantParameters.template GetAsWhole<u1>();
        Util::GenericStoreToLocalVar<s8>(Context.GetThreadStack(), Context.GetLocalVariables(), Index);
    }
    DEFINE_OPCODE_HANDLER(FSTORE)
    {
        const u1 Index = ConstantParameters.template GetAsWhole<u1>();
        Util::GenericStoreToLocalVar<float>(Context.GetThreadStack(), Context.GetLocalVariables(), Index);
    }
    DEFINE_OPCODE_HANDLER(DSTORE)
    {
        const u1 Index = ConstantParameters.template GetAsWhole<u1>();
        Util::GenericStoreToLocalVar<double>(Context.GetThreadStack(), Context.GetLocalVariables(), Index);
    }
    DEFINE_OPCODE_HANDLER(ASTORE)
    {
        const u1 Index = ConstantParameters.template GetAsWhole<u1>();
        Util::GenericStoreToLocalVar<oop>(Context.GetThreadStack(), Context.GetLocalVariables(), Index);
    }
    DEFINE_OPCODE_HANDLER(ISTORE_0)
    {
        Util::GenericStoreToLocalVar<s4>(Context.GetThreadStack(), Context.GetLocalVariables(), 0);
    }

    // 60 - 69
    DEFINE_OPCODE_HANDLER(ISTORE_1)
    {
        Util::GenericStoreToLocalVar<s4>(Context.GetThreadStack(), Context.GetLocalVariables(), 1);
    }
    DEFINE_OPCODE_HANDLER(ISTORE_2)
    {
        Util::GenericStoreToLocalVar<s4>(Context.GetThreadStack(), Context.GetLocalVariables(), 2);
    }
    DEFINE_OPCODE_HANDLER(ISTORE_3)
    {
        Util::GenericStoreToLocalVar<s4>(Context.GetThreadStack(), Context.GetLocalVariables(), 3);
    }
    DEFINE_OPCODE_HANDLER(LSTORE_0)
    {
        Util::GenericStoreToLocalVar<s8>(Context.GetThreadStack(), Context.GetLocalVariables(), 0);
    }
    DEFINE_OPCODE_HANDLER(LSTORE_1)
    {
        Util::GenericStoreToLocalVar<s8>(Context.GetThreadStack(), Context.GetLocalVariables(), 1);
    }
    DEFINE_OPCODE_HANDLER(LSTORE_2)
    {
        Util::GenericStoreToLocalVar<s8>(Context.GetThreadStack(), Context.GetLocalVariables(), 2);
    }
    DEFINE_OPCODE_HANDLER(LSTORE_3)
    {
        Util::GenericStoreToLocalVar<s8>(Context.GetThreadStack(), Context.GetLocalVariables(), 3);
    }
    DEFINE_OPCODE_HANDLER(FSTORE_0)
    {
        Util::GenericStoreToLocalVar<float>(Context.GetThreadStack(), Context.GetLocalVariables(), 0);
    }
    DEFINE_OPCODE_HANDLER(FSTORE_1)
    {
        Util::GenericStoreToLocalVar<float>(Context.GetThreadStack(), Context.GetLocalVariables(), 1);
    }
    DEFINE_OPCODE_HANDLER(FSTORE_2)
    {
        Util::GenericStoreToLocalVar<float>(Context.GetThreadStack(), Context.GetLocalVariables(), 2);
    }

    // 70 - 79
    DEFINE_OPCODE_HANDLER(FSTORE_3)
    {
        Util::GenericStoreToLocalVar<float>(Context.GetThreadStack(), Context.GetLocalVariables(), 3);
    }
    DEFINE_OPCODE_HANDLER(DSTORE_0)
    {
        Util::GenericStoreToLocalVar<double>(Context.GetThreadStack(), Context.GetLocalVariables(), 0);
    }
    DEFINE_OPCODE_HANDLER(DSTORE_1)
    {
        Util::GenericStoreToLocalVar<double>(Context.GetThreadStack(), Context.GetLocalVariables(), 1);
    }
    DEFINE_OPCODE_HANDLER(DSTORE_2)
    {
        Util::GenericStoreToLocalVar<double>(Context.GetThreadStack(), Context.GetLocalVariables(), 2);
    }
    DEFINE_OPCODE_HANDLER(DSTORE_3)
    {
        Util::GenericStoreToLocalVar<double>(Context.GetThreadStack(), Context.GetLocalVariables(), 3);
    }
    DEFINE_OPCODE_HANDLER(ASTORE_0)
    {
        Util::GenericStoreToLocalVar<oop>(Context.GetThreadStack(), Context.GetLocalVariables(), 0);
    }
    DEFINE_OPCODE_HANDLER(ASTORE_1)
    {
        Util::GenericStoreToLocalVar<oop>(Context.GetThreadStack(), Context.GetLocalVariables(), 1);
    }
    DEFINE_OPCODE_HANDLER(ASTORE_2)
    {
        Util::GenericStoreToLocalVar<oop>(Context.GetThreadStack(), Context.GetLocalVariables(), 2);
    }
    DEFINE_OPCODE_HANDLER(ASTORE_3)
    {
        Util::GenericStoreToLocalVar<oop>(Context.GetThreadStack(), Context.GetLocalVariables(), 3);
    }
    DEFINE_OPCODE_HANDLER(IASTORE)
    {
    }

    // 80 - 89
    DEFINE_OPCODE_HANDLER(LASTORE)
    {
    }
    DEFINE_OPCODE_HANDLER(FASTORE)
    {
    }
    DEFINE_OPCODE_HANDLER(DASTORE)
    {
    }
    DEFINE_OPCODE_HANDLER(AASTORE)
    {
    }
    DEFINE_OPCODE_HANDLER(BASTORE)
    {
    }
    DEFINE_OPCODE_HANDLER(CASTORE)
    {
    }
    DEFINE_OPCODE_HANDLER(SASTORE)
    {
    }
    DEFINE_OPCODE_HANDLER(POP)
    {
        Context.GetThreadStack().PopDiscard(1);
    }
    DEFINE_OPCODE_HANDLER(POP2)
    {
        Context.GetThreadStack().PopDiscard(2);
    }
    DEFINE_OPCODE_HANDLER(DUP)
    {
        Context.GetThreadStack().Dup();
    }

    // 90 - 99
    DEFINE_OPCODE_HANDLER(DUP_X1)
    {
        Context.GetThreadStack().DupX1();
    }
    DEFINE_OPCODE_HANDLER(DUP_X2)
    {
        Context.GetThreadStack().DupX1();
    }
    DEFINE_OPCODE_HANDLER(DUP2)
    {
        Context.GetThreadStack().Dup2();
    }
    DEFINE_OPCODE_HANDLER(DUP2_X1)
    {
        Context.GetThreadStack().Dup2X1();
    }
    DEFINE_OPCODE_HANDLER(DUP2_X2)
    {
        Context.GetThreadStack().Dup2X2();
    }
    DEFINE_OPCODE_HANDLER(SWAP)
    {
        Context.GetThreadStack().Swap();
    }
    DEFINE_OPCODE_HANDLER(IADD)
    {
        Util::GenericAdd<s4>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(LADD)
    {
        Util::GenericAdd<s8>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(FADD)
    {
        Util::GenericAdd<float>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(DADD)
    {
        Util::GenericAdd<double>(Context.GetThreadStack());
    }

    // 100 - 109
    DEFINE_OPCODE_HANDLER(ISUB)
    {
        Util::GenericSub<s4>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(LSUB)
    {
        Util::GenericSub<s8>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(FSUB)
    {
        Util::GenericSub<float>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(DSUB)
    {
        Util::GenericSub<double>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(IMUL)
    {
        Util::GenericMul<s4>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(LMUL)
    {
        Util::GenericMul<s8>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(FMUL)
    {
        Util::GenericMul<float>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(DMUL)
    {
        Util::GenericMul<double>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(IDIV)
    {
        Util::GenericDiv<s4>(Context);
    }
    DEFINE_OPCODE_HANDLER(LDIV)
    {
        Util::GenericDiv<s8>(Context);
    }

    // 110 - 119
    DEFINE_OPCODE_HANDLER(FDIV)
    {
        Util::GenericDiv<float>(Context);
    }
    DEFINE_OPCODE_HANDLER(DDIV)
    {
        Util::GenericDiv<double>(Context);
    }
    DEFINE_OPCODE_HANDLER(IREM)
    {
        Util::GenericRem<s4>(Context);
    }
    DEFINE_OPCODE_HANDLER(LREM)
    {
        Util::GenericRem<s8>(Context);
    }
    DEFINE_OPCODE_HANDLER(FREM)
    {
        Util::GenericRem<float>(Context);
    }
    DEFINE_OPCODE_HANDLER(DREM)
    {
        Util::GenericRem<double>(Context);
    }
    DEFINE_OPCODE_HANDLER(INEG)
    {
        Util::GenericNeg<s4>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(LNEG)
    {
        Util::GenericNeg<s8>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(FNEG)
    {
        Util::GenericNeg<float>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(DNEG)
    {
        Util::GenericNeg<double>(Context.GetThreadStack());
    }

    // 120 - 129
    DEFINE_OPCODE_HANDLER(ISHL)
    {
    }
    DEFINE_OPCODE_HANDLER(LSHL)
    {
    }
    DEFINE_OPCODE_HANDLER(ISHR)
    {
    }
    DEFINE_OPCODE_HANDLER(LSHR)
    {
    }
    DEFINE_OPCODE_HANDLER(IUSHR)
    {
    }
    DEFINE_OPCODE_HANDLER(LUSHR)
    {
    }
    DEFINE_OPCODE_HANDLER(IAND)
    {
        Util::GenericAnd<s4>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(LAND)
    {
        Util::GenericAnd<s8>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(IOR)
    {
        Util::GenericOr<s4>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(LOR)
    {
        Util::GenericOr<s8>(Context.GetThreadStack());
    }

    // 130 - 139
    DEFINE_OPCODE_HANDLER(IXOR)
    {
        Util::GenericXor<s4>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(LXOR)
    {
        Util::GenericXor<s8>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(IINC)
    {
        struct CStructure
        {
            const u1 Index;
            const s1 Constant;
        }
        Structure = ConstantParameters.template GetAsWhole<CStructure>();

        const u2 Index = static_cast<u2>(Structure.Index);

        const s4 Value = Context.GetLocalVariables().Get<s4>(Index);
        Context.GetLocalVariables().Set(Index, Value + static_cast<s4>(Structure.Constant));
    }
    DEFINE_OPCODE_HANDLER(I2L)
    {
        Util::CastOnStack<s4, s8>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(I2F)
    {
        Util::CastOnStack<s4, float>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(I2D)
    {
        Util::CastOnStack<s4, double>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(L2I)
    {
        Util::CastOnStack<s8, s4>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(L2F)
    {
        Util::CastOnStack<s8, float>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(L2D)
    {
        Util::CastOnStack<s8, double>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(F2I)
    {
        Util::CastOnStack<float, s4>(Context.GetThreadStack());
    }

    // 140 - 149
    DEFINE_OPCODE_HANDLER(F2L)
    {
        Util::CastOnStack<float, s8>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(F2D)
    {
        Util::CastOnStack<float, double>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(D2I)
    {
        Util::CastOnStack<double, s4>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(D2L)
    {
        Util::CastOnStack<double, s8>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(D2F)
    {
        Util::CastOnStack<double, float>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(I2B)
    {
        Util::CastOnStack<s4, s1>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(I2C)
    {
        Util::CastOnStack<s4, u2>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(I2S)
    {
        Util::CastOnStack<s4, s2>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(LCMP)
    {
        VM::CThreadStack& ThreadStack = Context.GetThreadStack();

        const s8 Value1 = ThreadStack.Pop<s8>();
        const s8 Value2 = ThreadStack.Pop<s8>();

        if (Value1 > Value2)
        {
            ThreadStack.Push<s4>(1);
        }
        else if (Value1 < Value2)
        {
            ThreadStack.Push<s4>(-1);
        }
        else
        {
            ASSERT(Value1 == Value2);
            ThreadStack.Push(0);
        }
    }
    DEFINE_OPCODE_HANDLER(FCMPL)
    {
        VM::CThreadStack& ThreadStack = Context.GetThreadStack();

        const float Value1 = ThreadStack.Pop<float>();
        const float Value2 = ThreadStack.Pop<float>();

        // TODO: Finish
    }

    // 150 - 159
    DEFINE_OPCODE_HANDLER(FCMPG)
    {
    }
    DEFINE_OPCODE_HANDLER(DCMPL)
    {
    }
    DEFINE_OPCODE_HANDLER(DCMPG)
    {
    }
    DEFINE_OPCODE_HANDLER(IFEQ)
    {
        const bool bResult = Util::GenericCompareIntZero<Util::ECompareOperation::EQ>(Context.GetThreadStack());
        Context.template SetConditionResult<bool>(bResult);
    }
    DEFINE_OPCODE_HANDLER(IFNE)
    {
        const bool bResult = Util::GenericCompareIntZero<Util::ECompareOperation::NE>(Context.GetThreadStack());
        Context.template SetConditionResult<bool>(bResult);
    }
    DEFINE_OPCODE_HANDLER(IFLT)
    {
        const bool bResult = Util::GenericCompareIntZero<Util::ECompareOperation::LT>(Context.GetThreadStack());
        Context.template SetConditionResult<bool>(bResult);
    }
    DEFINE_OPCODE_HANDLER(IFGE)
    {
        const bool bResult = Util::GenericCompareIntZero<Util::ECompareOperation::GE>(Context.GetThreadStack());
        Context.template SetConditionResult<bool>(bResult);
    }
    DEFINE_OPCODE_HANDLER(IFGT)
    {
        const bool bResult = Util::GenericCompareIntZero<Util::ECompareOperation::GT>(Context.GetThreadStack());
        Context.template SetConditionResult<bool>(bResult);
    }
    DEFINE_OPCODE_HANDLER(IFLE)
    {
        const bool bResult = Util::GenericCompareIntZero<Util::ECompareOperation::LE>(Context.GetThreadStack());
        Context.template SetConditionResult<bool>(bResult);
    }
    DEFINE_OPCODE_HANDLER(IF_ICMPEQ)
    {
        const bool bResult = Util::GenericCompare2<s4, Util::ECompareOperation::EQ>(Context.GetThreadStack());
        Context.template SetConditionResult<bool>(bResult);
    }

    // 160 - 169
    DEFINE_OPCODE_HANDLER(IF_ICMPNE)
    {
        const bool bResult = Util::GenericCompare2<s4, Util::ECompareOperation::NE>(Context.GetThreadStack());
        Context.template SetConditionResult<bool>(bResult);
    }
    DEFINE_OPCODE_HANDLER(IF_ICMPLT)
    {
        const bool bResult = Util::GenericCompare2<s4, Util::ECompareOperation::LT>(Context.GetThreadStack());
        Context.template SetConditionResult<bool>(bResult);
    }
    DEFINE_OPCODE_HANDLER(IF_ICMPGE)
    {
        const bool bResult = Util::GenericCompare2<s4, Util::ECompareOperation::GE>(Context.GetThreadStack());
        Context.template SetConditionResult<bool>(bResult);
    }
    DEFINE_OPCODE_HANDLER(IF_ICMPGT)
    {
        const bool bResult = Util::GenericCompare2<s4, Util::ECompareOperation::GT>(Context.GetThreadStack());
        Context.template SetConditionResult<bool>(bResult);
    }
    DEFINE_OPCODE_HANDLER(IF_ICMPLE)
    {
        const bool bResult = Util::GenericCompare2<s4, Util::ECompareOperation::LE>(Context.GetThreadStack());
        Context.template SetConditionResult<bool>(bResult);
    }
    DEFINE_OPCODE_HANDLER(IF_ACMPEQ)
    {
        const bool bResult = Util::GenericCompare2<oop, Util::ECompareOperation::EQ>(Context.GetThreadStack());
        Context.template SetConditionResult<bool>(bResult);
    }
    DEFINE_OPCODE_HANDLER(IF_ACMPNE)
    {
        const bool bResult = Util::GenericCompare2<oop, Util::ECompareOperation::NE>(Context.GetThreadStack());
        Context.template SetConditionResult<bool>(bResult);
    }
    DEFINE_OPCODE_HANDLER(GOTO)
    {
    }
    DEFINE_OPCODE_HANDLER(JSR)
    {
    }
    DEFINE_OPCODE_HANDLER(RET)
    {
    }

    // 170 - 179
    DEFINE_OPCODE_HANDLER(TABLESWITCH)
    {
        const s4 Key = Context.GetThreadStack().Pop<s4>();


        //ConstantParameters
    }

    /**
     * Performs a lookup switch with the given parameters.
     *
     *
     * @param Context Execution context
     * @param ConstantParameters Is an array of: [s4 DefaultOffset, s4 NumPairs, <and then NumPairs pairs of> {s4 Match, s4 Offset}]
     */
    DEFINE_OPCODE_HANDLER(LOOKUPSWITCH)
    {
        const s4 Key = Context.GetThreadStack().Pop<s4>();
        const s4 Offset = Util::LookupSwitch(Key, ConstantParameters.CreateMemoryReader());

        ASSERT(CMathUtils::IsNumberWithinRange<u2>(Offset));

        Context.SetConditionResult<u2>(static_cast<u2>(Offset));
    }
    DEFINE_OPCODE_HANDLER(IRETURN)
    {
    }
    DEFINE_OPCODE_HANDLER(LRETURN)
    {
    }
    DEFINE_OPCODE_HANDLER(FRETURN)
    {
    }
    DEFINE_OPCODE_HANDLER(DRETURN)
    {
    }
    DEFINE_OPCODE_HANDLER(ARETURN)
    {
    }
    DEFINE_OPCODE_HANDLER(RETURN)
    {
    }
    DEFINE_OPCODE_HANDLER(GETSTATIC)
    {
    }
    DEFINE_OPCODE_HANDLER(PUTSTATIC)
    {
    }

    // 180 - 189
    DEFINE_OPCODE_HANDLER(GETFIELD)
    {
    }
    DEFINE_OPCODE_HANDLER(PUTFIELD)
    {
    }
    DEFINE_OPCODE_HANDLER(INVOKEVIRTUAL)
    {
    }
    DEFINE_OPCODE_HANDLER(INVOKESPECIAL)
    {
    }
    DEFINE_OPCODE_HANDLER(INVOKESTATIC)
    {
    }
    DEFINE_OPCODE_HANDLER(INVOKEINTERFACE)
    {
    }
    DEFINE_OPCODE_HANDLER(INVOKEDYNAMIC)
    {
    }
    DEFINE_OPCODE_HANDLER(NEW)
    {
    }
    DEFINE_OPCODE_HANDLER(NEWARRAY)
    {
    }
    DEFINE_OPCODE_HANDLER(ANEWARRAY)
    {
    }

    // 190 - 199
    DEFINE_OPCODE_HANDLER(ARRAYLENGTH)
    {
    }
    DEFINE_OPCODE_HANDLER(ATHROW)
    {
    }
    DEFINE_OPCODE_HANDLER(CHECKCAST)
    {
    }
    DEFINE_OPCODE_HANDLER(INSTANCEOF)
    {
    }
    DEFINE_OPCODE_HANDLER(MONITORENTER)
    {
    }
    DEFINE_OPCODE_HANDLER(MONITOREXIT)
    {
    }
    DEFINE_OPCODE_HANDLER(WIDE)
    {
    }
    DEFINE_OPCODE_HANDLER(MULTIANEWARRAY)
    {
    }
    DEFINE_OPCODE_HANDLER(IFNULL)
    {
        const oop Value = Context.GetThreadStack().Pop<oop>();
        Context.template SetConditionResult<bool>(Value == Null);
    }
    DEFINE_OPCODE_HANDLER(IFNONNULL)
    {
        const oop Value = Context.GetThreadStack().Pop<oop>();
        Context.template SetConditionResult<bool>(Value != Null);
    }

    // 200 - 201
    DEFINE_OPCODE_HANDLER(GOTO_W)
    {
    }
    DEFINE_OPCODE_HANDLER(JSR_W)
    {
    }
#pragma endregion // Opcode handler definition

#undef DEFINE_OPCODE_HANDLER
}




namespace Bytecode
{
    std::vector<const COpcode*> COpcode::DEBUG_GetOpcodes()
    {
        std::vector<const COpcode *> Opcodes{};
        Opcodes.reserve(ARRAY_COUNT(GOpcodesArray));

        for (const COpcode* OpcodeRef: GOpcodesArray)
        {
            Opcodes.push_back(OpcodeRef);
        }

        return Opcodes;
    }
}
