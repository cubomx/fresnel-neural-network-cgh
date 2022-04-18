import string
from random import choices
import os
import shutil

class Utilities:
    def generateRandomString(num_chars):
        return ''.join(choices(string.ascii_uppercase + string.digits, k=num_chars))

    def gen():
        return choices([0, 3, 1, 2])

    def clean(removeFolder, nameFolder, createFolder):
        if removeFolder:
            if os.path.exists(nameFolder):
                shutil.rmtree(nameFolder)
            if createFolder:
                os.mkdir(nameFolder)