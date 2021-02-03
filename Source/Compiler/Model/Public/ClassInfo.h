//
// Created by ASUS on 03/01/2021.
//

#pragma once

#include "Types.h"
#include "ConstantPool.h"

#include "FieldInfo.h"
#include "MethodInfo.h"

#include "SerializedArray.h"

namespace Parse
{
    class CClassReader;

    enum class EClassInfoDeserializingMode : u1
    {
        ConstantPool,

        All = std::numeric_limits<u1>::max()
    };

    struct EClassAccessFlags
    {
        using Type = u2;

        // Declared public; may be accessed from outside its package.
        static constexpr Type ACC_PUBLIC 	    = 0x0001;

        // Declared final; no subclasses allowed.
        static constexpr Type ACC_FINAL 	    = 0x0010;

        // Treat superclass methods specially when invoked by the invokespecial instruction.
        static constexpr Type ACC_SUPER 	    = 0x0020;

        // Is an interface, not a class.
        static constexpr Type ACC_INTERFACE 	= 0x0200;

        // Declared abstract; must not be instantiated.
        static constexpr Type ACC_ABSTRACT      = 0x0400;

        // Declared synthetic; not present in the source code.
        static constexpr Type ACC_SYNTHETIC 	= 0x1000;

        // Declared as an annotation type.
        static constexpr Type ACC_ANNOTATION 	= 0x2000;

        // Declared as an enum type.
        static constexpr Type ACC_ENUM 	        = 0x4000;
    };

    class CClassInfo
    {
    public:
        void Deserialize(CClassReader& Reader,
                         EClassInfoDeserializingMode ClassInfoDeserializingMode = EClassInfoDeserializingMode::All
        );

        FORCEINLINE friend void operator>>(CClassReader& Reader, CClassInfo& Instance)
        {
            Instance.Deserialize(Reader, EClassInfoDeserializingMode::All);
        }

        void Debug_PrintFields() const;
        void Debug_PrintMethods() const;

    private:
        u4 Magic        = (u4)0;
        u2 MinorVersion = (u2)0;
        u2 MajorVersion = (u2)0;

        std::shared_ptr<CConstantPool> ConstantPool = std::make_shared<CConstantPool>();

        EClassAccessFlags::Type AccessFlags = (EClassAccessFlags::Type)0;
        u2 ThisClass    = (u2)0;
        u2 SuperClass   = (u2)0;

        Util::TStandardSerializedArray<u2> Interfaces;
        Util::TStandardSerializedArray<CFieldInfo> Fields;
        Util::TStandardSerializedArray<CMethodInfo> Methods;

        Util::TStandardSerializedArray<CSharedAttributeInfo> Attributes;
    };
}
