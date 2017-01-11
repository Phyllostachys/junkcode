```makefile
$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $(INCLUDES) -c $< $(LIB_INC) $(LIBS)
```

Where ```SOURCES``` is a list of source files and ```OBJECTS``` is a list of object files:  
- ```$<``` - is the first (or next) file from ```SOURCES```  
- ```$@``` - is the first (or next) file from ```OBJECTS```  
- ```$^``` - is the entire list of dependences if listed individually (```SOURCES```)

Also, from the Make manual:  
> - ```AR``` - Archive-maintaining program; default ‘ar’.
> - ```AS``` - Program for compiling assembly files; default ‘as’.
> - ```CC``` - Program for compiling C programs; default ‘cc’.
> - ```CXX``` - Program for compiling C++ programs; default ‘g++’.
> - ```CPP``` - Program for running the C preprocessor, with results to standard output; default ‘$(CC) -E’.
> - ```RM``` - Command to remove a file; default ‘rm -f’.  
> Here is a table of variables whose values are additional arguments for the programs above. The default values for all of these is the empty string, unless otherwise noted.
> - ```ARFLAGS``` - Flags to give the archive-maintaining program; default ‘rv’.
> - ```ASFLAGS``` - Extra flags to give to the assembler (when explicitly invoked on a ‘.s’ or ‘.S’ file).
> - ```CFLAGS``` - Extra flags to give to the C compiler.
> - ```CXXFLAGS``` - Extra flags to give to the C++ compiler.
> - ```CPPFLAGS``` - Extra flags to give to the C preprocessor and programs that use it (the C and Fortran compilers).
> - ```LDFLAGS``` - Extra flags to give to compilers when they are supposed to invoke the linker, ‘ld’, such as -L. Libraries (-lfoo) should be added to the LDLIBS variable instead.
> - ```LDLIBS``` - Library flags or names given to compilers when they are supposed to invoke the linker, ‘ld’. LOADLIBES is a deprecated (but still supported) alternative to LDLIBS. Non-library linker flags, such as -L, should go in the LDFLAGS variable.
