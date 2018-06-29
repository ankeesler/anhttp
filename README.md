anhttp = Andrew's HTTP library
         ^^       ^^^^

This is an academic HTTP library.

Build setup:
1. Go into a separate directory
2. Run `cmake path/to/anhttp/root`
3. Run `make anhttp` (the libanhttp.a artifact will pop out in source/)

Directory structure:
- include/ contains the public library API
- source/ contains the library source code
- test/ contains the tests

Coding standard:
- All symbols are camelCase
- Public symbols are capitalized
- Types end in \_t
