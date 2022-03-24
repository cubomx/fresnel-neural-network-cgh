from turtle import circle
import numpy as np
from random import randint, random
import cv2

RAND_MAX = 32767
maskSize = (25, 25)
mapMin = np.zeros(maskSize) - 1
counter = 0
randomImages = 50

class ImageData:
    def __init__(self, size=(1024,1024,1), circleSize = 5, imageSize = 625, 
     imageDensity = 0.02, circles=5):
        self.size = size
        self.circleSize = circleSize
        self.imageSize = imageSize
        self.lowerRange = self.getLowerRange()
        self.upperRange = -self.imageSize / 2
        self.imageDensity = imageDensity
        self.circles = circles

    def getLowerRange(self):
        return self.circleSize[0] - self.imageSize - self.imageSize / 2


class Image:
    def randomMatrix(imageData: ImageData):
        global mapMin, counter, maskSize
        map = np.zeros(maskSize)
        # generate a blank image
        random = np.zeros(imageData.size, dtype=np.uint8)
        # generate a random distribution
        dist = np.random.uniform(0, maskSize[0], size=100)
        circleSize = imageData.circleSize
        minusCircleSize = circleSize - 1
        
        for index in range(imageData.circles):
            toContinue = True
            while toContinue:
                
                # generate the random points within the mask
                randCol = int(dist[randint(0,25)])
                randRow = int(dist[randint(0,25)])
                X = int( circleSize + randint(0, 25)  / \
                    (randint(0, 25) (minusCircleSize - circleSize)))
                Y = int( circleSize + randint(0, 25)  / \
                    (randint(0, 25) (minusCircleSize - circleSize)))

                if mapMin[randRow][randCol] == mapMin:
                    mapMin[randRow][randCol] += 1
                    toContinue = False
                    cv2.circle(random, (200 + randRow * 25 + X, 200 + randCol * 25 + Y), circleSize, 255, -1)
                    counter += 1
                else:
                    toContinue = True

                if counter % imageData.imageSize == 0:
                    mapMin += 1
        return random

        