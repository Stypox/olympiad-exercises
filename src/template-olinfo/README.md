# Template resources
### This folder contains some useful resources common to every task:
- **input/output** file streams;
- **`using namespace std`**;
- **abbreviations** for most used type names (e.g. `std::vector` -> `vec`). All mathematical types are as large as possible by default (for example, signed integer `si` type defaults to `long long`);
- `INLINE` macro, that can be used instead of `inline` to **force the compiler to inline** a function;
- `<bits/stdc++.h>` is `#include`d, to make **compilation faster** and remove the problem of remembering the name of a library;
- empty `main()`;
- `README.md` with default **olympiad links** and score placeholder;
- A vscode configuration file "tasks.json" for tasks such as **build, run** and clean. Many compiler warnings are enabled;
- `deb()` function for debugging, that prints only when `DEBUG` is `#define`d;
- Everything needed to debug with `gdb`: vscode configuration file "launch.json", `-g` compiler option;
<!--# [ ($PROBLEM)](https://training.olinfo.it/#/task/$PROBLEM/statement)
<!--Score: /100
