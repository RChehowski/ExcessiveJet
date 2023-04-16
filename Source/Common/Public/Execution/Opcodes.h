//
// Created by ASUS on 31/12/2020.
//

#ifndef CPP20_OPCODES_H
#define CPP20_OPCODES_H

#include <array>
#include <vector>

#include "Util/Types.h"
#include "Util/ExcessiveAssert.h"
#include "Execution/ExecutionContext.h"


typedef void (*COpcodeHandler)(VM::CExecutionContext&, const Util::CAllocationRef);

namespace Bytecode
{
    enum class EOpcodeFlags : u2;

    FORCEINLINE constexpr EOpcodeFlags operator| (EOpcodeFlags A, EOpcodeFlags B)
    {
        return static_cast<EOpcodeFlags>(static_cast<std::underlying_type_t<EOpcodeFlags>>(A) | static_cast<std::underlying_type_t<EOpcodeFlags>>(B));
    }

    FORCEINLINE constexpr EOpcodeFlags operator& (EOpcodeFlags A, EOpcodeFlags B)
    {
        return static_cast<EOpcodeFlags>(static_cast<std::underlying_type_t<EOpcodeFlags>>(A) & static_cast<std::underlying_type_t<EOpcodeFlags>>(B));
    }

    enum class EOpcodeFlags : u2
    {
        /** The opcode has no side effects */
        None = 0,

        /** The opcode does integer division (can throw a java.lang.ArithmeticException("divide by zero")) */
        DoesIntegerDivision = 1 << 0,

        /** This opcode accesses an object reference (can throw a java.lang.NullPointerException) */
        ReadsObjectReference = 1 << 1,

        /** This opcode reads from an array (can throw a java.lang.ArrayIndexOutOfBoundsException) */
        ReadsFromArray = 1 << 2,

        /** This opcode allocates memory (can throw a java.lang.OutOfMemoryError) */
        AllocatesMemory = 1 << 3,

        /** Performs a class cast (can throw a java.lang.ClassCastException) */
        DoesClassCast = 1 << 4,

        /** Calls method (potential java.lang.StackOverflowError) */
        InvokesMethod = 1 << 5,

        ChangesControlFlow = 1 << 6,

        EvaluatesCondition = 1 << 7,






        // === MIX === //
        InvokesInstanceMethod = ReadsObjectReference | InvokesMethod,
        Branching = ChangesControlFlow | EvaluatesCondition,
    };



    class COpcode
    {
    private:
        /** Only can be constructed from COpcodes (a friend class below) */
        constexpr COpcode(const u1 InByteCode, const char *InLabel, COpcodeHandler InHandler, const EOpcodeFlags InOpcodeFlags = EOpcodeFlags::None) noexcept
            : ByteCode(InByteCode)
            , Label(InLabel)
            , Handler(InHandler)
            , OpcodeFlags(InOpcodeFlags)
        {
        }

        friend class COpcodes;

    public:
        // disallow copy and move construction
        constexpr COpcode(const COpcode&) = delete;
        constexpr COpcode(COpcode&&) = delete;

        // disallow copy and move assignment
        constexpr COpcode& operator=(const COpcode&) = delete;
        constexpr COpcode& operator=(COpcode&&) = delete;

        FORCEINLINE constexpr bool operator==(const COpcode& Other) const
        {
        	return GetByteCode() == Other.GetByteCode();
        }

        [[nodiscard]]
        constexpr u1 GetByteCode() const
        {
            return ByteCode;
        }

        [[nodiscard]]
        constexpr const char* GetLabel() const
        {
            return Label;
        }

        FORCEINLINE void Execute(VM::CExecutionContext& ExecutionContext, const Util::CAllocationRef& ConstantParameters) const
        {
            ASSERT(!HasAllFlags(EOpcodeFlags::EvaluatesCondition));

            ASSERT_MSG(IsValid(), "Can not execute a null handler")
            Handler(ExecutionContext, ConstantParameters);
        }

        FORCEINLINE bool ExecuteCondition(VM::CExecutionContext& ExecutionContext, const Util::CAllocationRef& ConstantParameters) const
        {
            ASSERT(HasAllFlags(EOpcodeFlags::EvaluatesCondition));

            Execute(ExecutionContext, ConstantParameters);
            return ExecutionContext.template GetConditionResult<bool>();
        }

        FORCEINLINE u2 ExecuteSwitch(VM::CExecutionContext& ExecutionContext, const Util::CAllocationRef& ConstantParameters) const
        {
            ASSERT(HasAllFlags(EOpcodeFlags::EvaluatesCondition));

            Execute(ExecutionContext, ConstantParameters);
            return ExecutionContext.template GetConditionResult<u2>();
        }

        [[nodiscard]] bool IsValid() const
        {
            return Handler != nullptr;
        }

        [[nodiscard]] const COpcode& EnsureValid() const
        {
            ASSERT(IsValid());
            return *this;
        }

        static constexpr usz GetNumOpcodes();

        static constexpr const COpcode& GetOpcodeForByte(u1 Byte);

        // Debug only. Copies opcode pointers
        static std::vector<const COpcode*> DEBUG_GetOpcodes();

        [[nodiscard]] FORCEINLINE bool HasAllFlags(const EOpcodeFlags InOpcodeFlags) const
        {
            return (OpcodeFlags & InOpcodeFlags) != EOpcodeFlags::None;
        }

