
#include <array>

#include "ClassReader.h"
#include "ClassInfo.h"
#include "MethodInfo.h"

#include "ExcessiveAssert.h"

#include "Attributes/CodeAttributeInfo.h"
#include "Attributes/LineNumberTableAttributeInfo.h"


using Util::CByteOrders;
using Compiler::CClassInfo;
using Compiler::CClassReader;

using Compiler::CCodeAttributeInfo;
using Compiler::CLineNumberTableAttributeInfo;
using Compiler::CLineNumberTableAttributeInfoEntry;

USING_ALL_CONSTANT_INFOS;

using Util::CMathUtils;

#include <string>
#include <iostream>
#include <filesystem>

void TraverseDirectory(const std::string& Root, std::function<void(const std::string&)> Consumer)
{
    for (const auto & entry : std::filesystem::directory_iterator(Root))
    {
        if (std::filesystem::is_directory(entry.path()))
        {
            // Recurse
            TraverseDirectory(entry.path().string(), Consumer);
        }
        else if (std::filesystem::is_regular_file(entry.path()))
        {
            Consumer(entry.path().string());
        }
    }
}

#include <stack>
#include <ConstantPool/ConstantIntegerInfo.h>
#include <ConstantPool/ConstantFloatInfo.h>
#include <ConstantPool/ConstantLongInfo.h>
#include <ConstantPool/ConstantDoubleInfo.h>

#include "Opcodes.h"
#include "Bits.h"

#include "FileSystem.h"

using Bytecode::COpcodes;
using Bytecode::COpcode;

#include "Service/Public/ThreadStack.h"
#include "Service/Public/LocalVariables.h"


void Sum(Service::CThreadStack* ThreadStack)
{
//    const int Op1 = ThreadStack->Pop8<int>();
//    const int Op2 = ThreadStack->Pop8<int>();
//
//    const int Res = Op1 + Op2;
//
//    ThreadStack->Push8(Res);
}

/**
 * To be stored in a static variable.
 */
/* constexpr */ class CExcessiveInvocationInfo
{
public:
    constexpr CExcessiveInvocationInfo(const char* const InInvocationMethodName, const s4 InInvocationLineNumber) :
            InvocationMethodName(InInvocationMethodName), InvocationLineNumber(InInvocationLineNumber)
    {
    }

private:
    const char* const InvocationMethodName;
    const s4 InvocationLineNumber;
};

typedef void (*CExcessiveInvokableMethod)(Service::CThreadStack*);

FORCEINLINE void InvokeExcessiveMethod(
    const CExcessiveInvokableMethod& ExcessiveInvokableMethod,
    Service::CThreadStack* ThreadStack,
    const CExcessiveInvocationInfo& ExcessiveInvocationInfo
)
{
    ExcessiveInvokableMethod(ThreadStack);
}



typedef void (*CBytecodeExecFunc)(
        Service::CThreadStack& ThreadStack,
        Service::CLocalVariables& LocalVariables,
        Compiler::CConstantPool& ConstantPool,
        const std::initializer_list<u1>& OtherBytes
);
CBytecodeExecFunc BytecodeExecFuncs[Bytecode::NumOpcodes];


#define BYTECODE_EXEC_FUNC_ARGS(THREAD_STACK_VAR_NAME, LOCAL_VARIABLES_VAR_NAME, CONSTANT_POOL_VAR_NAME, OTHER_BYTES_VAR_NAME)\
    Service::CThreadStack& (THREAD_STACK_VAR_NAME),         \
    Service::CLocalVariables& (LOCAL_VARIABLES_VAR_NAME),   \
    Compiler::CConstantPool& (CONSTANT_POOL_VAR_NAME),      \
    const std::initializer_list<u1>& OTHER_BYTES_VAR_NAME

#define DEFINE_BYTECODE_EXEC_FUNC(OPCODE, THREAD_STACK_VAR_NAME, LOCAL_VARIABLES_VAR_NAME, CONSTANT_POOL_VAR_NAME, OTHER_BYTES_VAR_NAME) \
    FORCEINLINE void OPCODE##_BytecodeExecFunc(                 \
        Service::CThreadStack& (THREAD_STACK_VAR_NAME),         \
        Service::CLocalVariables& (LOCAL_VARIABLES_VAR_NAME),   \
        Compiler::CConstantPool& (CONSTANT_POOL_VAR_NAME),      \
        const std::initializer_list<u1>& OTHER_BYTES_VAR_NAME   \
    )

#define BYTECODE_EXEC_FUNC_NAME(OPCODE) OPCODE##_BytecodeExecFunc

