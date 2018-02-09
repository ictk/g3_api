import os
import re
list_files = ['run.py','old','i2c_sw.c','il005communication.c','i2c_sw.h','il005communication.h','il005define.h','il005hal_i2c.c','il005hal_i2c.h','main.c',]
print("START")
for tmp  in os.listdir():
    match = re.match(r'.+\.c',tmp)
    if match == None:
        continue
    print(tmp)
        
        
    

    continue
    if tmp in list_files:
        print(tmp)
        
        
        
        continue
    #print(tmp)
    #os.rename(tmp,"old/"+tmp)
    
    
        