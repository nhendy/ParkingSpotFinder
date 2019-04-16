import cv2
import numpy as np
import logging
from Utilities.drawing_utils import draw_contours
from Utilities.colors import COLOR_GREEN, COLOR_WHITE, COLOR_BLUE
from torchvision import models, transforms
import torch.nn as nn
import torch

class MotionDetector:
    LAPLACIAN = 3
    EDGE_DETECTION = 20
    DETECT_DELAY = 1
    # MODEL_PATH = 'models/alexnet_car_classifier.pt'
    MODEL_PATH = 'models/working_model.pt'

    def __init__(self, coordinates):
        self.coordinates_data = coordinates
        self.contours = []                                      # Coordinates
        self.bounds = []                                        # Bounding upright rectangles
        self.mask = []                                          # MASK ?????
        self.model = None

        self.statuses = [False] * len(self.coordinates_data)    # State of each ROI
        self.times = [None] * len(self.coordinates_data)        # Time registered for each ROI

        self._init_parameters()


    def _init_parameters(self):
        """Initializes contours, bounds, masks
        """
        coordinates_data = self.coordinates_data
        logging.debug("coordinates data: %s", coordinates_data)
        for p in coordinates_data:
            coordinates = self._coordinates(p)
            logging.debug("coordinates: %s", coordinates)

            rect = cv2.boundingRect(coordinates)
            logging.debug("rect: %s", rect)

            self.contours.append(coordinates)
            self.bounds.append(rect)

        self.model = models.alexnet(pretrained=False)
        num_ftrs = self.model.classifier[-1].in_features
        self.model.classifier[-1] = nn.Linear(num_ftrs, 2)
        state = torch.load(MotionDetector.MODEL_PATH, map_location='cpu')
        logging.info('Loading the model ...')
        self.model.load_state_dict(state)
        self.model.eval()



    def detect_motion(self, frame):
        new_frame = frame.copy()
        logging.debug("new_frame: %s", new_frame)

        for index, c in enumerate(self.coordinates_data):
            self.statuses[index] = self.__apply(new_frame, index, c)

        for index, p in enumerate(self.coordinates_data):
            coordinates = self._coordinates(p)

            color = COLOR_GREEN if self.statuses[index] else COLOR_BLUE
            draw_contours(new_frame, coordinates, str(p["id"]), COLOR_WHITE, color)

        return (new_frame, self.statuses)

    def __apply(self, frame, index, p):
        coordinates = self._coordinates(p)
        logging.debug("points: %s", coordinates)

        rect = self.bounds[index]
        logging.debug("rect: %s", rect)

        roi  = frame[rect[1]:(rect[1] + rect[3]), rect[0]:(rect[0] + rect[2])]
        status =  self._binary_classification(roi, index)

        return status




    def _binary_classification(self, roi_img, index):
        with torch.no_grad():
            data_transforms = transforms.Compose([
                transforms.ToPILImage(),
                transforms.Resize(256),
                transforms.CenterCrop(224),
                transforms.ToTensor()
            ])

            roi_img = data_transforms(roi_img).unsqueeze(0).float()
            outputs = self.model(roi_img)
            prediction = nn.Softmax()
            probablities = prediction(outputs)
            status = probablities.data[0][0].item() > probablities.data[0][1].item()

        logging.info('index: {}, Vacant: {:.2f}, Occupied:  {:.2f}'.format(index, probablities.data[0][0],
                                                                                 probablities.data[0][1]))
        return status

    @staticmethod
    def _coordinates(p):
        return np.array(p["coordinates"])

    @staticmethod
    def same_status(coordinates_status, index, status):
        return status == coordinates_status[index]

    @staticmethod
    def status_changed(coordinates_status, index, status):
        return status != coordinates_status[index]