    private:
        const u1 ByteCode;
        const char* const Label;
        COpcodeHandler Handler;

        const EOpcodeFlags OpcodeFlags;
    };

    // Interpreter only
    namespace OpcodeHandlers
    {
#define DECLARE_OPCODE_HANDLER(Opcode) void Handle_##Opcode(VM::CExecutionContext&, Util::CAllocationRef);

#pragma region Opcode handler declaration
        // 0 - 9
        DECLARE_OPCODE_HANDLER(NOP)
        DECLARE_OPCODE_HANDLER(ACONST_NULL)
        DECLARE_OPCODE_HANDLER(ICONST_M1)
        DECLARE_OPCODE_HANDLER(ICONST_0)
        DECLARE_OPCODE_HANDLER(ICONST_1)
        DECLARE_OPCODE_HANDLER(ICONST_2)
        DECLARE_OPCODE_HANDLER(ICONST_3)
        DECLARE_OPCODE_HANDLER(ICONST_4)
        DECLARE_OPCODE_HANDLER(ICONST_5)
        DECLARE_OPCODE_HANDLER(LCONST_0)

        // 10 - 19
        DECLARE_OPCODE_HANDLER(LCONST_1)
        DECLARE_OPCODE_HANDLER(FCONST_0)
        DECLARE_OPCODE_HANDLER(FCONST_1)
        DECLARE_OPCODE_HANDLER(FCONST_2)
        DECLARE_OPCODE_HANDLER(DCONST_0)
        DECLARE_OPCODE_HANDLER(DCONST_1)
        DECLARE_OPCODE_HANDLER(BIPUSH)
        DECLARE_OPCODE_HANDLER(SIPUSH)
        DECLARE_OPCODE_HANDLER(LDC)
        DECLARE_OPCODE_HANDLER(LDC_W)

        // 20 - 29
        DECLARE_OPCODE_HANDLER(LDC2_W)
        DECLARE_OPCODE_HANDLER(ILOAD)
        DECLARE_OPCODE_HANDLER(LLOAD)
        DECLARE_OPCODE_HANDLER(FLOAD)
        DECLARE_OPCODE_HANDLER(DLOAD)
        DECLARE_OPCODE_HANDLER(ALOAD)
        DECLARE_OPCODE_HANDLER(ILOAD_0)
        DECLARE_OPCODE_HANDLER(ILOAD_1)
        DECLARE_OPCODE_HANDLER(ILOAD_2)
        DECLARE_OPCODE_HANDLER(ILOAD_3)

        // 30 - 39
        DECLARE_OPCODE_HANDLER(LLOAD_0)
        DECLARE_OPCODE_HANDLER(LLOAD_1)
        DECLARE_OPCODE_HANDLER(LLOAD_2)
        DECLARE_OPCODE_HANDLER(LLOAD_3)
        DECLARE_OPCODE_HANDLER(FLOAD_0)
        DECLARE_OPCODE_HANDLER(FLOAD_1)
        DECLARE_OPCODE_HANDLER(FLOAD_2)
        DECLARE_OPCODE_HANDLER(FLOAD_3)
        DECLARE_OPCODE_HANDLER(DLOAD_0)
        DECLARE_OPCODE_HANDLER(DLOAD_1)

        // 40 - 49
        DECLARE_OPCODE_HANDLER(DLOAD_2)
        DECLARE_OPCODE_HANDLER(DLOAD_3)
        DECLARE_OPCODE_HANDLER(ALOAD_0)
        DECLARE_OPCODE_HANDLER(ALOAD_1)
        DECLARE_OPCODE_HANDLER(ALOAD_2)
        DECLARE_OPCODE_HANDLER(ALOAD_3)
        DECLARE_OPCODE_HANDLER(IALOAD)
        DECLARE_OPCODE_HANDLER(LALOAD)
        DECLARE_OPCODE_HANDLER(FALOAD)
        DECLARE_OPCODE_HANDLER(DALOAD)

        // 50 - 59
        DECLARE_OPCODE_HANDLER(AALOAD)
        DECLARE_OPCODE_HANDLER(BALOAD)
        DECLARE_OPCODE_HANDLER(CALOAD)
        DECLARE_OPCODE_HANDLER(SALOAD)
        DECLARE_OPCODE_HANDLER(ISTORE)
        DECLARE_OPCODE_HANDLER(LSTORE)
        DECLARE_OPCODE_HANDLER(FSTORE)
        DECLARE_OPCODE_HANDLER(DSTORE)
        DECLARE_OPCODE_HANDLER(ASTORE)
        DECLARE_OPCODE_HANDLER(ISTORE_0)

        // 60 - 69
        DECLARE_OPCODE_HANDLER(ISTORE_1)
        DECLARE_OPCODE_HANDLER(ISTORE_2)
        DECLARE_OPCODE_HANDLER(ISTORE_3)
        DECLARE_OPCODE_HANDLER(LSTORE_0)
        DECLARE_OPCODE_HANDLER(LSTORE_1)
        DECLARE_OPCODE_HANDLER(LSTORE_2)
        DECLARE_OPCODE_HANDLER(LSTORE_3)
        DECLARE_OPCODE_HANDLER(FSTORE_0)
        DECLARE_OPCODE_HANDLER(FSTORE_1)
        DECLARE_OPCODE_HANDLER(FSTORE_2)

