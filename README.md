# Optimized Collatz Function

This is a set of collatz function implementations, including a counter to keep track of how many iterations it takes to get to 1.

One is a standard, naive implementation with an if/else statement to check parity, and the standard optimization of diving by two immediately after the 3x+1 operation.

The other two make use of a count-trailing-zeroes (ctz) bitwise operation. This is the same as asking "how many times can I divide this number by 2 before I get an odd number?", and takes only a single clock cycle to execute on most modern hardware.

We can then add this to the iteration count, and perform a bitshift by that number, equivalent to actually dividing it by 2 until an odd number is reached. The resulting odd number can then go through the 3x+1 step. This removes a fairly unpredictable branch and tons of extra instructions.

Finally, we can perform a simple check to determine if we should exit the loop (if 1 has been reached). The two optimized implementations differ by how they choose to exit this loop. The one that exits after the bitshift seems to be slightly faster than the one that exits after the 3x+1 step, however the two produce almost identical CPU instructions, so the difference may just be a matter of how the OOO hardware in the CPU decides to schedule it.


Compilation:
```
clang -O3 collatz.c
```
(GCC would work too, though clang seems to produce slightly faster code)

Running this on an AMD R5 2500U (with the ```-march=znver1``` flag added for native optimizations), I got the following results:


Clang:
```
Naive: 16.479097 seconds
Optimized: 9.230728 seconds
Alt-optimized: 9.648446 seconds
```

GCC:
```
Naive: 29.300638 seconds
Optimized: 9.549285 seconds
Alt-optimized: 9.616181 seconds
```

