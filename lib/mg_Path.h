#ifndef __MG_PATH_H__
#define __MG_PATH_H__

namespace Path
{
    /**
     * Return the length of the path, not counting the NUL-terminator.
     * Return -1 if no NUL is encountered after 256 characters.
     *
     * Examples
     * --------
     *      // Example 1
     *      Path::len("my/path/to/file.bob");
     *
     *      // Example 2
     *      const char* path = "my/path/to/file.bob";
     *      Path::len(path);
     *
     *      // Example 3
     *      const char* path = {'h','i','/','b','o','b','\0'};
     *      Path::len(path);
     *
     * Note
     * ----
     * In Example 3 above, if the NUL-terminator is omitted, Path::len() might not return -1.
     *
     *      // Example 3 -- BAD
     *      const char* path = {'h','i','/','b','o','b'};
     *      Path::len(path);
     *
     * Path::len() returns -1 if no NUL is encountered after 256 characters.
     * This always works for C string literals because they implicitly contain a NUL
     * terminator. But character arrays only contain what you put in them.
     *
     * So in the above BAD version of Example 3, you would expect Path::len(path) == -1.
     * It might be. It might not be. It depends on what is in memory.
     * If a NUL is encountered before hitting 256 characters, Path::len() does not return
     * -1, it returns the number of characters up to that NUL.
     *
     * To work directly with char arrays like this (and still rely on Path::len() returning
     * -1), start with a char buffer that is greater than 256 chars so that Path::len() is
     * guaranteed to give up before finding a random `\0'.
     *
     * Use at least 257 chars. And just in case this char buffer is later treated
     * like a C string literal (expecting a '\0' somewhere), it is a good idea to put a '\0'
     * at the end of the array.
     *
     * For example:
     *      constexpr int SIZE = 257;
     *      char buf[SIZE]; memset(buf, '-',SIZE); buf[SIZE-1]='\0';
     *
     *      Path::len(buf); // Returns -1
     *
     * \param path a path as a C-string-literal  like "a/b/c/d.e"
     */
    int len(const char *path)
    {
        constexpr int MAX = 256;                        // MAX chars to walk before giving up
        const char* c = path; int n=0;                  // Start at beginning of path
        while((*c++!='\0') && (n<MAX)) n++;             // Walk to end of path
        return n==MAX ? -1 : n;
    }
}

#endif // __MG_PATH_H__

