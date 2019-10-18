# Blastn
An implementation of the basic local alignment search tool
(Blast) for nucleotides. The goal of this project is to implement the algorithm on an FPGA to hardware accelerate the process utilizing tools such as HLS (High Level Synthesis).

![Blastn Process](blastn-flowchart.png)

## Requirements
* Python
  * python 3.6+
  * pip3
  * numpy
  * tqdm
* C++
  * c++17
  * g++ 7.4+
  * GNU Make 4.2.1+
* C
  * c11
  * gcc 7.4+
  * GNU Make 4.2.1+

## Building
### Docker
Run "`docker build -t blastn .`" to create the environment with all necessary dependencies. Blastn will be placed under /root.
### C++
See the [C++ README.md](cpp/README.md).
### C
See the [C README.md](c/README.md)

## Members
Electrical and Computer Engineering Senior Project
at California State Polytechnic University, Pomona
- Alden Param
- Alex Chan
- Hmayak Apetyan
- Jacob London
- Simon Tutak
- Sivaramakrishnan Prabakar

## Advisors
- Mohamed El-Hadedy (Mohamed Aly)
- Mostafa M. Hashim Ellabaan
