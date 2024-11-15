#!/bin/bash

cmake ./
make
GTEST_COLOR=1 ctest -V
