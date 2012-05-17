#!/bin/bash

cd dist/
./tst_frameworktest -xunitxml -o TEST-framework.xml
./tst_parsetest -xunitxml -o TEST-parse.xml
./tst_filerunnertest -xunitxml -o TEST-filerunner.xml

exit 0
