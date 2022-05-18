import numpy as np
from random import randint
from math import ceil
import cv2

class ImageData:
    def __init__(self, maskSize, cellSize, circleSize = 5, mapMin = 0, imageDensity = 0.02, circleQuan = 0, size=(1024,1024,1) ):
        self.map = np.zeros(maskSize)
        self.size = size
        self.cellSize = cellSize
        self.circleSize = circleSize
        self.imageDensity = imageDensity
        self.circles = ceil(imageDensity * maskSize[0]*maskSize[1])
        self.maskSize = maskSize
        self.counter = 0
        self.mapMin = mapMin
        self.circleQuan = circleQuan
        self.start_point = int( (self.size[0] - cellSize[0] * self.maskSize[0]) / 2)


class Image:
    def randomMatrix(imageData: ImageData):
        Map = imageData.map
        start_point = imageData.start_point
        circleQuan = imageData.circleQuan
        # generate a blank image
        img = np.zeros(imageData.size, dtype=np.uint8)
        # generate random distribution for both axes
        
        # init index values to loop around distributions
        circleSize = imageData.circleSize
        cellSize = imageData.cellSize
        # generate a distribution from 0 t0 1 for moving around the cell
        dist_coord = np.random.uniform(0, 1.0, 20)
        
        for _ in range(imageData.circles):
            distX = np.random.uniform(0, imageData.maskSize[0], size=imageData.maskSize[0]*4*circleQuan)
            distY = np.random.uniform(0, imageData.maskSize[1], size=imageData.maskSize[1]*4*circleQuan)

            idX = 0
            idY = 0
            while True:
                
                # get the cell in which we are going to draw the circle
                randCol = int(distX[idX])
                randRow = int(distY[idY])
                # get the center coords inside the cell
                X = int( circleSize + dist_coord[randint(0,19)]  * (cellSize[0] - circleSize))
                Y = int( circleSize + dist_coord[randint(0,19)]  * (cellSize[0] - circleSize))
                
               
                # draw one circle per cell
                if imageData.map[randCol][randRow] <= imageData.mapMin:
                    
                    # making unavailable this cell
                    imageData.map[randCol][randRow] += 1
                    # p0 + range(0-24) * 25 + ?
                    x = start_point + randRow * cellSize[0] + X
                    y = start_point + randCol * cellSize[0] + Y
                    
                    # draw a circle
                    cv2.circle(img, (x, y), circleSize, 255, -1)
                    imageData.counter += 1
                    break
                # verifying if all cells have been used
                if imageData.counter >= imageData.maskSize[0]*imageData.maskSize[1]*circleQuan:
                    break

                idX += 1
                idY = idX

                if idX >= len(distX) - 1:
                    print("siuuuu")
                    return (Map, None, False)

        return (img, imageData.counter, True)
