import os
import torch.utils.data as data
import cv2
import torch
import PIL
import numpy as np
from xml.dom import minidom
import xml.etree.ElementTree as et
from collections import namedtuple
# segment_root = "C:/Users/Damini/Documents/PKLot/PKLotSegmented/PUC/Cloudy/2012-09-28"
# xml_root = "C:/Users/Damini/Documents/PKLot/PKLot/PUCPR/Cloudy/2012-09-16"
xml_root = "/Users/programming/PycharmProjects/Park/park_3/data"
annotation = namedtuple("ID", ["Labels", "BBox"])
CLASSES = 2
def get_anno_per_image(xml_file):
    anno = list()
    bbox = list()
    # for annotation_file in os.listdir(xml_root):
    image_ID = xml_file.split(".")[0]
    image = xml_file.split('#')[0]
    tree = et.parse(xml_root + "/" + xml_file)
    root = tree.getroot()
    for spot in root.iter("space"):
        if spot.find("contour"):
            for contour in spot.findall('contour'):
                odd = False
                for point in contour.findall("point"):
                    if odd is False:  # TODO: find a better way to find xmin ymin xmax ymax -> creat a function to deal with this
                        #TODO: also scale down multiloss calulated the data with error loss
                        bbox.append(point.attrib['x'])
                        bbox.append(point.attrib['y'])
                    odd = not odd
                bbox.append(spot.attrib['occupied'])
                anno.append(bbox.copy())
                bbox.clear()
    return anno

def get_anno_dataset(xml_root):
    data_anno= {}
    for idx, annotation_file in enumerate(os.listdir(xml_root)):
        if annotation_file.endswith('.xml'):
            annotation_id = annotation_file.split('.')[0]
            data_anno[annotation_id] = get_anno_per_image(annotation_file)
    return data_anno


class transformbBox(object):
    def __init__(self, transform=None, bbox=None, scale =None):
        self.transform = transform
        self.bbox = bbox #TODO: this is a list -> whole another level of problems
        self.scale = scale

    def transformBbox(self):
        print(self.transform)
        return scaledBbox

class CustomDetection(data.Dataset):
    def __init__(self, root, data=None, transforms=None,  annotation=None, phase=None):
        self.ids = list(annotation.keys())
        self.annotations = annotation
        self.phase = phase
        self.root = root
        self.num_classes = CLASSES
        self.transforms = transforms

    def __getitem__(self, idx):
        img, annotation, h, w, _, _ = self.pull_item(idx) #TODO:check format
        print(img)
        return (img, annotation)

    def __len__(self):
        return len(self.ids)

    def pull_item(self, idx):

        img_id = self.ids[idx]
        # print(img_id)
        annotation = self.annotations[img_id]
        # print(annotation)
        path = os.path.join(self.root, img_id)
        path = path + ".jpg"
        img_from_file = PIL.Image.open(path)

        print(type(img_from_file))
        img_h, img_w = img_from_file.size
        newBbox = transformbBox(self.transforms, scale=(img_h/300,img_w/300))
        img = img_from_file.copy()
        img = self.transforms(img)
        print(img.size)
        img = np.array(img)
        return torch.from_numpy(img).permute(2, 0, 1), annotation, img_h, img_w, img, img_id

    def pull_img(self, idx):
        img_id = self.ids[idx]
        path = os.path.join(self.root, img_id)
        path = path + ".jpg"
        return cv2.imread(path, cv2.IMREAD_COLOR)



if __name__ == "__main__":
    annos = get_anno_dataset(xml_root)
    print(annos)
    dataset = CustomDetection(root = xml_root, annotation=annos, phase="Train")