        // 70 - 79
        DECLARE_OPCODE_HANDLER(FSTORE_3)
        DECLARE_OPCODE_HANDLER(DSTORE_0)
        DECLARE_OPCODE_HANDLER(DSTORE_1)
        DECLARE_OPCODE_HANDLER(DSTORE_2)
        DECLARE_OPCODE_HANDLER(DSTORE_3)
        DECLARE_OPCODE_HANDLER(ASTORE_0)
        DECLARE_OPCODE_HANDLER(ASTORE_1)
        DECLARE_OPCODE_HANDLER(ASTORE_2)
        DECLARE_OPCODE_HANDLER(ASTORE_3)
        DECLARE_OPCODE_HANDLER(IASTORE)

        // 80 - 89
        DECLARE_OPCODE_HANDLER(LASTORE)
        DECLARE_OPCODE_HANDLER(FASTORE)
        DECLARE_OPCODE_HANDLER(DASTORE)
        DECLARE_OPCODE_HANDLER(AASTORE)
        DECLARE_OPCODE_HANDLER(BASTORE)
        DECLARE_OPCODE_HANDLER(CASTORE)
        DECLARE_OPCODE_HANDLER(SASTORE)
        DECLARE_OPCODE_HANDLER(POP)
        DECLARE_OPCODE_HANDLER(POP2)
        DECLARE_OPCODE_HANDLER(DUP)

        // 90 - 99
        DECLARE_OPCODE_HANDLER(DUP_X1)
        DECLARE_OPCODE_HANDLER(DUP_X2)
        DECLARE_OPCODE_HANDLER(DUP2)
        DECLARE_OPCODE_HANDLER(DUP2_X1)
        DECLARE_OPCODE_HANDLER(DUP2_X2)
        DECLARE_OPCODE_HANDLER(SWAP)
        DECLARE_OPCODE_HANDLER(IADD)
        DECLARE_OPCODE_HANDLER(LADD)
        DECLARE_OPCODE_HANDLER(FADD)
        DECLARE_OPCODE_HANDLER(DADD)

        // 100 - 109
        DECLARE_OPCODE_HANDLER(ISUB)
        DECLARE_OPCODE_HANDLER(LSUB)
        DECLARE_OPCODE_HANDLER(FSUB)
        DECLARE_OPCODE_HANDLER(DSUB)
        DECLARE_OPCODE_HANDLER(IMUL)
        DECLARE_OPCODE_HANDLER(LMUL)
        DECLARE_OPCODE_HANDLER(FMUL)
        DECLARE_OPCODE_HANDLER(DMUL)
        DECLARE_OPCODE_HANDLER(IDIV)
        DECLARE_OPCODE_HANDLER(LDIV)

        // 110 - 119
        DECLARE_OPCODE_HANDLER(FDIV)
        DECLARE_OPCODE_HANDLER(DDIV)
        DECLARE_OPCODE_HANDLER(IREM)
        DECLARE_OPCODE_HANDLER(LREM)
        DECLARE_OPCODE_HANDLER(FREM)
        DECLARE_OPCODE_HANDLER(DREM)
        DECLARE_OPCODE_HANDLER(INEG)
        DECLARE_OPCODE_HANDLER(LNEG)
        DECLARE_OPCODE_HANDLER(FNEG)
        DECLARE_OPCODE_HANDLER(DNEG)

        // 120 - 129
        DECLARE_OPCODE_HANDLER(ISHL)
        DECLARE_OPCODE_HANDLER(LSHL)
        DECLARE_OPCODE_HANDLER(ISHR)
        DECLARE_OPCODE_HANDLER(LSHR)
        DECLARE_OPCODE_HANDLER(IUSHR)
        DECLARE_OPCODE_HANDLER(LUSHR)
        DECLARE_OPCODE_HANDLER(IAND)
        DECLARE_OPCODE_HANDLER(LAND)
        DECLARE_OPCODE_HANDLER(IOR)
        DECLARE_OPCODE_HANDLER(LOR)

        // 130 - 139
        DECLARE_OPCODE_HANDLER(IXOR)
        DECLARE_OPCODE_HANDLER(LXOR)
        DECLARE_OPCODE_HANDLER(IINC)
        DECLARE_OPCODE_HANDLER(I2L)
        DECLARE_OPCODE_HANDLER(I2F)
        DECLARE_OPCODE_HANDLER(I2D)
        DECLARE_OPCODE_HANDLER(L2I)
        DECLARE_OPCODE_HANDLER(L2F)
        DECLARE_OPCODE_HANDLER(L2D)
        DECLARE_OPCODE_HANDLER(F2I)

        // 140 - 149
        DECLARE_OPCODE_HANDLER(F2L)
        DECLARE_OPCODE_HANDLER(F2D)
        DECLARE_OPCODE_HANDLER(D2I)
        DECLARE_OPCODE_HANDLER(D2L)
        DECLARE_OPCODE_HANDLER(D2F)
        DECLARE_OPCODE_HANDLER(I2B)
        DECLARE_OPCODE_HANDLER(I2C)
        DECLARE_OPCODE_HANDLER(I2S)
        DECLARE_OPCODE_HANDLER(LCMP)
        DECLARE_OPCODE_HANDLER(FCMPL)

