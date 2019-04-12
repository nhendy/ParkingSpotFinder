from __future__ import print_function, division
import os
import sys
import torch
# from skimage import io, transform
import numpy as np
import scipy.io
# import matplotlib.pyplot as plt
import torch.nn as nn
import torch.optim as optim
from torch.optim import lr_scheduler
from torch.utils.data import Dataset, DataLoader
from torchvision import datasets, models, transforms
import copy
import cv2
from cv2 import imshow
import time
from PIL import Image


def binary_classify(bounds, roi_img, net):
    with torch.no_grad():
        # cv2.imshow('image', roi_img)
        roi_img = Image.fromarray(roi_img)
        data_transforms = transforms.Compose([
            transforms.Resize(256),
            transforms.CenterCrop(224),
            transforms.ToTensor()
        ])
        roi_img = data_transforms(roi_img)
        #
        # print(roi_img.shape)
        # roi_img = torch.transpose(roi_img, 2, 1)
        device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
        roi_img = roi_img.type('torch.FloatTensor')
        roi_img = roi_img.to(device)
        # imshow("Display window", roi_img)


        roi_img = roi_img.unsqueeze(0)

        outputs = net(roi_img)
        m = nn.Softmax()
        probablities = m(outputs)
        print("out = {}".format(outputs))
        print("class1 = {}, class2 = {}".format(probablities.data[0][0], probablities.data[0][1]))
        status = probablities.data[0][0] > probablities.data[0][1]
    return status
    #take bounds
#crop to get image
#visualize image
# test image
#see if correct
#send image as tru or false depending.

