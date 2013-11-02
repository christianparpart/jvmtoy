JVMtoy
------

This is a toy project to play with JVM bytecode interpretation.

### Motivation

While sticking to the topic of compiler development (via LLVM) I could fully live out 
the goal to get this VM as fast as possible for real server-oriented work loads,
especially interesting subjects are

- high concurrency
- runtime profiling data generation
- tracing JIT implementation
- drop in replacement for at least locally interesting software (especially Sqltap).

### Goals

Implement a minimal JVM, supporting:

- Interpret the - interpret the complete instruction set (as defined in the jvmspec)
- IR API
- Bytecode generation from IR
- Writing .class files
- Loading of .class files
- Loading of .jar files
- Support some core java libraries, such as System API and Threading API
- JIT compiling (target[s]: x86-64), not necessarily via LLVM, and/or maybe "tracing JIT":
  - perform SSA block coloring denoting the frequency a block has been visited:
    - and JIT them on certain thresholds,
    - and remove blocks never entered (e.g. `if (false) {}` or `if (!variableIsFalse) {}`
      In the latter case, we know where `variableIsFalse` can be modified and if we're
      sure, that this one is not to change in the future, then these code blocks can also be omitted.
- Ideally Sqltap should be able to at least run on it.
- The ExecutionEngine must not recurse into callees but push calle frames onto the frame stack
  - returning from a callee just pops the head from the frame stack and continues at the program[pc] from the caller's frame.
- Every thead is run by own private ExecutionEngine.
- ...

#### Possible Milestone Schedule

This may be some loosely defined priority list on what would have to be implemented after the other.

1. class-file loading and primitive bytecode interpretation
2. functional type system (including type checking)
3. exception handling
4. functional `System.out.println()`
5. basic JNI, maybe let libjvmrt use this to expose system implementations, too
6. `java.lang.reflect.*`
7. `java.lang.Thread` and related
8. basic JIT compiling via LLVM (-Xllvm to enable it)
9. basic JIT compiling for x86-64 by hand
