#
# Simple Makefile that compiles all .c and .s files in the same folder
#

# If you move this project you can change the directory 
# to match your GBDK root directory (ex: GBDK_HOME = "C:/GBDK/"
GBDK_HOME = C:/gbdk/

LCC = $(GBDK_HOME)bin/lcc 
PNG2ASSET = $(GBDK_HOME)bin/png2asset 

# You can uncomment the line below to turn on debug output
# LCC = $(LCC) -debug

# You can set the name of the .gb ROM file here
PROJECTNAME    = TilmapCollision

GENDIR = gen
RESDIR = res
SRCDIR = src
DSTDIR = dist

BINS	    = $(PROJECTNAME).gb
BINS2	    = $(PROJECTNAME)_SinglePoint.gb
CSOURCES   := $(wildcard $(GENDIR)/*.c) src/common.c

all: clean prepare	png2asset $(BINS) $(BINS2)

prepare:
	mkdir -p $(GENDIR)
	mkdir -p $(DSTDIR)

png2asset:
	$(PNG2ASSET) $(RESDIR)/Tilemap.png -c $(GENDIR)/tilemap.c -map -source_tileset $(RESDIR)/Tileset.png -noflip -keep_palette_order
	$(PNG2ASSET) $(RESDIR)/Tileset.png -c $(GENDIR)/tileset.c -tiles_only -map -noflip -keep_palette_order
	$(PNG2ASSET) $(RESDIR)/Ball.png -c $(GENDIR)/ball.c -noflip -spr8x16 -keep_palette_order

compile.bat: Makefile
	@echo "REM Automatically generated from Makefile" > compile.bat
	@make -sn | sed y/\\//\\\\/ | grep -v make >> compile.bat

# Compile and link all source files in a single call to LCC
$(BINS):	src/main.c $(CSOURCES)
	$(LCC) -I$(GENDIR) -o $(DSTDIR)/$@ src/main.c $(CSOURCES)

# Compile and link all source files in a single call to LCC
$(BINS2):	src/main_singlepoint.c $(CSOURCES)
	$(LCC) -I$(GENDIR) -o $(DSTDIR)/$@ src/main_singlepoint.c $(CSOURCES) 

clean:
	rm -f  $(DSTDIR)/*.*
	rm -f  $(GENDIR)/*.*
	rm -f *.o *.lst *.map *.gb *.ihx *.sym *.cdb *.adb *.asm

