import os
import torch.utils.data as data
import cv2
import torch
import numpy as np
from xml.dom import minidom
import xml.etree.ElementTree as et
from collections import namedtuple
import jinja2
from PIL import Image
from pprint import pprint
from jinja2 import Template
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


def extract_objs(annos):
    list_object = list()
    for  key, item  in annos.items():
        for index, bbox in enumerate(item):
            if( bbox[4] == 0):

               list_object.append({'name':'occupied', 'pose':'unspecified', 'truncated': 0, 'difficult': 0, 'xmin':bbox[0], 'xmax':bbox[2], 'ymin':bbox[1], 'ymax':bbox[3]})
            else:
               list_object.append({'name': 'vacant', 'pose': 'unspecified', 'truncated': 0, 'difficult': 0, 'xmin': bbox[0], 'xmax': bbox[2], 'ymin': bbox[1], 'ymax': bbox[3]})
    return  list_object

def extract_file_info(path):
    image_path = os.path.splitext(path)[0] + '.jpg'
    image_name = os.path.splitext(os.path.basename(path))[0] + '.jpg'
    im = Image.open(image_path)
    width, height = im.size
    depth = len(im.mode)

    result_dict = {'folder'    : os.path.dirname(path),
                   'filename'  : image_name,
                   'path'      : image_path,
                   'database'  : 'Unspecified',
                   'width'     : width,
                   'height'    : height,
                   'depth'     : depth,
                   'segmented' : 0}

    return result_dict


def create_new_xml(file_info, list_obj, output_file):
    templateLoader = jinja2.FileSystemLoader(searchpath="./")
    templateEnv = jinja2.Environment(loader=templateLoader)
    TEMPLATE_FILE = "template.xml"
    template = templateEnv.get_template(TEMPLATE_FILE)
    output = template.render(**file_info, objects=list_obj)
    # print(output)
    with open(output_file, 'w') as file:
        file.write(output)


def test():
    templateLoader = jinja2.FileSystemLoader(searchpath="./")
    templateEnv = jinja2.Environment(loader=templateLoader)
    TEMPLATE_FILE = "template.xml"
    template = templateEnv.get_template(TEMPLATE_FILE)
    outputText = template.render()
    # print(outputText)


if __name__=='__main__':
    annos = get_anno_dataset(xml_root)
    # print(len(annos['2012-09-12_06_57_29']))
    # # pprint(annos)
    list_obj = extract_objs(annos)
    file_info = extract_file_info(os.path.join(xml_root, '2012-09-12_06_57_29.xml'))
    # pprint(len(list_obj))
    createNewXML(file_info, list_obj, 'output.xml')
    # test()

    # pprint(extract_file_info('./data/2012-09-12_06_57_29.xml'))



