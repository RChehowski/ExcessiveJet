//
// Created by ASUS on 10/01/2021.
//

#pragma once

#include "Types.h"
#include "Platform/Memory.h"
#include "ClassReader.h"
#include "AttributeInfo.h"

using Util::Memory;
using Util::TStandardSerializedArray;

namespace Parse
{
#pragma region CVerificationTypeInfo
    enum class EVariableInfoTag : u1
    {
        ITEM_Top = 0,
        ITEM_Integer = 1,
        ITEM_Float = 2,
        ITEM_Double = 3,
        ITEM_Long = 4,
        ITEM_Null = 5,
        ITEM_UninitializedThis = 6,
        ITEM_Object = 7,
        ITEM_Uninitialized = 8
    };

    class CVariableInfo
    {
    public:
        CVariableInfo(EVariableInfoTag InTag) : Tag(InTag)
        {
        }

        virtual ~CVariableInfo() = default;

        virtual void DeserializeBody(CClassReader& Reader)
        {
        }

    private:
        EVariableInfoTag Tag;
    };

    /**
     * The Top_variable_info type indicates that the local variable has the verification type top.
     */
    class CTopVariableInfo final : public CVariableInfo
    {
        using CVariableInfo::CVariableInfo;
    };

    /**
     * The Integer_variable_info type indicates that the location contains the verification type int.
     */
    class CIntegerVariableInfo final : public CVariableInfo
    {
        using CVariableInfo::CVariableInfo;
    };

    /**
     * The Float_variable_info type indicates that the location contains the verification type float.
     */
    class CFloatVariableInfo final : public CVariableInfo
    {
        using CVariableInfo::CVariableInfo;
    };

    /**
     * The Double_variable_info type indicates that the location contains the verification type double.
     */
    class CDoubleVariableInfo final : public CVariableInfo
    {
        using CVariableInfo::CVariableInfo;
    };

    /**
     * The Long_variable_info type indicates that the location contains the verification type long.
     */
    class CLongVariableInfo final : public CVariableInfo
    {
        using CVariableInfo::CVariableInfo;
    };

    /**
     * The Null_variable_info type indicates that location contains the verification type null.
     */
    class CNullVariableInfo final : public CVariableInfo
    {
        using CVariableInfo::CVariableInfo;
    };

    /**
     *The UninitializedThis_variable_info type indicates that the location contains the verification type uninitializedThis.
     */
    class CUninitializedThisVariableInfo final : public CVariableInfo
    {
        using CVariableInfo::CVariableInfo;
    };

    /**
     * The Object_variable_info type indicates that the location contains an instance of the class represented
     * by the CONSTANT_Class_info (§4.4.1) structure found in the constant_pool table at the index given by cpool_index.
     */
    class CObjectVariableInfo final : public CVariableInfo
    {
        using CVariableInfo::CVariableInfo;

    public:
        void DeserializeBody(CClassReader& Reader) override
        {
            CVariableInfo::DeserializeBody(Reader);
            Reader >> ConstantPoolIndex;
        }

        [[nodiscard]]
        FORCEINLINE u2 GetConstantPoolIndex() const
        {
            return ConstantPoolIndex;
        }

    private:
        u2 ConstantPoolIndex = (u2) 0;
    };

    /**
     * The Uninitialized_variable_info type indicates that the location contains the
     * verification type uninitialized(offset). The offset item indicates the offset,
     * in the code array of the Code attribute (§4.7.3) that contains this StackMapTable attribute,
     * of the new instruction (§new) that created the object being stored in the location.
     */
    class CUninitializedVariableInfo final : public CVariableInfo
    {
        using CVariableInfo::CVariableInfo;

    public:
        void DeserializeBody(CClassReader& Reader) override
        {
            CVariableInfo::DeserializeBody(Reader);
            Reader >> Offset;
        }

        [[nodiscard]]
        FORCEINLINE u2 GetOffset() const
        {
            return Offset;
        }

    private:
        u2 Offset = (u2) 0;
    };


    union CVerificationTypeInfo
    {
    private:
        /**
         * Generic, Inaccessible, for fluent GetVariableInfoTag()
         */
        CVariableInfo VariableInfo;

    public:
        CTopVariableInfo TopVariableInfo;
        CIntegerVariableInfo IntegerVariableInfo;
        CFloatVariableInfo FloatVariableInfo;
        CLongVariableInfo LongVariableInfo;
        CDoubleVariableInfo DoubleVariableInfo;
        CNullVariableInfo NullVariableInfo;
        CUninitializedThisVariableInfo UninitializedThisVariableInfo;
        CObjectVariableInfo ObjectVariableInfo;
        CUninitializedVariableInfo UninitializedVariableInfo;

        CVerificationTypeInfo()
        {
            // Nullify the memory
            Memory::MemZero(&VariableInfo, sizeof(this));
        }

        [[nodiscard]]
        FORCEINLINE EVariableInfoTag GetVariableInfoTag() const
        {
            return VariableInfo.Tag;
        }
    };
#pragma endregion // CVerificationTypeInfo