#define ASSIGN_BYTECODE_EXEC_FUNC(ARRAY, OPCODE, EXEC_FUNCTION)\
    ARRAY[(OPCODE).GetOperation()] = EXEC_FUNCTION;


FORCEINLINE void Impl_LDC(Service::CThreadStack& ThreadStack, const Compiler::CConstantPool& ConstantPool, const usz IndexInConstantPool)
{
    std::shared_ptr<Compiler::CConstantInfo> ConstantInfo = ConstantPool[IndexInConstantPool];

    switch (ConstantInfo->GetConstantPoolInfoTag())
    {
        case Compiler::EConstantPoolInfoTag::Utf8:
            break;
        case Compiler::EConstantPoolInfoTag::Integer:
        {
            const std::shared_ptr<Compiler::CConstantIntegerInfo> ConstantIntegerInfo =
                    Compiler::CConstantInfo::CastConstantInfo<Compiler::CConstantIntegerInfo>(ConstantInfo);

            ThreadStack.Push4(ConstantIntegerInfo->GetBytes());
            break;
        }
        case Compiler::EConstantPoolInfoTag::Float:
        {
            const std::shared_ptr<Compiler::CConstantFloatInfo> ConstantFloatInfo =
                    Compiler::CConstantInfo::CastConstantInfo<Compiler::CConstantFloatInfo>(ConstantInfo);

            ThreadStack.Push4(ConstantFloatInfo->GetBytes());
            break;
        }
            // For ldc2w
//        case Compiler::EConstantPoolInfoTag::Long:
//        {
//            const std::shared_ptr<Compiler::CConstantLongInfo> ConstantLongInfo =
//                    Compiler::CConstantInfo::CastConstantInfo<Compiler::CConstantLongInfo>(ConstantInfo);
//
//            const u8 AsU8 = Util::CMathUtils::Convert2U32ToU64(ConstantLongInfo->GetHighBytes(), ConstantLongInfo->GetLowBytes());
//
//            ThreadStack.Push8(AsU8);
//            break;
//        }
//        case Compiler::EConstantPoolInfoTag::Double:
//        {
//            const std::shared_ptr<Compiler::CConstantDoubleInfo> ConstantDoubleInfo =
//                    Compiler::CConstantInfo::CastConstantInfo<Compiler::CConstantDoubleInfo>(ConstantInfo);
//
//            const u8 AsU8 = Util::CMathUtils::Convert2U32ToU64(ConstantDoubleInfo->GetHighBytes(), ConstantDoubleInfo->GetLowBytes());
//
//            ThreadStack.Push8(AsU8);
//            break;
//        }
        case Compiler::EConstantPoolInfoTag::Class:
        case Compiler::EConstantPoolInfoTag::String:
        case Compiler::EConstantPoolInfoTag::FieldRef:
        case Compiler::EConstantPoolInfoTag::MethodRef:
        case Compiler::EConstantPoolInfoTag::InterfaceMethodRef:
        case Compiler::EConstantPoolInfoTag::NameAndType:
        case Compiler::EConstantPoolInfoTag::MethodHandle:
        case Compiler::EConstantPoolInfoTag::MethodType:
        case Compiler::EConstantPoolInfoTag::InvokeDynamic:
        case Compiler::EConstantPoolInfoTag::Invalid_NotATag:
            break;
    }
}

void Impl_ILOAD(Service::CThreadStack& ThreadStack, const Service::CLocalVariables& LocalVariables, const usz LocalVariableIndex)
{
    const Service::CLocalVariable& LocalVariable = LocalVariables[LocalVariableIndex];

    ASSERT(LocalVariable.IsInt());

    const s4 Int = LocalVariable.GetInt();
    ThreadStack.Push4(Int);
}

void Impl_LLOAD(Service::CThreadStack& ThreadStack, const Service::CLocalVariables& LocalVariables, const usz LocalVariableIndex)
{
    const Service::CLocalVariable& LocalVariable = LocalVariables[LocalVariableIndex];

    ASSERT(LocalVariable.IsLong());

    const s8 Long = LocalVariable.GetLong();
    ThreadStack.Push8(Long);
}

void Impl_FLOAD(Service::CThreadStack& ThreadStack, const Service::CLocalVariables& LocalVariables, const usz LocalVariableIndex)
{
    const Service::CLocalVariable& LocalVariable = LocalVariables[LocalVariableIndex];

    ASSERT(LocalVariable.IsFloat());

    const f4 Float = LocalVariable.GetFloat();
    ThreadStack.Push4(Float);
}