        // 150 - 159
        DECLARE_OPCODE_HANDLER(FCMPG)
        DECLARE_OPCODE_HANDLER(DCMPL)
        DECLARE_OPCODE_HANDLER(DCMPG)
        DECLARE_OPCODE_HANDLER(IFEQ)
        DECLARE_OPCODE_HANDLER(IFNE)
        DECLARE_OPCODE_HANDLER(IFLT)
        DECLARE_OPCODE_HANDLER(IFGE)
        DECLARE_OPCODE_HANDLER(IFGT)
        DECLARE_OPCODE_HANDLER(IFLE)
        DECLARE_OPCODE_HANDLER(IF_ICMPEQ)

        // 160 - 169
        DECLARE_OPCODE_HANDLER(IF_ICMPNE)
        DECLARE_OPCODE_HANDLER(IF_ICMPLT)
        DECLARE_OPCODE_HANDLER(IF_ICMPGE)
        DECLARE_OPCODE_HANDLER(IF_ICMPGT)
        DECLARE_OPCODE_HANDLER(IF_ICMPLE)
        DECLARE_OPCODE_HANDLER(IF_ACMPEQ)
        DECLARE_OPCODE_HANDLER(IF_ACMPNE)
        DECLARE_OPCODE_HANDLER(GOTO)
        DECLARE_OPCODE_HANDLER(JSR)
        DECLARE_OPCODE_HANDLER(RET)

        // 170 - 179
        DECLARE_OPCODE_HANDLER(TABLESWITCH)
        DECLARE_OPCODE_HANDLER(LOOKUPSWITCH)
        DECLARE_OPCODE_HANDLER(IRETURN)
        DECLARE_OPCODE_HANDLER(LRETURN)
        DECLARE_OPCODE_HANDLER(FRETURN)
        DECLARE_OPCODE_HANDLER(DRETURN)
        DECLARE_OPCODE_HANDLER(ARETURN)
        DECLARE_OPCODE_HANDLER(RETURN)
        DECLARE_OPCODE_HANDLER(GETSTATIC)
        DECLARE_OPCODE_HANDLER(PUTSTATIC)

        // 180 - 189
        DECLARE_OPCODE_HANDLER(GETFIELD)
        DECLARE_OPCODE_HANDLER(PUTFIELD)
        DECLARE_OPCODE_HANDLER(INVOKEVIRTUAL)
        DECLARE_OPCODE_HANDLER(INVOKESPECIAL)
        DECLARE_OPCODE_HANDLER(INVOKESTATIC)
        DECLARE_OPCODE_HANDLER(INVOKEINTERFACE)
        DECLARE_OPCODE_HANDLER(INVOKEDYNAMIC)
        DECLARE_OPCODE_HANDLER(NEW)
        DECLARE_OPCODE_HANDLER(NEWARRAY)
        DECLARE_OPCODE_HANDLER(ANEWARRAY)

        // 190 - 199
        DECLARE_OPCODE_HANDLER(ARRAYLENGTH)
        DECLARE_OPCODE_HANDLER(ATHROW)
        DECLARE_OPCODE_HANDLER(CHECKCAST)
        DECLARE_OPCODE_HANDLER(INSTANCEOF)
        DECLARE_OPCODE_HANDLER(MONITORENTER)
        DECLARE_OPCODE_HANDLER(MONITOREXIT)
        DECLARE_OPCODE_HANDLER(WIDE)
        DECLARE_OPCODE_HANDLER(MULTIANEWARRAY)
        DECLARE_OPCODE_HANDLER(IFNULL)
        DECLARE_OPCODE_HANDLER(IFNONNULL)

        // 200 - 201
        DECLARE_OPCODE_HANDLER(GOTO_W)
        DECLARE_OPCODE_HANDLER(JSR_W)

#undef DECLARE_OPCODE_HANDLER
#pragma endregion // Opcode handler declaration
    }

#pragma region Opcode array
#define DEFINE_OPCODE(Byte, Name, ...) static constexpr COpcode Name\
    {\
        static_cast<u1>(Byte),\
        LITERAL_TO_STRING(Name),\
        OpcodeHandlers::Handle_##Name,\
        ##__VA_ARGS__\
    }

    struct COpcodes
    {
        // 0 - 9
        DEFINE_OPCODE(0, NOP);
        DEFINE_OPCODE(1, ACONST_NULL);
        DEFINE_OPCODE(2, ICONST_M1);
        DEFINE_OPCODE(3, ICONST_0);
        DEFINE_OPCODE(4, ICONST_1);
        DEFINE_OPCODE(5, ICONST_2);
        DEFINE_OPCODE(6, ICONST_3);
        DEFINE_OPCODE(7, ICONST_4);
        DEFINE_OPCODE(8, ICONST_5);
        DEFINE_OPCODE(9, LCONST_0);

        // 10 - 19
        DEFINE_OPCODE(10, LCONST_1);
        DEFINE_OPCODE(11, FCONST_0);
        DEFINE_OPCODE(12, FCONST_1);
        DEFINE_OPCODE(13, FCONST_2);
        DEFINE_OPCODE(14, DCONST_0);
        DEFINE_OPCODE(15, DCONST_1);
        DEFINE_OPCODE(16, BIPUSH);
        DEFINE_OPCODE(17, SIPUSH);
        DEFINE_OPCODE(18, LDC);
        DEFINE_OPCODE(19, LDC_W);

