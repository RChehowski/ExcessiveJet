//
// Created by ASUS on 31/12/2020.
//

#ifndef CPP20_ASSERT_H
#define CPP20_ASSERT_H

void DebugBreakOrExit();

#define WITH_ASSERT 1

#if WITH_ASSERT
    #define ASSERT(Condition)\
        while (!(Condition))\
        {\
            fprintf(stderr, "In %s:%d\n", __FILE__, __LINE__);\
            fprintf(stderr, "Assertion failed: %s", LITERAL_TO_STRING(Condition));\
            fflush(stderr);\
            DebugBreakOrExit();\
        }

    #define ASSERT_MSG(Condition, Fmt, ...)\
        while (!(Condition))\
        {\
            fprintf(stderr, "In %s:%d\n", __FILE__, __LINE__);\
            fprintf(stderr, "Assertion failed: %s\n", LITERAL_TO_STRING(Condition));\
            fprintf(stderr, Fmt, ##__VA_ARGS__);\
            fflush(stderr);\
            DebugBreakOrExit();\
        }
#else
    #define ASSERT(Condition)
    #define ASSERT_MSG(Condition, Fmt, ...)
#endif // WITH_ASSERT

#define ASSERT_NOT_NULLPTR(Item) ASSERT_MSG(((Item) != nullptr), "%s must not be nullptr", LITERAL_TO_STRING(Item))

#define CONSTEXPR_ASSERT(Condition, Str) []<bool _flag = Condition>() { static_assert(_flag, Str); }()

#endif //CPP20_ASSERT_H
