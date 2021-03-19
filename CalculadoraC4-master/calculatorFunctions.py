import tkinter as tk
import numpy
import math

#writen equation visor
class wEV():

    def __init__(self):
        #visor text takes whats going to be show on display
        self.visortext=""
        #toNumpy takes the string to  evaluate to numpy
        self.toNumpy=""
        #numberbuffer takes the number being typed for ln, exp...
        self.numberbuffer=""
        #locknumber locks numbers (after results)
        self.locknumber=0
        #lockparentesis lock the right parentesis (avoid systax error)
        self.lockparentesis=1
        #locks operators, double ones
        self.lockop=0
        #variable to check syntax errors
        self.eqError=0
        #correct visortext and numpy parentesis for functions, ln, exp...
        self.parentesisCorrector=0
        #left parentesis
        self.pQtde=0
        #right parentesis
        self.pQtdd=0
        #stores last result found
        self.Ans=""

    #check if have had any SyntaxError equation evaluated to numpy
    #to decide the visortext
    def checkEqError(self):
        if(self.eqError==1):
            self.visortext=self.visortextbuffer
            self.eqError=0

    #looks if number has point, to convert it to float or let insert it by user
    def searchPoint(self):
        print("kle")
        t=0
        for i in range (len(self.numberbuffer)):
            if(self.numberbuffer[i]=="."):
                t=1
                print("has")

        for i in range (len(self.toNumpy)-1,-1,-1):
            if(self.toNumpy[i]==" " and (self.toNumpy[i-1]=="+" or
               self.toNumpy[i-1]=="-" or self.toNumpy[i-1]=="*" or
               self.toNumpy[i-1]=="/")):
                break
            elif(self.toNumpy[i]=="."):
                print("okl")
                t=1

        return t

    #verifica a quantidade de parenteses inseridos para clear do buffer
    def checkBufferClear(self):
        if(self.pQtde>0 and self.pQtdd>0):
            return 1
        else:
            return 0

    #function correction of parentesis in x roots
    def cParentesis(self):
        if(self.parentesisCorrector==1):
            self.visortext+=")"
            self.toNumpy+=")"
            self.parentesisCorrector=0

    #add .0, if needed, to keep numbers in float and refact string to label
    #numpy and number buffer and stores the right syntax for each one
    def refactStr(self,k):
        #parentesis correction for x roots
        if(k=="(y)root of x"):
            self.parentesisCorrector=1

        #do not allow double operators
        if(k==" + " or k==" - " or k==" * " or k==" / "):
            self.lockop=1
        else:
            print("KLAY")
            self.lockop=0

        #need to be here to update dictonary
        if(k=="Ans"):
            pass
        elif(k!="0" and k!="1" and k!="2" and k!="3" and k!="4" and k!="5"
           and k!="6" and k!="7" and k!="8" and k!="." and k!="9" and k!="( "
           and k!="pi" and k!="e" and self.searchPoint()==0):
            if(self.toNumpy=="" or self.toNumpy[len(self.toNumpy)-1]==")"):
                pass
            else:
                print(self.searchPoint()==0)
                self.numberbuffer=self.numberbuffer+".0"
                self.visortext=self.visortext+".0"
                self.toNumpy=self.toNumpy+".0"
        print("k:{}".format(k))

        if(self.checkBufferClear()==1):
            print("\n--------------------\nENTREI\n----------------------\n")
            n=0
            t=0
            v=0
            n=len(self.numberbuffer)
            t=len(self.toNumpy)
            v=len(self.visortext)
            #parentesis posistions
            fpn=0
            lpn=0
            fpv=0
            lpv=0
            for i in range (t-1):
                if(self.toNumpy[i]=="(" and self.toNumpy[i+1]==" "):
                    fpn=i
                if(self.toNumpy[i]==" " and self.toNumpy[i+1]==")"):
                    lpn=i
                    print("before: {} {}".format(fpn,lpn))
                    break
            self.numberbuffer=str(eval(self.toNumpy[fpn+1:lpn+1]))
            self.toNumpy=self.toNumpy[:fpn]
            for i in range (v-1):
                if(self.visortext[i]=="(" and self.visortext[i+1]==" "):
                    fpv=i
                if(self.visortext[i]==" " and self.visortext[i+1]==")"):
                    lpv=i
                    break
            self.visortext=self.visortext[:fpv]

            self.toNumpy+=self.numberbuffer
            self.visortext+=self.numberbuffer
            self.pQtdd-=1
            self.pQtde-=1
            print("visorasd: {}".format(self.visortext))
            print("numpyasd: {}".format(self.toNumpy))
            print("numberbufferasd: {}".format(self.numberbuffer))


        numpyfydict={
            "sin":(self.toNumpy[:len(self.toNumpy)-len(self.numberbuffer)]+
                    "numpy.sin("+self.numberbuffer+")"),
            "cos":(self.toNumpy[:len(self.toNumpy)-len(self.numberbuffer)]+
                    "numpy.cos("+self.numberbuffer+")"),
            "tan":(self.toNumpy[:len(self.toNumpy)-len(self.numberbuffer)]+
                    "numpy.tan("+self.numberbuffer+")"),
            "log":(self.toNumpy[:len(self.toNumpy)-len(self.numberbuffer)]+
                    "numpy.log10("+self.numberbuffer+")"),
            "ln":(self.toNumpy[:len(self.toNumpy)-len(self.numberbuffer)]+
                    "numpy.log("+self.numberbuffer+")"),

            "arcsin":(self.toNumpy[:len(self.toNumpy)-len(self.numberbuffer)]+
                    "numpy.arcsin("+self.numberbuffer+")"),
            "arccos":(self.toNumpy[:len(self.toNumpy)-len(self.numberbuffer)]+
                    "numpy.arccos("+self.numberbuffer+")"),
            "arctan":(self.toNumpy[:len(self.toNumpy)-len(self.numberbuffer)]+
                    "numpy.arctan("+self.numberbuffer+")"),
            "x!":(self.toNumpy[:len(self.toNumpy)-len(self.numberbuffer)]+
                    "math.factorial("+self.numberbuffer+")"),
            "e**x":(self.toNumpy[:len(self.toNumpy)-len(self.numberbuffer)]+
                    "numpy.exp("+self.numberbuffer+")"),

            "sinh":(self.toNumpy[:len(self.toNumpy)-len(self.numberbuffer)]+
                    "numpy.sinh("+self.numberbuffer+")"),
            "cosh":(self.toNumpy[:len(self.toNumpy)-len(self.numberbuffer)]+
                    "numpy.cosh("+self.numberbuffer+")"),
            "tanh":(self.toNumpy[:len(self.toNumpy)-len(self.numberbuffer)]+
                    "numpy.tanh("+self.numberbuffer+")"),
            "x**2":(self.toNumpy[:len(self.toNumpy)-len(self.numberbuffer)]+
                    "math.pow("+self.numberbuffer+",2.0)"),
            "x**k":(self.toNumpy[:len(self.toNumpy)-len(self.numberbuffer)]+
                    self.numberbuffer+"**"),

            "arcsinh":(self.toNumpy[:len(self.toNumpy)-len(self.numberbuffer)]+
                    "numpy.arcsinh("+self.numberbuffer+")"),
            "arccosh":(self.toNumpy[:len(self.toNumpy)-len(self.numberbuffer)]+
                    "numpy.arccosh("+self.numberbuffer+")"),
            "arctanh":(self.toNumpy[:len(self.toNumpy)-len(self.numberbuffer)]+
                    "numpy.arctanh("+self.numberbuffer+")"),
            "sqrt":(self.toNumpy[:len(self.toNumpy)-len(self.numberbuffer)]+
                    "numpy.sqrt("+self.numberbuffer+")"),
            "(y)root of x":(self.toNumpy[:len(self.toNumpy)-len(self.numberbuffer)]+
                    self.numberbuffer+"**(1/"),

            "( ":self.toNumpy+"( ",
            " )":self.toNumpy+" )",
            "pi":self.toNumpy+("numpy.pi"),
            "e":self.toNumpy+("numpy.exp(1)"),

            "7":self.toNumpy+"7",
            "8":self.toNumpy+"8",
            "9":self.toNumpy+"9",
            "DEL":(self.toNumpy[:len(self.toNumpy)-1]),
            "AC":"",

            "4":self.toNumpy+"4",
            "5":self.toNumpy+"5",
            "6":self.toNumpy+"6",
            " * ":self.toNumpy+" * ",
            " / ":self.toNumpy+" / ",

            "1":self.toNumpy+"1",
            "2":self.toNumpy+"2",
            "3":self.toNumpy+"3",
            " + ":self.toNumpy+" + ",
            " - ":self.toNumpy+" - ",

            "0":self.toNumpy+"0",
            ".":self.toNumpy+".",
            "10**x":self.toNumpy[:len(self.toNumpy)-len(self.numberbuffer)]
                +"10**"+self.numberbuffer,
            "Ans":self.toNumpy+self.Ans
        }

        labelfy={
            "sin":(self.visortext[:len(self.visortext)-len(self.numberbuffer)]+
                    "sin("+self.numberbuffer+")"),
            "cos":(self.visortext[:len(self.visortext)-len(self.numberbuffer)]+
                    "cos("+self.numberbuffer+")"),
            "tan":(self.visortext[:len(self.visortext)-len(self.numberbuffer)]+
                    "tan("+self.numberbuffer+")"),
            "log":(self.visortext[:len(self.visortext)-len(self.numberbuffer)]+
                    "log10("+self.numberbuffer+")"),
            "ln":(self.visortext[:len(self.visortext)-len(self.numberbuffer)]+
                    "log("+self.numberbuffer+")"),

            "arcsin":(self.visortext[:len(self.visortext)-len(self.numberbuffer)]+
                    "arcsin("+self.numberbuffer+")"),
            "arccos":(self.visortext[:len(self.visortext)-len(self.numberbuffer)]+
                    "arccos("+self.numberbuffer+")"),
            "arctan":(self.visortext[:len(self.visortext)-len(self.numberbuffer)]+
                    "arctan("+self.numberbuffer+")"),
            "x!":(self.visortext[:len(self.visortext)-len(self.numberbuffer)]+
                    "factorial("+self.numberbuffer+")"),
            "e**x":(self.visortext[:len(self.visortext)-len(self.numberbuffer)]+
                    "e^"+self.numberbuffer),

            "sinh":(self.visortext[:len(self.visortext)-len(self.numberbuffer)]+
                    "sinh("+self.numberbuffer+")"),
            "cosh":(self.visortext[:len(self.visortext)-len(self.numberbuffer)]+
                    "cosh("+self.numberbuffer+")"),
            "tanh":(self.visortext[:len(self.visortext)-len(self.numberbuffer)]+
                    "tanh("+self.numberbuffer+")"),
            "x**2":(self.visortext[:len(self.visortext)-len(self.numberbuffer)]+
                    self.numberbuffer+"^2"),
            "x**k":(self.visortext[:len(self.visortext)-len(self.numberbuffer)]+
                    self.numberbuffer+"^"),

            "arcsinh":(self.visortext[:len(self.visortext)-len(self.numberbuffer)]+
                    "arcsinh("+self.numberbuffer+")"),
            "arccosh":(self.visortext[:len(self.visortext)-len(self.numberbuffer)]+
                    "arccosh("+self.numberbuffer+")"),
            "arctanh":(self.visortext[:len(self.visortext)-len(self.numberbuffer)]+
                    "arctanh("+self.numberbuffer+")"),
            "sqrt":(self.visortext[:len(self.visortext)-len(self.numberbuffer)]+
                    "sqrt("+self.numberbuffer+")"),
            "(y)root of x":(self.visortext[:len(self.visortext)-len(self.numberbuffer)]+
                    self.numberbuffer+"^(1/"),

            "( ":self.visortext+"( ",
            " )":self.visortext+" )",
            "pi":self.visortext+("pi"),
            "e":self.visortext+("e"),

            "7":self.visortext+"7",
            "8":self.visortext+"8",
            "9":self.visortext+"9",
            "DEL":(self.visortext[:len(self.visortext)-1]),
            "AC":"",

            "4":self.visortext+"4",
            "5":self.visortext+"5",
            "6":self.visortext+"6",
            " * ":self.visortext+" * ",
            " / ":self.visortext+" / ",

            "1":self.visortext+"1",
            "2":self.visortext+"2",
            "3":self.visortext+"3",
            " + ":self.visortext+" + ",
            " - ":self.visortext+" - ",

            "0":self.visortext+"0",
            ".":self.visortext+".",
            "10**x":self.visortext[:len(self.visortext)-len(self.numberbuffer)]
                +"10^x"+self.numberbuffer,
            "Ans":self.visortext+self.Ans
        }
        if(k=="0" or k=="1"or k=="2" or k=="3" or k=="4" or k=="5" or
           k=="6" or k=="7" or k=="8" or k=="9" or k=="( " or k==" )"):
            if(k=="( "):
                self.lockparentesis-=1
                self.pQtde+=1
            if(k==" )" and self.lockparentesis>0):
                pass
            else:
                if(k==" )"):
                    self.lockparentesis+=1
                    self.pQtdd+=1
                if(k!="( " and k!=" )"):
                    self.numberbuffer+=k
                self.visortext+=k
                self.toNumpy+=k
        elif(k=="." and self.searchPoint()==0):
            self.numberbuffer+=k
            self.visortext+=k
            self.toNumpy+=k
        else:
            print("m")
            print(self.numberbuffer)
            print(self.visortext)
            print(self.toNumpy)

            self.visortext=labelfy[k]
            self.toNumpy=numpyfydict[k]
            if(self.checkBufferClear()==2):
                self.numberbuffer+=k
            if(self.checkBufferClear()==0):
                print("c")
                self.numberbuffer=""
            if(k=="pi" or k=="e"):
                self.numberbuffer+=k
                print(self.numberbuffer)
            print(self.numberbuffer)
            print(self.visortext)
            print(self.toNumpy)

    #v means to visor label
    #entry passes the value of the pressed button
    #operators are passed between blancspaces to better manipulation
    def toEquation(self,v,entry):

        if(len(v["text"])>=32 and len(v["text"])<50):
            v.configure(font=("Arial",10))
        elif(len(v["text"])>=50):
            v.configure(font=("Arial",8))
        else:
            v.configure(font=("Arial",15))

        print("hi bb{}".format(len(v["text"])))


        if(entry!="1" and entry!="2" and entry!="3" and entry!="4" and
           entry!="5" and entry!="6" and entry!="7" and entry!="8" and
           entry!="9" and entry!="0" and entry!="( " and entry!=" )" and
           entry!="pi" and entry!="e" and self.locknumber==1):
            self.locknumber=0

        if(self.locknumber==0):
            if((entry==" + " or entry==" - " or entry==" * " or entry==" / ")
               and self.lockop==1):
                pass
            elif(entry=="Ans" and self.Ans==""):
                pass
            else:
                if(entry==" + " or entry==" - " or entry==" * " or entry==" / "):
                   self.cParentesis()
                self.refactStr(entry)
                print("visor: {}".format(self.visortext))
                print("numpy: {}".format(self.toNumpy))
                print("numberbuffer: {}".format(self.numberbuffer))
                v.configure(text=self.visortext)

    def btDel(self,v):
        #self.checkEqError()
        print(self.locknumber)
        #checks if theres values inserted
        #if number is not locked its not provided from a btResult()
        #if buffer not empty, excludes from this
        #else, if theres parentesis, excludes and fix paramenters to this
        #else, calculate the operator to exclude
        if(self.visortext==""):
            pass
        elif(self.locknumber==0):
            if(len(self.numberbuffer)>0):
                if(self.toNumpy[len(self.toNumpy)-1]==")" and
                    self.toNumpy[len(self.toNumpy)-2]==" "):
                    self.pQtdd-=1
                    self.lockparentesis-=1
                    self.toNumpy=self.toNumpy[:len(self.toNumpy)-2]
                    self.visortext=self.visortext[:len(self.visortext)-2]
                elif(self.toNumpy[len(self.toNumpy)-1]==" " and
                    self.toNumpy[len(self.toNumpy)-2]=="("):
                    self.pQtde+=1
                    self.lockparentesis-=1
                    self.toNumpy=self.toNumpy[:len(self.toNumpy)-2]
                    self.visortext=self.visortext[:len(self.visortext)-2]
                else:
                    self.toNumpy=self.toNumpy[:len(self.toNumpy)-1]
                    self.visortext=self.visortext[:len(self.visortext)-1]
                    self.numberbuffer=self.numberbuffer[:len(self.numberbuffer)-1]
            else:
                numpyNEnd=0
                visorNEnd=0
                for i in range(len(self.toNumpy)):
                    print(self.toNumpy[i])
                for i in range(0,len(self.toNumpy)-2,1):
                    print(self.toNumpy)
                    print(len(self.toNumpy))
                    print(i)
                    print(self.toNumpy[i])
                    if(self.toNumpy[i]==" " and (self.toNumpy[i+1]=="+"
                        or self.toNumpy[i+1]=="-" or self.toNumpy[i+1]=="*"
                        or self.toNumpy[i+1]=="/")):
                        numpyNEnd=i
                for i in range(0,len(self.visortext)-2,1):
                    if(self.visortext[i]==" " and (self.visortext[i+1]=="+"
                        or self.visortext[i+1]=="-" or self.visortext[i+1]=="*"
                        or self.visortext[i+1]=="/")):
                        visorNEnd=i
                if(self.toNumpy[len(self.toNumpy)-1]== " " and
                   (self.toNumpy[len(self.toNumpy)-2]=="+" or
                   self.toNumpy[len(self.toNumpy)-2]=="-" or
                   self.toNumpy[len(self.toNumpy)-2]=="/" or
                   self.toNumpy[len(self.toNumpy)-2]=="*")):
                    self.toNumpy=self.toNumpy[:(numpyNEnd)]
                    self.visortext=self.visortext[:(visorNEnd)]
                    self.lockop=0
                #case its the last number
                elif(numpyNEnd==0):
                    self.toNumpy=self.toNumpy[:0]
                    self.visortext=self.visortext[:0]
                    self.lockop=0
                else:
                    print("OI NENEM")
                    self.toNumpy=self.toNumpy[:(numpyNEnd+3)]
                    self.visortext=self.visortext[:(visorNEnd+3)]
                    self.lockop=0
            v.configure(text=self.visortext)
        print("visor: {}".format(self.visortext))
        print("numpy: {}".format(self.toNumpy))
        print("numberbuffer: {}".format(self.numberbuffer))

    def btAc(self,v):
        #clean everything
        self.pQtdd=0
        self.pQtde=0
        self.parentesisCorrector=0
        self.locknumber=0
        self.toNumpy=""
        self.visortext=""
        self.numberbuffer=""
        print("visor: {}".format(self.visortext))
        print("numpy: {}".format(self.toNumpy))
        print("numberbuffer: {}".format(self.numberbuffer))
        v.configure(text=self.visortext)


    def btResult(self,v):
        if(len(v["text"])>=32 and len(v["text"])<50):
            v.configure(font=("Arial",10))
        elif(len(v["text"])>=50):
            v.configure(font=("Arial",8))
        else:
            v.configure(font=("Arial",15))
        #shows result
        self.cParentesis()
        self.parentesisCorrector=0
        self.locknumber=1
        print("hi")
        print(self.toNumpy)
        print(self.visortext)
        print(self.numberbuffer)
        try:
            v.configure(text=str(eval(self.toNumpy)))
            self.Ans=str(eval(self.toNumpy))
            self.toNumpy=str(eval(self.toNumpy))
            self.visortext=str(eval(self.toNumpy))
            self.numberbuffer=str(eval(self.toNumpy))
        except SyntaxError as error1:
            self.eqError=1
            v.configure(text="SYNTAX ERROR")
            print("NOT A VALID EQUATION")
            self.locknumber=0
        except NameError as error2:
            v.configure(text="CMPLX NUMBER")
        print("########################################################")