void Impl_DLOAD(Service::CThreadStack& ThreadStack, const Service::CLocalVariables& LocalVariables, const usz LocalVariableIndex)
{
    const Service::CLocalVariable& LocalVariable = LocalVariables[LocalVariableIndex];

    ASSERT(LocalVariable.IsDouble());

    const f8 Double = LocalVariable.GetDouble();
    ThreadStack.Push8(Double);
}

void Impl_ALOAD(Service::CThreadStack& ThreadStack, const Service::CLocalVariables& LocalVariables, const usz LocalVariableIndex)
{
    const Service::CLocalVariable& LocalVariable = LocalVariables[LocalVariableIndex];

    ASSERT(LocalVariable.IsReference());

    const oop Reference = LocalVariable.GetReference();
    ThreadStack.PushOOP(Reference);
}


// 0-9
DEFINE_BYTECODE_EXEC_FUNC(NOP, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
}
DEFINE_BYTECODE_EXEC_FUNC(ACONST_NULL, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    ThreadStack.Push8(nullptr);
}
DEFINE_BYTECODE_EXEC_FUNC(ICONST_M1, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    ThreadStack.Push4((s4)-1);
}
DEFINE_BYTECODE_EXEC_FUNC(ICONST_0, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    ThreadStack.Push4((s4)0);
}
DEFINE_BYTECODE_EXEC_FUNC(ICONST_1, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    ThreadStack.Push4((s4)1);
}
DEFINE_BYTECODE_EXEC_FUNC(ICONST_2, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    ThreadStack.Push4((s4)2);
}
DEFINE_BYTECODE_EXEC_FUNC(ICONST_3, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    ThreadStack.Push4((s4)3);
}
DEFINE_BYTECODE_EXEC_FUNC(ICONST_4, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    ThreadStack.Push4((s4)4);
}
DEFINE_BYTECODE_EXEC_FUNC(ICONST_5, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    ThreadStack.Push4((s4)5);
}
DEFINE_BYTECODE_EXEC_FUNC(LCONST_0, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    ThreadStack.Push8((s8)0);
}

// 10-19
DEFINE_BYTECODE_EXEC_FUNC(LCONST_1, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    ThreadStack.Push8((s8)1);
}
DEFINE_BYTECODE_EXEC_FUNC(FCONST_0, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    ThreadStack.Push4((f4)0.0f);
}
DEFINE_BYTECODE_EXEC_FUNC(FCONST_1, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    ThreadStack.Push4((f4)1.0f);
}
DEFINE_BYTECODE_EXEC_FUNC(FCONST_2, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    ThreadStack.Push4((f4)2.0f);
}
DEFINE_BYTECODE_EXEC_FUNC(DCONST_0, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    ThreadStack.Push8((f8)0.0);
}
DEFINE_BYTECODE_EXEC_FUNC(DCONST_1, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    ThreadStack.Push8((f8)1.0);
}
DEFINE_BYTECODE_EXEC_FUNC(BIPUSH, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    const u1 Byte0 = OtherBytes.begin()[0];

    const s4 ByteAsInt = (s4)Byte0;
    ThreadStack.Push4(ByteAsInt);
}
DEFINE_BYTECODE_EXEC_FUNC(SIPUSH, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    const u1 Byte0 = OtherBytes.begin()[0];
    const u1 Byte1 = OtherBytes.begin()[1];

    const s4 ByteAsInt = (s4)CMathUtils::Convert2U1To1U2(Byte0, Byte1);
    ThreadStack.Push4(ByteAsInt);
}
DEFINE_BYTECODE_EXEC_FUNC(LDC, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    const u1 Index = OtherBytes.begin()[0];

    const usz IndexInConstantPool = CMathUtils::ConvertToUsz(Index);
    Impl_LDC(ThreadStack, ConstantPool, IndexInConstantPool);
}
DEFINE_BYTECODE_EXEC_FUNC(LDC_W, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    const u1 Byte0 = OtherBytes.begin()[0];
    const u1 Byte1 = OtherBytes.begin()[1];

    const usz IndexInConstantPool = CMathUtils::ConvertToUsz(CMathUtils::Convert2U1To1U2(Byte0, Byte1));
    Impl_LDC(ThreadStack, ConstantPool, IndexInConstantPool);
}

