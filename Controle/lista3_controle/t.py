# Python 3.9.1
import numpy as np #v1 .19.3
import math
import matplotlib . pyplot as plt #v3 .3.3
linewidth =1
#1 Vari á veis bá sicas
# item a
init = .0
end = 5.0
delta_t = .01
t = np . arange ( init , end +.01 , delta_t )
# item b
y = t **2
# item c
yd_ref = 2* t
# item d
yi_ref = ( t **3/3)
print ("01 done ")
#2 Derivada num érica , sem r u d o
# item a
t_size = t . size
yd = np . zeros ( t_size )
for k in range (1 , t_size ) :
yd [ k ] = ( y [ k ] - y [k -1]) / ( delta_t )
# item b
fig , axes = plt . subplots ()
plt . grid ( lw = 0.5)
plt . title (" yd_ref e de yd em fun ção de t")
plt . xlabel (" Tempo (s)")
plt . ylabel (" Valor ")
plt . plot (t , yd_ref , linestyle =' --', color =" green ", label =" yd_ref ",
linewidth = linewidth )
plt . plot (t , yd , linestyle =':', color =" red ", label ="yd", linewidth =
linewidth )
plt . legend ( fancybox = True , framealpha =1)
print ("02 done ")
#3 Adição de r u d o
# item a
media =.0
desvio_padrao =0.2
r = np . random . normal ( loc = media , scale = desvio_padrao , size = t_size )
fig , axes = plt . subplots ()
plt . grid ( lw = 0.5)
plt . title (" R u d o branco gaussiano (mé dia =0.0; desvio padr ão =0.2) ")
plt . xlabel (" Tempo (s)")
plt . ylabel (" Valor ")

plt . plot (t , r , linestyle ='-', color =" blue ", label =" noise ", linewidth =
linewidth )
plt . legend ( fancybox = True , framealpha =1)
# item b
z = y + r
fig , axes = plt . subplots ()
plt . grid ( lw = 0.5)
plt . title ("y e z em fun ção de t")
plt . xlabel (" Tempo (s)")
plt . ylabel (" Valor ")
plt . plot (t , z , linestyle ='-', color =" grey ", label ="z", linewidth =
linewidth )
plt . plot (t , y , linestyle ='-', color =" red ", label ="y", linewidth =
linewidth )
plt . legend ( fancybox = True , framealpha =1)
print ("03 done ")
#4 Derivada num érica , com r u d o
# item a
zd = np . zeros ( t_size )
for k in range (1 , t_size ) :
zd [ k ] = ( z [ k ] - z [k -1]) / ( delta_t )
# item b
fig , axes = plt . subplots ()
plt . grid ( lw = 0.5)
plt . title (" yd_ref e zd em fun ção de t")
plt . xlabel (" Tempo (s)")
plt . ylabel (" Valor ")
plt . plot (t , zd , linestyle ='-', color =" lightblue ", label ="zd", linewidth =
linewidth )
plt . plot (t , yd_ref , linestyle ='-', color =" green ", label =" yd_ref ",
linewidth = linewidth )
plt . legend ( fancybox = True , framealpha =1)
print ("04 done ")
#5 Integral num érica , com r u d o
zi = np . zeros ( t_size )
for k in range (0 , t_size -1) :
zi [ k +1] = zi [ k ] + (( delta_t ) * z [ k ])
# item b
fig , axes = plt . subplots ()
plt . grid ( lw = 0.5)
plt . title (" yi_ref e zi em fun ção de t")
plt . xlabel (" Tempo (s)")
plt . ylabel (" Valor ")
plt . plot (t , zi , linestyle ='-', color =" blue ", label ="zi", linewidth =
linewidth )
plt . plot (t , yi_ref , linestyle ='-', color =" green ", label =" yi_ref ",
linewidth = linewidth )
plt . legend ( fancybox = True , framealpha =1)
print ("05 done ")
print ('\ nt \ t | yd_ref \ t | yd \ t | zd \ t \ t | yi_ref \t | zi ')
for i in range (0 , 6) :
print (" {:.2 f}\t |{:.2 f}\t |{:.2 f}\t |{:.2 f}\t\t |{:.2 f}\t |{:.2 f}"
. format ( t [ i *100] , yd_ref [ i *100] , yd [i *100] , zd [ i *100] , yi_ref [ i
*100] , zi [ i *100]) )

print ("\ nShowing graphs ... ")
plt . show ()
print ("\ nFinished ")
