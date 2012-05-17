TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
    libs \
    plugins \
    app \
    tests

OTHER_FILES += \
    runtests.sh \
    runexamples.sh