// 20-29
DEFINE_BYTECODE_EXEC_FUNC(LDC2_W, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    const u1 Byte0 = OtherBytes.begin()[0];
    const u1 Byte1 = OtherBytes.begin()[1];

    const usz IndexInConstantPool = CMathUtils::ConvertToUsz(CMathUtils::Convert2U1To1U2(Byte0, Byte1));
    Impl_LDC(ThreadStack, ConstantPool, IndexInConstantPool);
}
DEFINE_BYTECODE_EXEC_FUNC(ILOAD, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    const u1 Byte0 = OtherBytes.begin()[0];
    const usz LocalVariableIndex = CMathUtils::ConvertToUsz(Byte0);

    Impl_ILOAD(ThreadStack, LocalVariables, LocalVariableIndex);
}
DEFINE_BYTECODE_EXEC_FUNC(LLOAD, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    const u1 Byte0 = OtherBytes.begin()[0];
    const usz LocalVariableIndex = CMathUtils::ConvertToUsz(Byte0);

    Impl_LLOAD(ThreadStack, LocalVariables, LocalVariableIndex);
}
DEFINE_BYTECODE_EXEC_FUNC(FLOAD, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    const u1 Byte0 = OtherBytes.begin()[0];
    const usz LocalVariableIndex = CMathUtils::ConvertToUsz(Byte0);

    Impl_FLOAD(ThreadStack, LocalVariables, LocalVariableIndex);
}
DEFINE_BYTECODE_EXEC_FUNC(DLOAD, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    const u1 Byte0 = OtherBytes.begin()[0];
    const usz LocalVariableIndex = CMathUtils::ConvertToUsz(Byte0);

    Impl_DLOAD(ThreadStack, LocalVariables, LocalVariableIndex);
}
DEFINE_BYTECODE_EXEC_FUNC(ALOAD, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    const u1 Byte0 = OtherBytes.begin()[0];
    const usz LocalVariableIndex = CMathUtils::ConvertToUsz(Byte0);

    Impl_ALOAD(ThreadStack, LocalVariables, LocalVariableIndex);
}
DEFINE_BYTECODE_EXEC_FUNC(ILOAD_0, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    Impl_ILOAD(ThreadStack, LocalVariables, (usz)0);
}
DEFINE_BYTECODE_EXEC_FUNC(ILOAD_1, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    Impl_ILOAD(ThreadStack, LocalVariables, (usz)1);
}
DEFINE_BYTECODE_EXEC_FUNC(ILOAD_2, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    Impl_ILOAD(ThreadStack, LocalVariables, (usz)2);
}
DEFINE_BYTECODE_EXEC_FUNC(ILOAD_3, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    Impl_ILOAD(ThreadStack, LocalVariables, (usz)3);
}

// 30-39
DEFINE_BYTECODE_EXEC_FUNC(LLOAD_0, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    Impl_LLOAD(ThreadStack, LocalVariables, (usz)0);
}
DEFINE_BYTECODE_EXEC_FUNC(LLOAD_1, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    Impl_LLOAD(ThreadStack, LocalVariables, (usz)1);
}
DEFINE_BYTECODE_EXEC_FUNC(LLOAD_2, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    Impl_LLOAD(ThreadStack, LocalVariables, (usz)2);
}
DEFINE_BYTECODE_EXEC_FUNC(LLOAD_3, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    Impl_LLOAD(ThreadStack, LocalVariables, (usz)3);
}
DEFINE_BYTECODE_EXEC_FUNC(FLOAD_0, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    Impl_FLOAD(ThreadStack, LocalVariables, (usz)0);
}
DEFINE_BYTECODE_EXEC_FUNC(FLOAD_1, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    Impl_FLOAD(ThreadStack, LocalVariables, (usz)1);
}
DEFINE_BYTECODE_EXEC_FUNC(FLOAD_2, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    Impl_FLOAD(ThreadStack, LocalVariables, (usz)2);
}
DEFINE_BYTECODE_EXEC_FUNC(FLOAD_3, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    Impl_FLOAD(ThreadStack, LocalVariables, (usz)3);
}
DEFINE_BYTECODE_EXEC_FUNC(DLOAD_0, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    Impl_DLOAD(ThreadStack, LocalVariables, (usz)0);
}
DEFINE_BYTECODE_EXEC_FUNC(DLOAD_1, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    Impl_DLOAD(ThreadStack, LocalVariables, (usz)1);
}

