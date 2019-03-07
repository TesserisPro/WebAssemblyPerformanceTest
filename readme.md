# WebAssembly vs Native C++
This is very simple applciation to test performance of WebAssembly comparing to native C++. You can find extremely simple C++ program in this repository. 

To run it as usual C++ just use VS 2017 project and solution.

To build WebAssembly you can use [Emscripten](https://emscripten.org/docs/getting_started/downloads.html) 

You can use following command to build *.wasm file

```
emcc TimeTest.cpp -o TimeTest.html -s WASM=1 -s SINGLE_FILE=1 -s ALLOW_MEMORY_GROWTH=1 -O3
```

This command also generates *.html file that starts everything and doo measurment.

Our results for ```main``` function execution was:

Native: 19733 ms
WebAssembly (optimized): 29911 ms
WebAssembly:	34162 ms