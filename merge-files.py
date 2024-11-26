#import os
import pandas as pd 
  
# reading csv files 
data1 = pd.read_csv('studentexcel1.csv') 
data2 = pd.read_csv('studentexcel2.csv') 
  
# using merge function by setting how='outer' 
output4 = pd.merge(data1, data2,  
                   on='Roll_no',  
                   how='outer') 
  
# displaying result 
print(output4) 
#os.system("gcc student_database.c")