// 40-49
DEFINE_BYTECODE_EXEC_FUNC(DLOAD_2, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    Impl_DLOAD(ThreadStack, LocalVariables, (usz)2);
}
DEFINE_BYTECODE_EXEC_FUNC(DLOAD_3, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    Impl_DLOAD(ThreadStack, LocalVariables, (usz)3);
}
DEFINE_BYTECODE_EXEC_FUNC(ALOAD_0, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    Impl_ALOAD(ThreadStack, LocalVariables, (usz)0);
}
DEFINE_BYTECODE_EXEC_FUNC(ALOAD_1, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    Impl_ALOAD(ThreadStack, LocalVariables, (usz)1);
}
DEFINE_BYTECODE_EXEC_FUNC(ALOAD_2, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    Impl_ALOAD(ThreadStack, LocalVariables, (usz)2);
}
DEFINE_BYTECODE_EXEC_FUNC(ALOAD_3, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    Impl_ALOAD(ThreadStack, LocalVariables, (usz)3);
}
DEFINE_BYTECODE_EXEC_FUNC(IALOAD, ThreadStack, LocalVariables, ConstantPool, OtherBytes)
{
    const s4 Index = ThreadStack.Pop<s4>();
    const oop ArrayOOP = ThreadStack.Pop<oop>();

    // TODO
    ASSERT(false);
}





void ExecuteBytecode(const COpcode& Opcode, BYTECODE_EXEC_FUNC_ARGS(ThreadStack, LocalVariables, ConstantPool, Args = {}))
{
    const CBytecodeExecFunc& BytecodeExecFunc = BytecodeExecFuncs[Opcode.GetOperation()];

    ASSERT_MSG(BytecodeExecFunc != nullptr, "No bytecode execution function for opcode: %s", Opcode.GetLabel());

    BytecodeExecFunc(ThreadStack, LocalVariables, ConstantPool, Args);
}

void FillBytecodeExecFuncsTable()
{
    static bool bAlreadyFilled = false;
    if (bAlreadyFilled)
    {
        return;
    }

    bAlreadyFilled = true;

    Util::CMemory::MemZero(BytecodeExecFuncs, sizeof(BytecodeExecFuncs));

#pragma region Opcodes 0-9
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::NOP,         BYTECODE_EXEC_FUNC_NAME(NOP));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::ACONST_NULL, BYTECODE_EXEC_FUNC_NAME(ACONST_NULL));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::ICONST_M1,   BYTECODE_EXEC_FUNC_NAME(ICONST_M1));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::ICONST_0,    BYTECODE_EXEC_FUNC_NAME(ICONST_0));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::ICONST_1,    BYTECODE_EXEC_FUNC_NAME(ICONST_1));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::ICONST_2,    BYTECODE_EXEC_FUNC_NAME(ICONST_2));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::ICONST_3,    BYTECODE_EXEC_FUNC_NAME(ICONST_3));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::ICONST_4,    BYTECODE_EXEC_FUNC_NAME(ICONST_4));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::ICONST_5,    BYTECODE_EXEC_FUNC_NAME(ICONST_5));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::LCONST_0,    BYTECODE_EXEC_FUNC_NAME(LCONST_0));
#pragma endregion
#pragma region Opcodes 10-19
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::LCONST_1,    BYTECODE_EXEC_FUNC_NAME(LCONST_1));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::FCONST_0,    BYTECODE_EXEC_FUNC_NAME(FCONST_0));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::FCONST_1,    BYTECODE_EXEC_FUNC_NAME(FCONST_1));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::FCONST_2,    BYTECODE_EXEC_FUNC_NAME(FCONST_2));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::DCONST_0,    BYTECODE_EXEC_FUNC_NAME(DCONST_0));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::DCONST_1,    BYTECODE_EXEC_FUNC_NAME(DCONST_1));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::BIPUSH,      BYTECODE_EXEC_FUNC_NAME(BIPUSH));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::SIPUSH,      BYTECODE_EXEC_FUNC_NAME(SIPUSH));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::LDC,         BYTECODE_EXEC_FUNC_NAME(LDC));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::LDC_W,       BYTECODE_EXEC_FUNC_NAME(LDC_W));
#pragma endregion
#pragma region Opcodes 20-29
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::LDC2_W,      BYTECODE_EXEC_FUNC_NAME(LDC_W));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::ILOAD,       BYTECODE_EXEC_FUNC_NAME(ILOAD));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::LLOAD,       BYTECODE_EXEC_FUNC_NAME(LLOAD));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::FLOAD,       BYTECODE_EXEC_FUNC_NAME(FLOAD));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::DLOAD,       BYTECODE_EXEC_FUNC_NAME(DLOAD));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::ALOAD,       BYTECODE_EXEC_FUNC_NAME(ALOAD));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::ILOAD_0,     BYTECODE_EXEC_FUNC_NAME(ILOAD_0));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::ILOAD_1,     BYTECODE_EXEC_FUNC_NAME(ILOAD_1));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::ILOAD_2,     BYTECODE_EXEC_FUNC_NAME(ILOAD_2));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::ILOAD_3,     BYTECODE_EXEC_FUNC_NAME(ILOAD_3));
#pragma endregion
#pragma region Opcodes 30-39
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::LLOAD_0,     BYTECODE_EXEC_FUNC_NAME(LLOAD_0));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::LLOAD_1,     BYTECODE_EXEC_FUNC_NAME(LLOAD_1));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::LLOAD_2,     BYTECODE_EXEC_FUNC_NAME(LLOAD_2));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::LLOAD_3,     BYTECODE_EXEC_FUNC_NAME(LLOAD_3));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::FLOAD_0,     BYTECODE_EXEC_FUNC_NAME(FLOAD_0));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::FLOAD_1,     BYTECODE_EXEC_FUNC_NAME(FLOAD_1));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::FLOAD_2,     BYTECODE_EXEC_FUNC_NAME(FLOAD_2));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::FLOAD_3,     BYTECODE_EXEC_FUNC_NAME(FLOAD_3));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::DLOAD_0,     BYTECODE_EXEC_FUNC_NAME(DLOAD_0));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::DLOAD_1,     BYTECODE_EXEC_FUNC_NAME(DLOAD_1));
#pragma endregion

