We want to prioritize simplicity/understanding over performance, compile-time<2s, and executable size.
Using header files like `#include "lib.h"` complicates our program more than including the c files directly `#include "lib.c"`.
First reason headers complicate the project more, is that each file included needs a corresponding header file, meaning >7 more files in our project.
Second reason is that using header files requires a linking step, for linking object files to the executable. Removing internal header files completely removes this step.

In search of issues including c files instead of header files, I found [these](https://stackoverflow.com/questions/52792348/why-not-explicitly-include-c-files) stack overflow answers.
They list downsides of including c files instead of header files, and we have answered each one:

Problem 1:
Including `.c` means you cannot split the compilation up.
Splitting it up helps compilation time.

Answer 1:
We prioritize simplicity over compilation time.
Therefore, is this not an issue.

Problem 2:
You cannot make variable names local to a file.
To avoid duplicate symbols. In the dependency tree below, "A" is defined twice, causing an error.
```
 A     A
 |     |
a.c   a.c
 |     |
b.c   c.c
   \  /
  main.c
```

Answer 2:
We do not care about global variable/function names.
If two variables/functions are named the same and so collide, then the name wasn't explicit enough, and the two usages should be differentiated.

There is also a workaround available, but we won't need it.
This is an example of the workaround applied to the above dependency graph.
```c
#define A A1
#include "c.c"
#undef A

#define A A2
#include "b.c"
#undef A
```