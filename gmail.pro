TEMPLATE = app
QT = gui core
CONFIG += qt warn_on console release
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
SOURCES = src/main.cpp src/gmail.cpp src/gmailImpl.cpp
HEADERS += src/gmail.h src/gmailImpl.h
FORMS += ui/gmail.ui
