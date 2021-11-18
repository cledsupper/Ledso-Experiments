/** gatos.c - uma árvore de felídeos! */
#include <stdio.h>

#include "arvore.h"

/** A funcão gera_gatos() tem como base a família felídeos, conforme:
 * -> https://pt.wikipedia.org/wiki/Fel%C3%ADdeos
 * Último acesso em: 18 de nov. 2021.
 */
le_arvore_t * gera_gatos();

/** Similar a gets(), mas com limite de escrita */
void getsn(char * str, int s);

int main() {
  #define plen 25
  char palavras[3][plen] = {"", "", ""};
  le_arvore_t * ani;
  le_arvore_t * arv = gera_gatos();

  puts("Insira os termos para acesso em minúsculas sem acentos (cada um por linha):");
  getsn(palavras[0], plen);
  getsn(palavras[1], plen);
  getsn(palavras[2], plen);

  ani = le_arvore_acessa(
    arv,
    palavras[0],
    palavras[1],
    palavras[2],
    NULL
  );
  if (ani) {
    int n;
    puts("\nAnimais encontrados:");
    for (n=0; n < ani->len; n++)
      le_arvore_mostra_tudo(&(ani->nos[n]), 1);
    if (! ani->len)
      puts("Nenhum!");
  }
  else
    puts("\nClasses não encontradas na árvore!");

  le_arvore_cerra(arv);
  return 0;
}

void getsn(char * str, int s) {
  int c, n;
  for (n=0; n < s-1; ++n) {
    c = getchar();
    if (c == '\n' || c == EOF)
      break;
    *(str++) = c;
  }
  *str = 0;
}

le_arvore_t * gera_gatos() {
  le_arvore_t * arv = le_arvore("felideos");

  le_arvore_nos(arv, "pantherinae", "panthera", "leo", NULL);
  le_arvore_nos(arv, "pantherinae", "panthera", "tigris", NULL);
  le_arvore_nos(arv, "pantherinae", "panthera", "pardus", NULL);
  le_arvore_nos(arv, "pantherinae", "panthera", "onca", NULL);
  le_arvore_nos(arv, "pantherinae", "panthera", "uncia", NULL);
  le_arvore_nos(arv, "pantherinae", "neofelis", "nebulosa", NULL);
  le_arvore_nos(arv, "pantherinae", "neofelis", "diardi", NULL);
  le_arvore_nos(arv, "felineos", "catopuma", "temminckii", NULL);
  le_arvore_nos(arv, "felineos", "catopuma", "badia", NULL);
  le_arvore_nos(arv, "felineos", "pardofelis", "marmorata", NULL);
  le_arvore_nos(arv, "felineos", "caracal", "caracal", NULL);
  le_arvore_nos(arv, "felineos", "caracal", "aurata", NULL);
  le_arvore_nos(arv, "felineos", "leptailurus", "serval", NULL);
  le_arvore_nos(arv, "felineos", "leopardus", "pardalis", NULL);
  le_arvore_nos(arv, "felineos", "leopardus", "wiedii", NULL);
  le_arvore_nos(arv, "felineos", "leopardus", "colocolo", NULL);
  le_arvore_nos(arv, "felineos", "leopardus", "jacobita", NULL);
  le_arvore_nos(arv, "felineos", "leopardus", "tigrinus", NULL);
  le_arvore_nos(arv, "felineos", "leopardus", "geoffroyi", NULL);
  le_arvore_nos(arv, "felineos", "leopardus", "guigna", NULL);
  le_arvore_nos(arv, "felineos", "leopardus", "guttulus", NULL);
  le_arvore_nos(arv, "felineos", "lynx", "lynx", NULL);
  le_arvore_nos(arv, "felineos", "lynx", "pardinus", NULL);
  le_arvore_nos(arv, "felineos", "lynx", "canadensis", NULL);
  le_arvore_nos(arv, "felineos", "lynx", "rufus", NULL);
  le_arvore_nos(arv, "felineos", "acinonyx", "jubatus", NULL);
  le_arvore_nos(arv, "felineos", "puma", "concolor", NULL);
  le_arvore_nos(arv, "felineos", "puma", "yagouaroundi", NULL);
  le_arvore_nos(arv, "felineos", "prionailurus", "bengalensis", NULL);
  le_arvore_nos(arv, "felineos", "prionailurus", "viverrinus", NULL);
  le_arvore_nos(arv, "felineos", "prionailurus", "planiceps", NULL);
  le_arvore_nos(arv, "felineos", "prionailurus", "rubiginosus", NULL);
  le_arvore_nos(arv, "felineos", "prionailurus", "iriomotensis", NULL);
  le_arvore_nos(arv, "felineos", "felis", "silvestris", "cattus", NULL);
  le_arvore_nos(arv, "felineos", "felis", "margarita", NULL);
  le_arvore_nos(arv, "felineos", "felis", "chaus", NULL);
  le_arvore_nos(arv, "felineos", "felis", "nigripes", NULL);
  le_arvore_nos(arv, "felineos", "felis", "bieti", NULL);
  le_arvore_nos(arv, "felineos", "felis", "manul", NULL);
  le_arvore_nos(arv, "machairodontinae", "smilodon", "gracilis", NULL);
  le_arvore_nos(arv, "machairodontinae", "smilodon", "populator", NULL);
  le_arvore_nos(arv, "machairodontinae", "smilodon", "fatalis", NULL);
  le_arvore_nos(arv, "machairodontinae", "dinofelis", "abeli", NULL);
  le_arvore_nos(arv, "machairodontinae", "dinofelis", "barlowi", NULL);
  le_arvore_nos(arv, "machairodontinae", "dinofelis", "paleoonca", NULL);
  le_arvore_nos(arv, "machairodontinae", "dinofelis", "diastemata", NULL);
  le_arvore_nos(arv, "machairodontinae", "dinofelis", "piveteaui", NULL);
  le_arvore_nos(arv, "machairodontinae", "dinofelis", "thereailurus", NULL);
  le_arvore_nos(arv, "machairodontinae", "paramachairodus", "ogygia", NULL);
  le_arvore_nos(arv, "machairodontinae", "paramachairodus", "orientalis", NULL);
  le_arvore_nos(arv, "machairodontinae", "homotherium", "latidens", NULL);
  le_arvore_nos(arv, "machairodontinae", "homotherium", "ethiopicom", NULL);
  le_arvore_nos(arv, "machairodontinae", "homotherium", "serum", NULL);
  le_arvore_nos(arv, "machairodontinae", "homotherium", "venezuelensis", NULL);
  le_arvore_nos(arv, "machairodontinae", "xenosmilus", "hodsonae", NULL);
  le_arvore_nos(arv, "machairodontinae", "megantereon", "ekidoit", NULL);
  le_arvore_nos(arv, "machairodontinae", "megantereon", "cultridens", NULL);
  le_arvore_nos(arv, "machairodontinae", "megantereon", "hesperus", NULL);
  le_arvore_nos(arv, "machairodontinae", "megantereon", "inexpectatus", NULL);
  le_arvore_nos(arv, "machairodontinae", "megantereon", "microta", NULL);
  le_arvore_nos(arv, "machairodontinae", "megantereon", "whitei", NULL);
  le_arvore_nos(arv, "machairodontinae", "megantereon", "vakhshensis", NULL);
  le_arvore_nos(arv, "machairodontinae", "megantereon", "falconeri", NULL);

  return arv;
}
