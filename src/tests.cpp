#include "mg_Test.h"
#include "mg_Path_tests.cpp"
int main()
{
    //////////
    // WELCOME
    //////////
    puts("Running tests...");
    ///////////////////////
    // PUT TEST SUITES HERE
    ///////////////////////
    run_tests_for_mg_Path();
    ////////////////////
    // REPORT TEST STATS
    ////////////////////
    printf("FAIL/PASS/TOTAL: %d/%d/%d\n",Tests::fail,Tests::pass,Tests::total);
    TESTeq(Tests::pass+Tests::fail,Tests::total);
}
