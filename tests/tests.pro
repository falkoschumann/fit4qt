TEMPLATE = subdirs

SUBDIRS += \
    framework \
    parse \
    filerunner

CONFIG += ordered

OTHER_FILES = runtests.sh
