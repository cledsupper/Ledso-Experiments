CC=clang
RUNOW=./

all: shm
	$(RUNOW)shm_create &
	usleep 500000
	$(RUNOW)shm_write
	# shm_create:

shm:
	$(CC) shm_create.c -o shm_create -lrt
	$(CC) shm_write.c -o shm_write -lrt

android: to-android
	$(RUNOW)and_create &
	usleep 500000
	$(RUNOW)and_write
	# and_create.c

to-android:
	$(CC) and_create.c -o and_create -landroid-shmem
	$(CC) and_write.c -o and_write -landroid-shmem
