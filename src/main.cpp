#include "SDL.h"
#include "mg_WindowInfo.h"
#include "mg_Path.h"

constexpr bool DEBUG = true; 
#define LOGint(var) if(DEBUG) printf("%4d:%s: %d\n",__LINE__,#var,var);
#define LOGhex(var) if(DEBUG) printf("%4d:%s: 0x%X\n",__LINE__,#var,var);
void get_title_from_argv0(char* argv0, char *title, const int MAX)
{
    if(DEBUG) printf("%4d:Enter get_title_from_argv0()\n", __LINE__);
    // 9:Enter get_title_from_argv0()

    char* path = argv0;
    if(DEBUG) printf("%4d:path: %s\n", __LINE__, path);
    // 13:path: C:\msys64\home\mike\gitrepos\cpp\play-music\build\main.exe

    // Find indices of first and last char in folder name
    char* c = path; int n=0; while(*c++!='\0') n++;    // Walk to end of path
    while((n>=0)&&( (*c!='\\')&&(*c!='/') )) {n--;c=&path[n];} // Walk back to next slash
    int n1 = n;                                         // Store index of slash
    if(DEBUG)
    { // 23:path[49]: \main.exe
        char* slash1 = &path[n1];
        printf("%4d:path[%d]: %s\n", __LINE__, n1, slash1);
    }
    c--;n--;                                            // Move past the slash
    while((n>=0)&&( (*c!='\\')&&(*c!='/') )) {n--;c=&path[n];} // Walk back to next slash
    int n2 = n;                                         // Store index of slash
    if(DEBUG)
    { // 31:path[43]: \build\main.exe
        char* slash2 = &path[n2];
        printf("%4d:path[%d]: %s\n", __LINE__, n2, slash2);
    }
    c--;n--;                                            // Move past the slash
    while((n>=0)&&( (*c!='\\')&&(*c!='/') )) {n--;c=&path[n];} // Walk back to next slash
    int n3 = n;                                         // Store index of slash
    if(DEBUG)
    { // 39:path[32]: \play-music\build\main.exe
        char* slash3 = &path[n3];
        printf("%4d:path[%d]: %s\n", __LINE__, n3, slash3);
    }

    // Extract indices of folder name
    int first_c = n3+1;                                 // First letter in folder name
    int last_c = n2;                                    // Trailing slash

    // Use folder name as game title
    int title_length = last_c - first_c;
    if(DEBUG) printf("%4d:length: %d chars\n",__LINE__,title_length);
    // 47:length: 10 chars

    // Copy folder name into title
    int i=0;                                            // Index into the title
    for(int n=first_c; (n<last_c)&&(i<MAX-1); n++, i++) title[i] = path[n];
    title[i] = '\0';                                    // NUL-terminate the title
}

void shutdown()
{
}

int main(int argc, char* argv[])
{
    { // Set window position, size and behavior
        if(DEBUG)
        { // Report executable and cmdline args
            printf("%4d:Run: \"%s\"",__LINE__,argv[0]);
            if(argc>1) printf("\n%4d:cmdline args: ",__LINE__);
            for(int i=1;i<argc;i++) printf("%s%s",argv[i],i+1==argc?"":", ");
            puts("");
        }
        // Set default window behavior if no cmdline args passed
        WindowInfo wI{.x=10,.y=10,.w=200,.h=200, .flags=SDL_WINDOW_RESIZABLE};
        { // Use any cmdline args (if passed) for window behavior
            if(argc > 1) {wI.x = atoi(argv[1]);} LOGint(wI.x);
            if(argc > 2) {wI.y = atoi(argv[2]);} LOGint(wI.y);
            if(argc > 3) {wI.w = atoi(argv[3]);} LOGint(wI.w);
            if(argc > 4) {wI.h = atoi(argv[4]);} LOGint(wI.h);
        }
        { // If passed args, probably from Vim, so make window always-on-top
            if(argc > 1) wI.flags |= SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP;
            LOGhex(wI.flags);
        }
    }
    SDL_Init(SDL_INIT_VIDEO);
    // Use folder name as game title
    constexpr int MAX = 64;                             // Max name length is 63 chars
    char title[MAX];                                    // Last char is NUL
    get_title_from_argv0(argv[0], title, MAX);
    puts(title);
    int n = Path::len(argv[0]);
    if(n<0)
    {
        printf("%4d:ERROR: path is too long:\n    \"%s\"\n",__LINE__,argv[0]);
        shutdown(); return EXIT_FAILURE;
    }
    LOGint(n);
    /* SDL_CreateWindow(argv[0], */
    return EXIT_SUCCESS;
}
