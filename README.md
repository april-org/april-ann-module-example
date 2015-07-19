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
