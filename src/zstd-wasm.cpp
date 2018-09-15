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

long _ZSTD_getFrameContentSize(unsigned int src, size_t srcSize) {
	//TODO: THis function actually reutnrs long long
	return ZSTD_getFrameContentSize((uint8_t *) src, srcSize);
}



//TODO: const char* ZSTD_getErrorName(size_t code);     /*!< provides readable string from an error code */


EMSCRIPTEN_BINDINGS(zsd) {
	function("ZSTD_compress", &_ZSTD_compress);
	function("ZSTD_decompress", &_ZSTD_decompress);
	function("ZSTD_getFrameContentSize", _ZSTD_getFrameContentSize);

	// Helper functions
	function("ZSTD_compressBound", &ZSTD_compressBound);
	function("ZSTD_isError", &ZSTD_isError);
    function("ZSTD_maxCLevel", &ZSTD_maxCLevel);
	function("ZSTD_versionNumber", &ZSTD_versionNumber);
}

