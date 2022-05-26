
from lib2to3.pgen2.tokenize import untokenize
import cv2
files = []
import os
from model import unet
import tensorflow as tf


def divide_images(isTraining, directory):
    type_subset = 'validation'
    if isTraining:
        type_subset = 'training'

    result = tf.keras.utils.image_dataset_from_directory(
    directory,
    labels="inferred",
    label_mode="int",
    class_names=None,
    color_mode="grayscale",
    batch_size=32,
    image_size=(512, 512),
    shuffle=True,
    seed=10,
    validation_split=0.2,
    subset=type_subset
    )

    return result

directory = "images" 


training = divide_images(True, directory)
#validation = divide_images(False, directory)
training = training.prefetch(buffer_size=tf.data.experimental.AUTOTUNE)

model = unet()

#model.fit_generator(myGene,steps_per_epoch=300,epochs=1)

model.fit(training, batch_size=32, epochs=5)