#pragma region Opcodes 40-49
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::DLOAD_2,     BYTECODE_EXEC_FUNC_NAME(DLOAD_2));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::DLOAD_3,     BYTECODE_EXEC_FUNC_NAME(DLOAD_3));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::ALOAD_0,     BYTECODE_EXEC_FUNC_NAME(ALOAD_0));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::ALOAD_1,     BYTECODE_EXEC_FUNC_NAME(ALOAD_1));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::ALOAD_2,     BYTECODE_EXEC_FUNC_NAME(ALOAD_2));
    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::ALOAD_3,     BYTECODE_EXEC_FUNC_NAME(ALOAD_3));

    ASSIGN_BYTECODE_EXEC_FUNC(BytecodeExecFuncs, COpcodes::IALOAD,      BYTECODE_EXEC_FUNC_NAME(IALOAD));
#pragma endregion
}

#include <Windows.h>


enum class EClassLoadStatus
{
    NotLoaded,
    Loading,
    Loaded,
    Unloading
};

class CClass
{
public:
    void Load()
    {
        std::cout << "Loading class..." << std::endl;
    }

    void Unload()
    {
        std::cout << "Unloading class..." << std::endl;
    }
};

extern "C" __declspec(dllexport) CClass* _$New_Class()
{
    return new CClass();
}

#include "StringUtils.h"
#include <fstream>
#include <variant>

#include <cstddef>

#include "MathUtils.h"


#define STRUCT_FIELD_OFFSETOF(Struct, Field) ((usz)&(((Struct*)(nullptr))->Field))
#define STRUCT_METHOD_ADDROF(Struct, Method) 0//(*reinterpret_cast<const void**>(&(Struct::Method)))

struct CFieldMeta
{
    const u2 ConstantPoolIndex;
    const usz FieldOffset;
};

struct CMethodMeta
{
    const u2 ConstantPoolIndex;
    const void* MethodAddress;
};

struct alignas(sizeof(void*)) CGeneratedSample
{
    char c;
    short s;
    int i;
    long long ll;

    void f1() {}
    void f2() {}
    void f3() {}

    // Meta
    const static CFieldMeta FieldMetas[];
    const static CMethodMeta MethodMetas[];

    static FORCEINLINE void GetFieldMetas(const CFieldMeta** FieldMetasPtr, usz* NumFieldsPtr);
    static FORCEINLINE void GetMethodMetas(const CMethodMeta** MethodMetasPtr, usz* NumMethodsPtr);
};

const CFieldMeta CGeneratedSample::FieldMetas[] = {
    {0, STRUCT_FIELD_OFFSETOF(CGeneratedSample, c)},
    {1, STRUCT_FIELD_OFFSETOF(CGeneratedSample, s)},
    {2, STRUCT_FIELD_OFFSETOF(CGeneratedSample, i)},
    {3, STRUCT_FIELD_OFFSETOF(CGeneratedSample, ll)}
};
const CMethodMeta CGeneratedSample::MethodMetas[] = {
    {0, STRUCT_METHOD_ADDROF(CGeneratedSample, f1) },
    {1, STRUCT_METHOD_ADDROF(CGeneratedSample, f2) },
    {2, STRUCT_METHOD_ADDROF(CGeneratedSample, f3) }
};

