# Template resources
### This folder contains some useful resources common to every task:
- classes to handle **input/output** in a simple, fast and flexible way. By default they use input.txt and output.txt, but by defining ``USE_STDIN`` or ``USE_STDOUT`` this can be changed;
- **abbreviations** for most used type names (e.g. ``std::string`` -> ``str``). All mathematical types are as large as possible by default (for example, signed integer type defaults to ``long long``);
- ``INLINE`` macro, that can be used instead of ``inline`` to **force the compiler to inline** a function;
- ``<bits/stdc++.h>`` is #include'd, to make **compilation faster** and remove the problem of remembering the name of a library;
- ``main()`` with ``return 0``;
- ``README.md`` with default **olympiad links** and score placeholder;
- A vscode configuration file "tasks.json" for tasks such as **build, run** and clean. Many compiler warnings are enabled;
- Everything needed to debug: vscode configuration file "launch.json", ``-g`` compiler option, disabled optimizations (but only when debugging);
<!--# [ ()](https://training.olinfo.it/#/task//statement)
<!--Score: /100