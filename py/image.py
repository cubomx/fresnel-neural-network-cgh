import numpy as np

class ImageData:
    def __init__(self, size=(1024,1024,1), circleSize = 5, imageSize = 625, 
    randomImages = 50, imageDensity = 0.02, maskSize = (25, 25), mapMin=0, counter=0):
        self.size = size
        self.circleSize = circleSize
        self.imageSize = imageSize
        self.randomImages = randomImages
        self.lowerRange = self.getLowerRange()
        self.upperRange = -self.imageSize / 2
        self.imageDensity = imageDensity
        self.maskSize = maskSize
        self.mapMin = mapMin
        self.counter = counter

    def getLowerRange(self):
        return self.circleSize[0] - self.imageSize - self.imageSize / 2


class Image:
    def randomMatrix(imageData: ImageData):
        random = np.zeros(imageData.size, dtype=np.ui)
        