#define _GNU_SOURCE
#include <dlfcn.h>
#include <link.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
   void *handle;
   Dl_serinfo serinfo;
   Dl_serinfo *sip;
   int j;

   if (argc != 2) {
       fprintf(stderr, "Usage: %s <libpath>\n", argv[0]);
       exit(EXIT_FAILURE);
   }

   /* Obtain a handle for shared objects specified on command line */

   handle = dlopen(argv[1], RTLD_NOW);
   if (handle == NULL) {
       fprintf(stderr, "dlopen() failed: %s\n", dlerror());
       exit(EXIT_FAILURE);
   }

   /* Discover the size of the buffer that we must pass to
      RTLD_DI_SERINFO */

   if (dlinfo(handle, RTLD_DI_SERINFOSIZE, &serinfo) == -1) {
       fprintf(stderr, "RTLD_DI_SERINFOSIZE failed: %s\n", dlerror());
       exit(EXIT_FAILURE);
   }

   /* Allocate the buffer for use with RTLD_DI_SERINFO */

   sip = malloc(serinfo.dls_size);
   if (sip == NULL) {
       perror("malloc");
       exit(EXIT_FAILURE);
   }

   /* Initialize the 'dls_size' and 'dls_cnt' fields in the newly
      allocated buffer */

   if (dlinfo(handle, RTLD_DI_SERINFOSIZE, sip) == -1) {
       fprintf(stderr, "RTLD_DI_SERINFOSIZE failed: %s\n", dlerror());
       exit(EXIT_FAILURE);
   }

   /* Fetch and print library search list */

   if (dlinfo(handle, RTLD_DI_SERINFO, sip) == -1) {
       fprintf(stderr, "RTLD_DI_SERINFO failed: %s\n", dlerror());
       exit(EXIT_FAILURE);
   }

   for (j = 0; j < serinfo.dls_cnt; j++)
       printf("dls_serpath[%d].dls_name = %s\n",
               j, sip->dls_serpath[j].dls_name);

   exit(EXIT_SUCCESS);
}
