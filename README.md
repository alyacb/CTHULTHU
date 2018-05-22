# CTHULTHU
A C++ library for computing the eigenvalues of a matrix using the Hessenberg QR-Algorithm.

## Why?
Why create another library for this when there are already excellent ones out there, not to mention tools like Matlab? Because...
- I like linear algebra.
- I like C++.
- I was once naive enough to think eigenvalue generation was trivial. I was sorely mistaken.

## Compiling & Running:
Go to the src directory, and run either
```
make
```
or
```
make debug
```
- default: compiles all the classes
- debug: compiles classes with debugging output enabled

The code can be executed by running the generated executable, 'CTHULTHU'.
```
./CTHULTHU
```
At the moment, the program functionality is limited to running the unit-tests I have set-up using the 't' command. More to come...

## Fun facts:
- The name was chosen because implementing this felt at times like fighting a giant dragon-octopus-anthropoid hybrid, i.e. CTHULHU. The name was mispelled because I felt like a T was missing. :)
