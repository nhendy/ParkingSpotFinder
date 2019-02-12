#!/usr/bin/env python3

import os
import numpy as np
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('-I', '--input', help= "Path to input data folder that has image/xml files.",
                    type=str, metavar= "Input data folder", required=True)
parser.add_argument('-S', '--split', help= "Validation split ratio.",
                     type= float, metavar= "split in (0, 1)", required=True)
args = parser.parse_args()

def split_data_in_folder(data_folder, valid_split):
    """Creates a .txt file containing which files would in validation set and which
    would be in the training set.

    Parameters
    ----------
    data_folder : str
        Name of the folder containing the xml/img files.
    valid_split : str
        Name of the folder containing the xml/img files.

    """
    path    = os.path.abspath(data_folder)
    files   = os.listdir(path.rstrip(os.sep))
    output_path = os.path.join(os.path.dirname(path), 'ImageSets', 'Main')
    if not os.path.exists(output_path):
        os.makedirs(output_path)

    TRAINOUT = open(os.path.join(output_path, 'train.txt'), 'w')
    VALIDOUT = open(os.path.join(output_path, 'valid.txt'), 'w')

    indices = list(range(len(files)))
    dataset_size = len(indices)

    split_indx = int(np.floor(valid_split * dataset_size))
    np.random.shuffle(indices)

    validation_indices, training_indices = indices[:split_indx], indices[split_indx:]


    for idx in validation_indices:
        file = files[idx]
        VALIDOUT.write(os.path.splitext(file)[0] + '\n')

    for idx in training_indices:
        file = files[idx]
        TRAINOUT.write(os.path.splitext(file)[0] + '\n')


    VALIDOUT.close()
    TRAINOUT.close()

if __name__ == "__main__":
    if 0 > args.split  or 1 < args.split :
        raise ValueError('Split must be a fraction between 0 and 1.')

    split_data_in_folder(args.input, args.split)
