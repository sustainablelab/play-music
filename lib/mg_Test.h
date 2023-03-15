#ifndef __MG_TEST_H__
#define __MG_TEST_H__
#define TESTeq(a,b) if(a!=b) \
    {\
        printf("%4d:FAIL:Expect '%s == %d' but '%s == %d'\n",\
                __LINE__,#a,b,#a,a);\
        Tests::fail++;\
    }\
    else Tests::pass++;\
    Tests::total++;
namespace Tests
{
    int total = 0;
    int pass = 0;
    int fail = 0;
}
#endif // __MG_TEST_H__

