//
// Created by ASUS on 06/02/2021.
//

#pragma once

#include <string>

#include "StringUtf8.h"

using Util::CStringUtf8;

namespace Debug
{
    std::string DecodeType(const std::string& TypeString);

    std::string DecodeFunctionReturnValue(const std::string& SignatureString);

    std::string DecodeFunctionArgumentsJoined(const std::string& SignatureString);
}
