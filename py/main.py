from hmac import new
import cv2
from utilities import Utilities
from image import Image, ImageData
from copy import deepcopy as dp
import numpy as np

Utilities.clean(True, "images/", True)


myData = ImageData(maskSize=(25,25), cellSize=(20, 20))

num_circles = myData.maskSize[0] * myData.maskSize[1]
circles_perImg = myData.circles
num_Images = 50
counti = 0
for i in range(num_Images):
    # check if sufficient missing circles to complete a image
    if num_circles - myData.counter >= circles_perImg:
         
        randomName =  Utilities.generateRandomString(10)
        # try until success
        counter = 0
        new_image = None
        while True:
            Map, Counter = myData.map.copy(), dp(myData.counter)
            new_image, counter, isCorrect = Image.randomMatrix(myData)
            if isCorrect:
                break
            else:
                myData.map = Map
                myData.counter = Counter
        
        if counter is not None:
            counti = max(counti, counter)
        
        if counter >= num_circles * .95 * (myData.mapMin + 1):
            myData.mapMin += 1

        if i == 49:
            print(counti)
        cv2.imwrite("images/" + randomName + '.png', new_image)
    else:
        break