# Preprocessing
To convert PKLot to VOC format. Use pklot2voc.py as follows:
```python
usage: pklot2voc.py [-h] -I Input data folder -O Output data folder
                    [-TF Template folder] [-TN Template file]

Script to convert xml annotation files from PKLot format to PASCAL VOC format.

optional arguments:
  -h, --help            show this help message and exit
  -I Input data folder, --input Input data folder
                        Path to input data folder in PKLot format.
  -O Output data folder, --output Output data folder
                        Path to output data folder in VOC format.
  -TF Template folder, --template_folder Template folder
                        Path to template folder.
  -TN Template file, --template_name Template file
                        Name of template file.
```
