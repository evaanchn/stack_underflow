include ../../common/Makefile

FLAG +=-Iinclude
FLAG += $(shell fltk-config --cxxflags)

LIBS +=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lfltk_images -lpng
LIBS += $(shell fltk-config --ldflags)

# default test
DEFAULT_ARGS = tests/simul_systems.csv print
.PHONY: simulation
# prioritize command line ARGS
simulation:
	@$(MAKE) run ARGS='$(if $(ARGS),$(ARGS),$(DEFAULT_ARGS))'
