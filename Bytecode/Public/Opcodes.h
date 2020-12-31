//
// Created by ASUS on 31/12/2020.
//

#ifndef CPP20_OPCODES_H
#define CPP20_OPCODES_H

#include "Types.h"
#include "Assert.h"





namespace Bytecode
{
    struct Opcode
    {
        const u1 Operation;
        const std::string StringRepresentation;
    };

    #define DECLARE_OPCODE(Code, Name) static const Opcode Name({Code, LITERAL_TO_STRING(Name)})

    struct Opcodes
    {
        DECLARE_OPCODE(0, NOP);
        DECLARE_OPCODE(1, ACONST_NULL);
        DECLARE_OPCODE(2, ICONST_M1);
        DECLARE_OPCODE(3, ICONST_0);
        DECLARE_OPCODE(4, ICONST_1);
        DECLARE_OPCODE(5, ICONST_2);
        DECLARE_OPCODE(6, ICONST_3);
        DECLARE_OPCODE(7, ICONST_4);
        DECLARE_OPCODE(8, ICONST_5);
        DECLARE_OPCODE(9, LCONST_0);
        DECLARE_OPCODE(10, LCONST_1);
        DECLARE_OPCODE(11, FCONST_0);
        DECLARE_OPCODE(12, FCONST_1);
        DECLARE_OPCODE(13, FCONST_2);
        DECLARE_OPCODE(14, DCONST_0);
        DECLARE_OPCODE(15, DCONST_1);
        DECLARE_OPCODE(16, BIPUSH);
        DECLARE_OPCODE(17, SIPUSH);
        DECLARE_OPCODE(18, LDC);
        DECLARE_OPCODE(19, LDC_W);
        DECLARE_OPCODE(20, LDC2_W);
        DECLARE_OPCODE(21, ILOAD);
        DECLARE_OPCODE(22, LLOAD);
        DECLARE_OPCODE(23, FLOAD);
        DECLARE_OPCODE(24, DLOAD);
        DECLARE_OPCODE(25, ALOAD);
        DECLARE_OPCODE(26, ILOAD_0);
        DECLARE_OPCODE(27, ILOAD_1);
        DECLARE_OPCODE(28, ILOAD_2);
        DECLARE_OPCODE(29, ILOAD_3);
        DECLARE_OPCODE(30, LLOAD_0);
        DECLARE_OPCODE(31, LLOAD_1);
        DECLARE_OPCODE(32, LLOAD_2);
        DECLARE_OPCODE(33, LLOAD_3);
        DECLARE_OPCODE(34, FLOAD_0);
        DECLARE_OPCODE(35, FLOAD_1);
        DECLARE_OPCODE(36, FLOAD_2);
        DECLARE_OPCODE(37, FLOAD_3);
        DECLARE_OPCODE(38, DLOAD_0);
        DECLARE_OPCODE(39, DLOAD_1);
        DECLARE_OPCODE(40, DLOAD_2);
        DECLARE_OPCODE(41, DLOAD_3);
        DECLARE_OPCODE(42, ALOAD_0);
        DECLARE_OPCODE(43, ALOAD_1);
        DECLARE_OPCODE(44, ALOAD_2);
        DECLARE_OPCODE(45, ALOAD_3);
        DECLARE_OPCODE(46, IALOAD);
        DECLARE_OPCODE(47, LALOAD);
        DECLARE_OPCODE(48, FALOAD);
        DECLARE_OPCODE(49, DALOAD);
        DECLARE_OPCODE(50, AALOAD);
        DECLARE_OPCODE(51, BALOAD);
        DECLARE_OPCODE(52, CALOAD);
        DECLARE_OPCODE(53, SALOAD);
        DECLARE_OPCODE(54, ISTORE);
        DECLARE_OPCODE(55, LSTORE);
        DECLARE_OPCODE(56, FSTORE);
        DECLARE_OPCODE(57, DSTORE);
        DECLARE_OPCODE(58, ASTORE);
        DECLARE_OPCODE(59, ISTORE_0);
        DECLARE_OPCODE(60, ISTORE_1);
        DECLARE_OPCODE(61, ISTORE_2);
        DECLARE_OPCODE(62, ISTORE_3);
        DECLARE_OPCODE(63, LSTORE_0);
        DECLARE_OPCODE(64, LSTORE_1);
        DECLARE_OPCODE(65, LSTORE_2);
        DECLARE_OPCODE(66, LSTORE_3);
        DECLARE_OPCODE(67, FSTORE_0);
        DECLARE_OPCODE(68, FSTORE_1);
        DECLARE_OPCODE(69, FSTORE_2);
        DECLARE_OPCODE(70, FSTORE_3);
        DECLARE_OPCODE(71, DSTORE_0);
        DECLARE_OPCODE(72, DSTORE_1);
        DECLARE_OPCODE(73, DSTORE_2);
        DECLARE_OPCODE(74, DSTORE_3);
        DECLARE_OPCODE(75, ASTORE_0);
        DECLARE_OPCODE(76, ASTORE_1);
        DECLARE_OPCODE(77, ASTORE_2);
        DECLARE_OPCODE(78, ASTORE_3);
        DECLARE_OPCODE(79, IASTORE);
        DECLARE_OPCODE(80, LASTORE);
        DECLARE_OPCODE(81, FASTORE);
        DECLARE_OPCODE(82, DASTORE);
        DECLARE_OPCODE(83, AASTORE);
        DECLARE_OPCODE(84, BASTORE);
        DECLARE_OPCODE(85, CASTORE);
        DECLARE_OPCODE(86, SASTORE);
        DECLARE_OPCODE(87, POP);
        DECLARE_OPCODE(88, POP2);
        DECLARE_OPCODE(89, DUP);
        DECLARE_OPCODE(90, DUP_X1);
        DECLARE_OPCODE(91, DUP_X2);
        DECLARE_OPCODE(92, DUP2);
        DECLARE_OPCODE(93, DUP2_X1);
        DECLARE_OPCODE(94, DUP2_X2);
        DECLARE_OPCODE(95, SWAP);
        DECLARE_OPCODE(96, IADD);
        DECLARE_OPCODE(97, LADD);
        DECLARE_OPCODE(98, FADD);
        DECLARE_OPCODE(99, DADD);
        DECLARE_OPCODE(100, ISUB);
        DECLARE_OPCODE(101, LSUB);
        DECLARE_OPCODE(102, FSUB);
        DECLARE_OPCODE(103, DSUB);
        DECLARE_OPCODE(104, IMUL);
        DECLARE_OPCODE(105, LMUL);
        DECLARE_OPCODE(106, FMUL);
        DECLARE_OPCODE(107, DMUL);
        DECLARE_OPCODE(108, IDIV);
        DECLARE_OPCODE(109, LDIV);
        DECLARE_OPCODE(110, FDIV);
        DECLARE_OPCODE(111, DDIV);
        DECLARE_OPCODE(112, IREM);
        DECLARE_OPCODE(113, LREM);
        DECLARE_OPCODE(114, FREM);
        DECLARE_OPCODE(115, DREM);
        DECLARE_OPCODE(116, INEG);
        DECLARE_OPCODE(117, LNEG);
        DECLARE_OPCODE(118, FNEG);
        DECLARE_OPCODE(119, DNEG);
        DECLARE_OPCODE(120, ISHL);
        DECLARE_OPCODE(121, LSHL);
        DECLARE_OPCODE(122, ISHR);
        DECLARE_OPCODE(123, LSHR);
        DECLARE_OPCODE(124, IUSHR);
        DECLARE_OPCODE(125, LUSHR);
        DECLARE_OPCODE(126, IAND);
        DECLARE_OPCODE(127, LAND);
        DECLARE_OPCODE(128, IOR);
        DECLARE_OPCODE(129, LOR);
        DECLARE_OPCODE(130, IXOR);
        DECLARE_OPCODE(131, LXOR);
        DECLARE_OPCODE(132, IINC);
        DECLARE_OPCODE(133, I2L);
        DECLARE_OPCODE(134, I2F);
        DECLARE_OPCODE(135, I2D);
        DECLARE_OPCODE(136, L2I);
        DECLARE_OPCODE(137, L2F);
        DECLARE_OPCODE(138, L2D);
        DECLARE_OPCODE(139, F2I);
        DECLARE_OPCODE(140, F2L);
        DECLARE_OPCODE(141, F2D);
        DECLARE_OPCODE(142, D2I);
        DECLARE_OPCODE(143, D2L);
        DECLARE_OPCODE(144, D2F);
        DECLARE_OPCODE(145, I2B);
        DECLARE_OPCODE(146, I2C);
        DECLARE_OPCODE(147, I2S);
        DECLARE_OPCODE(148, LCMP);
        DECLARE_OPCODE(149, FCMPL);
        DECLARE_OPCODE(150, FCMPG);
        DECLARE_OPCODE(151, DCMPL);
        DECLARE_OPCODE(152, DCMPG);
        DECLARE_OPCODE(153, IFEQ);
        DECLARE_OPCODE(154, IFNE);
        DECLARE_OPCODE(155, IFLT);
        DECLARE_OPCODE(156, IFGE);
        DECLARE_OPCODE(157, IFGT);
        DECLARE_OPCODE(158, IFLE);
        DECLARE_OPCODE(159, IF_ICMPEQ);
        DECLARE_OPCODE(160, IF_ICMPNE);
        DECLARE_OPCODE(161, IF_ICMPLT);
        DECLARE_OPCODE(162, IF_ICMPGE);
        DECLARE_OPCODE(163, IF_ICMPGT);
        DECLARE_OPCODE(164, IF_ICMPLE);
        DECLARE_OPCODE(165, IF_ACMPEQ);
        DECLARE_OPCODE(166, IF_ACMPNE);
        DECLARE_OPCODE(167, GOTO);
        DECLARE_OPCODE(168, JSR);
        DECLARE_OPCODE(169, RET);
        DECLARE_OPCODE(170, TABLESWITCH);
        DECLARE_OPCODE(171, LOOKUPSWITCH);
        DECLARE_OPCODE(172, IRETURN);
        DECLARE_OPCODE(173, LRETURN);
        DECLARE_OPCODE(174, FRETURN);
        DECLARE_OPCODE(175, DRETURN);
        DECLARE_OPCODE(176, ARETURN);
        DECLARE_OPCODE(177, RETURN);
        DECLARE_OPCODE(178, GETSTATIC);
        DECLARE_OPCODE(179, PUTSTATIC);
        DECLARE_OPCODE(180, GETFIELD);
        DECLARE_OPCODE(181, PUTFIELD);
        DECLARE_OPCODE(182, INVOKEVIRTUAL);
        DECLARE_OPCODE(183, INVOKESPECIAL);
        DECLARE_OPCODE(184, INVOKESTATIC);
        DECLARE_OPCODE(185, INVOKEINTERFACE);
        DECLARE_OPCODE(186, INVOKEDYNAMIC);
        DECLARE_OPCODE(187, NEW);
        DECLARE_OPCODE(188, NEWARRAY);
        DECLARE_OPCODE(189, ANEWARRAY);
        DECLARE_OPCODE(190, ARRAYLENGTH);
        DECLARE_OPCODE(191, ATHROW);
        DECLARE_OPCODE(192, CHECKCAST);
        DECLARE_OPCODE(193, INSTANCEOF);
        DECLARE_OPCODE(194, MONITORENTER);
        DECLARE_OPCODE(195, MONITOREXIT);
        DECLARE_OPCODE(196, WIDE);
        DECLARE_OPCODE(197, MULTIANEWARRAY);
        DECLARE_OPCODE(198, IFNULL);
        DECLARE_OPCODE(199, IFNONNULL);
        DECLARE_OPCODE(200, GOTO_W);
        DECLARE_OPCODE(201, JSR_W);
    };

