#!/bin/bash

script_path=$(cd `dirname "$0"` && pwd)
create_xml="$1"

function runtest() {
    test_path=$1
    cd "$script_path/$test_path"
    if [ "$create_xml" == "-xml" ] ;
    then
        "./${test_path}test" -xunitxml -o unittest-report.xml
        /Users/Shared/Applications/gcovr --root=. --exclude=moc_* --xml >test-coverage.xml
    else
        "./${test_path}test"
    fi
}

runtest "framework"
runtest "parse"
