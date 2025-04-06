include ../../common/Makefile

FLAG +=-Iinclude
FLAG += $(shell fltk-config --cxxflags)

LIBS +=-lsfml-graphics -lsfml-window -lsfml-system -lfltk_images -lpng
LIBS += $(shell fltk-config --ldflags)