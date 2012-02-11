#!/bin/bash

cd dist/
./testframework -xunitxml -o TEST-framework.xml
./testparse -xunitxml -o TEST-parse.xml
./testfilerunner -xunitxml -o TEST-filerunner.xml
