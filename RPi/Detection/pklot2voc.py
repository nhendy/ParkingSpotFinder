#!/usr/bin/env python3

""" Script to convert xml annotation files from PKLot format
to PASCAL VOC format.

[1] Almeida, P., Oliveira, L. S., Silva Jr, E., Britto Jr, A., Koerich, A.,
PKLot – A robust dataset for parking lot classification,
Expert Systems with Applications, 42(11):4937-4949, 2015.

[2] Everingham, M., Van Gool, L., Williams, C. K. I., Winn, J. and Zisserman, A.
International Journal of Computer Vision, 88(2), 303-338, 2010.
"""

import os
from collections import namedtuple
import jinja2
from PIL import Image
from jinja2 import Template
from bs4 import BeautifulSoup
import argparse
from tqdm import tqdm

__author__     = "Damini Rhijwani, Noureldin Hendy"
__copyright__  = "Copyright 2019, Parking Spot Finder, All rights reserved."
__license__    = "MIT"
__version__    = "0.0.1"
__email__      = "drijhwan@purdue.edu "
__status__     = "Development"


"""Default name of VOC template
"""
TEMPLATE_FILE = "template.xml"


parser = argparse.ArgumentParser(description="""
                        Script to convert xml annotation files from PKLot format
                        to PASCAL VOC format.""")
parser.add_argument('-I', '--input', help= "Path to input data folder in PKLot format.",
                    type=str, metavar= "Input data folder", required=True)
parser.add_argument('-O', '--output', help= "Path to output data folder in VOC format.",
                    type=str, metavar= "Output data folder", required=True)
parser.add_argument('-TF', '--template_folder', metavar= "Template folder",
                    help= "Path to template folder.", type=str, required=False,
                    default='templates')
parser.add_argument('-TN', '--template_name', help= "Name of template file.",
                     metavar= "Template file",
                     type=str, required=False, default=TEMPLATE_FILE)
args = parser.parse_args()




def get_annotations_per_file(xml_file_path):
    """Parses xml file that holds annotations for an image and
    extracts all annotations necessary to convert to PASCAL VOC format.


    Parameters
    ----------
    xml_file : str
        Name of the xml file in PKLot format.

    Returns
    -------
    annotations : list
        List of tuples.
        First element is the id of the object.
        Second element is a list of [xmin, ymin, xmax, ymax].
        Third element is 1 if occupied, 0 if vaccant.

    Notes
    -----
    Only xmin, xmax, ymin, ymax are parsed. Angles, centroids and other
    coordinate points are discarded.

    """
    annotations = []
    _, ext = os.path.splitext(xml_file_path)
    if ext != '.xml':
        raise ValueError('File must be an xml file. Input file is {}'.format(xml_file_path))

    path = os.path.abspath(xml_file_path)

    with open(path, mode='r', encoding='utf-8') as file:
            xml = file.read()

    Space  = namedtuple('Space',['id', 'xmin', 'xmax', 'ymin', 'ymax', 'occupied'] )
    soup   = BeautifulSoup(xml,'xml')
    spaces = soup.find_all('space')
    try:
        for space in spaces:
            space_id, occupied = int(space['id']), int(space.get('occupied', 0))
            contour_points = space.find_all('point', recursive=True)

            #TODO : THERE'S A HUGE BUG RIGHT HERE !!!! -> NOT any more
            xmin, xmax, ymin, ymax = float("Inf"), float("-Inf"), float("Inf"), float("-Inf")
            for point in contour_points:
                x, y = int(point['x']), int(point['y'])
                if   x > xmax : xmax = x
                if   x < xmin : xmin = x

                if   y > ymax : ymax = y
                if   y < ymin : ymin = y

            assert(xmin != float("Inf"))
            assert(ymin != float("Inf"))
            assert(xmax != float("-Inf"))
            assert(ymax != float("-Inf"))
            annotations.append(Space(id= space_id,
                                     xmin=xmin,
                                     ymin=ymin,
                                     xmax=xmax,
                                     ymax=ymax,
                                     occupied=occupied))
    except Exception as e:
        print('FAILED @ {} id {}'.format(xml_file_path, space_id))
        if isinstance(e, AssertionError):
            print('xmin {}'.format(xmin))
            print('xmax {}'.format(xmax))
            print('ymin {}'.format(ymin))
            print('ymax {}'.format(ymax))
            os.system('subl '+ xml_file_path)
        exit(0)

    return annotations

