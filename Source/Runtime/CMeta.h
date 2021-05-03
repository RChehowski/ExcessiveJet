//
// Created by ASUS on 28/04/2021.
//

#pragma once

#include "Types.h"
#include <ostream>

enum class EMetaType : u1
{
    Class,
    Method
};

class CMeta
{
public:
    FORCEINLINE explicit CMeta(const EMetaType& InMetaType) : MetaType(InMetaType) {}

    [[nodiscard]] FORCEINLINE bool IsClass() const    { return MetaType == EMetaType::Class; }
    [[nodiscard]] FORCEINLINE bool IsMethod() const   { return MetaType == EMetaType::Method; }

    virtual void PrintInto(std::ostream& os) const {}

private:
    const EMetaType MetaType;
};