        // 20 - 29
        DEFINE_OPCODE(20, LDC2_W);
        DEFINE_OPCODE(21, ILOAD);
        DEFINE_OPCODE(22, LLOAD);
        DEFINE_OPCODE(23, FLOAD);
        DEFINE_OPCODE(24, DLOAD);
        DEFINE_OPCODE(25, ALOAD);
        DEFINE_OPCODE(26, ILOAD_0);
        DEFINE_OPCODE(27, ILOAD_1);
        DEFINE_OPCODE(28, ILOAD_2);
        DEFINE_OPCODE(29, ILOAD_3);

        // 30 - 39
        DEFINE_OPCODE(30, LLOAD_0);
        DEFINE_OPCODE(31, LLOAD_1);
        DEFINE_OPCODE(32, LLOAD_2);
        DEFINE_OPCODE(33, LLOAD_3);
        DEFINE_OPCODE(34, FLOAD_0);
        DEFINE_OPCODE(35, FLOAD_1);
        DEFINE_OPCODE(36, FLOAD_2);
        DEFINE_OPCODE(37, FLOAD_3);
        DEFINE_OPCODE(38, DLOAD_0);
        DEFINE_OPCODE(39, DLOAD_1);

        // 40 - 49
        DEFINE_OPCODE(40, DLOAD_2);
        DEFINE_OPCODE(41, DLOAD_3);
        DEFINE_OPCODE(42, ALOAD_0);
        DEFINE_OPCODE(43, ALOAD_1);
        DEFINE_OPCODE(44, ALOAD_2);
        DEFINE_OPCODE(45, ALOAD_3);
        DEFINE_OPCODE(46, IALOAD);
        DEFINE_OPCODE(47, LALOAD);
        DEFINE_OPCODE(48, FALOAD);
        DEFINE_OPCODE(49, DALOAD);

        // 50 - 59
        DEFINE_OPCODE(50, AALOAD);
        DEFINE_OPCODE(51, BALOAD);
        DEFINE_OPCODE(52, CALOAD);
        DEFINE_OPCODE(53, SALOAD);
        DEFINE_OPCODE(54, ISTORE);
        DEFINE_OPCODE(55, LSTORE);
        DEFINE_OPCODE(56, FSTORE);
        DEFINE_OPCODE(57, DSTORE);
        DEFINE_OPCODE(58, ASTORE);
        DEFINE_OPCODE(59, ISTORE_0);

        // 60 - 69
        DEFINE_OPCODE(60, ISTORE_1);
        DEFINE_OPCODE(61, ISTORE_2);
        DEFINE_OPCODE(62, ISTORE_3);
        DEFINE_OPCODE(63, LSTORE_0);
        DEFINE_OPCODE(64, LSTORE_1);
        DEFINE_OPCODE(65, LSTORE_2);
        DEFINE_OPCODE(66, LSTORE_3);
        DEFINE_OPCODE(67, FSTORE_0);
        DEFINE_OPCODE(68, FSTORE_1);
        DEFINE_OPCODE(69, FSTORE_2);

        // 70 - 79
        DEFINE_OPCODE(70, FSTORE_3);
        DEFINE_OPCODE(71, DSTORE_0);
        DEFINE_OPCODE(72, DSTORE_1);
        DEFINE_OPCODE(73, DSTORE_2);
        DEFINE_OPCODE(74, DSTORE_3);
        DEFINE_OPCODE(75, ASTORE_0);
        DEFINE_OPCODE(76, ASTORE_1);
        DEFINE_OPCODE(77, ASTORE_2);
        DEFINE_OPCODE(78, ASTORE_3);
        DEFINE_OPCODE(79, IASTORE);

        // 80 - 89
        DEFINE_OPCODE(80, LASTORE);
        DEFINE_OPCODE(81, FASTORE);
        DEFINE_OPCODE(82, DASTORE);
        DEFINE_OPCODE(83, AASTORE);
        DEFINE_OPCODE(84, BASTORE);
        DEFINE_OPCODE(85, CASTORE);
        DEFINE_OPCODE(86, SASTORE);
        DEFINE_OPCODE(87, POP);
        DEFINE_OPCODE(88, POP2);
        DEFINE_OPCODE(89, DUP);

        // 90 - 99
        DEFINE_OPCODE(90, DUP_X1);
        DEFINE_OPCODE(91, DUP_X2);
        DEFINE_OPCODE(92, DUP2);
        DEFINE_OPCODE(93, DUP2_X1);
        DEFINE_OPCODE(94, DUP2_X2);
        DEFINE_OPCODE(95, SWAP);
        DEFINE_OPCODE(96, IADD);
        DEFINE_OPCODE(97, LADD);
        DEFINE_OPCODE(98, FADD);
        DEFINE_OPCODE(99, DADD);

