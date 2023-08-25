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

BINS	    = $(PROJECTNAME).gb
BINS2	    = $(PROJECTNAME)_SinglePoint.gb
CSOURCES   := tilemap.c tileset.c ball.c

all:	png2asset $(BINS) $(BINS2)

png2asset:
	$(PNG2ASSET) tilemap.png -map -source_tileset tileset.png -noflip -keep_palette_order
	$(PNG2ASSET) tileset.png -tiles_only -map -noflip -keep_palette_order
	$(PNG2ASSET) ball.png -noflip -spr8x16 -keep_palette_order

compile.bat: Makefile
	@echo "REM Automatically generated from Makefile" > compile.bat
	@make -sn | sed y/\\//\\\\/ | grep -v make >> compile.bat

# Compile and link all source files in a single call to LCC
$(BINS):	main.c $(CSOURCES)
	$(LCC) -o $@ main.c $(CSOURCES)

# Compile and link all source files in a single call to LCC
$(BINS2):	main_singlepoint.c $(CSOURCES)
	$(LCC) -o $@ main_singlepoint.c $(CSOURCES)

clean:
	rm -f *.o *.lst *.map *.gb *.ihx *.sym *.cdb *.adb *.asm

