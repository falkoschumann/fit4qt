Fit for Qt
==========

This is an implementation of the Fit framework for Nokia Qt (formerly Trolltech Qt). For more
information aabout Fit see http://fit.c2.com.


Running Unit Tests
==================

Add the folling environment variable

  DYLD_LIBRARY_PATH=../../libs/fit

This value is O.k. if you run tests with the following commands. The better way is to set the
absolute path to the project sub directory libs/fit.

The unit tests make use of QTestLib and configured as test cases. So the tests can run with

  make check

The output will be written to console. If you need XML files e. g. for a continious integration
build. The shell srcipt runtests.sh create XML results with Cobertura format.


Running Unit Tests with Code Coverage
=====================================

Add the following environment variables

  DYLD_LIBRARY_PATH=../../libs/fit
  GCOV_PREFIXx=../../libs/fit

Run tests with

  make check
