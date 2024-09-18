Using bf interpreter
* Compile bf.cpp using c++ compiler 
* First argument will be used as bf program to interpret
* Test files found in benches/ folder

Flags (anywhere in args)
* "-p" : [profiler flag] Outputs bf instructions & loop counts, loop strings limited in size, add "-v" flag to remove this limit, ie *./a.out file.bf -p -v*
* "-v" : [verbose flag] Loop string output of "-p" flag limited by default due to some loop strings being extremely long, use this flag to output full loop strings
* "-d" : [debugging flag] Will output every bf file token as it's interpreted 

Makefile
* Due to evolving complexity of project the makefile is now nothing of interests, just used for personal debugging

Refrence to spec
* https://github.com/sunjay/brainfuck/blob/master/brainfuck.md
