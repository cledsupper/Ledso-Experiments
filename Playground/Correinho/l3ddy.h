#ifndef _L3DDY_KEY_H_
#define _L3DDY_KEY_H_

static inline void get_key_for_l3ddy(key_t *pl3ddy) {
  char cwd[256]="/";
  int cwd_len = 256;
  if (!getcwd(cwd, 256)) exit(1);
  else if (cwd[(cwd_len = strlen(cwd))-1] != '/') {
    cwd[cwd_len++] = '/';
    cwd[cwd_len] = '\0';
  }
  strncat(cwd, "l3ddy.h", 255-cwd_len-5);
  if ((*pl3ddy = ftok(cwd, 'L')) == -1) {
    perror("Falha ao gerar chave");
    exit(1);
  }
}

#endif
