# #
# # # import cv2
# # #
# # # cap = cv2.VideoCapture('http://14.47.226.237:91/cgi-bin/faststream.jpg?fps=1?stream=full&data=v.mjpg', cv2.CAP_FFMPEG)
# # # while(cap.isOpened()):
# # #     ret, frame = cap.read()
# # #     print('.',end='')
# # #     cv2.imshow('frame',frame)
# # #     cv2.imwrite('frame.jpg', frame)
# # #     if cv2.waitKey(10) & 0xFF == ord('q'):
# # #         cv2.destroyAllWindows()
# #
# #
#
# import cv2
# import numpy as np
# import yaml
#



# with open('coordinates_1.yml', "r") as data:
#     p = yaml.load(data)
#
#
# img = cv2.imread('images/parking_lot_1.png')
# rect = cv2.boundingRect(np.array(p[3]["coordinates"]))
# roi = img[rect[1]:(rect[1] + rect[3]), rect[0]:(rect[0] + rect[2])]
# cv2.imwrite('roi.png', roi)
#
#
#
# # while(1):
# img = cv2.imread('roi.png')
# blurred = cv2.GaussianBlur(img.copy(), (5, 5), 10)
# gray = cv2.cvtColor(blurred, cv2.COLOR_BGR2GRAY)
# laplacian = cv2.Laplacian(gray,cv2.CV_64F)
# print(laplacian)
# print(np.mean(np.abs(laplacian)))
# cv2.imshow('laplacian',laplacian)
# cv2.imshow('blurred',blurred)
#
#
# if cv2.waitKey(0) & 0xFF == ord('q'):
#     cv2.destroyAllWindows()
#     # break

########################################################################################################
# import cv2
# import numpy as np
#
# #Capture livestream video content from camera 0
# cap = cv2.VideoCapture(0)
#
# while(1):
#
#     # Take each frame
#     _, frame = cap.read()
#
#     # Convert to HSV for simpler calculations
#     hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
#
#     # Calcution of Sobelx
#     sobelx = cv2.Sobel(frame,cv2.CV_64F,1,0,ksize=5)
#
#     # Calculation of Sobely
#     sobely = cv2.Sobel(frame,cv2.CV_64F,0,1,ksize=5)
#
#     # Calculation of Laplacian
#     laplacian = cv2.Laplacian(frame,cv2.CV_64F)
#
#     cv2.imshow('sobelx',sobelx)
#     cv2.imshow('sobely',sobely)
#     cv2.imshow('laplacian',laplacian)
#     k = cv2.waitKey(5) & 0xFF
#     if k == 27:
#         break
#
# cv2.destroyAllWindows()
#
# #release the frame
# cap.release()
########################################################################################################
########################################################################################################
# import cv2
# import yaml
# import numpy as np

#
# with open('coordinates_1.yml', "r") as data:
#         p = yaml.load(data)
#
#
#
#
#
# # capture frames from a video
# img = cv2.imread('images/parking_lot_1.png')
#
# # Trained XML classifiers describes some features of some object we want to detect
# car_cascade = cv2.CascadeClassifier('cars.xml')
#
# # loop runs if capturing has been initialized.
# while True:
#     # reads frames from a video
#     # ret, frames = cap.read()
#     frames = img
#
    # coordinates = np.array(p[0]["coordinates"])
    # x, y, w, h = cv2.boundingRect(np.array(p[0]["coordinates"]))
#     rect = (x, y, w, h)
#     cv2.rectangle(frames, (x, y), (x+w, y+h), (0, 255, 0), 2)
#
    # roi = frames[rect[1]:(rect[1] + rect[3]), rect[0]:(rect[0] + rect[2])]
