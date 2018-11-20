# calculator

An application made with C to input a valid mathematical operation and then show the answer.
Done to fulfill IF2220 Formal Language Theory and Automata's Big Mission (or whatever Tugas Besar is called).

**Context-Free Grammar:**
```bash
S -> E 
E -> T | T+E| T-E 
T -> F | F*T | F/T 
F -> I | +I | -I | F^F 
I -> N | (E) 

N -> R | Ri | i 
R -> D | D.D 
D -> AD | A 
A -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
```
**Hints**: _S(tart), E(xpression), T(erm), F(actor), I(tem), N(umber), R(eal), D(igits), A(\_digit)_

## Current To-Do's:

Edit this README.md if you have already fulfilled the task.
* Quality assurance by testing.

## Installation and Running
* Make sure that GNU C is already installed on your computer.
* To compile the source, execute:
``` bash
calculator> gcc calculator.c -o Calculator
```
* To run the program, execute:
``` bash
calculator> "Calculator"
```
