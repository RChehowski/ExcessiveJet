//
// Created by ASUS on 09/04/2021.
//

#pragma once

#include <string>
#include <vector>
#include <functional>

namespace Util
{
    using CString = std::string;

    class CStringUtils
    {
    public:
        template<typename TAllocator>
        static void ParseIntoVector(const CString& String, const CString& Separator, std::vector<CString, TAllocator>& Result)
        {
            using CStringSizeType = CString::size_type;

            CStringSizeType BeginIndex = 0;
            CStringSizeType EndIndex = 0;

            CStringSizeType SeparatorLength = Separator.length();

            auto AddSubstring = [&String, &Result](CStringSizeType BeginIndex, CStringSizeType EndIndex)
            {
                const CStringSizeType SubstringLen = EndIndex - BeginIndex;
                if (SubstringLen > 0)
                {
                    Result.push_back(std::move(String.substr(BeginIndex, SubstringLen)));
                }
            };

            while ((EndIndex = String.find(Separator, BeginIndex)) != CString::npos)
            {
                AddSubstring(BeginIndex, EndIndex);
                BeginIndex = EndIndex = (EndIndex + SeparatorLength);
            }

            AddSubstring(BeginIndex, String.length());
        }

        static std::vector<CString> ParseIntoVector(const CString& String, const CString& Separator)
        {
            std::vector<CString> Result;
            ParseIntoVector(String, Separator, Result);

            return Result;
        }
    };
}