def get_annotations_per_folder(data_folder, same_structure=False):
    """Walks down the filesystem tree to find xml files that contain annotations
    and collects them into one dict.

    Parameters
    ----------
    xml_root : str
        Relative or absolute path to the root directory of PKLot.
    same_structure: bool
        If True, then output dictionary will have a structure similar to
        the file directory tree structure.
    Returns
    -------
    img_to_annotations : dict
        Dictionary of image file name to annotations. annotations
        are in the same structure as in get_annotations_per_image functions.

    Notes
    -----
    This is the assumed structure under the data_folder.
    .
    ├── PKLot
    │   ├── PUCPR
    │   │   ├── Cloudy
    │   │   ├── Rainy
    │   │   └── Sunny
    │   ├── UFPR04
    │   │   ├── Cloudy
    │   │   ├── Rainy
    │   │   └── Sunny
    │   └── UFPR05
    │       ├── Cloudy
    │       ├── Rainy
    │       └── Sunny
    .
    .
    .
    """

    if not os.path.isdir(data_folder):
        raise FileNotFoundError('Directory path is incorrect.')

    if same_structure:
        raise NotImplementedError('This is not supported yet.')

    else:

        img_to_annotations= {}
        path = os.path.abspath(data_folder)
        with tqdm(total=12417) as pbar:
            for (dirpath, dirnames, filenames) in os.walk(path):
                # once we're at the bottom of the tree
                if dirnames == []:
                    for filename in filenames:
                        if filename.endswith('.xml'):
                            pbar.update(1)
                            img_name = os.path.join(dirpath,os.path.splitext(filename)[0] + '.jpg')
                            xml_path = os.path.join(dirpath, filename)
                            img_to_annotations[img_name] = get_annotations_per_file(xml_path)
    return img_to_annotations


def annotations_to_objs(annotations):
    """Converts array of annotations to objects in format needed for VOC temlpate.

    Parameters
    ----------
    annotations : list
        List of tuples.
        ('id', 'xmin', 'xmax', 'ymin', 'ymax', 'occupied')

    Returns
    -------
    object_list : list
        list of dictionaries of objects in the annotations.

    """
    object_list = []
    for  space  in annotations:
       object_list.append({'name'     :'occupied' if space.occupied == 1 else 'vaccant',
                           'pose'     :'unspecified',
                           'truncated': 0,
                           'difficult': 0,
                           'xmin'     :space.xmin,
                           'xmax'     :space.xmax,
                           'ymin'     :space.ymin,
                           'ymax'     :space.ymax})

    return  object_list

def extract_file_info(img_path):
    """Extracts file information as needed for VOC xml template.

    Parameters
    ----------
    img_path : str
        Image path.

    Returns
    -------
    file_info_dict : dict
        Dictionary containing image file information.

    """
    image_name = os.path.basename(img_path)
    im = Image.open(img_path)
    width, height = im.size
    depth = len(im.mode)

    file_info_dict = {'folder'    : os.path.dirname(img_path),
                      'filename'  : image_name,
                      'path'      : img_path,
                      'database'  : 'unspecified',
                      'width'     : width,
                      'height'    : height,
                      'depth'     : depth,
                      'segmented' : 0}

    return file_info_dict

def extract_voc_info_from_folder(data_folder):
    """Accumulates all the info required about each xml file to convert to VOC
    format.

    Parameters
    ----------
    data_folder : str
        Input data folder.

    Returns
    -------
    files
        List of dictionaries storing files info.

    """
    files = []
    img_to_annotations = get_annotations_per_folder(data_folder)

    for img_path, annotations in img_to_annotations.items():
        objects   = annotations_to_objs(annotations)
        file_info = extract_file_info(img_path)
        file_info.update([('objects', objects)])
        files.append(file_info)
        print('=', end='',flush=True)


    return files

def render_voc_xml(input_folder, output_folder, template_path, template_name):
    """Renders VOC format xml files in output folder from xml files in
    input_folder.

    Parameters
    ----------
    input_folder : str
        Path to input data folder in PKLot format.
    output_folder : str
        Path to output data folder in VOC format..
    template_path : str
        Path to template folder.
    template_name : str
        Template file name.


    """
    with open(os.path.join(template_path, template_name), mode='r') as file:
        template_data = file.read()

    template = jinja2.Template(template_data)
    files    = extract_voc_info_from_folder(input_folder)

    if not os.path.exists(output_folder):
        os.mkdir(output_folder)

    for file in files:
        output = template.render(**file)
        output_file = os.path.splitext(os.path.basename(file['filename']))[0] + '.xml'

        with open(os.path.join(output_folder, output_file), 'w') as file:
            file.write(output)




if __name__=='__main__':
    render_voc_xml(args.input, args.output, args.template_folder, args.template_name)
