import cv2
from utilities import Utilities
from image import Image, ImageData

myData = ImageData(maskSize=(25,25), cellSize=(20, 20))

num_Images = 50
for i in range(num_Images):
    randomName =  Utilities.generateRandomString(10)
    new_image, counter = Image.randomMatrix(myData)
    if i == 49:
        print(counter)
    cv2.imwrite("images/" + randomName + '.png', new_image)