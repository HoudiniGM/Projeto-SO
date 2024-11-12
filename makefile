TARGET = mergesort

SOURCES = mergesort.c ordenacao.c

CFLAGS = -lpthread

$(TARGET): $(SOURCES)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)