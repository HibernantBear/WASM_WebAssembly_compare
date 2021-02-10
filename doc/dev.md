# WASM/WebAssembly

## Prepare

In this section, the following step will guide you install every thing you need for WASM/WebAssembly compile and runing.

Since it's more convenient to develop WASM under Linux, The following instruction are all for linux.

### System Require

1. `sudo apt install python2.7 git cmake build-essential gcc`
2. make sure python2.7 is default in your teminal

### Install emsdk

1. `git clone https://github.com/juj/emsdk.git`
2. `cd emsdk`
3. `./emsdk install latest`
4. `./emsdk activate latest`
5. config environment following the information print from last step, 
e.g. `echo 'source "$HOME/emsdk/emsdk_env.sh"' >> $HOME/.bash_profile`

### Test WASM Compile Tools
1. create test C file<br/>
    example C code:
    ```C
    #include <stdio.h>

    int main(void)
    {
      printf("Hello World!\n");
      return 0;
    }
    ```
2. build src using `emcc`
    ```bash
    emcc src/test.c -s WASM=1 -o output/test.html
    ```
3. run dev server with `emrun` tool
    ```bash
    emrun --no_browser --port 8080 test.html
    ```
4. open url [localhost:8080/test.html](localhost:8080/test.html) in browser

## Compile

### Options

it is important to know the compile options of `emcc`, here list the most useful part I met during test

1. `-s WASM=`: control the build edition, for browser support WASM we should give `1`, for old browser only support asm.js give `0`
2. `-O`: optimize, `0`no optimize, `1`minimal optimize, `2`well-optimize, `3`better than`2`and may cause size bigger, `s`better than`2`and similar with`3`but focuse on size reduce
3. `-o`: output, this give the output path and filename, also ext control the output files. `.wasm`only generate wasm files, `.js`build the js files that can be import directly, `.html`generate html test with wasm and js files

for browser use the command should be `emcc src/$1.c -Os -s WASM=1 -o output/$1/$1.$2` or `emcc src/$1.c -O3 -s WASM=1 -o output/$1/$1.$2`, $1is the filename and $2 is the ext

### Optimize

optimize is so important 'cause demo c file with single line `printf("Hello World!\n")` result in a 12KB wasm file, after `-O2` optimized reduced to 3KB.

also, optimize work for JS modules too.

### Build js or not

building js file is aimed at covering the gape between WASM and JS coding concepts. 
if you know nothing about WASM or C/C++, it is suggested that build the WASM with JS module to make your coding experience more seamless.
but if you chase a better performance of you project, you can do all function calls directly from the WASM module.

**Notice** always remember the functions in JS module are only available when you build with `-s EXPORTED_FUNCTIONS='["_main","_func1"]'` option, the value of this option is the export function names which prefix with `_` before the origin names

## Performance

### Test

in this experiment, I choose the lorenz attractor as the computation core. 
also involve with memeory allocate and free

### Data
- step: 2^24
    | Type | Time(ms) | Memeory(MB) |
    |:----:|:--------:|:-----------:|
    |Local |746       |NA           |
    |WASM-O0|719-1725  |2.64        |
    |WASM-O3|820-1200  |1.68        |
    |JS-Array|2400-3200|600+        |
    |JS-ArrayBuffer|180|2.56        |
- step: 2^24*1000
    | Type | Time(ms) | Memeory(MB) |
    |:----:|:--------:|:-----------:|
    |WASM-O3|116292   |NA           |
    |JS-ArrayBuffer|110202|NA       |

### Conclusion
Local > JS-ArrayBuffer(Optimized) > WASM-O3/WASM-Os > WASM-O0 > JS-Array(Normal Code)
