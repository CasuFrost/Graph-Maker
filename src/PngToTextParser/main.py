# -*- coding: utf-8 -*-
"""
Created on Sat Mar 23 13:24:21 2024

@author: Chiara :)
"""

import images
import os

def project(folder_in: str, folder_out : str):
    for name in os.listdir(folder_in):
        fullname = folder_in + "\\"+ name
        generate_text(fullname, folder_out)

def generate_text(start_img: str, folder_out):
    imm = images.load_RGBA_notA(start_img)
    file_out = start_img.split("\\")
    file_out = file_out[1]
    file_out = file_out.split(".")
    file_out = folder_out + "\\" + file_out[0]+ ".txt"
    f = open(file_out, "w")
    for row in imm:
        for pixel in row:
            if pixel == (0,0,0):
                f.write("1")
            else:
                f.write("0")
        f.write("\n")
    f.close()
 
project("PngLetters", "PngText")
    