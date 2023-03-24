//
// Created by ASUS on 06/02/2021.
//

#include "Model/Debug/DebugMisc.h"

#include <vector>
#include <sstream>
#include <algorithm>

#include "Util/ExcessiveAssert.h"

namespace Debug
{
    std::string ArrayDimensionsToString(usz ArrayDimensions)
    {
        std::ostringstream Oss;

        for (usz Index = 0; Index < ArrayDimensions; ++Index)
        {
            Oss << "[]";
        }

        return Oss.str();
    }

    std::vector<std::string> SplitMethodArguments(std::string& TypeString)
    {
        std::vector<std::string> Result;

        std::string::size_type TypeStringLength = TypeString.length();

        std::string::size_type Begin = 0;
        bool bObjectScanInProgress = false;
        bool bArrayScanInProgress = false;

        for (std::string::size_type Index = 0; Index < TypeStringLength; ++Index)
        {
            if (!bObjectScanInProgress)
            {
                const char FirstChar = TypeString[Index];

                bool bIsPrimitive = [FirstChar]
                {
                    switch (FirstChar)
                    {
                        case 'Z':
                        case 'B':
                        case 'C':
                        case 'S':
                        case 'I':
                        case 'J':
                        case 'F':
                        case 'D':
                            return true;
                        default:
                            return false;
                    }
                }();

                if (bIsPrimitive)
                {
                    Result.push_back(TypeString.substr(Begin, (Index - Begin) + 1));

                    bObjectScanInProgress = false;
                    bArrayScanInProgress = false;

                    Begin = Index + 1;
                }
                else
                {
                    if (FirstChar == '[')
                    {
                        Begin = Index;
                        bArrayScanInProgress = true;
                    }
                    else if (FirstChar == 'L')
                    {
                        if (!bArrayScanInProgress)
                        {
                            Begin = Index;
                        }
                        // Otherwise this is an array of objects, we should not move `Begin`

                        bObjectScanInProgress = true;
                    }
                    else
                    {
                        ASSERT_MSG(false, "Unknown first char: %c. TypeString: %s, Index: %llu",
                           FirstChar,
                           TypeString.c_str(),
                           (unsigned long long)Index
                       );
                    }
                }
            }
            else if (TypeString[Index] == ';')
            {
                Result.push_back(TypeString.substr(Begin, (Index - Begin) + 1));

                bObjectScanInProgress = false;
                bArrayScanInProgress = false;

                Begin = Index + 1;
            }
        }

        return Result;
    }

    std::string DecodeType(const std::string& TypeString)
    {
        std::string::size_type TypeStringIndex = 0;

        usz ArrayDimensions = 0;
        while (TypeString[TypeStringIndex] == '[')
        {
            ArrayDimensions++;
            TypeStringIndex++;
        }

        if ((TypeString.size() - TypeStringIndex) == 1)
        {
            // Primitive
            std::string PrimitiveTypeName;
            switch (TypeString[TypeStringIndex])
            {
                case 'Z':   { PrimitiveTypeName = "boolean";    break; }
                case 'B':   { PrimitiveTypeName = "byte";       break; }
                case 'C':   { PrimitiveTypeName = "char";       break; }
                case 'S':   { PrimitiveTypeName = "short";      break; }
                case 'I':   { PrimitiveTypeName = "int";        break; }
                case 'J':   { PrimitiveTypeName = "long";       break; }
                case 'F':   { PrimitiveTypeName = "float";      break; }
                case 'D':   { PrimitiveTypeName = "double";     break; }

                default:    { PrimitiveTypeName.clear();        break; }
            }

            return PrimitiveTypeName + ArrayDimensionsToString(ArrayDimensions);
        }
        else if (TypeString[TypeStringIndex] == 'L')
        {
            // ObjectBase
            const std::string::size_type IndexOfEnd = TypeString.find(';', TypeStringIndex);

            std::string ClassName = TypeString.substr(
                TypeStringIndex + 1,
                IndexOfEnd - TypeStringIndex - 1
            );
            std::replace(ClassName.begin(), ClassName.end(), '/', '.');

            return ClassName + ArrayDimensionsToString(ArrayDimensions);
        }
        else
        {
            ASSERT_MSG(false, "Unknown TypeString: \"%s\"", TypeString.c_str());

            // No idea what was that
            return TypeString;
        }
    }

    std::string DecodeMethodReturnType(const std::string& SignatureString)
    {
        const std::string::size_type SecondParenIndex = SignatureString.find_last_of(')');

        std::string ReturnTypeString = SignatureString.substr(SecondParenIndex + 1);

        if (ReturnTypeString == "V")
        {
            return "void";
        }
        else
        {
            return DecodeType(ReturnTypeString);
        }
    }

    std::string DecodeMethodArgumentTypesJoined(const std::string& SignatureString)
    {
        const std::string::size_type FirstParenIndex = SignatureString.find('(', 0);
        const std::string::size_type SecondParenIndex = SignatureString.find(')', FirstParenIndex);

        std::string ArgumentsString = SignatureString.substr(FirstParenIndex + 1, SecondParenIndex - FirstParenIndex - 1);

        std::vector<std::string> VectorOfArguments = SplitMethodArguments(ArgumentsString);

        std::ostringstream Oss;
        for (std::vector<std::string>::size_type i = 0; i < VectorOfArguments.size(); ++i)
        {
            Oss << DecodeType(VectorOfArguments[i]);

            if (i < (VectorOfArguments.size() - 1))
            {
                Oss << ", ";
            }
        }

        return Oss.str();
    }
}