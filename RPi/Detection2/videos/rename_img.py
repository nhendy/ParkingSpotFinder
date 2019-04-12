path = "D:/caltech/"
import os
for filename in os.listdir(path):
    print(filename)
    # newname = "airplane_" + filename
    # os.rename(os.path.join(path,filename),os.path.join(path,newname))