        // 100 - 109
        DEFINE_OPCODE(100, ISUB);
        DEFINE_OPCODE(101, LSUB);
        DEFINE_OPCODE(102, FSUB);
        DEFINE_OPCODE(103, DSUB);
        DEFINE_OPCODE(104, IMUL);
        DEFINE_OPCODE(105, LMUL);
        DEFINE_OPCODE(106, FMUL);
        DEFINE_OPCODE(107, DMUL);
        DEFINE_OPCODE(108, IDIV);
        DEFINE_OPCODE(109, LDIV);

        // 110 - 119
        DEFINE_OPCODE(110, FDIV);
        DEFINE_OPCODE(111, DDIV);
        DEFINE_OPCODE(112, IREM);
        DEFINE_OPCODE(113, LREM);
        DEFINE_OPCODE(114, FREM);
        DEFINE_OPCODE(115, DREM);
        DEFINE_OPCODE(116, INEG);
        DEFINE_OPCODE(117, LNEG);
        DEFINE_OPCODE(118, FNEG);
        DEFINE_OPCODE(119, DNEG);

        // 120 - 129
        DEFINE_OPCODE(120, ISHL);
        DEFINE_OPCODE(121, LSHL);
        DEFINE_OPCODE(122, ISHR);
        DEFINE_OPCODE(123, LSHR);
        DEFINE_OPCODE(124, IUSHR);
        DEFINE_OPCODE(125, LUSHR);
        DEFINE_OPCODE(126, IAND);
        DEFINE_OPCODE(127, LAND);
        DEFINE_OPCODE(128, IOR);
        DEFINE_OPCODE(129, LOR);

        // 130 - 139
        DEFINE_OPCODE(130, IXOR);
        DEFINE_OPCODE(131, LXOR);
        DEFINE_OPCODE(132, IINC);
        DEFINE_OPCODE(133, I2L);
        DEFINE_OPCODE(134, I2F);
        DEFINE_OPCODE(135, I2D);
        DEFINE_OPCODE(136, L2I);
        DEFINE_OPCODE(137, L2F);
        DEFINE_OPCODE(138, L2D);
        DEFINE_OPCODE(139, F2I);

        // 140 - 149
        DEFINE_OPCODE(140, F2L);
        DEFINE_OPCODE(141, F2D);
        DEFINE_OPCODE(142, D2I);
        DEFINE_OPCODE(143, D2L);
        DEFINE_OPCODE(144, D2F);
        DEFINE_OPCODE(145, I2B);
        DEFINE_OPCODE(146, I2C);
        DEFINE_OPCODE(147, I2S);
        DEFINE_OPCODE(148, LCMP);
        DEFINE_OPCODE(149, FCMPL);

        // 150 - 159
        DEFINE_OPCODE(150, FCMPG);
        DEFINE_OPCODE(151, DCMPL);
        DEFINE_OPCODE(152, DCMPG);
        DEFINE_OPCODE(153, IFEQ,        EOpcodeFlags::Branching);
        DEFINE_OPCODE(154, IFNE,        EOpcodeFlags::Branching);
        DEFINE_OPCODE(155, IFLT,        EOpcodeFlags::Branching);
        DEFINE_OPCODE(156, IFGE,        EOpcodeFlags::Branching);
        DEFINE_OPCODE(157, IFGT,        EOpcodeFlags::Branching);
        DEFINE_OPCODE(158, IFLE,        EOpcodeFlags::Branching);
        DEFINE_OPCODE(159, IF_ICMPEQ,   EOpcodeFlags::Branching);

        // 160 - 169
        DEFINE_OPCODE(160, IF_ICMPNE,   EOpcodeFlags::Branching);
        DEFINE_OPCODE(161, IF_ICMPLT,   EOpcodeFlags::Branching);
        DEFINE_OPCODE(162, IF_ICMPGE,   EOpcodeFlags::Branching);
        DEFINE_OPCODE(163, IF_ICMPGT,   EOpcodeFlags::Branching);
        DEFINE_OPCODE(164, IF_ICMPLE,   EOpcodeFlags::Branching);
        DEFINE_OPCODE(165, IF_ACMPEQ,   EOpcodeFlags::Branching);
        DEFINE_OPCODE(166, IF_ACMPNE,   EOpcodeFlags::Branching);
        DEFINE_OPCODE(167, GOTO,        EOpcodeFlags::ChangesControlFlow);
        DEFINE_OPCODE(168, JSR,         EOpcodeFlags::ChangesControlFlow);
        DEFINE_OPCODE(169, RET,         EOpcodeFlags::ChangesControlFlow);

        // 170 - 179
        DEFINE_OPCODE(170, TABLESWITCH, EOpcodeFlags::Branching);
        DEFINE_OPCODE(171, LOOKUPSWITCH,EOpcodeFlags::Branching);
        DEFINE_OPCODE(172, IRETURN);
        DEFINE_OPCODE(173, LRETURN);
        DEFINE_OPCODE(174, FRETURN);
        DEFINE_OPCODE(175, DRETURN);
        DEFINE_OPCODE(176, ARETURN);
        DEFINE_OPCODE(177, RETURN);
        DEFINE_OPCODE(178, GETSTATIC);
        DEFINE_OPCODE(179, PUTSTATIC);

