#-*-coding:utf8;-*-
#qpy:3
#qpy:console

# DESCRIÇÃO
# O Dynamic Rend é um programa que simula uma conta de investimento (como a NuConta). Nele, você define a taxa de juros e a frequência desta (T), a meta que você quer atingir com os depósitos e rendimentos e tem uma previsão de quantos T's serão necessários para atingir essa meta.

import os
import math

COMANDO_LIMPAR = "cls" if os.name == "nt" else "clear"
TAXA_SELIC = 1.064
ANO_PARA_MES = 12
MES_PARA_DIA = 30.43
UNIDADE_PADRAO = "ano"

juros = TAXA_SELIC
unidade = UNIDADE_PADRAO

def clearscr():
  os.system(COMANDO_LIMPAR)
  print("SIMULADOR DE APLICAÇÕES")
  print("  por ledsoupper")
  print("| este simulador não define descontos de impostos nem dias não remunerados |")
  print()

def ajuda():
  global unidade
  clearscr()
  print("TECLAS DE ATALHO (HOTKEYS)")
  print("\n  a: alterar taxa de juros e unidade"\
        "\n -u: sacar último depósito"\
        "\n  z: zerar conta"\
        "\n  d: visualizar depósitos"\
        "\n  m: atualizar meta de investimento"
        "\n   : avançar %s" % (unidade))
  input()
  

def obter_juros_padrao(unidade_sel):
  global juros
  global unidade
  unidade = unidade_sel
  juros = TAXA_SELIC
  u = unidade.lower()[0]
  if u == 'a':
    pass
  elif u == 'm':
    juros = juros**(1/ANO_PARA_MES)
  elif u == 'd':
    juros = (juros**(1/ANO_PARA_MES))**(1/MES_PARA_DIA)
  else:
    unidade = "ano"

def alterar_juros():
  global juros
  global unidade
  print("Qual unidade de tempo representar: \"ano\", \"mês\" ou \"dia\"?")
  unidade = input()
  obter_juros_padrao(unidade)
  print()
  print("Insira a taxa de juros (ex: %.2f para %.2f%% a.%c):"\
    % ((juros-1)*100, (juros-1)*100, unidade[0]))
  novo_per_j = float(input())
  if novo_per_j == 0:
    print("| Valor padrão de %.2f%% selecionado. Tecle ENTER..." % ((juros-1)*100))
    input()
  else:
    juros = 1+novo_per_j/100

meta_m = 0
def alterar_meta():
  global meta_m
  clearscr()
  print(" META\n")
  print("Sobre a função meta: esta função descobre quanto tempo na unidade atual será necessário para você atingir a sua meta.")
  print("Para começar, insira o valor que você deseja alcançar no futuro. Levaremos em conta a atual taxa de juros. Se a meta for 0, não será calculada. Entre:")
  meta_m = float(input())

def render_depositos(juros, depositos = []):
  for i in range(len(depositos)):
    depositos[i] = depositos[i]*juros
  montante = 0
  for deposito in depositos:
    montante = montante + deposito
  return montante

def sacar_valor(valor, depositos = []):
  len_depositos = len(depositos)
  montante = 0
  for i in range(len_depositos):
    montante = montante + depositos[i]

  if (valor > montante):
    print("Não existem depósitos suficientes!")
    input()
    return montante

  for i in range(len_depositos-1, -1, -1):
    if valor == 0:
      break
    if depositos[i] <= valor:
      valor = valor - depositos[i]
      montante = montante - depositos[i]
      del depositos[i]
    else:
      depositos[i] = depositos[i]-valor
      montante = montante - valor
      valor = 0
  return montante

def detalhar(depositos = []):
  clearscr()
  print("DEPÓSITOS ATUAIS")
  for deposito in depositos:
    print(" $ %.2f" % (deposito))
  print("\nInsira qualquer coisa para continuar…")
  input()

clearscr()
alterar_juros()
alterar_meta()

continuando = True
t = 0

print()
print("Multiplicador: %f a cada %s" % (juros, unidade))
print("Saldo: $ 0.00")
print("Depósito inicial:")
montante = float(input())
depositos = [montante]

while continuando:
  clearscr()
  if meta_m > montante and montante > 0:
    tmeta = math.log(meta_m/montante, juros)
    print("Tempo restante para a meta $ %.2f: %.1f %c's" % (meta_m, tmeta, unidade[0]))
  elif montante >= meta_m and meta_m > 0: 
    print("META ALCANÇADA!")

  if t > 0:
    print("[DADOS APÓS %s %d]" % (unidade.upper(), t))
  print("RENDIMENTO: %.2f%% a.%c" % ((juros-1)*100, unidade[0]))
  print("SALDO: $ %.2f \n" % (montante))
  print("Movimentar:\n[+X para depositar, -X para sacar, s para sair, ? para saber mais]")
  valor = input()

  if valor == '?':
    ajuda()

  elif valor == 'a':
    alterar_juros()

  elif valor == 'm':
    alterar_meta()

  elif valor == 's':
    continuando = False

  elif valor == 'd':
    detalhar(depositos)

  elif valor == "":
    t = t+1
    montante = render_depositos(juros, depositos)


  elif valor == "-u":
    montante = sacar_valor(depositos[-1], depositos)

  elif (valor[0] >= '0' and valor[0] <= '9') or valor[0] == '-' or valor[0] == '+':
    rval = float(valor)
    if valor[0] != '-':
      depositos.append(rval)
      montante = montante + rval
    else:
      montante = sacar_valor(rval*(-1), depositos)

  elif valor[0] == 'z':
    del depositos[:]
    montante = 0
    t = 0

  else:
    print("Entrada inválida: %s" % (valor))
    input()

print("\nVocê deve ter baixado uma cópia deste programa por https://github.com/cleds.upper")
print("Caso contrário, escreva para ledsoupper@yahoo.com")
