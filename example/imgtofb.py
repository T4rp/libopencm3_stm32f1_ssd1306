#!/bin/python3

import argparse
from PIL import Image
import numpy as np
import math
import os


def image_to_framebuffer(image_path, dither):
    im = Image.open(image_path)

    image_name = os.path.splitext(os.path.basename(image_path))[0]

    width = im.width
    height = im.height

    aspect_ratio = width / height

    if aspect_ratio > 2:
        width = 128
        height = width / aspect_ratio
    else:
        height = 64
        width = height * aspect_ratio

    im = im.resize((int(width), int(height)))

    dither_type = Image.Dither.NONE

    if dither:
        dither_type = Image.Dither.FLOYDSTEINBERG

    im = im.convert("1", dither=dither_type)

    new_img = Image.new("L", (128, 64))
    new_img.paste(im)

    data = [0] * 1024

    for page_i in range(8):
        for byte_i in range(128):
            byte = 0
            for i in range(8):
                page_x = 0
                page_y = (page_i + 1) * 8
                x = page_x + byte_i
                y = page_y - i - 1

                pix = new_img.getpixel((x, y))
                if pix > 127.0:
                    byte = byte << 1 | 1
                else:
                    byte = byte << 1 | 0

            data[page_i * 128 + byte_i] = byte

    header_flag = "FB_IMAGE_" + image_name

    header = ""

    header += "#ifndef " + header_flag + "_H\n"
    header += "#define " + header_flag + "_H\n"
    header += "\n"
    header += "const char fb_image_data_"
    header += image_name
    header += "[1024] = {"

    for b in data:
        b = int(b)
        header += str(b)
        header += ","

    header += "};\n"
    header += "\n"
    header += "#endif"

    print(header)

    return new_img


def main():
    parser = argparse.ArgumentParser(prog="imgtofb")
    parser.add_argument("image_path")
    parser.add_argument("-s", "--show", action="store_true")
    parser.add_argument("-d", "--dither", action="store_true")

    args = parser.parse_args()

    im = image_to_framebuffer(args.image_path, args.dither)
    if args.show:
        im.show()


if __name__ == "__main__":
    main()
