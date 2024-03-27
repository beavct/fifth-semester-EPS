bpm=12
divisor=1
resp=0

while(divisor <= bpm/2):
    if(bpm%divisor==0):
            resp+=divisor
    divisor+=1
    
print(resp)