# Adding code
Add the code on the `code` folder and its path inside this directory to `CODE_NAMES` in `Makefile`.

# Adding tests
Add the test on the `test` folder, its path inside this directory to `TEST_NAMES` in `Makefile` and describe a target to build its object under the `test rules` section in the `Makefile`.

# Testing
Compile and run `test/main` to run every test.
Run it with the flag `--gtest_filter='-*_STRESS.*'` to ignore stress testing.
