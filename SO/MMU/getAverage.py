t="sc4.txt"

with open(t,"r") as f:
    lines=f.readlines()
k=0

string = ["" for x in range(48)]
string2 = ["" for x in range(48)]

for i in range (4):
    for j in range(12):
        string[j+k]=(''.join(lines[k+j]))
    k+=12

for i in range (48):
    if(i!=0 and i!=12 and i!=24 and i!=36):
        string[i]=string[i].strip().split(":")
        string2[i]=string[i][1]
        if(i==11 or i ==23 or i==35 or i==47):
            print(string2[i])
            string2[i]=string2[i][:-8]
        string2[i]=string2[i].strip()

print(string2)
with open(t, "a") as f:
    f.write("\nAverage\n")
    for i in range (11):
        #f.write(string[i+1][0])
        k=(float(string2[i+1])+float(string2[i+13])+float(string2[i+25])+float(string2[i+37]))/4
        #print(k)
        f.write(string[i+1][0]+": "+str(k)+"\n")
    f.close()
#print(string2)
#print(string)
