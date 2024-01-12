#include "nosystem.h"

#include <atomic>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <thread>
#include <vector>

#include <unistd.h>

#if defined(__APPLE__)
#include <TargetConditionals.h>
#if TARGET_OS_IPHONE
#undef stdin
#undef stdout
#undef stderr
extern "C" {
extern __thread FILE* nosystem_stdin;
extern __thread FILE* nosystem_stdout;
extern __thread FILE* nosystem_stderr;
};
#define stdin nosystem_stdin
#define stdout nosystem_stdout
#define stderr nosystem_stderr
#endif
#endif

extern "C" {

int uname_main(int argc, char** argv) {
#if __APPLE__
    const auto kernel = "Darwin\n";
#elif __wasi__
    const auto kernel = "WASI\n";
#else
#error No system interface kernel defined
#endif
    if (argc == 1) {
        fprintf(stdout, kernel);
    }
    else if (argc > 1) {
        const auto opt = std::string(argv[1]);
        if (opt == "-v") {
            fprintf(stdout, "Darwin Kernel Version xx.y.z\n");
        } else if (opt == "-r") {
            fprintf(stdout, "xx.y.z\n");
        } else if (opt == "-s") {
            fprintf(stdout, kernel);
        }
    }
    fflush(stdout);
    return 0;
}

}