void CGeneratedSample::GetFieldMetas(const CFieldMeta** FieldMetasPtr, usz* NumFieldsPtr)
{
    if (FieldMetasPtr)
        *FieldMetasPtr = FieldMetas;

    if (NumFieldsPtr)
        *NumFieldsPtr = sizeof(FieldMetas) / sizeof(*FieldMetas);
}
void CGeneratedSample::GetMethodMetas(const CMethodMeta** MethodMetasPtr, usz* NumMethodsPtr)
{
    if (MethodMetasPtr)
        *MethodMetasPtr = MethodMetas;

    if (NumMethodsPtr)
        *NumMethodsPtr = sizeof(MethodMetas) / sizeof(*MethodMetas);
}

struct JMarkWord
{
    s4 HashCode;

    oop Klass;

    u1 Reserved[4];
};

static_assert(Util::CMathUtils::IsAligned(sizeof(JMarkWord), sizeof(oop)));


void test()
{
    puts("Hello");
}

#include "Bits.h"
#include <algorithm>
#include <random>

#include "Compiler/Printer/CppPrinter.h"

#include "ww898/utf_converters.hpp"

FORCEINLINE void ConvertUtf8ToUtf16LEBytes(const Util::IStringUtf8& StringUtf8, std::vector<u1>& StringUtf16Bytes)
{
    using namespace ww898::utf;
    static thread_local std::u16string U16String;
    {
        U16String.clear();
        U16String.reserve(StringUtf8.GetNumBytes());
    }

    convz<utf_selector_t<u1>, utf16>(StringUtf8.GetBytes(), std::back_inserter(U16String));

    StringUtf16Bytes.reserve(StringUtf16Bytes.size() + (U16String.length() * sizeof(char16_t)));
    for (const char16_t& U16Char : U16String)
    {
        u1 Byte0 = (u1)0;
        u1 Byte1 = (u1)0;

        Util::ExplodeBytes(Util::CByteOrders::GetLittleEndian(), U16Char, &Byte0, &Byte1);

        StringUtf16Bytes.push_back(Byte0);
        StringUtf16Bytes.push_back(Byte1);
    }
}