#
#     # convert to gray scale of each frames
#     gray = cv2.cvtColor(roi, cv2.COLOR_BGR2GRAY)
#
#     # Detects cars of different sizes in the input image
#     cars = car_cascade.detectMultiScale(gray, 1.02, 1)
#     print(cars)
#
#     # To draw a rectangle in each cars
#     for (x,y,w,h) in cars:
#         cv2.rectangle(roi,(x,y),(x+w,y+h),(0,0,255),2)
#
#    # Display frames in a window
#     cv2.imshow('video2', roi)
#
#     # Wait for Esc key to stop
#     if cv2.waitKey(33) == ord('q'):
#         break
#
# # De-allocate any associated memory usage
#  cv2.destroyAllWindows()
########################################################################################################
########################################################################################################
# from imageai.Detection import ObjectDetection
# from imageai.Prediction import ImagePrediction
# import os
# import cv2
#
# with open('coordinates_1.yml', "r") as data:
#     p = yaml.load(data)
#
# img = cv2.imread('images/parking_lot_1.png')
# coordinates = np.array(p[2]["coordinates"])
# rect = cv2.boundingRect(np.array(p[2]["coordinates"]))
# roi = img[rect[1]:(rect[1] + rect[3]), rect[0]:(rect[0] + rect[2])]
# cv2.imwrite('roi.png', roi)
#
#
# execution_path = os.getcwd()
#
# prediction = ImagePrediction()
# prediction.setModelTypeAsInceptionV3()
# prediction.setModelPath(os.path.join(execution_path, "models/inception.h5"))
# prediction.loadModel()
#
#
# predictions, probabilities = prediction.predictImage(roi, input_type="array", result_count=10)
#
#
# for eachPrediction, eachProbability in zip(predictions, probabilities):
#     print(eachPrediction , " : " , eachProbability)

########################################################################################################
########################################################################################################
# detector = ObjectDetection()
# detector.setModelTypeAsTinyYOLOv3()
# detector.setModelPath("models/yolo-tiny.h5")
# detector.loadModel()
# detections = detector.detectObjectsFromImage(input_image="images/parking_lot_1.png",
#                                              output_image_path="imagenew.jpg",
#                                              minimum_percentage_probability=20)
# for eachObject in detections:
#     print(eachObject["name"] , " : ", eachObject["percentage_probability"], " : ", eachObject["box_points"] )
#
#     print("--------------------------------")
########################################################################################################
########################################################################################################
import torch
import torch.nn as nn
from torchvision import datasets, models, transforms
import yaml
import cv2
import numpy as np
from PIL import Image

from torch.autograd import Variable

imsize = 224
loader = transforms.Compose([transforms.ToPILImage(),
                             transforms.Resize(imsize),
                             transforms.ToTensor()
                             ])

# def image_loader(image_name):
#     """load image, returns tensor"""
#     image = Image.open(image_name)
#     image = loader(image).float()
#     image = Variable(image, requires_grad=True)
#     image = image.unsqueeze(0)  #this is for VGG, may not be needed for ResNet
#     print(image.size())
#     return image  #assumes that you're us




MODEL_PATH = 'models/alex_pretrained_pklot.pt'


model = models.alexnet(pretrained=False)
num_ftrs = model.classifier[-1].in_features
model.classifier[-1] = nn.Linear(num_ftrs, 2)
state = torch.load(MODEL_PATH, map_location='cpu')

print('Loading the model ...')
model.load_state_dict(state)
model.eval()

with open('data/coordinates_1.yml', "r") as data:
    p = yaml.load(data)


img = cv2.imread('images/parking_lot_1.png')
coordinates = np.array(p[0]["coordinates"])
x, y, w, h = cv2.boundingRect(np.array(p[0]["coordinates"]))
rect = (x, y, w, h)
# cv2.rectangle(img, (x, y), (x+w, y+h), (0, 255, 0), 2)

roi = img[rect[1]:(rect[1] + rect[3]), rect[0]:(rect[0] + rect[2])]
# image_loader('images/parking_lot_1.png')
roi_t = loader(roi).unsqueeze(0).float()
outputs = model(roi_t)
_, preds = torch.max(outputs, 1)
print(preds)


for _ in range(10):
    model = models.alexnet(pretrained=False)
    num_ftrs = model.classifier[-1].in_features
    model.classifier[-1] = nn.Linear(num_ftrs, 2)
    state = torch.load(MODEL_PATH, map_location='cpu')

    print('Loading the model ...')
    model.load_state_dict(state)
    model.eval()
    outputs = model(roi_t)
    _, preds = torch.max(outputs, 1)
    print(preds)




# print(loader(roi).size())
# print(roi)
# roi_t = torch.from_numpy(roi).float().permute(2,0,1).unsqueeze(0)
# print(torch.from_numpy(roi).float().permute(2,0,1).unsqueeze(0).size())
# image = loader(roi_t).float()
#
# print(image.size())


while(1):
    cv2.imshow('video2', roi)
    if cv2.waitKey(33) == ord('q'):
        cv2.destroyAllWindows()
        break
########################################################################################################