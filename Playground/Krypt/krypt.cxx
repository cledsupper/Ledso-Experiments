/* Um algoritmo humilde de criptografia.
 * Autor: Cledson Ferreira. */


#include <iostream>
#include <fstream>
using namespace std;
#include <cerrno>
#include <cstdio>
#include <cstring>

const char *LINE_24WBAR = "------------------------";

int prekey(char *key) {
	int len = 0;
	while (*key) {
		(*key) -= ' ';
		/*if ((*key) >= '0' && (*key) <= '9')
			(*key) -= '0'+27;
		else if ((*key) >= 'A' && (*key) <= 'Z')
			(*key) -= 'A';
		else if ((*key) >= 'a' && (*key) <= 'z')
			(*key) -= 'a';*/
		key++;
		len++;
	}
	return len;
}

void krypt(char *text, unsigned int text_size, char key[17], bool dec) {
	int key_len = prekey(key);
	int i, k,
	     sign = dec ? -1 : 1;
	for (i=0, k=0;
	       i  < text_size-1;
	       i++, k = (k+1)%key_len) {
	
		char c = text[i], r;
		/*if (c >= '0' && c <= '9') {
			c -= '0';
			if (sign < 0) {
				for (r=key[k]; r > 0; r--) {
					if (!c) c = 9;
					else c--;
				}
			} else
				c = (c + key[k])%10;
			c += '0';
		} else if (c >= 'A' && c <= 'Z') {
			c -= 'A';
			if (sign < 0) {
				for (r=key[k]; r > 0; r--) {
					if (!c) c = 25;
					else c--;
				}
			} else
				c = (c + key[k])%26;
			c += 'A';
		} else if (c >= 'a' && c <= 'z') {
			c -= 'a';
			if (sign < 0) {
				for (r=key[k]; r > 0; r--) {
					if (!c) c = 25;
					else c--;
				}
			} else
				c = (c + key[k])%26;
			c += 'a';
		}*/
		if (c >= ' ' && c <= '~') {
			c -= ' ';
			c = (c + key[k]*sign + 
			     (sign == -1 ? 95 : 0))%95;
			c += ' ';
		}
		text[i] = c;
	}
}

void fresh_stdin() {
	int c;
	while ((c = getchar()) != '\n')
		if (c == EOF)
			break;
}

int main(int argc, char *argv[]) {
	fstream ftext;
	unsigned int text_size;
	char *text, key[17];
	char file_path[256];
	bool decrypt;

	if (argc == 3) {
		if (!strcmp(argv[1], "decrypt"))
			decrypt = true;
		else if (!strcmp(argv[1], "encrypt"))
			decrypt = false;
		else {
			cerr << "Argumentos {(" << argv[1] << "), (" << argv[2] << ")} não identificados. Use:\n";
			cerr << "\t " << argv[0] << " [[encrypt | decrypt] [endereço do arquivo de texto]]\n";
			return 1;
		}
		strncpy(file_path, argv[2], sizeof(file_path)-1);
	} else if (argc == 1) {
		cout << "Insira o endereço do arquivo abaixo:\n";
		cin.getline(file_path, sizeof(file_path));
		cout << "Cryptografar [e] ou descriptografar [d]?\n";
		decrypt = getchar() == 'd' ? true : false;
		fresh_stdin();
	} else {
		cerr << "Sintaxe inválida. A forma correta é:\n";
		cerr << "\t " << argv[0] << " [[encrypt | decrypt] [endereço do arquivo de texto]]\n";
		return 1;
	}

	ftext.open(file_path, fstream::in);
	if (ftext.is_open() == false) {
		cerr << "Erro (\"" << strerror(errno) << "\") ao abrir o arquivo [ " << file_path << " ]\n";
		return errno;
	}
	ftext.seekg(0, ftext.end);
	text_size = ((int)ftext.tellg()) + 1;
	ftext.seekg(0, ftext.beg);
	text = new char[text_size];
	ftext.read(text, text_size-1);
	ftext.close();

	cout << "CHAVE:\n";
	scanf("%16[0-9 A-Z a-z]", key);
	fresh_stdin();

	krypt(text, text_size, key, decrypt);
	cout << LINE_24WBAR << '\n' << text << '\n' << LINE_24WBAR << '\n';

	cout << "Adicionar em [ " << file_path << " ]? [s/n]\n";
	if (getchar() == 's') {
		ftext.open(file_path, fstream::app);
		if (ftext.is_open() == false) {
			cerr << "Erro (\"" << strerror(errno) << " ao reabrir arquivo para escrita" << '\n';
			delete[] text;
			return errno;
		}
		ftext << '\n' << LINE_24WBAR << '\n' << text << '\n';
		ftext.close();
	}
	delete[] text;
	return 0;
}
