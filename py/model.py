import os
suma = 0
for file in os.listdir("images9__1"):
    if file.endswith(".png"):
        print(os.path.join("/mydir", file))
    