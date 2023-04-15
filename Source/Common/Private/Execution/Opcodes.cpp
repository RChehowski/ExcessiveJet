//
// Created by ASUS on 31/12/2020.
//

#include "Common/Public/Execution/Opcodes.h"


#include <algorithm>

namespace Util
{
    enum class ECompareOperation : u8
    {
        // Equals (A==B)
        EQ,
        // Not equals (A!=B)
        NE,

        // Less than (A < B)
        LT,
        // Less or equals than (A <= B)
        LE,

        // Greater than (A > B)
        GT,

        // Greater or equals than (A >= B)
        GE
    };

    template<typename T>
    FORCEINLINE void GenericAdd(VM::CThreadStack& ThreadStack)
    {
        const T Value1 = ThreadStack.Pop<T>();
        const T Value2 = ThreadStack.Pop<T>();

        const T Result = Value1 + Value2;

        ThreadStack.Push<T>(Result);
    }

    template<typename T>
    FORCEINLINE void GenericSub(VM::CThreadStack& ThreadStack)
    {
        const T Value1 = ThreadStack.Pop<T>();
        const T Value2 = ThreadStack.Pop<T>();

        const T Result = Value1 - Value2;

        ThreadStack.Push<T>(Result);
    }

    template<typename T>
    FORCEINLINE void GenericMul(VM::CThreadStack& ThreadStack)
    {
        const T Value1 = ThreadStack.Pop<T>();
        const T Value2 = ThreadStack.Pop<T>();

        const T Result = Value1 * Value2;

        ThreadStack.Push<T>(Result);
    }

    template<typename T>
    FORCEINLINE void GenericDiv(VM::CThreadStack& ThreadStack)
    {
        const T Value1 = ThreadStack.Pop<T>();
        const T Value2 = ThreadStack.Pop<T>();

        const T Result = Value1 * Value2;

        ThreadStack.Push<T>(Result);
    }

#pragma region Rem
    template<typename T, typename = std::enable_if<std::is_integral_v<T>>>
    FORCEINLINE void GenericRem(VM::CThreadStack& ThreadStack)
    {
        const T Value1 = ThreadStack.Pop<T>();
        const T Value2 = ThreadStack.Pop<T>();

        ThreadStack.template Push<T>(Value1 % Value2);
    }

    template <>
    FORCEINLINE void GenericRem<float>(VM::CThreadStack& ThreadStack)
    {
        const float Value1 = ThreadStack.Pop<float>();
        const float Value2 = ThreadStack.Pop<float>();

        ThreadStack.template Push<float>(fmodf(Value1, Value2));
    }

    template <>
    FORCEINLINE void GenericRem<double>(VM::CThreadStack& ThreadStack)
    {
        const double Value1 = ThreadStack.Pop<double>();
        const double Value2 = ThreadStack.Pop<double>();

        ThreadStack.template Push<double>(fmod(Value1, Value2));
    }
#pragma endregion Rem


    template<typename T>
    FORCEINLINE void GenericNeg(VM::CThreadStack& ThreadStack)
    {
        const T Value = ThreadStack.Pop<T>();
        const T Result = -Value;

        ThreadStack.Push<T>(Result);
    }

    template<typename T>
    FORCEINLINE void GenericAnd(VM::CThreadStack& ThreadStack)
    {
        static_assert(std::is_integral_v<T>);

        const T Value1 = ThreadStack.Pop<T>();
        const T Value2 = ThreadStack.Pop<T>();

        const T Result = Value1 & Value2;

        ThreadStack.Push<T>(Result);
    }

    template<typename T>
    FORCEINLINE void GenericOr(VM::CThreadStack& ThreadStack)
    {
        static_assert(std::is_integral_v<T>);

        const T Value1 = ThreadStack.Pop<T>();
        const T Value2 = ThreadStack.Pop<T>();

        const T Result = Value1 | Value2;

        ThreadStack.Push<T>(Result);
    }

    template<typename T>
    FORCEINLINE void GenericXor(VM::CThreadStack& ThreadStack)
    {
        static_assert(std::is_integral_v<T>);

        const T Value1 = ThreadStack.Pop<T>();
        const T Value2 = ThreadStack.Pop<T>();

        const T Result = Value1 ^ Value2;

        ThreadStack.Push<T>(Result);
    }

