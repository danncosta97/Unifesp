import tkinter as tk
import numpy
import math
import calculatorInterface as cInterface
import interpolacao as cInterpolacao

def toplevel1():
    #toplevels
    t=cInterface.initCalInterface(janela)
    t.start()

def interpolacao():
    i=cInterpolacao.initInterpolacao(janela)
    i.start()


#inicia janela principal
janela=tk.Tk()
janela.geometry("640x360")
janela.minsize(640, 360)

#inicializacoes da janela principal
botoesMain=[]
#grid
for i in range (3):
    if(i==0):
        k=1
    else:
        k=1
    tk.Grid.rowconfigure(janela, i, weight=k)
for i in range (2):
    tk.Grid.columnconfigure(janela, i, weight=1)
#visor
visorMain=tk.Label(janela,text="textmain",bg="light cyan",
               fg="black", font=("Arial",15))
visorMain.grid(row=0,columnspan=2,sticky=tk.N+tk.S+tk.E+tk.W)
#dicionarios
textButtonMain = {
    "00":"Calculadora básica\n(radianos)",
    "01":"Interpolação",

    "10":"botao3","11":"botao4",
}
functionButtonMain = {
    "00":toplevel1,"01":interpolacao,
    "10":"","11":""
}
#cria botoes
for i in range (2):
    botoesMain.append([])
    for j in range (2):
        botoesMain[i].append(tk.Button(janela, text=textButtonMain[str(i)+str(j)],
                                   font=("Arial",15)))
        botoesMain[i][j].grid(row=(i+1),column=(j),sticky=tk.N+tk.S+tk.E+tk.W)
#atribui funcao do botao
for i in range (2):
    for j in range (2):
        botoesMain[i][j].configure(command=functionButtonMain[str(i)+str(j)])

janela.mainloop()
