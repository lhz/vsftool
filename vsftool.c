#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define sysfail(str) { perror(str); exit(EXIT_FAILURE); }


char *snapshot_data = NULL;
long  snapshot_size;
char *snapshot_mem;


bool check_snapshot(char *filename) {
  if (strstr(snapshot_data, "VICE Snapshot File") != snapshot_data) {
    fprintf(stderr, "%s: Not a VICE snapshot file.\n", filename);
    return false;
  }
  /* if (strstr(snapshot_data, "C64MEM") == NULL) { */
  /*   fprintf(stderr, "%s: No C64MEM block found.\n", filename); */
  /*   return false; */
  /* } */
  return true;
}


bool read_snapshot(char* filename) {
  FILE *f;
  bool success = false;
  if (f = fopen(filename, "rb")) {
    fseek(f, 0, SEEK_END);
    snapshot_size = ftell(f);
    rewind(f);
    if (snapshot_data = malloc(snapshot_size + 1)) {
      size_t bytes_read = fread(snapshot_data, 1, snapshot_size, f);
      if (bytes_read == snapshot_size)
	success = check_snapshot(filename);
      else
	perror(filename);
    }
    else {
      fputs("Failed to allocate memory for snapshot buffer.\n", stderr);
    }
    fclose(f);
  }
  else {
    perror(filename);
  }
  return success;
}


void write_snapshot(char* filename) {
  FILE *f;
  if (f = fopen(filename, "wb")) {
    fwrite(snapshot_data, 1, snapshot_size, f);
    fclose(f);
  }
  else {
  }
}


void inject_file_into_snapshot(char* filename) {
}


int main(int argc, char* argv[]) {
  if (argc < 4) {
    printf("Usage: %s <source-snapshot> <target-snapshot> <files>\n", argv[0]);
    return -1;
  }

  if (read_snapshot(argv[1])) {
    for (int i = 3; i < argc; i++)
      inject_file_into_snapshot(argv[i]);
    write_snapshot(argv[2]);
  }

  if (snapshot_data)
    free(snapshot_data);
}
