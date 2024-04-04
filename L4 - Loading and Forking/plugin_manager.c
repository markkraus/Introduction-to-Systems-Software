#include <dlfcn.h> // provides dlopen, etc
#include <stdio.h> // provides fprintf and stderr
int main(int argc, char *argv[]){



     // Check for failure when loading
    if(argc < 2) {
        printf("Error: Missing argument\n");
        return 1;
    }

    char plugin_path[100];
    sprintf(plugin_path, "./%s.so", argv[1]);

    void * handle = dlopen(plugin_path, RTLD_LAZY);


    // Check that file opened successfully
    if(!handle){
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    // Function pointer declaration
    int (*initialize)();
    int (*run)();
    int (*cleanup)();

    initialize = dlsym(handle, "initialize");
    char * error = dlerror();
    if(dlerror()) {
        fprintf(stderr, "%s\n", error);
        return 1;
    }

    run = dlsym(handle, "run");
    error = dlerror();
    if(error) {
        fprintf(stderr, "%s\n", error);
        return 1;
    }

    cleanup = dlsym(handle, "cleanup");
    error = dlerror();
    if(error) {
        fprintf(stderr, "%s\n", error);
        return 1;
    }

    initialize();
    run();
    cleanup();


    dlclose(handle);
    return 0;
}
