# APRIL-ANN module example

Code base example for modules implemented out of
[APRIL-ANN](https://github.com/pakozm/april-ann) repository. This code base
contains:

- `example.cc` is the C++ source code of the module.
- `makefile` contains the compilation line.
- `test.lua` is a Lua code example which loads and uses the module.

You can compile and execute this code this way:

```
$ make
g++ -O3 -fPIC -shared -o example.so example.cc -I/usr/include/lua5.2 -I/usr/include/april-ann -lapril-ann -llua5.2 
$ lua test.lua
APRIL-ANN v0.4.0  Copyright (C) 2012-2015 DSIC-UPV, CEU-UCH
Compiled at Sat Jul 18 17:41:10 2015, timestamp 1437234070
This program comes with ABSOLUTELY NO WARRANTY; for details see LICENSE.txt.
This is free software, and you are welcome to redistribute it
under certain conditions; see LICENSE.txt for details.
 4000          4000          4000          4000         ...  4000
 4000          4000          4000          4000         ...  4000
 4000          4000          4000          4000         ...  4000
 4000          4000          4000          4000         ...  4000
 4000          4000          4000          4000         ...  4000
...
 4000          4000          4000          4000         ...  4000
# Matrix of size [10,10] stride [10,1] ref [0x26e7290 data= 0x26e7360]
```

Building new modules out of APRIL-ANN repository
------------------------------------------------

Currently this option has been tested for Linux systems, despite it can be done
in MacOS X. So, for Linux systems, you need to install APRIL-ANN using the
following commands (after you have downloaded or cloned the main repository):

```
$ ./DEPENDENCIES-INSTALLER.sh
$ make
$ sudo make install
```

After that, you need to link your software using `pkg-config` to configure your
compiler:

```
$ g++ -fPIC -shared -o YOUR_MODULE_NAME.so *.o $(pkg-config --cflags --libs april-ann)
```

Don't forget to require APRIL-ANN in your C++ code using the following
instruction:

```C
luaL_requiref(L, "aprilann", luaopen_aprilann, 1);
```

Once you have done this steps, you can load your module into APRIL-ANN using Lua
interpreter:

```
$ lua
Lua 5.2.2  Copyright (C) 1994-2013 Lua.org, PUC-Rio
> require "aprilann"
APRIL-ANN v0.4.0  Copyright (C) 2012-2015 DSIC-UPV, CEU-UCH
Compiled at Sat Jul 18 13:45:52 2015, timestamp 1437219952
This program comes with ABSOLUTELY NO WARRANTY; for details see LICENSE.txt.
This is free software, and you are welcome to redistribute it
under certain conditions; see LICENSE.txt for details.
> your_module = require "YOUR_MODULE_NAME"
```

The next C++ code is an example of file which can be loaded as external module
for APRIL-ANN:

```C++
// includes all APRIL-ANN dependencies and declares luaopen_aprilann header
#include "april-ann.h"
using AprilMath::MatrixExt::Initializers::matFill;
using AprilUtils::LuaTable;
using AprilUtils::SharedPtr;
using Basics::MatrixFloat;
// exported function example
int get(lua_State *L) {
  SharedPtr<MatrixFloat> m = new MatrixFloat(2, 10, 20);
  matFill(m.get(), 20.0f);
  // using LuaTable you can push APRIL-ANN objects in Lua stack (be careful,
  // not all objects can be pushed)
  LuaTable::pushInto(L, m.get());
  return 1;
}
// declaration of module opening function
extern "C" {
  int luaopen_example(lua_State *L) {
    static const luaL_Reg funcs[] = {
      {"get", get},
      {NULL, NULL}
    };
    luaL_requiref(L, "aprilann", luaopen_aprilann, 1);
    lua_pop(L, 1);
    luaL_newlib(L, funcs);
    return 1;
  }
}
```
