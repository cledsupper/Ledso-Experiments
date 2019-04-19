CC=clang
LINKER=-lncurses
DEPEND_GLIB_INC=`pkg-config glib-2.0 --cflags`
DEPEND_GLIB_LIB=`pkg-config glib-2.0 --libs`

all:
	# Compilando
	$(CC) -c PlaySong.c $(DEPEND_GLIB_INC)
	$(CC) -o PlaySong PlaySong.o $(LINKER) $(DEPEND_GLIB_LIB)
	# Executando
	./PlaySong

depends-install-ubuntu:
	# Procure (search) pelos pacotes clang, mpg321, pkg-config libglib*-dev e libncurses*-dev (este provavelmente já instalado) e os instale em seu Ubuntu

depends-install-android:
	apt install clang pkg-config glib-dev ncurses-dev sox

help:
	# No Ubuntu, execute:
	# $ make depends-install-ubuntu
	# Siga os passos indicados e depois:
	# $ make
	# Exemplo para Android (Termux):
	# $ make depends-install-android
	# $ make

