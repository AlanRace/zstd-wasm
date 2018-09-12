
all:
	emcc -v
	CC=emcc $(MAKE) -C zstd/lib libzstd.a MOREFLAGS="-Werror"
	emcc -O3 --bind -std=c++11 -I ./zstd/lib/ src/zstd-wasm.cpp -o bin/zstd.js zstd/lib/libzstd.a
	cp bin/* examples/

clean:
	$(MAKE) -C zstd clean
