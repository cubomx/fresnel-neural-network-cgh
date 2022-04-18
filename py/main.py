import cv2
from utilities import Utilities
from image import Image, ImageData

Utilities.clean(True, "images/", True)


myData = ImageData(maskSize=(25,25), cellSize=(20, 20))

num_circles = myData.maskSize[0] * myData.maskSize[1]
circles_perImg = myData.circles
num_Images = 50
for i in range(num_Images):
    # check if sufficient missing circles to complete a image
    if num_circles - myData.counter >= circles_perImg:
        randomName =  Utilities.generateRandomString(10)
        new_image, counter = Image.randomMatrix(myData)

        if i == 49:
            print(counter)
        cv2.imwrite("images/" + randomName + '.png', new_image)
    else:
        break