    template<typename T>
    FORCEINLINE void GenericLoad(VM::CThreadStack& ThreadStack, const VM::CLocalVariables& LocalVariables, const u1 Index)
    {
        const T Value = LocalVariables.template Get<T>(static_cast<u2>(Index));
        ThreadStack.template Push<T>(Value);
    }

    template<typename T>
    FORCEINLINE void GenericStore(VM::CThreadStack& ThreadStack, VM::CLocalVariables& LocalVariables, const u1 Index)
    {
        const T Value = ThreadStack.template Pop<T>();
        LocalVariables.template Set<T>(static_cast<u2>(Index), Value);
    }

    template<typename TFrom, typename TTo>
    FORCEINLINE void Cast(VM::CThreadStack& ThreadStack);

    template<> FORCEINLINE void Cast<s4, s8>(VM::CThreadStack& ThreadStack)
    {
        const s4 Value = ThreadStack.Pop<s4>();
        const s8 Result = static_cast<s8>(Value);
        ThreadStack.Push<s8>(Result);
    }

    template<> FORCEINLINE void Cast<s4, float>(VM::CThreadStack& ThreadStack)
    {
        const s4 Value = ThreadStack.Pop<s4>();
        const float Result = static_cast<float>(Value);
        ThreadStack.Push<float>(Result);
    }

    template<> FORCEINLINE void Cast<s4, double>(VM::CThreadStack& ThreadStack)
    {
        const s4 Value = ThreadStack.Pop<s4>();
        const double Result = static_cast<double>(Value);
        ThreadStack.Push<float>(Result);
    }


    // Cast to a signed 1byte (java "byte")
    template<> FORCEINLINE void Cast<s4, s1>(VM::CThreadStack& ThreadStack)
    {
        const s4 Value = ThreadStack.Pop<s4>();
        const s4 Result = CMathUtils::Clamp
        (
            Value,
            static_cast<s4>(std::numeric_limits<s1>::min()),
            static_cast<s4>(std::numeric_limits<s1>::max())
        );
        ThreadStack.Push<s4>(Result);
    }

    // Cast to an unsigned 2char (java "char")
    template<> FORCEINLINE void Cast<s4, u2>(VM::CThreadStack& ThreadStack)
    {
        const s4 Value = ThreadStack.Pop<s4>();
        const s4 Result = CMathUtils::Clamp
        (
            Value,
            static_cast<s4>(std::numeric_limits<u2>::min()),
            static_cast<s4>(std::numeric_limits<u2>::max())
        );
        ThreadStack.Push<s4>(Result);
    }

    // Cast to a signed 2short (java "short")
    template<> FORCEINLINE void Cast<s4, s2>(VM::CThreadStack& ThreadStack)
    {
        const s4 Value = ThreadStack.Pop<s4>();
        const s4 Result = CMathUtils::Clamp
        (
            Value,
            static_cast<s4>(std::numeric_limits<s2>::min()),
            static_cast<s4>(std::numeric_limits<s2>::max())
        );
        ThreadStack.Push<s4>(Result);
    }

    template <typename T, ECompareOperation CompareOperation>
    FORCEINLINE bool GenericCompareImpl(const T Value1, const T Value2)
    {
        // There is no constexpr switch yet, partial specialization is not allowed either
        if constexpr (CompareOperation == ECompareOperation::EQ)
        {
            return Value1 == Value2;
        }
        else if constexpr (CompareOperation == ECompareOperation::NE)
        {
            return Value1 != Value2;
        }
        else if constexpr (CompareOperation == ECompareOperation::LT)
        {
            static_assert(!TIsOop<T>, "< is not supported for oops");
            return Value1 < Value2;
        }
        else if constexpr (CompareOperation == ECompareOperation::LE)
        {
            static_assert(!TIsOop<T>, "<= is not supported for oops");
            return Value1 <= Value2;
        }
        else if constexpr (CompareOperation == ECompareOperation::GT)
        {
            static_assert(!TIsOop<T>, "> is not supported for oops");
            return Value1 > Value2;
        }
        else if constexpr (CompareOperation == ECompareOperation::GE)
        {
            static_assert(!TIsOop<T>, ">= is not supported for oops");
            return Value1 >= Value2;
        }
        else
        {
            // can't use 'false' -- expression has to depend on a template parameter
            static_assert(!sizeof(T*), "CompareOperation is not supported");
            return false;
        }
    }

