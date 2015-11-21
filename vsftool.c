#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


char *snapshot_data = NULL;
long  snapshot_size;
char *snapshot_mem;


void *memstr(const void *haystack, size_t hlen, const void *needle)
{
  int needle_first;
  const void *p = haystack;
  size_t plen = hlen;
  size_t nlen = strlen(needle);

  if (!nlen)
    return NULL;

  needle_first = *(unsigned char *)needle;

  while (plen >= nlen && (p = memchr(p, needle_first, plen - nlen + 1))) {
    if (!memcmp(p, needle, nlen))
      return (void *)p;
    p++;
    plen = hlen - (p - haystack);
  }
  return NULL;
}


bool check_snapshot(char *filename)
{
  if (strstr(snapshot_data, "VICE Snapshot File") != snapshot_data) {
    fprintf(stderr, "%s: Not a VICE snapshot file.\n", filename);
    return false;
  }

  snapshot_mem = memstr(snapshot_data, snapshot_size, "C64MEM");
  if (!snapshot_mem) {
    fprintf(stderr, "%s: No C64MEM block found.\n", filename);
    return false;
  }
  snapshot_mem += 26;
  printf("Found C64MEM block at offset %ld.\n", (snapshot_mem - snapshot_data));

  return true;
}


bool read_snapshot(char* filename)
{
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


void write_snapshot(char* filename)
{
  FILE *f;
  if (f = fopen(filename, "wb")) {
    fwrite(snapshot_data, 1, snapshot_size, f);
    fclose(f);
  }
  else {
  }
}


void inject_file_into_snapshot(char* filename)
{
}


int main(int argc, char* argv[])
{
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
