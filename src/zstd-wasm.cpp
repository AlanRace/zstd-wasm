#include <stdlib.h>    // malloc, free, exit
#include <stdio.h>     // fprintf, perror, fopen, etc.
#include <string.h>    // strlen, strcat, memset, strerror
#include <errno.h>     // errno
#include <sys/stat.h>  // stat
#include <zstd.h>      // presumes zstd library is installed

#include <emscripten.h>
#include <emscripten/bind.h>

using namespace emscripten;

//https://github.com/kripken/emscripten/issues/6747
size_t _ZSTD_compress(unsigned int output_ptr, int num_bytes, unsigned int input_ptr, int num_bytes_in, int level) {

	return ZSTD_compress((uint8_t *) output_ptr, num_bytes, (uint8_t *) input_ptr, num_bytes_in, level);
}

size_t _ZSTD_decompress(unsigned int output_ptr, int num_bytes, unsigned int input_ptr, int num_bytes_in) {

	return ZSTD_decompress((uint8_t *) output_ptr, num_bytes, (uint8_t *) input_ptr, num_bytes_in);
}

EMSCRIPTEN_BINDINGS(zsd) {
	function("ZSTD_compress", &_ZSTD_compress);
	function("ZSTD_decompress", &_ZSTD_decompress);
  function("ZSTD_maxCLevel", &ZSTD_maxCLevel);
	function("ZSTD_versionNumber", &ZSTD_versionNumber);
}


int main() {
  double data[] = {100.123423, 999.2348238904};
  double compressed[4];
  double decompressed[2];
  int len = 2;
  int level = 3;

  printf("hello, world!\n");

  size_t rc = ZSTD_compress(&compressed, 32, &data, 16, level);

  if(ZSTD_isError(rc)) {
	printf("Error: %s\n", ZSTD_getErrorName(rc));

	return 0;
  }

  rc = ZSTD_decompress(&decompressed, 16, &compressed, rc);

  if(ZSTD_isError(rc)) {
        printf("Error: %s\n", ZSTD_getErrorName(rc));

        return 0;
  }

  printf("%f -> %f -> %f\n", data[0], compressed[0], decompressed[0]);

  return 0;
}
