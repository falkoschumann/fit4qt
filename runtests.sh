#!/bin/bash

tests/framework/tst_frameworktest -xunitxml -o TEST-framework.xml
tests/parse/tst_parsetest -xunitxml -o TEST-parse.xml
tests/filerunner/tst_filerunnertest -xunitxml -o TEST-filerunner.xml

exit 0
