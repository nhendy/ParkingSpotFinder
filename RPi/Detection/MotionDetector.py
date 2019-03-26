import cv2 as open_cv
import numpy as np
import logging
from Utilities.drawing_utils import draw_contours
from Utilities.colors import COLOR_GREEN, COLOR_WHITE, COLOR_BLUE


class MotionDetector:
    LAPLACIAN = 3
    DETECT_DELAY = 1

    def __init__(self, coordinates):
        self.coordinates_data = coordinates
        self.contours = []                                      # Coordinates
        self.bounds = []                                        # Bounding upright rectangles
        self.mask = []                                          # MASK ?????

        self.statuses = [False] * len(self.coordinates_data)     # State of each ROI
        self.times = [None] * len(self.coordinates_data)         # Time registered for each ROI

        self._init_parameters()


    def _init_parameters(self):
        """Initializes contours, bounds, masks
        """
        coordinates_data = self.coordinates_data
        logging.debug("coordinates data: %s", coordinates_data)
        for p in coordinates_data:
            coordinates = self._coordinates(p)
            logging.debug("coordinates: %s", coordinates)

            rect = open_cv.boundingRect(coordinates)
            logging.debug("rect: %s", rect)

            new_coordinates = coordinates.copy()
            new_coordinates[:, 0] = coordinates[:, 0] - rect[0]
            new_coordinates[:, 1] = coordinates[:, 1] - rect[1]
            logging.debug("new_coordinates: %s", new_coordinates)

            self.contours.append(coordinates)
            self.bounds.append(rect)

            mask = open_cv.drawContours(
                np.zeros((rect[3], rect[2]), dtype=np.uint8),
                [new_coordinates],
                contourIdx=-1,
                color=255,
                thickness=-1,
                lineType=open_cv.LINE_8)

            mask = mask == 255
            self.mask.append(mask)
            logging.debug("mask: %s", self.mask)

    def detect_motion(self, frame):
        blurred = open_cv.GaussianBlur(frame.copy(), (5, 5), 3)
        grayed = open_cv.cvtColor(blurred, open_cv.COLOR_BGR2GRAY)
        new_frame = frame.copy()
        logging.debug("new_frame: %s", new_frame)

        for index, c in enumerate(self.coordinates_data):
            self.statuses[index] = self.__apply(grayed, index, c)

        for index, p in enumerate(self.coordinates_data):
            coordinates = self._coordinates(p)

            color = COLOR_GREEN if self.statuses[index] else COLOR_BLUE
            draw_contours(new_frame, coordinates, str(p["id"]), COLOR_WHITE, color)

        return (new_frame, self.statuses)

    def __apply(self, grayed, index, p):
        coordinates = self._coordinates(p)
        logging.debug("points: %s", coordinates)

        rect = self.bounds[index]
        logging.debug("rect: %s", rect)

        roi_gray = grayed[rect[1]:(rect[1] + rect[3]), rect[0]:(rect[0] + rect[2])]
        laplacian = open_cv.Laplacian(roi_gray, open_cv.CV_64F)
        logging.debug("laplacian: %s", laplacian)

        coordinates[:, 0] = coordinates[:, 0] - rect[0]
        coordinates[:, 1] = coordinates[:, 1] - rect[1]

        mean = np.mean(np.abs(laplacian * self.mask[index]))
        logging.info('mean for {} is {:.2f}'.format(index, mean))
        status =  mean < MotionDetector.LAPLACIAN
        logging.debug("status: %s", status)

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

