//
// Created by ASUS on 06/02/2021.
//

#pragma once

#include "Util/Types.h"

#include <sstream>

namespace Compiler
{
    class CClassReader;

    class CClassVersion
    {
    public:
        constexpr CClassVersion(u2 InMajorVersion, u2 InMinorVersion)
            : MajorVersion(InMajorVersion)
            , MinorVersion(InMinorVersion)
        {
        }

        CClassVersion() = default;
        ~CClassVersion() = default;

        FORCEINLINE friend void operator>>(CClassReader& Reader, CClassVersion& Instance)
        {
            Reader >> Instance.MinorVersion;
            Reader >> Instance.MajorVersion;
        }

        [[nodiscard]]
        FORCEINLINE u2 GetMajorVersion() const
        {
            return MajorVersion;
        }

        [[nodiscard]]
        FORCEINLINE u2 GetMinorVersion() const
        {
            return MinorVersion;
        }

        FORCEINLINE bool operator< (const CClassVersion& ClassVersion) const
        {
            if (MajorVersion < ClassVersion.MajorVersion)
            {
                return true;
            }
            if (MajorVersion == ClassVersion.MajorVersion)
            {
                return MinorVersion < ClassVersion.MinorVersion;
            }

            return false;
        }

        [[nodiscard]]
        std::string ToString() const
        {
            std::ostringstream Oss;
            Oss << MajorVersion << "." << MinorVersion;

            return Oss.str();
        }

    private:
        u2 MajorVersion = (u2)0;
        u2 MinorVersion = (u2)0;
    };
}
