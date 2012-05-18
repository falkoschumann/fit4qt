TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
    libs \
    plugins \
    tests \
    app \

OTHER_FILES += \
    LICENSE.txt \
    runtests.sh \
    runexamples.sh
