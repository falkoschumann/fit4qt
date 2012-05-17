TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
    libs \
    plugins \
    app \
    tests

OTHER_FILES += \
    LICENSE.txt \
    runtests.sh \
    runexamples.sh
