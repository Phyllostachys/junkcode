```makefile
all: library.cpp main.cpp
```

In this case:
- ```$@``` evaluates to all
- ```$<``` evaluates to library.cpp
- ```$^``` evaluates to library.cpp main.cpp

Also, from the [Make manual](https://www.gnu.org/software/make/manual/html_node/Implicit-Variables.html):  
> - ```AR``` - Archive-maintaining program; default ‘ar’.
> - ```AS``` - Program for compiling assembly files; default ‘as’.
> - ```CC``` - Program for compiling C programs; default ‘cc’.
> - ```CXX``` - Program for compiling C++ programs; default ‘g++’.
> - ```CPP``` - Program for running the C preprocessor, with results to standard output; default ‘$(CC) -E’.
> - ```RM``` - Command to remove a file; default ‘rm -f’.  
> Here is a table of variables whose values are additional arguments for the programs above. The default values for all of these is the empty string, unless otherwise noted.
> - ```ARFLAGS``` - Flags to give the archive-maintaining program; default ‘rv’.
> - ```ASFLAGS``` - Extra flags to give to the assembler (when explicitly invoked on a ‘.s’ or ‘.S’ file).
> - ```CPPFLAGS``` - Extra flags to give to the C preprocessor and programs that use it (the C and Fortran compilers).
> - ```CFLAGS``` - Extra flags to give to the C compiler.
> - ```CXXFLAGS``` - Extra flags to give to the C++ compiler.
> - ```LDFLAGS``` - Extra flags to give to compilers when they are supposed to invoke the linker, ‘ld’, such as -L. Libraries (-lfoo) should be added to the LDLIBS variable instead.
> - ```LDLIBS``` - Library flags or names given to compilers when they are supposed to invoke the linker, ‘ld’. LOADLIBES is a deprecated (but still supported) alternative to LDLIBS. Non-library linker flags, such as -L, should go in the LDFLAGS variable.

To print out variables set in a makefile, use one of these rules:  
```print-% : ; @echo $* = $($*)```  
```print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true```  
