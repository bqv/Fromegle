TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS = qjson src

src.depends = qjson
