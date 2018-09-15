# zstd-wasm
WebAssembly bindings for Zstandard compression library

```html
<!doctype html>
<html>

<head>
	<meta charset="UTF-8">
</head>
<script>
	var Module = {
		onRuntimeInitialized: function () {
			console.log('zstd-wasm loaded.')
		}
	};
</script>
<script src="zstd.js"></script>
<script src="zstd-helper.js"></script>

<body>
	<button onclick="console.log(zstdDecompressFloat64(zstdCompressFloat64([123.456, 987.765, 398.3409], 10)));">Click me</button>
</body>

</html>
```
