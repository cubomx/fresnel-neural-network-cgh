
import cv2
files = []
import os


sizes = [3, 5, 9]
quantities = [1, 2, 3]

def get_images(folder_name, images):
    for file in os.listdir(folder_name):
        if file.endswith(".png"):
            filename = os.path.join(folder_name, file)
            images.append(cv2.imread(filename, 0))

    return images

prefix = 'cropped'
images = []
for size in sizes:
    for quantity in quantities:
        images = get_images(prefix + str(size) +  "__" + str(quantity), images)


print(len(images))








