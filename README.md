# SOFE 3950U / CSCI 3020U: Operating Systems
## TUTORIAL #5: POSIX Threads

### Objectives
- Learn the fundamentals of multithreading
- Gain experience using POSIX threads

### Important Notes
- Work in groups of four students
- All reports must be submitted as a PDF on blackboard, if source code is included submit everything as an archive (e.g. zip, tar.gz)
- Save the file as `<tutorial_number>_<first student’s id>.pdf` (e.g. tutorial5_100123456.pdf)
- If you cannot submit the document on Blackboard then please contact the TA (Omar Hemied) [Omar.hemied@ontariotechu.ca](mailto:Omar.hemied@ontariotechu.ca)

### Notice
- It is recommended for this lab activity and others that you save/bookmark the following resources as they are very useful for C programming.
  - [C++ Reference](http://en.cppreference.com/w/c)
  - [C++ Library Reference](http://www.cplusplus.com/reference/clibrary/)
  - [C Reference Card](http://users.ece.utexas.edu/~adnan/c-refcard.pdf)
  - [C Bootcamp](http://gribblelab.org/CBootcamp)
- The following resources are helpful as you will need to use pthreads in order to make your program multithreaded.
  - [Pthreads Tutorial](https://computing.llnl.gov/tutorials/pthreads/)
  - [Threads Tutorial](http://randu.org/tutorials/threads/)
  - [Pthreads Primer](http://pages.cs.wisc.edu/~travitch/pthreads_primer.html)

### Conceptual Questions
1. Read the pthread documentation and explain the following three functions: pthread_create, pthread_join, pthread_exit.
2. Explain how the memory of threads work in comparison to processes, do threads share the same memory, can threads access the memory of other threads?
3. Name the differences between multithreading and multiprocessing (multiple processes). What are the advantages and disadvantages of each?
4. Provide an explanation of mutual exclusion, what is a critical section?
5. Research the functions used to perform mutual exclusion with pthreads and explain the purpose of each function.

### Application Questions
All of your programs for this activity can be completed using the template provided, where you fill in the remaining content. A makefile is not necessary, to compile your programs use the following command in the terminal. If you do not have clang then replace clang with gcc, if you use gcc you must use -pthread instead of -lpthread. If you are still having issues please use -std=gnu99 instead of c99.
