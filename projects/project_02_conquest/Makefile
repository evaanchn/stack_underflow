include ../../common/Makefile

FLAG +=-Iinclude
FLAG += $(shell fltk-config --cxxflags)

LIBS +=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lfltk_images -lpng
LIBS += $(shell fltk-config --ldflags)

ARGS = tests/andromeda_systems.csv 10
