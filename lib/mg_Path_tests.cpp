#include "mg_Path.h"
#include "mg_Test.h"
#include <cstdio>
#include <cassert>
#include <cstring>
void run_tests_for_mg_Path(void)
{
    // Path::len() returns number of chars, not counting NUL
    TESTeq(Path::len("a/b/c/d.e"),9);

    // Path::len() returns 0 if string is empty
    TESTeq(Path::len(""),0);

    // Path::len() returns -1 if NUL is not found after N chars
    constexpr int SIZE = 257;
    char buf[SIZE]; memset(buf, '-',SIZE); buf[SIZE-1]='\0';
    TESTeq(Path::len(buf),-1);
}
