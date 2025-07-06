ifdef CLANG
CC = clang++
else
CC = g++
endif

CPPFLAGS = -std=c++17 -Werror -O3
SRC = src
LIB = lib

all: compress

compress: 
	$(CC) $(CPPFLAGS) $(SRC)/$(LIB)/bitmap.cpp $(SRC)/$(LIB)/gradpixel.cpp $(SRC)/main.cpp -o compress

clean:
	rm compress