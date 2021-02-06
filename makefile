
CC = 	gcc
CFLAGS = -Wall -pedantic

OBJFILES = mymat.o mat.o utils.o
TARGET = mymat

all: $(TARGET)

$(TARGET): $(OBJFILES) 

	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)


