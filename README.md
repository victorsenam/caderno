[![Build Status](https://travis-ci.org/victorsenam/caderno.svg?branch=master)](https://travis-ci.org/victorsenam/caderno)

[Latest Version](https://victorsenam.github.io/caderno/notebook.pdf)

# Initializing
The tests are made using [googletest](https://github.com/google/googletest/). It may be necessary to run
`git submodule update --init --recursive` once after you clone the repository for the first time, if the
folder `test/gtest/` is empty.

# Adding code
Add the code on the `code` folder.

# Adding tests
Add the test on the `test` folder, the file name should be `dir/file.testname.cpp` if you want to test `dir/file.cpp`.
Follow this format closely.

# Testing
Run `make` on the `test` folder (or on the main folder) to test all files. Individual executables are created with the same name as the test files.

# Generate Notebook
The code for latex generation is based on [this repository](https://github.com/jasison27/ACM-ICPC-CodeTemplate-Latex).  
Run `make` on the `latex` folder (or on the main folder) to generate `latex/notebook.pdf`.
