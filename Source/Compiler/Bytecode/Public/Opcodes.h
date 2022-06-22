//
// Created by ASUS on 31/12/2020.
//

#ifndef CPP20_OPCODES_H
#define CPP20_OPCODES_H

#include "Types.h"
#include "ExcessiveAssert.h"


namespace Bytecode
{
    class COpcode
    {
        friend class COpcodes;

    private:
        constexpr COpcode(const u1 InOperation, const char* InLabel) noexcept
            : Operation(InOperation), Label(InLabel)
        {
        }

        /*
        constexpr Opcode(const Opcode& Other) noexcept
            : Opcode(Other.Operation, Other.StringRepresentation)
        {
        }

        constexpr Opcode(Opcode&& Other) noexcept
            : Opcode(Other.Operation, Other.StringRepresentation)
        {
            Other.Operation = 0;
            Other.StringRepresentation = nullptr;
        }
        */

    public:
        [[nodiscard]]
        constexpr u1 GetOperation() const
        {
            return Operation;
        }

        [[nodiscard]]
        constexpr const char* GetLabel() const
        {
            return Label;
        }

    private:
        const u1 Operation;
        const char* const Label;
    };

#define DEFINE_OPCODE(Byte, Name) static constexpr COpcode Name =\
        COpcode((u1)Byte, LITERAL_TO_STRING(Name))

    class COpcodes
    {
    public:
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
        DEFINE_OPCODE(153, IFEQ);
        DEFINE_OPCODE(154, IFNE);
        DEFINE_OPCODE(155, IFLT);
        DEFINE_OPCODE(156, IFGE);
        DEFINE_OPCODE(157, IFGT);
        DEFINE_OPCODE(158, IFLE);
        DEFINE_OPCODE(159, IF_ICMPEQ);

        // 160 - 169
        DEFINE_OPCODE(160, IF_ICMPNE);
        DEFINE_OPCODE(161, IF_ICMPLT);
        DEFINE_OPCODE(162, IF_ICMPGE);
        DEFINE_OPCODE(163, IF_ICMPGT);
        DEFINE_OPCODE(164, IF_ICMPLE);
        DEFINE_OPCODE(165, IF_ACMPEQ);
        DEFINE_OPCODE(166, IF_ACMPNE);
        DEFINE_OPCODE(167, GOTO);
        DEFINE_OPCODE(168, JSR);
        DEFINE_OPCODE(169, RET);

        // 170 - 179
        DEFINE_OPCODE(170, TABLESWITCH);
        DEFINE_OPCODE(171, LOOKUPSWITCH);
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
        DEFINE_OPCODE(182, INVOKEVIRTUAL);
        DEFINE_OPCODE(183, INVOKESPECIAL);
        DEFINE_OPCODE(184, INVOKESTATIC);
        DEFINE_OPCODE(185, INVOKEINTERFACE);
        DEFINE_OPCODE(186, INVOKEDYNAMIC);
        DEFINE_OPCODE(187, NEW);
        DEFINE_OPCODE(188, NEWARRAY);
        DEFINE_OPCODE(189, ANEWARRAY);

        // 190 - 199
        DEFINE_OPCODE(190, ARRAYLENGTH);
        DEFINE_OPCODE(191, ATHROW);
        DEFINE_OPCODE(192, CHECKCAST);
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

    constexpr const COpcode* const G_OpcodesArray[]
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
        &COpcodes::JSR_W,
    };

    constexpr usz NumOpcodes = ARRAY_COUNT(G_OpcodesArray);

    static_assert
    (
        (NumOpcodes - 1) == (G_OpcodesArray[NumOpcodes - 1]->GetOperation()),
        "Check opcode table: inconsistency between opcode operations and indices"
    );

    constexpr const COpcode* GetOpcodeForByte(u1 Byte)
    {
        if ((usz)Byte < NumOpcodes)
        {
            return G_OpcodesArray[(usz) Byte];
        }

        // Unable to decode this opcode (maybe it's an argument for another opcode)
        return nullptr;
    }
}

#endif //CPP20_OPCODES_H