int main()
{
//    $StringMeta stringMeta;

    Compiler::CCppPrinter P;
    CClassReader ClassReader(R"(C:\Users\ASUS\Desktop\rt\java\lang\String.class)");

    CClassInfo ClassInfo;
    ClassReader >> ClassInfo;

    std::shared_ptr<const Compiler::CConstantPool> ConstantPool = ClassInfo.GetConstantPool();

    CConstantUtf8Info ConstantInfo(Util::CLiteralStringUtf8("AAA"));

    {
        std::vector<std::shared_ptr<CConstantUtf8Info>> ConstantUtf8Infos = ConstantPool->GetEachOfType<CConstantUtf8Info>();


        P.Append("const std::array<Util::CConstantUtf8Info, ").Append((usz)ConstantUtf8Infos.size()).Append("> ConstantUtf8Infos = ");
        P.ScopeBegin();

        std::vector<u1> Utf16LEBytes;
        for (const std::shared_ptr<CConstantUtf8Info>& ConstantUtf8Info : ConstantUtf8Infos)
        {
            Utf16LEBytes.clear();
            ConvertUtf8ToUtf16LEBytes(ConstantUtf8Info->GetStringUtf8(), Utf16LEBytes);

            P
                .Append("CConstantUtf8Info(Util::CLiteralStringUtf8(")
                .AppendNTBS(Utf16LEBytes)
                .Append(")),")
                .NewLine();
        }
        P.ScopeEnd().SemicolonNewLine();
    }

    std::cout << P;

#if 0
    for (const auto& Method : ClassInfo.GetMethods())
    {

        if (std::shared_ptr<CCodeAttributeInfo> CodeAttributeInfo =
                Method.GetAttribute<CCodeAttributeInfo>())
        {
            puts(Method.Debug_ToString(ClassInfo).c_str());

            const TSerializedArray<u4, u1>& Code = CodeAttributeInfo->GetCode();
            printf("Code length: %llu\n", (unsigned long long)Code.Size());

            if (std::shared_ptr<CLineNumberTableAttributeInfo> LineNumberTableAttributeInfo =
                CodeAttributeInfo->GetAttribute<CLineNumberTableAttributeInfo>())
            {
                for (const CLineNumberTableAttributeInfoEntry& LineNumberTableAttributeInfoEntry :
                    LineNumberTableAttributeInfo->GetLineNumberTable())
                {
                    const u2 LineNumber = LineNumberTableAttributeInfoEntry.GetLineNumber();
                    const u2 StartPc = LineNumberTableAttributeInfoEntry.GetStartPc();

                    printf("LineNumber: %d, StartPc: %d\n",
                           (int)LineNumber, (int)StartPc);
                }

                std::shared_ptr<const Compiler::CConstantPool> ConstantPool = ClassInfo.GetConstantPool();

//                for (usz OpcodeIndex = 0; OpcodeIndex < Code.Size();)
//                {
//                    const u1 RawOpcode = Code[OpcodeIndex];
//                    if (const Bytecode::COpcode* Opcode = Bytecode::GetOpcodeForByte(Code[OpcodeIndex]))
//                    {
//                        switch (Opcode->GetOperation())
//                        {
//                            case COpcodes::ALOAD_0.GetOperation():
//                            {
//                                std::cout << COpcodes::ALOAD_0.GetLabel() << std::endl;
//                                break;
//                            }
//                            case COpcodes::INVOKESPECIAL.GetOperation():
//                            {
//                                std::cout << COpcodes::INVOKESPECIAL.GetLabel() << std::endl;
//
//                                const u1 IndexByte1 = Code[++OpcodeIndex];
//                                const u1 IndexByte2 = Code[++OpcodeIndex];
//
//                                const u2 MethodRefIndex =
//                                        Util::CombineBytes(Util::CByteOrders::GetBigEndian(), IndexByte1, IndexByte2);
//
//                                std::shared_ptr<CConstantMethodRefInfo> ConstantMethodRefInfo =
//                                        ConstantPool->Get<CConstantMethodRefInfo>((usz) MethodRefIndex);
//                                ASSERT_NOT_NULLPTR(ConstantMethodRefInfo);
//
//
//                                std::shared_ptr<CConstantClassInfo> ConstantClassInfo =
//                                        ConstantPool->Get<CConstantClassInfo>(
//                                                (usz) ConstantMethodRefInfo->GetClassIndex());
//                                ASSERT_NOT_NULLPTR(ConstantClassInfo);
//
//                                std::shared_ptr<CConstantNameAndTypeInfo> ConstantNameAndTypeInfo =
//                                        ConstantPool->Get<CConstantNameAndTypeInfo>(
//                                                (usz) ConstantMethodRefInfo->GetNameAndTypeIndex());
//                                ASSERT_NOT_NULLPTR(ConstantNameAndTypeInfo);
//
//
//                                // Class name
//                                std::shared_ptr<CConstantUtf8Info> ClassName =
//                                        ConstantPool->Get<CConstantUtf8Info>((usz) ConstantClassInfo->GetNameIndex());
//                                ASSERT_NOT_NULLPTR(ClassName);
//
//
//                                // Name and type
//                                std::shared_ptr<CConstantUtf8Info> MethodName =
//                                        ConstantPool->Get<CConstantUtf8Info>(
//                                                (usz) ConstantNameAndTypeInfo->GetNameIndex());
//                                ASSERT_NOT_NULLPTR(MethodName);
//
//                                std::shared_ptr<CConstantUtf8Info> MethodDescriptor =
//                                        ConstantPool->Get<CConstantUtf8Info>(
//                                                (usz) ConstantNameAndTypeInfo->GetDescriptorIndex());
//                                ASSERT_NOT_NULLPTR(MethodDescriptor);
//
//                                break;
//                            }
//                            case COpcodes::ICONST_0.GetOperation():
//                            {
//                                std::cout << COpcodes::ICONST_0.GetLabel() << std::endl;
//                                break;
//                            }
//                            case COpcodes::PUTFIELD.GetOperation():
//                            {
//                                std::cout << COpcodes::PUTFIELD.GetLabel() << std::endl;
//                                OpcodeIndex += 2;
//                                break;
//                            }
//                            case COpcodes::DSTORE_1.GetOperation():
//                            {
//                                std::cout << COpcodes::DSTORE_1.GetLabel() << std::endl;
//                                break;
//                            }
//                            case COpcodes::NEWARRAY.GetOperation():
//                            {
//                                std::cout << COpcodes::NEWARRAY.GetLabel() << std::endl;
//                                OpcodeIndex += 1; // atype
//                                break;
//                            }
//                            case COpcodes::ACONST_NULL.GetOperation():
//                            {
//                                std::cout << COpcodes::ACONST_NULL.GetLabel() << std::endl;
//                                break;
//                            }
//                            case COpcodes::ASTORE_0.GetOperation():
//                            {
//                                std::cout << COpcodes::ASTORE_0.GetLabel() << std::endl;
//                                break;
//                            }
//                            case COpcodes::RETURN.GetOperation():
//                            {
//                                std::cout << COpcodes::RETURN.GetLabel() << std::endl;
//                                break;
//                            }
//                            default:
//                            {
//                                std::cout << "<< SOMETHING ELSE >>" << std::endl;
//                                break;
//                            }
//                        }
//                    }
//                    OpcodeIndex++;
//                }
            }
        }
    }
#endif
}
