#include "prx/libc/include/FileStream.hpp"
#include "prx/libc/include/general/VabiMacros.hpp"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string_view>
#ifdef _WIN32
#include <stdlib.h>
extern "C" _invalid_parameter_handler _set_thread_local_invalid_parameter_handler(_invalid_parameter_handler);
#endif
extern "C" {
FileStream* APS5_VABI freopen_nid_postfix(const char*, const char*, FileStream*);
int* APS5_VABI __error_nid_postfix();
extern FileStream* __stdoutp_nid_postfix;
extern FileStream* __stderrp_nid_postfix;
}

static void Require(bool value) { if (!value) std::abort(); }

namespace {
int g_invalidParameters = 0;

#ifdef _WIN32
void CountInvalidParameter(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, std::uintptr_t) {
    ++g_invalidParameters;
}
#endif

bool HostWrites(bool output) {
    std::FILE* const stream = output ? stdout : stderr;
    const bool written = std::fputs("host stream open\n", stream) >= 0 && std::fflush(stream) == 0;
    return written && g_invalidParameters == 0;
}
}

int main(int argc, char** argv) {
#ifdef _WIN32
    _set_thread_local_invalid_parameter_handler(CountInvalidParameter);
#endif
    Require(argc == 3);
    const std::string_view stream = argv[1];
    const std::string_view failure = argv[2];
    Require(stream == "stdout" || stream == "stderr");
    Require(failure == "missing" || failure == "unresolved");
    const bool output = stream == "stdout";
    FileStream* const guest = output ? __stdoutp_nid_postfix : __stderrp_nid_postfix;
    const char* const path = failure == "missing" ? "missing-freopen-host-dir/out.log" : "missing-freopen-host-dir/\xff.log";
    Require(HostWrites(output));
    *__error_nid_postfix() = 0;
    Require(freopen_nid_postfix(path, "w", guest) == nullptr && *__error_nid_postfix() == 2);
    Require(HostWrites(output));
    return 0;
}
