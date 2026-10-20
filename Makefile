# Nome do executável final
TARGET = xePS2.elf

# Configurações do Compilador para PowerPC (Xbox 360)
CC = powerpc-eabi-gcc
CXX = powerpc-eabi-g++
OBJCOPY = powerpc-eabi-objcopy

# Caminhos da Libxenon (Ajuste conforme seu ambiente no Termux/Linux)
DEVKITPPC ?= /opt/devkitpro/devkitPPC
LIBXENON ?= /usr/local/xenon

CFLAGS = -O2 -g -mcpu=xenon -mtune=xenon -m32 -fno-pic -mpowerpc64 -I$(LIBXENON)/usr/include -I./include
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
LDFLAGS = -T $(LIBXENON)/app.lds -L$(LIBXENON)/usr/lib -lxenon -m32 -nostdlib

# Arquivos fonte
SOURCES = src/main.cpp src/cpu/ee.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@
	@echo "Pronto! Copie o arquivo $(TARGET) como 'xenon.elf' para a raiz do seu pendrive FAT32."

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f source/*.o $(TARGET)

$(TARGET)

src/cpu/ee.cpp

