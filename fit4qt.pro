TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
    libs \
    plugins \
    tests \
    app \

OTHER_FILES += \
    LICENSE.txt \
    README.txt \
    runtests.sh \
    runexamples.sh
