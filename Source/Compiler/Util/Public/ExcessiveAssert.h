//
// Created by ASUS on 31/12/2020.
//

#ifndef CPP20_ASSERT_H
#define CPP20_ASSERT_H

void DebugBreakOrExit();

#define WITH_ASSERT 1

#if WITH_ASSERT
    #define ASSERT(Condition)\
        if (!(Condition))\
        {\
            fprintf(stderr, "In %s:%d\n", __FILE__, __LINE__);\
            fprintf(stderr, "Assertion failed: %s", LITERAL_TO_STRING(Condition));\
            fflush(stderr);\
            DebugBreakOrExit();\
        }

    #define ASSERT_MSG(Condition, Fmt, ...)\
        if (!(Condition))\
        {\
            fprintf(stderr, "In %s:%d\n", __FILE__, __LINE__);\
            fprintf(stderr, "Assertion failed: %s\n", LITERAL_TO_STRING(Condition));\
            fprintf(stderr, Fmt, __VA_ARGS__);\
            fflush(stderr);\
            DebugBreakOrExit();\
        }
#else
    #define ASSERT(Condition)
#endif // WITH_ASSERT

#define CONSTEXPR_ASSERT(Condition, Str) []<bool _flag = Condition>() { static_assert(_flag, Str); }()

#endif //CPP20_ASSERT_H
