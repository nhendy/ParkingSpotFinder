import argparse
from controller import Controller
import logging

def init_argparser():
    parser = argparse.ArgumentParser(description='None')  #TODO
    group  = parser.add_mutually_exclusive_group()
    group.add_argument('--url', '-u', dest= 'stream_url',
                        help='URL of the live video stream.')
    group.add_argument('--path', '-p', dest= 'video_path',
                        help='Path of the video file.')
    parser.add_argument("--data",
                        dest="data_file",
                        required=True,
                        help="Data file to store contours.")

    return parser.parse_args()





def main():
    logging.basicConfig(format='%(asctime)s - %(message)s', datefmt='%d-%b-%y %H:%M:%S', level=logging.INFO)
    args = init_argparser()
    if not (args.stream_url or args.video_path):
        raise ValueError('Either URL or path to video file need to be provided.')

    controller = Controller(**vars(args))
    controller.run()





if __name__ == "__main__":
    main()

