import tkinter as tk
import numpy
import math
import calculatorFunctions as cFunctions

class initCalInterface():
    #creates a top level entity following configures below
    def __init__(self,k):
        print(k)
        self.window2=tk.Toplevel(k)
        self.visor=tk.Label(self.window2,text="",bg="light cyan",
                       fg="black", font=("Arial",15))
        self.t=cFunctions.wEV()
        self.botoes=[]
    def start(self):
        #dicionarios
        textButtonsT01 = {
            "00":"sin",     "10":"arcsin",      "20":"sinh",
            "01":"cos",     "11":"arccos",      "21":"cosh",
            "02":"tan",     "12":"arctan",      "22":"tanh",
            "03":"log10",     "13":"x!",          "23":"x^2",
            "04":"ln",      "14":"e^x",         "24":"x^k",

            "30":"arcsinh",     "40":"(",       "50":"7",
            "31":"arccosh",     "41":")",       "51":"8",
            "32":"arctanh",     "42":"",       "52":"9",
            "33":"sqrt",        "43":"pi",      "53":"DEL",
            "34":"(y)root of x",  "44":"e",       "54":"AC",

            "60":"4",       "70":"1",       "80":"0",
            "61":"5",       "71":"2",       "81":".",
            "62":"6",       "72":"3",       "82":"10^x",
            "63":"*",       "73":"+",       "83":"Ans",
            "64":"/",       "74":"-",       "84":"=",
        }

        functionButtonsT01 = {
            "00":lambda:self.t.toEquation(self.visor,"sin"),
            "01":lambda:self.t.toEquation(self.visor,"cos"),
            "02":lambda:self.t.toEquation(self.visor,"tan"),
            "03":lambda:self.t.toEquation(self.visor,"log"),
            "04":lambda:self.t.toEquation(self.visor,"ln"),

            "10":lambda:self.t.toEquation(self.visor,"arcsin"),
            "11":lambda:self.t.toEquation(self.visor,"arccos"),
            "12":lambda:self.t.toEquation(self.visor,"arctan"),
            "13":lambda:self.t.toEquation(self.visor,"x!"),
            "14":lambda:self.t.toEquation(self.visor,"e**x"),

            "20":lambda:self.t.toEquation(self.visor,"sinh"),
            "21":lambda:self.t.toEquation(self.visor,"cosh"),
            "22":lambda:self.t.toEquation(self.visor,"tanh"),
            "23":lambda:self.t.toEquation(self.visor,"x**2"),
            "24":lambda:self.t.toEquation(self.visor,"x**k"),

            "30":lambda:self.t.toEquation(self.visor,"arcsinh"),
            "31":lambda:self.t.toEquation(self.visor,"arccosh"),
            "32":lambda:self.t.toEquation(self.visor,"arctanh"),
            "33":lambda:self.t.toEquation(self.visor,"sqrt"),
            "34":lambda:self.t.toEquation(self.visor,"(y)root of x"),

            "40":lambda:self.t.toEquation(self.visor,"( "),
            "41":lambda:self.t.toEquation(self.visor," )"),
            "42":"",
            "43":lambda:self.t.toEquation(self.visor,"pi"),
            "44":lambda:self.t.toEquation(self.visor,"e"),

            "50":lambda:self.t.toEquation(self.visor,"7"),
            "51":lambda:self.t.toEquation(self.visor,"8"),
            "52":lambda:self.t.toEquation(self.visor,"9"),
            "53":lambda:self.t.btDel(self.visor),
            "54":lambda:self.t.btAc(self.visor),

            "60":lambda:self.t.toEquation(self.visor,"4"),
            "61":lambda:self.t.toEquation(self.visor,"5"),
            "62":lambda:self.t.toEquation(self.visor,"6"),
            "63":lambda:self.t.toEquation(self.visor," * "),
            "64":lambda:self.t.toEquation(self.visor," / "),

            "70":lambda:self.t.toEquation(self.visor,"1"),
            "71":lambda:self.t.toEquation(self.visor,"2"),
            "72":lambda:self.t.toEquation(self.visor,"3"),
            "73":lambda:self.t.toEquation(self.visor," + "),
            "74":lambda:self.t.toEquation(self.visor," - "),

            "80":lambda:self.t.toEquation(self.visor,"0"),
            "81":lambda:self.t.toEquation(self.visor,"."),
            "82":lambda:self.t.toEquation(self.visor,"10**x"),
            "83":lambda:self.t.toEquation(self.visor,"Ans"),
            "84":lambda:self.t.btResult(self.visor),
        }
        #inicializacao
        self.window2.geometry("360x480")
        self.window2.minsize(360,480)
        #grid
        for i in range (10):
            if(i==0):
                k=1
            else:
                k=4
            tk.Grid.rowconfigure(self.window2, i, weight=1)
        for i in range (5):
            tk.Grid.columnconfigure(self.window2, i, weight=1)
        #visor
        self.visor.grid(row=0,columnspan=5,sticky=tk.N+tk.S+tk.E+tk.W)
        #cria botoes
        for i in range (9):
            self.botoes.append([])
            for j in range (5):
                self.botoes[i].append(tk.Button(self.window2,
                                                text=textButtonsT01[str(i)+str(j)],
                                                font=("Arial",10)))
                self.botoes[i][j].grid(row=(i+1),column=(j),
                                       sticky=tk.N+tk.S+tk.E+tk.W)
        #atribui funcoes
        for i in range (9):
            for j in range (5):
                self.botoes[i][j].configure(command=functionButtonsT01[str(i)+str(j)])