        // 180 - 189
        DEFINE_OPCODE(180, GETFIELD);
        DEFINE_OPCODE(181, PUTFIELD);
        DEFINE_OPCODE(182, INVOKEVIRTUAL,   EOpcodeFlags::InvokesInstanceMethod);
        DEFINE_OPCODE(183, INVOKESPECIAL,   EOpcodeFlags::InvokesInstanceMethod);
        DEFINE_OPCODE(184, INVOKESTATIC,    EOpcodeFlags::InvokesMethod);
        DEFINE_OPCODE(185, INVOKEINTERFACE, EOpcodeFlags::InvokesInstanceMethod);
        DEFINE_OPCODE(186, INVOKEDYNAMIC,   EOpcodeFlags::InvokesInstanceMethod);
        DEFINE_OPCODE(187, NEW,             EOpcodeFlags::AllocatesMemory);
        DEFINE_OPCODE(188, NEWARRAY,        EOpcodeFlags::AllocatesMemory);
        DEFINE_OPCODE(189, ANEWARRAY,       EOpcodeFlags::AllocatesMemory);

        // 190 - 199
        DEFINE_OPCODE(190, ARRAYLENGTH,     EOpcodeFlags::ReadsObjectReference);
        DEFINE_OPCODE(191, ATHROW);
        DEFINE_OPCODE(192, CHECKCAST,       EOpcodeFlags::DoesClassCast);
        DEFINE_OPCODE(193, INSTANCEOF);
        DEFINE_OPCODE(194, MONITORENTER);
        DEFINE_OPCODE(195, MONITOREXIT);
        DEFINE_OPCODE(196, WIDE);
        DEFINE_OPCODE(197, MULTIANEWARRAY);
        DEFINE_OPCODE(198, IFNULL);
        DEFINE_OPCODE(199, IFNONNULL);

        // 200 - 201
        DEFINE_OPCODE(200, GOTO_W);
        DEFINE_OPCODE(201, JSR_W);
    };
    #undef DEFINE_OPCODE

