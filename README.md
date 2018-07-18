```
anhttp = Andrew's HTTP library
         ^^       ^^^^
```

This is an academic HTTP library.

CMake build setup:
1. Go into a separate directory
1. Run `cmake path/to/anhttp/root`
1. Run `make anhttp` (the libanhttp.a artifact will pop out in source/)

Bazel build setup:
1. Run bazel build //source:anhttp
1. Uh...

Directory structure:
- include/ contains the public library API
- source/ contains the library source code
- test/ contains the tests
- examples/ contains example applications
- scripts/ contains helper scripts
- third\_party contains the build instructions for third\_party code

Coding standard:
- All symbols are camelCase
- Public symbols are capitalized
- Types end in \_t
- Wrap long function calls by passing one argument per line
