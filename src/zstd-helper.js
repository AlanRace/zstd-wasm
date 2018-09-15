function zstdCompressFloat32(data, level) {
    if(!(data instanceof Float32Array))
        data = new Float32Array(data);

    return zstdCompress(data, level);
}

function zstdCompressFloat64(data, level) {
    if(!(data instanceof Float64Array)) {
        data = new Float64Array(data);
    }

    return zstdCompress(data, level);
}

function zstdCompress(data, level) {
    let num_bytes = data.length * data.BYTES_PER_ELEMENT;
    let dataPtr = Module._malloc(num_bytes);
    let dataHeap = new Uint8Array(Module.HEAPU8.buffer, dataPtr, num_bytes);
    dataHeap.set(new Uint8Array(data.buffer));

    let num_bytes_compressed = Module.ZSTD_compressBound(num_bytes);
    let compressedPtr = Module._malloc(num_bytes_compressed);
    let compressedHeap = new Uint8Array(Module.HEAPU8.buffer, compressedPtr, num_bytes_compressed);

    let ret = Module.ZSTD_compress(compressedHeap.byteOffset, num_bytes_compressed, dataHeap.byteOffset, num_bytes, level);

    // Put result in new array so that we can free the memory
    let compressedData = new Uint8Array(compressedHeap.subarray(0, ret));

    // Free memory
    Module._free(dataHeap.byteOffset);
    Module._free(compressedHeap.byteOffset);

    return compressedData;
}

function zstdDecompressFloat64(data) {
    let floatData = zstdDecompress(data);

    return new Float64Array(floatData.buffer, floatData.byteOffset);
}

function zstdDecompress(data) {
    if(!(data instanceof Uint8Array)) {
        data = new Uint8Array(data);
    }

    let dataPtr = Module._malloc(data.length);
    let dataHeap = new Uint8Array(Module.HEAPU8.buffer, dataPtr, data.length);
    dataHeap.set(data);
    
    let num_bytes_decompressed = Module.ZSTD_getFrameContentSize(dataHeap.byteOffset, data.length); 
    let decompressedPtr = Module._malloc(num_bytes_decompressed);
    let decompressedHeap = new Uint8Array(Module.HEAPU8.buffer, decompressedPtr, num_bytes_decompressed);

    let ret = Module.ZSTD_decompress(decompressedHeap.byteOffset, num_bytes_decompressed, dataHeap.byteOffset, data.length);

    // Put result in new array so that we can free the memory
    let decompressedData = new Uint8Array(decompressedHeap.subarray(0, ret));

    // Free memory
    Module._free(dataHeap.byteOffset);
    Module._free(decompressedHeap.byteOffset);

    return decompressedData;
}