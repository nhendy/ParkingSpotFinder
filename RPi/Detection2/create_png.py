import cv2
vidcap = cv2.VideoCapture('videos/parklongedit1.mp4')
success,image = vidcap.read()
count = 0
while success:
    print(count)
    if(count == 6000):
          cv2.imwrite("longparkedit1.png" , image)     # save frame as JPEG file
          success,image = vidcap.read()
          print('Read a new frame: ', success)
          break
    count += 1