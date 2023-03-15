As part of exercises to teach myself C.

# Exercise 1

Write a program to parse the output of gcc compiler flag `-M` for
use by `ctags`.

*Mindset:* this is a "boot-strapping" program: it just needs to
do this one job so you can use it to help write other programs.

So:

- don't try to generalize this for parsing files in general; it
  only has to parse the output of `gcc` with the `-M` flag
- write it as a single file: `ctags-dlist.c` or `ctags-dlist.cpp`
- don't split this program up into reusable pieces

## Exercise 1 Details

Use `-M` to create list of dependencies. Output dependency list
as `main.d`:

```
g++ -M src/main.cpp -MF build/main.d
```

Write a program `ctags-dlist` that takes `main.d` as a cmdline
arg and generates a file named `headers.txt`

```
build/ctags-dlist build/main.d
```

Generate `ctags` using `headers.txt`:

```
ctags --c-kinds=+p+x -L headers.txt
```

# Exercise 2

Add unit tests to a project by rolling your own testing
framework. There are a lot of ways to do this, the method here is
just something I came up with on the fly.

Create a header-only library that defines the test functionality
(like testing if two values are equal) and that tracks the test
state. For example:

```c
#ifndef __MG_TEST_H__
#define __MG_TEST_H__
#define TESTeq(a,b) if(a!=b) printf("%4d:FAIL:Expect '%s == %d' but '%s == %d'\n",\
                                    __LINE__,#a,b,#a,a); Tests::count++;
namespace Tests
{
    int count = 0;
}
#endif // __MG_TEST_H__
```

Do not try to unit test main. Instead, move code from main out
into a header-only library, then create a `.c` or `.cpp` file for
each header-only library with `_tests` appended to its name.

The `_tests` file includes the header-only library under-test and
includes the unit test lib (`mg_Test.h`). This source file has no
`main` entry point, it defines a single function
`run_tests_for_LIBNAME` that runs the tests for that lib.

Finally, create a test runner file in `src`, e.g.,
`src/tests.cpp`. This file defines the `main` entry point for
running tests and glues all the tests together into one
executable.

```c
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
    printf("Tests::count: %d\n",Tests::count);
}
```

An alternative to avoid writing this test runner file is to give
each `_tests` file its own main entry point, then put a `for`
loop in a `make` recipe that loops over all the test files,
builds them, and runs them.

My way (with a test runner in C) is more work to set up because
I'm writing yet another source file, but it's easier for me to
figure out how to set it up this way and it gives me more
flexibility over which tests run. This is the sort of thing that
a proper test framework would be much better at.

Another weird thing about my method is that I *include* the
`_tests.cpp` source files in my test runner file! Then the
`main()` calls the `run_tests_for_LIBNAME` function defined in
the `.cpp` file.

Including anything other than `.h` is considered bad form, but I
think it's fine in this specific use case, so stop worrying and
just `#include "LIBNAME_tests.cpp"`.

Run unit tests with `make test`. This rebuilds all tests
every time, then it runs the tests.

```make
test: build/tests
.PHONY: build/tests
build/tests: src/tests.cpp
	$(CXX) $(CXXFLAGS_BASE) $^ -o $@
	build/tests
```

# Exercise 3

Write a cmdline music player. It takes a file path as an arg and
plays that file once.

First step is to parse file paths.
