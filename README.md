# Basic VCF file parser
This is my semester project for the course NPRG041, Programming in C++.

## Structure
All files necessary should be contained in this repository. It also includes a
small example of a VCF file following the VCF4.3 specifications, as well as a
test output file. 

## Running
This project can be run from the `main` method in the `main.cpp` file. Please 
replace the file paths for `test.vcf` and `test_out.vcf` with the respective 
paths on your system before running. Should the input file be malformed, 
the program will fail.

## What is provided
Primarily this provides the functionality for reading and writing VCF files. 
Additionally, the `main` method prints some additional information
about the input file in the following format:
```commandline
The file D:\UNI\C++\Project\test.vcf contains 3 samples,
7 variants,
and 4 variant lines from chromosome 20,
representing 5 variants.
```