//
// Created by ASUS on 09/04/2021.
//

#pragma once

#include "Types.h"
#include <vector>
#include <string>
#include <algorithm>
#include <ostream>
#include <sstream>
#include <limits>

#ifdef min
    #undef min
#endif

#ifdef max
    #undef max
#endif


namespace Compiler
{
    class CCppPrinter
    {
        friend class CLine;

        static constexpr usz NumLineReserveItems = 32;

        static constexpr const char* HeaderString = "// This code is generated. Please do not edit.";

    public:
        class CLine
        {
        public:
            FORCEINLINE explicit CLine(const u1 InNumTabs) : NumTabs(InNumTabs)
            {
                Items.reserve(CCppPrinter::NumLineReserveItems);
            }

            FORCEINLINE ~CLine() = default;

            FORCEINLINE void Append(const std::string& InItem)
            {
                Items.push_back(InItem);
            }

            FORCEINLINE void AppendNTBS(const std::vector<u1>& InItem)
            {
                std::string Result;
                Result.reserve(2 + (4 * InItem.size()));

                Result.push_back('\"');
                for (const u1 &Item : InItem)
                {
                    static const char HexNumberChars[] = {
                        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
                    };

                    Result.push_back('\\');
                    Result.push_back('x');
                    Result.push_back(HexNumberChars[(u1) ((Item >> 4) & 0x0f)]);
                    Result.push_back(HexNumberChars[(u1) (Item & 0x0f)]);
                }
                Result.push_back('\"');

                Items.push_back(std::move(Result));
            }

            FORCEINLINE void IncTabs() { NumTabs = (u1)std::min<s4>(((s4)NumTabs) + 1, (s4)std::numeric_limits<u1>::max()); }
            FORCEINLINE void DecTabs() { NumTabs = (u1)std::max<s4>(((s4)NumTabs) - 1, (s4)0); }

            [[nodiscard]]
            FORCEINLINE u1 GetNumTabs() const { return NumTabs; }

            friend std::ostream& operator<<(std::ostream& Os, const CLine& Line)
            {
                for (s4 Index = (s4)0; Index < (s4)Line.NumTabs; ++Index)
                    Os << "    ";

                for (const std::string& Item : Line.Items)
                    Os << Item;

                return Os;
            }

        private:
            u1 NumTabs;
            std::vector<std::string> Items;
        };

        enum class EOutputChannelType : u1
        {
            Header  = 0,
            Cpp     = 1,

            Num
        };

        static constexpr const char* GetFileExtension(const EOutputChannelType& OutputType)
        {
            switch (OutputType)
            {
                case EOutputChannelType::Header:
                    return "h";
                case EOutputChannelType::Cpp:
                    return "cpp";
                default:
                    return "";
            }
        }

        class COutputChannel
        {
            FORCEINLINE CLine& GetCurrentLine()
            {
                if (UNLIKELY(Lines.empty()))
                {
                    Lines.emplace_back(CLine((u1) 0)).Append(HeaderString);
                    NewLine();
                }

                return Lines.back();
            }
        public:
            FORCEINLINE void NewLine() { Lines.emplace_back(GetCurrentLine().GetNumTabs()); }
            FORCEINLINE void Append(const std::string& InItem) { GetCurrentLine().Append(InItem); }
            FORCEINLINE void AppendNTBS(const std::vector<u1>& InItem) { GetCurrentLine().AppendNTBS(InItem); }

            FORCEINLINE void IncTabs() { GetCurrentLine().IncTabs(); }
            FORCEINLINE void DecTabs() { GetCurrentLine().DecTabs(); }

            FORCEINLINE friend std::ostream& operator<<(std::ostream& Os, const COutputChannel& OutputChannel)
            {
                if (!OutputChannel.Lines.empty())
                {
                    for (const CLine &Line : OutputChannel.Lines)
                    {
                        Os << Line << std::endl;
                    }
                }
                else
                {
                    Os << "// File is empty";
                }

                return Os;
            }

