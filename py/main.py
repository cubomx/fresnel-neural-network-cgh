from hmac import new
import cv2
from utilities import Utilities
from image import Image, ImageData
from copy import deepcopy as dp
import numpy as np

father_path = 'images/'
sizes = [3, 5, 9]
circlesQuantity = [1, 2, 3]
for circleQuan in circlesQuantity:
    print("hiho")
    for size in sizes:
        Utilities.clean(True, father_path + "images" + str(size) + "__" +  str(circleQuan) + "/", True)
        Utilities.clean(True, father_path + "cropped" + str(size) +  "__" +  str(circleQuan) + "/", True)

        myData = ImageData(maskSize=(25,25), cellSize=(20, 20), circleSize=size, 
        imageDensity=0.02*circleQuan, circleQuan=circleQuan, mapMin=circleQuan)

        num_Images = 50
        circles_perImg = myData.circles
        num_circles = num_Images *myData.circles
        
        counti = 0

        limit = int(myData.size[0] / 4)
        sizeX = myData.size[0]
        sizeY = myData.size[1]

        for i in range(num_Images):
            # check if sufficient missing circles to complete a image
            if num_circles - myData.counter >= circles_perImg:
                
                randomName =  Utilities.generateRandomString(16)
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
                
                if counter >= num_circles * .90 * (myData.mapMin + 1):
                    myData.mapMin += 1

                if i == 49:
                    print(counti)
                cv2.imwrite(father_path + "images" + str(size) +  "__" +  str(circleQuan) + "/" + randomName + '.png', new_image)
                # crop image
                
                cv2.imwrite(father_path + "cropped" + str(size) +  "__" +  str(circleQuan) + "/" + randomName + '.png', new_image[limit:sizeX-limit, limit:sizeY-limit])
            else:
                break
