TARGET := promicro

ifeq ($(TARGET),pi)
OPTS := -e CONVERT_TO=elite_pi
endif

compile:
	qmk compile -kb sofle -km rgb_simon $(OPTS)

flash-right:
	qmk flash -kb sofle -km rgb_simon -bl uf2-split-right $(OPTS)

flash-left:
	qmk flash -kb sofle -km rgb_simon -bl uf2-split-left $(OPTS)