    template <ECompareOperation CompareOperation>
    FORCEINLINE bool GenericCompareIntZero(VM::CThreadStack& ThreadStack)
    {
        const s4 Value1 = ThreadStack.template Pop<s4>();
        return GenericCompareImpl<s4, CompareOperation>(Value1, static_cast<s4>(0));
    }

    template <typename T, ECompareOperation CompareOperation>
    FORCEINLINE bool GenericCompare2(VM::CThreadStack& ThreadStack)
    {
        const T Value1 = ThreadStack.template Pop<T>();
        const T Value2 = ThreadStack.template Pop<T>();

        return GenericCompareImpl<T, CompareOperation>(Value1, Value2);
    }
}


namespace Bytecode::OpcodeHandlers
{
#define DEFINE_OPCODE_HANDLER(Opcode) void Handle_##Opcode(VM::CExecutionContext& Context)

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
        const s1 Value = *Context.GetConstantParameters().template Get<s1>();
        Context.GetThreadStack().template Push<s4>(static_cast<s4>(Value));
    }
    DEFINE_OPCODE_HANDLER(SIPUSH)
    {
        const s2 Value = *Context.GetConstantParameters().template Get<s2>();
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
        const u1 Index = *Context.GetConstantParameters().Get<u1>();
        Util::GenericLoad<s4>(Context.GetThreadStack(), Context.GetLocalVariables(), Index);
    }
    DEFINE_OPCODE_HANDLER(LLOAD)
    {
        const u1 Index = *Context.GetConstantParameters().Get<u1>();
        Util::GenericLoad<s8>(Context.GetThreadStack(), Context.GetLocalVariables(), Index);
    }
    DEFINE_OPCODE_HANDLER(FLOAD)
    {
        const u1 Index = *Context.GetConstantParameters().Get<u1>();
        Util::GenericLoad<float>(Context.GetThreadStack(), Context.GetLocalVariables(), Index);
    }
    DEFINE_OPCODE_HANDLER(DLOAD)
    {
        const u1 Index = *Context.GetConstantParameters().Get<u1>();
        Util::GenericLoad<double>(Context.GetThreadStack(), Context.GetLocalVariables(), Index);
    }
    DEFINE_OPCODE_HANDLER(ALOAD)
    {
        const u1 Index = *Context.GetConstantParameters().Get<u1>();
        Util::GenericLoad<oop>(Context.GetThreadStack(), Context.GetLocalVariables(), Index);
    }
    DEFINE_OPCODE_HANDLER(ILOAD_0)
    {
        Util::GenericLoad<s4>(Context.GetThreadStack(), Context.GetLocalVariables(), 0);
    }
    DEFINE_OPCODE_HANDLER(ILOAD_1)
    {
        Util::GenericLoad<s4>(Context.GetThreadStack(), Context.GetLocalVariables(), 1);
    }
    DEFINE_OPCODE_HANDLER(ILOAD_2)
    {
        Util::GenericLoad<s4>(Context.GetThreadStack(), Context.GetLocalVariables(), 2);
    }
    DEFINE_OPCODE_HANDLER(ILOAD_3)
    {
        Util::GenericLoad<s4>(Context.GetThreadStack(), Context.GetLocalVariables(), 3);
    }

    // 30 - 39
    DEFINE_OPCODE_HANDLER(LLOAD_0)
    {
        Util::GenericLoad<s8>(Context.GetThreadStack(), Context.GetLocalVariables(), 0);
    }
    DEFINE_OPCODE_HANDLER(LLOAD_1)
    {
        Util::GenericLoad<s8>(Context.GetThreadStack(), Context.GetLocalVariables(), 1);
    }
    DEFINE_OPCODE_HANDLER(LLOAD_2)
    {
        Util::GenericLoad<s8>(Context.GetThreadStack(), Context.GetLocalVariables(), 2);
    }
    DEFINE_OPCODE_HANDLER(LLOAD_3)
    {
        Util::GenericLoad<s8>(Context.GetThreadStack(), Context.GetLocalVariables(), 3);
    }
    DEFINE_OPCODE_HANDLER(FLOAD_0)
    {
        Util::GenericLoad<float>(Context.GetThreadStack(), Context.GetLocalVariables(), 0);
    }
    DEFINE_OPCODE_HANDLER(FLOAD_1)
    {
        Util::GenericLoad<float>(Context.GetThreadStack(), Context.GetLocalVariables(), 1);
    }
    DEFINE_OPCODE_HANDLER(FLOAD_2)
    {
        Util::GenericLoad<float>(Context.GetThreadStack(), Context.GetLocalVariables(), 2);
    }
    DEFINE_OPCODE_HANDLER(FLOAD_3)
    {
        Util::GenericLoad<float>(Context.GetThreadStack(), Context.GetLocalVariables(), 3);
    }
    DEFINE_OPCODE_HANDLER(DLOAD_0)
    {
        Util::GenericLoad<double>(Context.GetThreadStack(), Context.GetLocalVariables(), 0);
    }
    DEFINE_OPCODE_HANDLER(DLOAD_1)
    {
        Util::GenericLoad<double>(Context.GetThreadStack(), Context.GetLocalVariables(), 1);
    }

    // 40 - 49
    DEFINE_OPCODE_HANDLER(DLOAD_2)
    {
        Util::GenericLoad<double>(Context.GetThreadStack(), Context.GetLocalVariables(), 2);
    }
    DEFINE_OPCODE_HANDLER(DLOAD_3)
    {
        Util::GenericLoad<double>(Context.GetThreadStack(), Context.GetLocalVariables(), 3);
    }
    DEFINE_OPCODE_HANDLER(ALOAD_0)
    {
        Util::GenericLoad<oop>(Context.GetThreadStack(), Context.GetLocalVariables(), 0);
    }
    DEFINE_OPCODE_HANDLER(ALOAD_1)
    {
        Util::GenericLoad<oop>(Context.GetThreadStack(), Context.GetLocalVariables(), 1);
    }
    DEFINE_OPCODE_HANDLER(ALOAD_2)
    {
        Util::GenericLoad<oop>(Context.GetThreadStack(), Context.GetLocalVariables(), 2);
    }
    DEFINE_OPCODE_HANDLER(ALOAD_3)
    {
        Util::GenericLoad<oop>(Context.GetThreadStack(), Context.GetLocalVariables(), 3);
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
        const u1 Index = *Context.GetConstantParameters().Get<u1>();
        Util::GenericStore<s4>(Context.GetThreadStack(), Context.GetLocalVariables(), Index);
    }
    DEFINE_OPCODE_HANDLER(LSTORE)
    {
        const u1 Index = *Context.GetConstantParameters().Get<u1>();
        Util::GenericStore<s8>(Context.GetThreadStack(), Context.GetLocalVariables(), Index);
    }
    DEFINE_OPCODE_HANDLER(FSTORE)
    {
        const u1 Index = *Context.GetConstantParameters().Get<u1>();
        Util::GenericStore<float>(Context.GetThreadStack(), Context.GetLocalVariables(), Index);
    }
    DEFINE_OPCODE_HANDLER(DSTORE)
    {
        const u1 Index = *Context.GetConstantParameters().Get<u1>();
        Util::GenericStore<double>(Context.GetThreadStack(), Context.GetLocalVariables(), Index);
    }
    DEFINE_OPCODE_HANDLER(ASTORE)
    {
        const u1 Index = *Context.GetConstantParameters().Get<u1>();
        Util::GenericStore<oop>(Context.GetThreadStack(), Context.GetLocalVariables(), Index);
    }
    DEFINE_OPCODE_HANDLER(ISTORE_0)
    {
        Util::GenericStore<s4>(Context.GetThreadStack(), Context.GetLocalVariables(), 0);
    }

    // 60 - 69
    DEFINE_OPCODE_HANDLER(ISTORE_1)
    {
        Util::GenericStore<s4>(Context.GetThreadStack(), Context.GetLocalVariables(), 1);
    }
    DEFINE_OPCODE_HANDLER(ISTORE_2)
    {
        Util::GenericStore<s4>(Context.GetThreadStack(), Context.GetLocalVariables(), 2);
    }
    DEFINE_OPCODE_HANDLER(ISTORE_3)
    {
        Util::GenericStore<s4>(Context.GetThreadStack(), Context.GetLocalVariables(), 3);
    }
    DEFINE_OPCODE_HANDLER(LSTORE_0)
    {
        Util::GenericStore<s8>(Context.GetThreadStack(), Context.GetLocalVariables(), 0);
    }
    DEFINE_OPCODE_HANDLER(LSTORE_1)
    {
        Util::GenericStore<s8>(Context.GetThreadStack(), Context.GetLocalVariables(), 1);
    }
    DEFINE_OPCODE_HANDLER(LSTORE_2)
    {
        Util::GenericStore<s8>(Context.GetThreadStack(), Context.GetLocalVariables(), 2);
    }
    DEFINE_OPCODE_HANDLER(LSTORE_3)
    {
        Util::GenericStore<s8>(Context.GetThreadStack(), Context.GetLocalVariables(), 3);
    }
    DEFINE_OPCODE_HANDLER(FSTORE_0)
    {
        Util::GenericStore<float>(Context.GetThreadStack(), Context.GetLocalVariables(), 0);
    }
    DEFINE_OPCODE_HANDLER(FSTORE_1)
    {
        Util::GenericStore<float>(Context.GetThreadStack(), Context.GetLocalVariables(), 1);
    }
    DEFINE_OPCODE_HANDLER(FSTORE_2)
    {
        Util::GenericStore<float>(Context.GetThreadStack(), Context.GetLocalVariables(), 2);
    }

    // 70 - 79
    DEFINE_OPCODE_HANDLER(FSTORE_3)
    {
        Util::GenericStore<float>(Context.GetThreadStack(), Context.GetLocalVariables(), 3);
    }
    DEFINE_OPCODE_HANDLER(DSTORE_0)
    {
        Util::GenericStore<double>(Context.GetThreadStack(), Context.GetLocalVariables(), 0);
    }
    DEFINE_OPCODE_HANDLER(DSTORE_1)
    {
        Util::GenericStore<double>(Context.GetThreadStack(), Context.GetLocalVariables(), 1);
    }
    DEFINE_OPCODE_HANDLER(DSTORE_2)
    {
        Util::GenericStore<double>(Context.GetThreadStack(), Context.GetLocalVariables(), 2);
    }
    DEFINE_OPCODE_HANDLER(DSTORE_3)
    {
        Util::GenericStore<double>(Context.GetThreadStack(), Context.GetLocalVariables(), 3);
    }
    DEFINE_OPCODE_HANDLER(ASTORE_0)
    {
        Util::GenericStore<oop>(Context.GetThreadStack(), Context.GetLocalVariables(), 0);
    }
    DEFINE_OPCODE_HANDLER(ASTORE_1)
    {
        Util::GenericStore<oop>(Context.GetThreadStack(), Context.GetLocalVariables(), 1);
    }
    DEFINE_OPCODE_HANDLER(ASTORE_2)
    {
        Util::GenericStore<oop>(Context.GetThreadStack(), Context.GetLocalVariables(), 2);
    }
    DEFINE_OPCODE_HANDLER(ASTORE_3)
    {
        Util::GenericStore<oop>(Context.GetThreadStack(), Context.GetLocalVariables(), 3);
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
    }

    // 90 - 99
    DEFINE_OPCODE_HANDLER(DUP_X1)
    {
    }
    DEFINE_OPCODE_HANDLER(DUP_X2)
    {
    }
    DEFINE_OPCODE_HANDLER(DUP2)
    {
    }
    DEFINE_OPCODE_HANDLER(DUP2_X1)
    {
    }
    DEFINE_OPCODE_HANDLER(DUP2_X2)
    {
    }
    DEFINE_OPCODE_HANDLER(SWAP)
    {
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
        Util::GenericDiv<s4>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(LDIV)
    {
        Util::GenericDiv<s8>(Context.GetThreadStack());
    }

    // 110 - 119
    DEFINE_OPCODE_HANDLER(FDIV)
    {
        Util::GenericDiv<float>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(DDIV)
    {
        Util::GenericDiv<double>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(IREM)
    {
        Util::GenericRem<s4>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(LREM)
    {
        Util::GenericRem<s8>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(FREM)
    {
        Util::GenericRem<float>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(DREM)
    {
        Util::GenericRem<double>(Context.GetThreadStack());
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
        } const* Structure = Context.GetConstantParameters().Get<CStructure>();

        const u2 Index = static_cast<u2>(Structure->Index);

        const s4 Value = Context.GetLocalVariables().Get<s4>(Index);
        Context.GetLocalVariables().Set(Index, Value + static_cast<s4>(Structure->Constant));
    }
    DEFINE_OPCODE_HANDLER(I2L)
    {
        Util::Cast<s4, s8>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(I2F)
    {
        Util::Cast<s4, float>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(I2D)
    {
        Util::Cast<s4, double>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(L2I)
    {
    }
    DEFINE_OPCODE_HANDLER(L2F)
    {
    }
    DEFINE_OPCODE_HANDLER(L2D)
    {
    }
    DEFINE_OPCODE_HANDLER(F2I)
    {
    }

    // 140 - 149
    DEFINE_OPCODE_HANDLER(F2L)
    {
    }
    DEFINE_OPCODE_HANDLER(F2D)
    {
    }
    DEFINE_OPCODE_HANDLER(D2I)
    {
    }
    DEFINE_OPCODE_HANDLER(D2L)
    {
    }
    DEFINE_OPCODE_HANDLER(D2F)
    {
    }
    DEFINE_OPCODE_HANDLER(I2B)
    {
        Util::Cast<s4, s1>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(I2C)
    {
        Util::Cast<s4, u2>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(I2S)
    {
        Util::Cast<s4, s2>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(LCMP)
    {
    }
    DEFINE_OPCODE_HANDLER(FCMPL)
    {
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
        bool* const ResultPtr = Context.GetConstantParameters().Get<bool>();
        *ResultPtr = Util::GenericCompareIntZero<Util::ECompareOperation::EQ>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(IFNE)
    {
        bool* const ResultPtr = Context.GetConstantParameters().Get<bool>();
        *ResultPtr = Util::GenericCompareIntZero<Util::ECompareOperation::NE>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(IFLT)
    {
        bool* const ResultPtr = Context.GetConstantParameters().Get<bool>();
        *ResultPtr = Util::GenericCompareIntZero<Util::ECompareOperation::LT>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(IFGE)
    {
        bool* const ResultPtr = Context.GetConstantParameters().Get<bool>();
        *ResultPtr = Util::GenericCompareIntZero<Util::ECompareOperation::GE>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(IFGT)
    {
        bool* const ResultPtr = Context.GetConstantParameters().Get<bool>();
        *ResultPtr = Util::GenericCompareIntZero<Util::ECompareOperation::GT>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(IFLE)
    {
        bool* const ResultPtr = Context.GetConstantParameters().Get<bool>();
        *ResultPtr = Util::GenericCompareIntZero<Util::ECompareOperation::LE>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(IF_ICMPEQ)
    {
        bool* const ResultPtr = Context.GetConstantParameters().Get<bool>();
        *ResultPtr = Util::GenericCompare2<s4, Util::ECompareOperation::EQ>(Context.GetThreadStack());
    }

    // 160 - 169
    DEFINE_OPCODE_HANDLER(IF_ICMPNE)
    {
        bool* const ResultPtr = Context.GetConstantParameters().Get<bool>();
        *ResultPtr = Util::GenericCompare2<s4, Util::ECompareOperation::NE>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(IF_ICMPLT)
    {
        bool* const ResultPtr = Context.GetConstantParameters().Get<bool>();
        *ResultPtr = Util::GenericCompare2<s4, Util::ECompareOperation::LT>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(IF_ICMPGE)
    {
        bool* const ResultPtr = Context.GetConstantParameters().Get<bool>();
        *ResultPtr = Util::GenericCompare2<s4, Util::ECompareOperation::GE>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(IF_ICMPGT)
    {
        bool* const ResultPtr = Context.GetConstantParameters().Get<bool>();
        *ResultPtr = Util::GenericCompare2<s4, Util::ECompareOperation::GT>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(IF_ICMPLE)
    {
        bool* const ResultPtr = Context.GetConstantParameters().Get<bool>();
        *ResultPtr = Util::GenericCompare2<s4, Util::ECompareOperation::LE>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(IF_ACMPEQ)
    {
        bool* const ResultPtr = Context.GetConstantParameters().Get<bool>();
        *ResultPtr = Util::GenericCompare2<oop, Util::ECompareOperation::EQ>(Context.GetThreadStack());
    }
    DEFINE_OPCODE_HANDLER(IF_ACMPNE)
    {
        bool* const ResultPtr = Context.GetConstantParameters().Get<bool>();
        *ResultPtr = Util::GenericCompare2<oop, Util::ECompareOperation::NE>(Context.GetThreadStack());
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
    }
    DEFINE_OPCODE_HANDLER(LOOKUPSWITCH)
    {
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
        *Context.GetConstantParameters().Get<bool>() = (Value == Null);
    }
    DEFINE_OPCODE_HANDLER(IFNONNULL)
    {
        const oop Value = Context.GetThreadStack().Pop<oop>();
        *Context.GetConstantParameters().Get<bool>() = (Value != Null);
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