    Opcode G_Opcodes[] = {
        NOP
        ACONST_NULL
        ICONST_M1
        ICONST_0
        ICONST_1
        ICONST_2
        ICONST_3
        ICONST_4
        ICONST_5
        LCONST_0
        LCONST_1
        FCONST_0
        FCONST_1
        FCONST_2
        DCONST_0
        DCONST_1
        BIPUSH
        SIPUSH
        LDC
        LDC_W
        LDC2_W
        ILOAD
        LLOAD
        FLOAD
        DLOAD
        ALOAD
        ILOAD_0
        ILOAD_1
        ILOAD_2
        ILOAD_3
        LLOAD_0
        LLOAD_1
        LLOAD_2
        LLOAD_3
        FLOAD_0
        FLOAD_1
        FLOAD_2
        FLOAD_3
        DLOAD_0
        DLOAD_1
        DLOAD_2
        DLOAD_3
        ALOAD_0
        ALOAD_1
        ALOAD_2
        ALOAD_3
        IALOAD
        LALOAD
        FALOAD
        DALOAD
        AALOAD
        BALOAD
        CALOAD
        SALOAD
        ISTORE
        LSTORE
        FSTORE
        DSTORE
        ASTORE
        ISTORE_0
        ISTORE_1
        ISTORE_2
        ISTORE_3
        LSTORE_0
        LSTORE_1
        LSTORE_2
        LSTORE_3
        FSTORE_0
        FSTORE_1
        FSTORE_2
        FSTORE_3
        DSTORE_0
        DSTORE_1
        DSTORE_2
        DSTORE_3
        ASTORE_0
        ASTORE_1
        ASTORE_2
        ASTORE_3
        IASTORE
        LASTORE
        FASTORE
        DASTORE
        AASTORE
        BASTORE
        CASTORE
        SASTORE
        POP
        POP2
        DUP
        DUP_X1
        DUP_X2
        DUP2
        DUP2_X1
        DUP2_X2
        SWAP
        IADD
        LADD
        FADD
        DADD
        ISUB
        LSUB
        FSUB
        DSUB
        IMUL
        LMUL
        FMUL
        DMUL
        IDIV
        LDIV
        FDIV
        DDIV
        IREM
        LREM
        FREM
        DREM
        INEG
        LNEG
        FNEG
        DNEG
        ISHL
        LSHL
        ISHR
        LSHR
        IUSHR
        LUSHR
        IAND
        LAND
        IOR
        LOR
        IXOR
        LXOR
        IINC
        I2L
        I2F
        I2D
        L2I
        L2F
        L2D
        F2I
        F2L
        F2D
        D2I
        D2L
        D2F
        I2B
        I2C
        I2S
        LCMP
        FCMPL
        FCMPG
        DCMPL
        DCMPG
        IFEQ
        IFNE
        IFLT
        IFGE
        IFGT
        IFLE
        IF_ICMPEQ
        IF_ICMPNE
        IF_ICMPLT
        IF_ICMPGE
        IF_ICMPGT
        IF_ICMPLE
        IF_ACMPEQ
        IF_ACMPNE
        GOTO
        JSR
        RET
        TABLESWITCH
        LOOKUPSWITCH
        IRETURN
        LRETURN
        FRETURN
        DRETURN
        ARETURN
        RETURN
        GETSTATIC
        PUTSTATIC
        GETFIELD
        PUTFIELD
        INVOKEVIRTUAL
        INVOKESPECIAL
        INVOKESTATIC
        INVOKEINTERFACE
        INVOKEDYNAMIC
        NEW
        NEWARRAY
        ANEWARRAY
        ARRAYLENGTH
        ATHROW
        CHECKCAST
        INSTANCEOF
        MONITORENTER
        MONITOREXIT
        WIDE
        MULTIANEWARRAY
        IFNULL
        IFNONNULL
        GOTO_W
        JSR_W
    };
    
//    constexpr size_t GetNumOpcodes()
//    {
//        const NumOpcodes = sizeof(Opcodes) / sizeof(*Opcodes);
//
//        return NumOpcodes;
//    }

    const Opcode& GetOpcodeForByte(const u1 Byte)
    {
        const Opcode& OpcodeForByte = G_Opcodes[(size_t)Byte];
        ASSERT(Byte == OpcodeForByte.Operation);

        return OpcodeForByte;
    }
}

namespace std
{
    FORCEINLINE string to_string(int _Val)
    {	// convert int to string
        return (_Integral_to_string<char>(_Val));
    }
}

#endif //CPP20_OPCODES_H
