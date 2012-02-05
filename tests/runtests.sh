#!/bin/bash

# path to gcovr or empty to run without code coverage
gcovr_bin=/Users/Shared/Applications/gcovr


### no changes need after this line

script_path=$(cd `dirname "$0"` && pwd)
create_xml="$1"

function runtest() {
    test_path=$1
    cd "$script_path/$test_path"
    if [ "$create_xml" == "-xml" ]
    then
        "./${test_path}test" -xunitxml -o unittest-report.xml
        if [ -n "$gcovr_bin" ]
        then
            "$gcovr_bin" --root="$script_path"/.. --exclude=moc_* --xml >test-coverage.xml
        fi
    else
        "./${test_path}test"
    fi
}

runtest "framework"
runtest "parse"
runtest "filerunner"
