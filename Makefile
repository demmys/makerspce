COMPILER = g++
CFLAGS = -Wextra -MMD -MP

SOURCEDIR = src
OBJDIR = obj
TARGETDIR = bin

TARGET = $(TARGETDIR)/makerspec

LIBS = /usr/local/lib/libassimp.dylib
SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS = $(subst $(SOURCEDIR),$(OBJDIR),$(SOURCES:.cpp=.o))
DEPENDS = $(OBJECTS:.o=.d)


.SUFFIXES: .cpp .o .d
.PHONY: all clean

$(TARGET): $(OBJECTS) $(LIBS)
	@[ -d $(TARGETDIR) ] || mkdir -p $(TARGETDIR)
	$(COMPILER) -o $@ $^

$(OBJDIR)/%.o: $(SOURCEDIR)/%.cpp
	@[ -d $(OBJDIR) ] || mkdir -p $(OBJDIR)
	$(COMPILER) $(CFLAGS) -o $@ -c $<

all: clean $(TARGET)

clean:
	rm -f $(OBJECTS) $(DEPENDS) $(TARGET)

-include $(DEPENDS)
