CC=clang
RUNOW=./

all: shm-create shm-write
	$(RUNOW)shm_create &
	sleep 1
	$(RUNOW)shm_write
	# shm_create:

shm-create:
	$(CC) shm_create.c -lrt -o shm_create

shm-write:
	$(CC) shm_write.c -lrt -o shm_write
