import numpy as np
import random as rd
import collections
import time
import sys
import gc

class page():
    def __init__(self,action,address,status,ramPosition): #action R or W
        self.action=action
        self.address=address
        self.status=status
        self.ramPosition=ramPosition

class vMemory():
    def __init__(self,size,pageSize):
        self.size=size
        self.pageSize=pageSize
        self.capacity=int(self.size/self.pageSize)
        self.pages=[]

    def generate(self): #
        k=self.capacity
        qtd1=list(range(1,k+1))
        rd.shuffle(qtd1)
        qtd2=list(range(1,k+1))
        rd.shuffle(qtd2)
        qtd3=list(range(1,k+1))
        rd.shuffle(qtd3)
        qtd4=list(range(1,k+1))
        rd.shuffle(qtd4)
        qtd=[*qtd1[:int(k/4)],*qtd2[int(k/4):int(2*k/4)],
                *qtd3[int(2*k/4):int(3*k/4)],*qtd4[int(3*k/4):]]
        rd.shuffle(qtd)
        time.sleep(1)

        #check for possible callbacks
        '''gh=qtd.copy()
        gh.sort()
        print(len(qtd))
        gk=sorted(set([x for x in qtd if qtd.count(x) > 1]))
        gk.sort()
        print(gk)
        print(gh)'''

        k=""
        for i in range(self.capacity):
            if(rd.randint(1,4)%4==0):
                k='W'
            else:
                k='R'
            self.pages.append(page(k,qtd[i],-1,-1))
        print("Virtual Memory Configured")

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
        self.clock=[]
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
            self.clock.append(-1)
        self.used=0;
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

    def verifyClass(self):
        i=0
        theClass=self.rw[i]
        if((theClass>0) or (self.used<self.capacity)):
            for j in range(self.capacity):
                if(self.rw[j]<theClass):
                    theClass=self.rw[j]
                    i=j
                if(theClass==-1):
                    break
        return i

    '''does not uses class hierarchy so, just for comparing,
    only occurs classes 2 (refenced and not modified) or 3
    (refenced and modified), simulanting only read and write
    situations'''
    def method_LRU(self):
        t1=time.time_ns()
        for i in range (len(self.vMemory.pages)):

            d=0
            if(self.debug==1):
                print("\n")
                for e in range(len((self.frames))):
                    if(self.frames[e]==self.vMemory.pages[i].address):
                        print("################################")
                        print("REQUESTED ALREADY IN RAM")
                        d=1
                print(self.vMemory.pages[i].address)
                print(self.frames)

            k=self.verifyOcurrency(self.vMemory.pages[i].address)
            l=-1
            if(k==-1):
                self.frames.pop(0)
                self.frames.append(self.vMemory.pages[i].address)
                l=self.rw.pop(0)
                self.pageFault+=1
            else:
                aux=self.frames.pop(k)
                self.frames.append(self.vMemory.pages[i].address)
                l=self.rw.pop(k)
            if(self.vMemory.pages[i].action=='W'):
                self.rw.append(3)
            elif(self.vMemory.pages[i].action=='R'):
                self.rw.append(2)
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
        print("\n## Least Recently Used (LRU) ##")
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
        with open("lru4.txt", "a") as f:
            f.write("## Least Recently Used (LRU) ##\n")
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


    def method_NRU(self):
        clk1=int(len(self.frames)*2)
        clk2=int(len(self.frames)*1.5)
        clk3=int(len(self.frames)*1)
        t1=time.time_ns()
        for i in range (len(self.vMemory.pages)):

            d=0
            if(self.debug==1):
                print("\n")
                for e in range(len((self.frames))):
                    if(self.frames[e]==self.vMemory.pages[i].address):
                        print("################################")
                        print("REQUESTED ALREADY IN RAM")
                        d=1
                print(self.vMemory.pages[i].address)
                print(self.frames)
                print(self.rw)
                print(self.clock)

            ''' CLOCK SIMULATION '''
            for j in range(len(self.clock)):
                self.clock[j]+=1

            ''' referenced and modified (stays for frames*2 clocks)
                referenced (stays for frames*1.5 clocks)
                modified (stays for frames clocks)
            '''
            for j in range(len(self.rw)):
                if(self.clock[j]==clk1 and self.rw[j]==3):
                        self.rw[j]=1
                        self.clock[j]=0
                elif(self.clock[j]==clk2 and self.rw[j]==2):
                        self.rw[j]=0
                        self.clock[j]=0
                elif(self.clock[j]==clk3 and self.rw[j]==1):
                        self.rw[j]=0
                        self.clock[j]=0

            k=self.verifyOcurrency(self.vMemory.pages[i].address)
            lowestClassIndex=-1
            l=-1
            if(k==-1):
                lowestClassIndex=self.verifyClass()
                self.frames.pop(lowestClassIndex)
                self.frames.insert(lowestClassIndex,self.vMemory.pages[i].address)
                l=self.rw[lowestClassIndex]
                self.pageFault+=1
                if(self.vMemory.pages[i].action=='W'):
                    self.rw[lowestClassIndex]=3
                elif(self.vMemory.pages[i].action=='R'):
                    self.rw[lowestClassIndex]=2
                else:
                    self.rw[lowestClassIndex]=-1 #gone wrong
                self.clock[lowestClassIndex]=0
                if(self.used<self.capacity):
                    self.used+=1
            else:
                if(self.vMemory.pages[i].action=='W'):
                    self.rw[k]=3
                elif(self.vMemory.pages[i].action=='R'):
                    self.rw[k]=2
                else:
                    self.rw[k]=-1 #gone wrong
                self.clock[k]=0
            if((k==-1)and(l>=0) and (l<=3)):
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
        print("\n## Not Recently Used (NRU) ##")
        print("Page size: {}".format(self.vMemory.pageSize))
        print("Physical memory: {}".format(self.size))
        print("Virtual memory: {}".format(self.vMemory.size))
        print("Physical memory page frames: {}".format(self.capacity))
        print("Logical memory virtual pages: {}".format(self.vMemory.capacity))
        print("Page faults: {}".format(self.pageFault))
        print("Referenced (Replaced): {}".format(self.ref))
        print("Unreferenced (Replaced): {}".format(self.nref))
        print("Modified (Replaced): {}".format(self.mod))
        print("Unmodified (Replaced): {}".format(self.nmod))
        print("Time: {} seconds".format(((t2-t1)/(10**9))))
        with open("nru3.txt", "a") as f:
            f.write("## Not Recently Used (NRU) ##\n")
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
        if(method=="LRU"):
            self.method_LRU()
        elif(method=="NRU"):
            self.method_NRU()



#"Processes" quantity generated considering logical memory size
#and page size
#Consider main value in kB

if __name__ == "__main__":
    debug=0
    page_size=64
    vmem=vMemory(1024000,page_size)
    vmem.generate()
    ram=RAM(128000,vmem,page_size,debug)
    ram.setUpRAM()
    ram.allocate("NRU")