    constexpr const COpcode* GOpcodesArray[]
	{
		// 0 - 9
		&COpcodes::NOP,
		&COpcodes::ACONST_NULL,
		&COpcodes::ICONST_M1,
		&COpcodes::ICONST_0,
		&COpcodes::ICONST_1,
		&COpcodes::ICONST_2,
		&COpcodes::ICONST_3,
		&COpcodes::ICONST_4,
		&COpcodes::ICONST_5,
		&COpcodes::LCONST_0,

		// 10 - 19
		&COpcodes::LCONST_1,
		&COpcodes::FCONST_0,
		&COpcodes::FCONST_1,
		&COpcodes::FCONST_2,
		&COpcodes::DCONST_0,
		&COpcodes::DCONST_1,
		&COpcodes::BIPUSH,
		&COpcodes::SIPUSH,
		&COpcodes::LDC,
		&COpcodes::LDC_W,

		// 20 - 29
		&COpcodes::LDC2_W,
		&COpcodes::ILOAD,
		&COpcodes::LLOAD,
		&COpcodes::FLOAD,
		&COpcodes::DLOAD,
		&COpcodes::ALOAD,
		&COpcodes::ILOAD_0,
		&COpcodes::ILOAD_1,
		&COpcodes::ILOAD_2,
		&COpcodes::ILOAD_3,

		// 30 - 39
		&COpcodes::LLOAD_0,
		&COpcodes::LLOAD_1,
		&COpcodes::LLOAD_2,
		&COpcodes::LLOAD_3,
		&COpcodes::FLOAD_0,
		&COpcodes::FLOAD_1,
		&COpcodes::FLOAD_2,
		&COpcodes::FLOAD_3,
		&COpcodes::DLOAD_0,
		&COpcodes::DLOAD_1,

		// 40 - 49
		&COpcodes::DLOAD_2,
		&COpcodes::DLOAD_3,
		&COpcodes::ALOAD_0,
		&COpcodes::ALOAD_1,
		&COpcodes::ALOAD_2,
		&COpcodes::ALOAD_3,
		&COpcodes::IALOAD,
		&COpcodes::LALOAD,
		&COpcodes::FALOAD,
		&COpcodes::DALOAD,

		// 50 - 59
		&COpcodes::AALOAD,
		&COpcodes::BALOAD,
		&COpcodes::CALOAD,
		&COpcodes::SALOAD,
		&COpcodes::ISTORE,
		&COpcodes::LSTORE,
		&COpcodes::FSTORE,
		&COpcodes::DSTORE,
		&COpcodes::ASTORE,
		&COpcodes::ISTORE_0,

		// 60 - 69
		&COpcodes::ISTORE_1,
		&COpcodes::ISTORE_2,
		&COpcodes::ISTORE_3,
		&COpcodes::LSTORE_0,
		&COpcodes::LSTORE_1,
		&COpcodes::LSTORE_2,
		&COpcodes::LSTORE_3,
		&COpcodes::FSTORE_0,
		&COpcodes::FSTORE_1,
		&COpcodes::FSTORE_2,

		// 70 - 79
		&COpcodes::FSTORE_3,
		&COpcodes::DSTORE_0,
		&COpcodes::DSTORE_1,
		&COpcodes::DSTORE_2,
		&COpcodes::DSTORE_3,
		&COpcodes::ASTORE_0,
		&COpcodes::ASTORE_1,
		&COpcodes::ASTORE_2,
		&COpcodes::ASTORE_3,
		&COpcodes::IASTORE,

		// 80 - 89
		&COpcodes::LASTORE,
		&COpcodes::FASTORE,
		&COpcodes::DASTORE,
		&COpcodes::AASTORE,
		&COpcodes::BASTORE,
		&COpcodes::CASTORE,
		&COpcodes::SASTORE,
		&COpcodes::POP,
		&COpcodes::POP2,
		&COpcodes::DUP,

		// 90 - 99
		&COpcodes::DUP_X1,
		&COpcodes::DUP_X2,
		&COpcodes::DUP2,
		&COpcodes::DUP2_X1,
		&COpcodes::DUP2_X2,
		&COpcodes::SWAP,
		&COpcodes::IADD,
		&COpcodes::LADD,
		&COpcodes::FADD,
		&COpcodes::DADD,

		// 100 - 109
		&COpcodes::ISUB,
		&COpcodes::LSUB,
		&COpcodes::FSUB,
		&COpcodes::DSUB,
		&COpcodes::IMUL,
		&COpcodes::LMUL,
		&COpcodes::FMUL,
		&COpcodes::DMUL,
		&COpcodes::IDIV,
		&COpcodes::LDIV,

		// 110 - 119
		&COpcodes::FDIV,
		&COpcodes::DDIV,
		&COpcodes::IREM,
		&COpcodes::LREM,
		&COpcodes::FREM,
		&COpcodes::DREM,
		&COpcodes::INEG,
		&COpcodes::LNEG,
		&COpcodes::FNEG,
		&COpcodes::DNEG,

		// 120 - 129
		&COpcodes::ISHL,
		&COpcodes::LSHL,
		&COpcodes::ISHR,
		&COpcodes::LSHR,
		&COpcodes::IUSHR,
		&COpcodes::LUSHR,
		&COpcodes::IAND,
		&COpcodes::LAND,
		&COpcodes::IOR,
		&COpcodes::LOR,

		// 130 - 139
		&COpcodes::IXOR,
		&COpcodes::LXOR,
		&COpcodes::IINC,
		&COpcodes::I2L,
		&COpcodes::I2F,
		&COpcodes::I2D,
		&COpcodes::L2I,
		&COpcodes::L2F,
		&COpcodes::L2D,
		&COpcodes::F2I,

		// 140 - 149
		&COpcodes::F2L,
		&COpcodes::F2D,
		&COpcodes::D2I,
		&COpcodes::D2L,
		&COpcodes::D2F,
		&COpcodes::I2B,
		&COpcodes::I2C,
		&COpcodes::I2S,
		&COpcodes::LCMP,
		&COpcodes::FCMPL,

		// 150 - 159
		&COpcodes::FCMPG,
		&COpcodes::DCMPL,
		&COpcodes::DCMPG,
		&COpcodes::IFEQ,
		&COpcodes::IFNE,
		&COpcodes::IFLT,
		&COpcodes::IFGE,
		&COpcodes::IFGT,
		&COpcodes::IFLE,
		&COpcodes::IF_ICMPEQ,

		// 160 - 169
		&COpcodes::IF_ICMPNE,
		&COpcodes::IF_ICMPLT,
		&COpcodes::IF_ICMPGE,
		&COpcodes::IF_ICMPGT,
		&COpcodes::IF_ICMPLE,
		&COpcodes::IF_ACMPEQ,
		&COpcodes::IF_ACMPNE,
		&COpcodes::GOTO,
		&COpcodes::JSR,
		&COpcodes::RET,

		// 170 - 179
		&COpcodes::TABLESWITCH,
		&COpcodes::LOOKUPSWITCH,
		&COpcodes::IRETURN,
		&COpcodes::LRETURN,
		&COpcodes::FRETURN,
		&COpcodes::DRETURN,
		&COpcodes::ARETURN,
		&COpcodes::RETURN,
		&COpcodes::GETSTATIC,
		&COpcodes::PUTSTATIC,

		// 180 - 189
		&COpcodes::GETFIELD,
		&COpcodes::PUTFIELD,
		&COpcodes::INVOKEVIRTUAL,
		&COpcodes::INVOKESPECIAL,
		&COpcodes::INVOKESTATIC,
		&COpcodes::INVOKEINTERFACE,
		&COpcodes::INVOKEDYNAMIC,
		&COpcodes::NEW,
		&COpcodes::NEWARRAY,
		&COpcodes::ANEWARRAY,

		// 190 - 199
		&COpcodes::ARRAYLENGTH,
		&COpcodes::ATHROW,
		&COpcodes::CHECKCAST,
		&COpcodes::INSTANCEOF,
		&COpcodes::MONITORENTER,
		&COpcodes::MONITOREXIT,
		&COpcodes::WIDE,
		&COpcodes::MULTIANEWARRAY,
		&COpcodes::IFNULL,
		&COpcodes::IFNONNULL,

		// 200 - 201
		&COpcodes::GOTO_W,
		&COpcodes::JSR_W
	};

#pragma endregion // Opcode array


    constexpr usz COpcode::GetNumOpcodes()
    {
        return static_cast<usz>(ARRAY_COUNT(GOpcodesArray));
    }

    constexpr const COpcode& COpcode::GetOpcodeForByte(const u1 Byte)
    {
        return *GOpcodesArray[Byte];
    }
}


#endif //CPP20_OPCODES_H
