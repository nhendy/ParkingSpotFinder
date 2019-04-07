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

import time


def test(net):
    correct = 0
    total = 0
    # with torch.no_grad():
    for data in dataloaders:
        images, labels = data
        images = images.to(device)
        labels = labels.to(device)
        print(labels)
        outputs = net(images)
        m = nn.Softmax()
        probablities = m(outputs)
        print("classes = {}".format(probablities))
        _, predicted = torch.max(outputs.data, 1)
        total += labels.size(0)
        correct += (predicted == labels).sum().item()

    print('Accuracy of the network on the 10000 test images: %d %%' % (
            100 * correct / total))



if __name__ == '__main__':
    data_transforms = transforms.Compose([
        transforms.Resize(256),
        transforms.CenterCrop(224),
        transforms.ToTensor(),
        transforms.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])
    ])

    data_dir = 'D:/PKLot/PKLOTtrial'
    image_datasets = datasets.ImageFolder(os.path.join(data_dir, 'test'),
                                              data_transforms)

    dataloaders = torch.utils.data.DataLoader(image_datasets, batch_size=4,
                                                  shuffle=True, num_workers=4)

    dataset_sizes = len(image_datasets)
    class_names = image_datasets.classes

    device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
    model_ft = models.resnet18(pretrained=True)
    num_ftrs = model_ft.fc.in_features
    model_ft.fc = nn.Linear(num_ftrs, 2)
    model_ft.load_state_dict(torch.load('carPretrained.pt'))
    model_ft = model_ft.to(device)
    test(model_ft)