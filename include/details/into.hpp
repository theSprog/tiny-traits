
#include <type_traits>

namespace tiny_traits {
template <typename... Ts>
struct make_void {
    typedef void type;
};

template <typename... Ts>
using void_t = typename make_void<Ts...>::type;

//      判断 U 是否显式声明了   operator T() const
//      （仅靠 SFINAE，不用 <type_traits> 里的 is_convertible，
//       因为后者连 T 的构造函数 / friend 转换都算进去，我们只想锁定“成员运算符”）
template <typename U, typename T, typename = void>
struct has_conversion_op : std::false_type {};

template <typename U, typename T>
struct has_conversion_op<U,
                         T,
                         void_t<
                             // 只要这个表达式合法，就说明有成员 operator T()
                             decltype(std::declval<U const&>().operator T())>> : std::true_type {};

// ---- 3. CRTP 基类 ---------------------------------------------------------
template <typename T, typename Derived>
struct Into {
    Into() {
        static_assert(has_conversion_op<Derived, T>::value, "Derived class must declare:  operator T()  const");
    }
};
} // namespace tiny_traits