    struct CFrame
    {
        u1 FrameType = (u1)0;

        CFrame(u1 InFrameType) : FrameType(InFrameType) {}
    };

    struct CSameFrame : public CFrame
    {
        using CFrame::CFrame;

        FORCEINLINE friend CClassReader& operator>>(CClassReader& Reader, CSameFrame& Instance) {}
    };

    struct CSameLocals1StackItemFrame : public CFrame
    {
        using CFrame::CFrame;

        CVerificationTypeInfo Stack[1] = {0};

        FORCEINLINE friend CClassReader& operator>>(CClassReader& Reader, CSameFrame& Instance)
        {
            Reader >> Stack[0];
        }
    };

    struct CSameLocals1StackItemFrameExtended : public CFrame
    {
        using CFrame::CFrame;

        u2 OffsetDelta = (u2) 0;
        CVerificationTypeInfo Stack[1] = {0};

        FORCEINLINE friend CClassReader& operator>>(CClassReader& Reader, CSameFrame& Instance)
        {
            Reader >> OffsetDelta;
            Reader >> Stack[0];
        }
    };

    struct CChopFrame : public CFrame
    {
        using CFrame::CFrame;

        u2 OffsetDelta = (u2) 0;

        FORCEINLINE friend CClassReader& operator>>(CClassReader& Reader, CSameFrame& Instance)
        {
            Reader >> OffsetDelta;
        }
    };

    struct CSameFrameExtended : public CFrame
    {
        using CFrame::CFrame;

        u2 OffsetDelta = (u2) 0;

        FORCEINLINE friend CClassReader& operator>>(CClassReader& Reader, CSameFrame& Instance)
        {
            Reader >> OffsetDelta;
        }
    };

    struct CAppendFrame : public CFrame
    {
        using CFrame::CFrame;

        u2 OffsetDelta = (u2) 0;
        CVerificationTypeInfo Locals[FrameType - 251];

        FORCEINLINE friend CClassReader& operator>>(CClassReader& Reader, CSameFrame& Instance)
        {

        }
    };

    struct CFullFrame : public CFrame
    {
        using CFrame::CFrame;

        u2 OffsetDelta = (u2) 0;
        TStandardSerializedArray<CVerificationTypeInfo> Locals;
        TStandardSerializedArray<CVerificationTypeInfo> Stack;
    };


    union CStackMapFrame
    {
        CSameFrame SameFrame;
        CSameLocals1StackItemFrame SameLocals1StackItemFrame;
        CSameLocals1StackItemFrameExtended SameLocals1StackItemFrameExtended;
        CChopFrame ChopFrame;
        CSameFrameExtended SameFrameExtended;
        CAppendFrame AppendFrame;
        CFullFrame FullFrame;

        friend CClassReader& operator>> (CClassReader& Reader, CStackMapFrame& Instance)
        {
            u1 FrameType = (u1)0;
            Reader >> FrameType;

            if ((FrameType >= 0) && (FrameType <= 63))
            {
                CSameFrame LocalSameFrame(FrameType);
                Reader >> LocalSameFrame;
                SameFrame = std::move(LocalSameFrame);

                return Reader;
            }
            if ((FrameType >= 64) && (FrameType <= 127))
            {
                CSameLocals1StackItemFrame LocalSameLocals1StackItemFrame(FrameType);
                Reader >> LocalSameLocals1StackItemFrame;
                SameLocals1StackItemFrame = std::move(LocalSameLocals1StackItemFrame);

                return Reader;
            }
            if (FrameType == 247)
            {
                CSameLocals1StackItemFrameExtended LocalSameLocals1StackItemFrameExtended(FrameType);
                Reader >> LocalSameLocals1StackItemFrameExtended;
                SameLocals1StackItemFrameExtended = std::move(LocalSameLocals1StackItemFrameExtended);

                return Reader;
            }
            if ((FrameType >= 248) && (FrameType <= 250))
            {
                CChopFrame LocalChopFrame(FrameType);
                Reader >> LocalChopFrame;
                ChopFrame = std::move(LocalChopFrame);

                return Reader;
            }
            if (FrameType == 251)
            {
                CSameFrameExtended LocalSameFrameExtended(FrameType);
                Reader >> LocalSameFrameExtended;
                SameFrameExtended = std::move(LocalSameFrameExtended);

                return Reader;
            }
            if ((FrameType >= 252) && (FrameType <= 254))
            {
                CAppendFrame LocalAppendFrame(FrameType);
                Reader >> LocalAppendFrame;
                AppendFrame = std::move(LocalAppendFrame);

                return Reader;
            }
            if (FrameType == 255)
            {
                CFullFrame LocalFullFrame(FrameType);
                Reader >> LocalFullFrame;
                FrameType = std::move(LocalFullFrame);

                return Reader;
            }

            ASSERT(false);
        }
    }

    class CStackMapTableAttributeInfo : public CAttributeInfo
    {
    public:
        void DeserializeBody(CClassReader& Reader) override
        {
            Reader >> Entries;
        }

    private:
        TStandardSerializedArray<CStackMapFrame> Entries;
    };
}

