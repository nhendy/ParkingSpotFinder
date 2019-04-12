import os
import shutil
relative = "C:/Users/Damini/Downloads/PATCHES"
dest = "D:/crn_dataset/train/"
with open("all.txt", 'r') as file:
    lines = file.readlines()
    for line in lines:
        print(line)
        src =  relative + "/" + line.split(" ")[0]
        class_label = int(line.split(" ")[1])
        if class_label == 1:#CAR EXISTS
            print(os.path.join(dest , "occupied" ))
            shutil.move(src, os.path.join(dest , "occupied" ))
            print(dest)
        elif class_label == 0: #no car
            shutil.move(src, os.path.join(dest, "empty"))