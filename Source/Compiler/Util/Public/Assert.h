//
// Created by ASUS on 31/12/2020.
//

#ifndef CPP20_ASSERT_H
#define CPP20_ASSERT_H

#define ASSERT(Condition) if (!(Condition)) { exit(1); }

#define CONSTEXPR_ASSERT(Condition, Str) []<bool _flag = Condition>() { static_assert(_flag, Str); }()

#endif //CPP20_ASSERT_H
