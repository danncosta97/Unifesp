import numpy as np
import random as rd
import collections
import time
import sys
import gc

class page():
    def __init__(self,r_or_w,op,point_to):
        self.r_or_w=r_or_w
        self.op=op
        self.point_to=point_to

class vMemory():
    def __init__(self,size,pageSize):
        self.size=size
        self.pageSize=pageSize
        self.capacity=int(self.size/self.pageSize)
        self.pages=[]

    def generate(self):
        k=self.capacity
        qtd1=list(range(1,k+1))
        qtd2=list(range(1,k+1))
        qtd3=list(range(1,k+1))
        qtd4=list(range(1,k+1))
        rd.shuffle(qtd1)
        rd.shuffle(qtd2)
        rd.shuffle(qtd3)
        rd.shuffle(qtd4)
        qtd=[*qtd1[:int(k/4)],*qtd2[int(k/4):int(2*k/4)],
                *qtd3[int(2*k/4):int(3*k/4)],*qtd4[int(3*k/4):]]
        rd.shuffle(qtd)
        time.sleep(1)
        k=""
        for i in range(self.capacity):
            if(rd.randint(1,4)%4==0):
                k='W'
            else:
                k='R'
            self.pages.append(page(k,qtd[i],-1))

class RAM():
    def __init__(self,size,vMemory,pageSize,debug):
        self.size=size
        self.vMemory=vMemory
        self.pageSize=pageSize
        self.debug=debug
        self.capacity=int(self.size/self.pageSize)
        self.used=0
        self.frames=[]
        self.rw=[]
        self.bit=[]
        self.pointer=0
        self.pageFault=0
        self.nref=0
        self.nmod=0
        self.ref=0
        self.mod=0

    def setUpRAM(self):
        print("\nConfiguring RAM")
        for i in range(self.capacity):
            self.frames.append(-1)
            self.rw.append(-1)
            self.bit.append(-1)
        self.used=0;
        self.pointer=0;
        self.pageFault=0
        self.nref=0
        self.nmod=0
        self.ref=0
        self.mod=0

    def verifyOcurrency(self, address):
        i=0
        while(i<self.capacity):
            if(address == self.frames[i]):
                break
            else:
                i+=1
        if(i<self.capacity):
            return i
        else:
            return -1

    def verifyBit(self):
        p=1
        z=0
        t=0
        while (p==1):
            for z in range(self.pointer,len(self.bit)):
                if(self.bit[z]<=0):
                    t=0
                    break
                else:
                    self.bit[z]=0
                    t=1
            self.pointer=z
            if((self.pointer==self.capacity) and (t==1)):
                self.pointer=0
            else:
                p=0

    def method_FIFO(self):
        t1=time.time_ns()
        for i in range (len(self.vMemory.pages)):

            d=0
            if(self.debug==1):
                print("\n")
                for e in range(len((self.frames))):
                    if(self.frames[e]==self.vMemory.pages[i].op):
                        print("################################")
                        print("REQUESTED ALREADY IN RAM")
                        d=1
                print(self.vMemory.pages[i].op)
                print(self.frames)

            k=self.verifyOcurrency(self.vMemory.pages[i].op)
            l=-1
            if(k==-1):
                self.frames.pop(0)
                self.frames.append(self.vMemory.pages[i].op)
                l=self.rw.pop(0)
                if(self.vMemory.pages[i].r_or_w=='W'):
                    self.rw.append(3)
                elif(self.vMemory.pages[i].r_or_w=='R'):
                    self.rw.append(2)
                else:
                    self.rw.append(-1)  #gone wrong
                self.pageFault+=1
            else:
                l=self.rw[k]
                if(self.vMemory.pages[i].r_or_w=='W'):
                    self.rw[k]=3
                elif(self.vMemory.pages[i].r_or_w=='R'):
                    self.rw[k]=2
                else:
                    self.rw.append(-1)  #gone wrong
            if((k==-1) and (l>=0) and (l<=3)):
                if(l==0):
                    self.nref+=1
                    self.nmod+=1
                elif(l==1):
                    self.nref+=1
                    self.mod+=1
                elif(l==2):
                    self.nmod+=1
                    self.ref+=1
                elif(l==3):
                    self.mod+=1
                    self.ref+=1

            if(self.debug==1):
                print(self.frames)
                if(d==1):
                    print("################################\n")
        t2=time.time_ns()
        print("\n## FIFO ##")
        print("Page size: {}".format(self.vMemory.pageSize))
        print("Physical memory: {}".format(self.size))
        print("Physical memory page frames: {}".format(self.capacity))
        print("Virtual memory: {}".format(self.vMemory.size))
        print("Logical memory virtual pages: {}".format(self.vMemory.capacity))
        print("Page faults: {}".format(self.pageFault))
        print("Referenced (Replaced): {}".format(self.ref))
        print("Unreferenced (Replaced): {}".format(self.nref))
        print("Modified (Replaced): {}".format(self.mod))
        print("Unmodified (Replaced): {}".format(self.nmod))
        print("Time: {} seconds".format(((t2-t1)/(10**9))))
        with open("trash.txt", "a") as f:
            f.write("## FIFO ##\n")
            f.write("Page size: {}\n".format(self.vMemory.pageSize))
            f.write("Physical memory: {}\n".format(self.size))
            f.write("Physical memory page frames: {}\n".format(self.capacity))
            f.write("Virtual memory: {}\n".format(self.vMemory.size))
            f.write("Logical memory virtual pages: {}\n".format(self.vMemory.capacity))
            f.write("Page faults: {}\n".format(self.pageFault))
            f.write("Referenced (Replaced): {}\n".format(self.ref))
            f.write("Unreferenced (Replaced): {}\n".format(self.nref))
            f.write("Modified (Replaced): {}\n".format(self.mod))
            f.write("Unmodified (Replaced): {}\n".format(self.nmod))
            f.write("Time: {} seconds\n".format(((t2-t1)/(10**9))))
        f.close()


    def method_SC(self):
        t1=time.time_ns()
        for i in range (len(self.vMemory.pages)):

            d=0
            if(self.debug==1):
                print("\n")
                for e in range(len((self.frames))):
                    if(self.frames[e]==self.vMemory.pages[i].op):
                        print("################################")
                        print("REQUESTED ALREADY IN RAM")
                        d=1
                print(self.vMemory.pages[i].op)
                print(self.frames)
                print(self.bit)
                print("vvvv")
                print(self.pointer)
                print("^^^^")

            k=self.verifyOcurrency(self.vMemory.pages[i].op)
            l=-1
            if(k==-1):
                self.verifyBit()
                self.frames[self.pointer]=self.vMemory.pages[i].op
                l=self.rw[self.pointer]
                if(self.vMemory.pages[i].r_or_w=='W'):
                    self.rw[self.pointer]=3
                elif(self.vMemory.pages[i].r_or_w=='R'):
                    self.rw[self.pointer]=2
                else:
                    self.rw[self.pointer]=-1  #gone wrong
                self.pageFault+=1
                self.bit[self.pointer]=0
                self.pointer=self.pointer+1
            else:
                if(self.vMemory.pages[i].r_or_w=='W'):
                    self.rw[k]=3
                elif(self.vMemory.pages[i].r_or_w=='R'):
                    self.rw[k]=2
                else:
                    self.rw.append(-1)  #gone wrong
                self.bit[k]=1
                self.pointer=self.pointer

            if(self.pointer==self.capacity):
                self.pointer=0

            if((k==-1) and (l>=0) and (l<=3)):
                if(l==0):
                    self.nref+=1
                    self.nmod+=1
                elif(l==1):
                    self.nref+=1
                    self.mod+=1
                elif(l==2):
                    self.nmod+=1
                    self.ref+=1
                elif(l==3):
                    self.mod+=1
                    self.ref+=1

            if(self.debug==1):
                print(self.frames)
                print(self.bit)
                print("vvvv")
                print(self.pointer)
                print("^^^^")
                if(d==1):
                    print("################################\n")
        t2=time.time_ns()
        print("\n## Second Chance ##")
        print("Page size: {}".format(self.vMemory.pageSize))
        print("Physical memory: {}".format(self.size))
        print("Physical memory page frames: {}".format(self.capacity))
        print("Virtual memory: {}".format(self.vMemory.size))
        print("Logical memory virtual pages: {}".format(self.vMemory.capacity))
        print("Page faults: {}".format(self.pageFault))
        print("Referenced (Replaced): {}".format(self.ref))
        print("Unreferenced (Replaced): {}".format(self.nref))
        print("Modified (Replaced): {}".format(self.mod))
        print("Unmodified (Replaced): {}".format(self.nmod))
        print("Time: {} seconds".format(((t2-t1)/(10**9))))
        with open("sc4.txt", "a") as f:
            f.write("## Second Chance (SC) ##\n")
            f.write("Page size: {}\n".format(self.vMemory.pageSize))
            f.write("Physical memory: {}\n".format(self.size))
            f.write("Physical memory page frames: {}\n".format(self.capacity))
            f.write("Virtual memory: {}\n".format(self.vMemory.size))
            f.write("Logical memory virtual pages: {}\n".format(self.vMemory.capacity))
            f.write("Page faults: {}\n".format(self.pageFault))
            f.write("Referenced (Replaced): {}\n".format(self.ref))
            f.write("Unreferenced (Replaced): {}\n".format(self.nref))
            f.write("Modified (Replaced): {}\n".format(self.mod))
            f.write("Unmodified (Replaced): {}\n".format(self.nmod))
            f.write("Time: {} seconds\n".format(((t2-t1)/(10**9))))
        f.close()

    def allocate(self,method):
        if(method=="FIFO"):
            self.method_FIFO()
        elif(method=="SC"):
            self.method_SC()



#"Processes" quantity generated considering logical memory size
#and page size
#Consider main value in kB

if __name__ == "__main__":
    debug=0
    page_size=64
    vmem=vMemory(512000,page_size)
    vmem.generate()
    ram=RAM(256000,vmem,page_size,debug)
    ram.setUpRAM()
    ram.allocate("SC")
