import string
from random import choices

class Utilities:
    def generateRandomString(num_chars):
        return ''.join(choices(string.ascii_uppercase + string.digits, k=num_chars))

    def gen():
        return choices([0, 3, 1, 2])
