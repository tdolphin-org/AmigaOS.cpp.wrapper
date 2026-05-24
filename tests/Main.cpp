//
//  AmigaOS MUI C++ wrapper
//
//  Tests
//
//  (c) 2024-2026 TDolphin
//

#include "Main.hpp"

#include <type_traits>
#include <utility>

#include "amiga_std_light/iostream.hpp"

using namespace std;

template <typename T, typename = void> struct is_stream_insertable : std::false_type
{
};

template <typename T>
struct is_stream_insertable<T, std::void_t<decltype(std::declval<amiga_std_light::basic_ostream &>() << std::declval<T>())>>
  : std::true_type
{
};

static_assert(is_stream_insertable<const char *>::value, "const char* should be stream insertable");
static_assert(is_stream_insertable<char>::value, "char should be stream insertable");
static_assert(is_stream_insertable<signed char>::value, "signed char should be stream insertable");
static_assert(is_stream_insertable<unsigned char>::value, "unsigned char should be stream insertable");
static_assert(is_stream_insertable<int>::value, "int should be stream insertable");
static_assert(is_stream_insertable<unsigned int>::value, "unsigned int should be stream insertable");
static_assert(is_stream_insertable<long>::value, "long should be stream insertable");
static_assert(is_stream_insertable<unsigned long>::value, "unsigned long should be stream insertable");
static_assert(is_stream_insertable<long long>::value, "long long should be stream insertable");
static_assert(is_stream_insertable<unsigned long long>::value, "unsigned long long should be stream insertable");
static_assert(is_stream_insertable<float>::value, "float should be stream insertable");
static_assert(is_stream_insertable<double>::value, "double should be stream insertable");
static_assert(is_stream_insertable<bool>::value, "bool should be stream insertable");

static_assert(std::is_same<decltype(std::declval<amiga_std_light::basic_ostream &>() << std::declval<long>()),
                           amiga_std_light::basic_ostream &>::value,
              "operator<<(long) must return basic_ostream&");

static_assert(std::is_same<decltype(std::declval<amiga_std_light::basic_ostream &>() << std::declval<unsigned long>()),
                           amiga_std_light::basic_ostream &>::value,
              "operator<<(unsigned long) must return basic_ostream&");

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    cout << "Tests started!" << endl;

    char a = 10;
    unsigned char b = 20;
    int c = 16;
    unsigned int d = 32;
    long e = 64;
    unsigned long f = 128;
    long long g = 256;
    unsigned long long h = 512;

    amiga_std_light::basic_ostream &same_stream
        = (std::cout << "chain test: " << static_cast<int>(a) << ' ' << b << ' ' << c << ' ' << d << ' ' << e << ' ' << f << ' ' << g
                     << ' ' << h << "\n");

    if (&same_stream != &std::cout)
    {
        std::cerr << "[FAIL] operator<< should return same stream instance" << endl;
        return 1;
    }

    std::cout << "base test dec=" << 255u << " hex=" << std::hex << 255u << " oct=" << std::oct << 255u << std::dec << "\n";
    std::cout.write("write/flush test\n", 17).flush();

    void *p = &same_stream;
    std::cout << "ptr=" << p << " bool=" << true << " float=" << 1.5f << " double=" << 2.25 << "\n";

    cout << "Tests finished!" << endl;

    return 0;
}