        private:
            std::vector<CLine> Lines = {};
        };

        FORCEINLINE COutputChannel& GetCurrentOutputChannel() { return OutputChannels[(usz)OutputChannelType]; }

    public:
        CCppPrinter& NewLine(usz NumNewLines = 1)
        {
            COutputChannel& OutputChannel = GetCurrentOutputChannel();

            for (usz Index = 0; Index < NumNewLines; ++Index)
                OutputChannel.NewLine();

            return *this;
        }

        template <typename TArithmetic, std::enable_if_t<std::is_arithmetic<TArithmetic>::value, bool> = true>
        CCppPrinter& Append(const TArithmetic Number)
        {
            Append(std::to_string(Number));
            return *this;
        }

        CCppPrinter& Append(const std::string& InItem)
        {
            GetCurrentOutputChannel().Append(InItem);
            return *this;
        }

        /**
         * Append a NTBS (a null-terminated byte string, each character is represented as '\xXX')
         *
         * @param InItem Vector, containing bytes of that string.
         * @return This CCppPrinter.
         */
        CCppPrinter& AppendNTBS(const std::vector<u1>& InItem)
        {
            GetCurrentOutputChannel().AppendNTBS(InItem);
            return *this;
        }

        CCppPrinter& IncTabs()
        {
            GetCurrentOutputChannel().IncTabs();
            return *this;
        }

        CCppPrinter& DecTabs()
        {
            GetCurrentOutputChannel().DecTabs();
            return *this;
        }

        // SUGAR
        FORCEINLINE CCppPrinter& ScopeBegin()   { return NewLine().Append("{").NewLine().IncTabs(); }
        FORCEINLINE CCppPrinter& ScopeEnd()     { return NewLine().DecTabs().Append("}"); }
        FORCEINLINE CCppPrinter& Space()        { return Append(" "); }

        FORCEINLINE CCppPrinter& Include(const std::string& String, bool bTriangle = false)
        {
            return Append("#include").Space()
                .Append(bTriangle ? "<" : "\"")
                .Append(String)
                .Append(bTriangle ? ">" : "\"")
                .NewLine();
        }

        FORCEINLINE CCppPrinter& ClassBegin(const std::string& ClassName)
        {
            return Append("class").Space().Append(ClassName).ScopeBegin();
        }

        FORCEINLINE CCppPrinter& ClassEnd(const std::string& ClassName)
        {
            return ScopeEnd().Append(";").NewLine();
        }

        FORCEINLINE CCppPrinter& Semicolon() { return Append(";"); }
        FORCEINLINE CCppPrinter& SemicolonNewLine() { return Semicolon().NewLine(); }

        // Switch between header/cpp
        FORCEINLINE CCppPrinter& SwitchToHeader()   { OutputChannelType = EOutputChannelType::Header;   return *this; }
        FORCEINLINE CCppPrinter& SwitchToCpp()      { OutputChannelType = EOutputChannelType::Cpp;      return *this; }

        // DEBUG
        FORCEINLINE friend void operator<<(std::ostream& Os, const CCppPrinter& CppPrinter)
        {
            std::string OutputChannelTypeNames[(usz)EOutputChannelType::Num];
            {
                OutputChannelTypeNames[(usz)EOutputChannelType::Header] = "Header file";
                OutputChannelTypeNames[(usz)EOutputChannelType::Cpp] = "Cpp file";
            }

            for (usz Index = 0; Index < (usz)EOutputChannelType::Num; ++Index)
            {
                Os << ">>> " << OutputChannelTypeNames[Index] << std::endl;
                Os << CppPrinter.OutputChannels[Index];

                Os << std::endl;
            }
        }

    private:
        EOutputChannelType OutputChannelType = EOutputChannelType::Header;
        COutputChannel OutputChannels[(usz)EOutputChannelType::Num];
    };
}