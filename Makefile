CC = gcc

CFLAGS = -std=c99 -Isrc/lib -Isrc/modules -Isrc/utils -D_GNU_SOURCE

TARGET = aula_studio

TEST_TARGET = tests/test

OBJ = obj/main.o \
      obj/hash_table.o \
      obj/list.o \
      obj/queue.o \
      obj/list_item.o \
      obj/studente.o \
      obj/prenotazione.o \
      obj/data_ora.o \
      obj/giorno_settimana.o \
      obj/load.o \
      obj/menu.o \
      obj/report.o

all: obj $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

obj/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o obj/main.o

obj/hash_table.o: src/lib/hash_table.c src/lib/hash_table.h
	$(CC) $(CFLAGS) -c src/lib/hash_table.c -o obj/hash_table.o

obj/list.o: src/lib/list.c src/lib/list.h src/lib/list_item.h
	$(CC) $(CFLAGS) -c src/lib/list.c -o obj/list.o

obj/queue.o: src/lib/queue.c src/lib/queue.h src/lib/queue_item.h
	$(CC) $(CFLAGS) -c src/lib/queue.c -o obj/queue.o

obj/list_item.o: src/lib/list_item.c src/lib/list_item.h
	$(CC) $(CFLAGS) -c src/lib/list_item.c -o obj/list_item.o

obj/studente.o: src/modules/studente.c src/modules/studente.h
	$(CC) $(CFLAGS) -c src/modules/studente.c -o obj/studente.o

obj/prenotazione.o: src/modules/prenotazione.c src/modules/prenotazione.h
	$(CC) $(CFLAGS) -c src/modules/prenotazione.c -o obj/prenotazione.o

obj/data_ora.o: src/modules/data_ora.c src/modules/data_ora.h
	$(CC) $(CFLAGS) -c src/modules/data_ora.c -o obj/data_ora.o

obj/giorno_settimana.o: src/modules/giorno_settimana.c src/modules/giorno_settimana.h
	$(CC) $(CFLAGS) -c src/modules/giorno_settimana.c -o obj/giorno_settimana.o

obj/load.o: src/utils/load.c src/utils/load.h
	$(CC) $(CFLAGS) -c src/utils/load.c -o obj/load.o

obj/menu.o: src/utils/menu.c src/utils/menu.h
	$(CC) $(CFLAGS) -c src/utils/menu.c -o obj/menu.o

obj/report.o: src/utils/report.c src/utils/report.h
	$(CC) $(CFLAGS) -c src/utils/report.c -o obj/report.o


OBJ_NO_MAIN = $(filter-out obj/main.o, $(OBJ))

test: obj $(TEST_TARGET)

$(TEST_TARGET): tests/run_test.c $(OBJ_NO_MAIN)
	$(CC) $(CFLAGS) tests/run_test.c $(OBJ_NO_MAIN) -o $(TEST_TARGET)

obj:
	mkdir -p obj

clean:
	rm -f obj/*.o $(TARGET) $(TEST_TARGET)

.PHONY: all test clean obj