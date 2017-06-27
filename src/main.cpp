// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>

#include <link.h>
#include <dlfcn.h>

typedef unsigned int (*functionPtr)(unsigned int);


int main (int argc, char *argv[])
{
  void *handle;
  char *error;
  functionPtr pFunc;

  if (argc < 2) {
    fprintf(stdout,"Usage: %s <integer>\n",argv[0]);
    return 1;
  }
  int inputValue = atoi(argv[1]);

  handle = dlopen ("/home/will/work/lockheed/testbays/sharedLib/lib/libfactorial.so", RTLD_LAZY);
  if (!handle) {
     fputs (dlerror(), stderr);
     exit(1);
  }

  link_map *map;
  dlinfo(handle, RTLD_DI_LINKMAP, &map);

  while (map != NULL) {
   printf("%p: %s\n", map->l_addr, map->l_name);
   map = map->l_next;
  }

  pFunc = (functionPtr) dlsym(handle, "factorial");
  if ((error = dlerror()) != NULL)  {
     fputs(error, stderr);
     exit(1);
  }

  fprintf(stdout,"%d! = %d\n", inputValue, (*pFunc)(inputValue));

  dlclose(handle);

  return 0;
}
