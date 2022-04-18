import numpy as np
from random import randint
from math import ceil
import cv2

map = None
minimio = 100000
class ImageData:
    def __init__(self, maskSize, cellSize, size=(1024,1024,1), circleSize = 5,imageDensity = 0.02):
        global map
        self.map = np.zeros(maskSize)
        self.size = size
        self.cellSize = cellSize
        self.circleSize = circleSize
        self.imageDensity = imageDensity
        self.circles = ceil(imageDensity * maskSize[0]*maskSize[1])
        self.maskSize = maskSize
        self.counter = 0
        self.mapMin = 0


class Image:
    def randomMatrix(imageData: ImageData):
        
        global minimio
        # generate a blank image
        img = np.zeros(imageData.size, dtype=np.uint8)
        # generate a random distribution
        dist = np.random.uniform(0, imageData.maskSize[0], size=100)
        circleSize = imageData.circleSize
        cellSize = imageData.cellSize
        # generate a distribution from 0 t0 1 for moving around the cell
        dist_coord = np.random.uniform(0, 1.0, 20)
        for _ in range(imageData.circles):
            while True:
                
                # get the cell in which we are going to draw the circle
                randCol = int(dist[randint(0,99)])
                randRow = int(dist[randint(0,99)])
                # get the center coords inside the cell
                X = int( circleSize + dist_coord[randint(0,19)]  * (cellSize[0] - circleSize))
                Y = int( circleSize + dist_coord[randint(0,19)]  * (cellSize[0] - circleSize))

                # the start from both axes (upper right corner)
                ## height - ( Cell.Height * Cell.Num  / 2)
                start_point = int( (imageData.size[0] - cellSize[0] * imageData.maskSize[0]) / 2)
                
                
                # draw one circle per cell
                if imageData.map[randCol][randRow] == 0:
                    
                    # making unavailable this cell
                    imageData.map[randCol][randRow] = 1
                    # p0 + range(0-24) * 25 + ?
                    x = start_point + randRow * cellSize[0] + X
                    y = start_point + randCol * cellSize[0] + Y
                    
                    minimio = min(minimio, x)
                    if imageData.counter > 610:
                        print(minimio)
                    # draw a circle
                    cv2.circle(img, (x, y), circleSize, 255, -1)
                    imageData.counter += 1
                    break
                # verifying if all cells have been used
                if imageData.counter >= imageData.maskSize[0]*imageData.maskSize[1]:
                    break
        return (img, imageData.counter)
