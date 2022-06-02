
from model import unet
import tensorflow as tf
import numpy as np
import os
import cv2
from sklearn.model_selection import train_test_split
from glob import glob

from model2 import build_model



def read_image(file):
    img = cv2.imread(file, 0)
    img = img.reshape((img.shape[0], img.shape[1],1))
    return img

def create_mask(file1, file2):
    img1 = read_image(file1)
    img2 = read_image(file2)
    mask = np.concatenate((img1, img2), axis=2)
    return mask

def create_img(file):
    img = read_image(file)
    return img

def load_data(baseDir, directory, subfolder, split=0.1):
    

    images = glob(os.path.join(baseDir, subfolder))
    pre_masks = glob(os.path.join(directory, subfolder))
    masks = []

    total_size = len(images)
    valid_size = int(split * total_size)
    test_size = int(split * total_size)

    for x in range(0, len(pre_masks), 2):
        masks.append([pre_masks[x], pre_masks[x+1]])

    train_x, valid_x = train_test_split(images, test_size=valid_size, random_state=42)
    train_y, valid_y = train_test_split(masks, test_size=valid_size, random_state=42)

    train_x, test_x = train_test_split(train_x, test_size=test_size, random_state=42)
    train_y, test_y = train_test_split(train_y, test_size=test_size, random_state=42)

    return (train_x, train_y), (valid_x, valid_y), (test_x, test_y)


def preprocess(x, y):
    def f(x,y):
        y = create_mask(y[0].decode(), y[1].decode())
        x = create_img(x.decode())
        
        return x, y

    images, masks = tf.numpy_function(f, [x, y], [tf.uint8, tf.uint8,])
    images.set_shape([512, 512, 1])
    masks.set_shape([512, 512, 2])

    return images, masks

def tf_dataset(x, y, batch=8):
    dataset = tf.data.Dataset.from_tensor_slices((x, y))
    #dataset = dataset.shuffle(buffer_size=1000)
    dataset = dataset.map(preprocess)
    dataset = dataset.batch(batch)
    #dataset = dataset.prefetch(2)
    dataset = dataset.repeat()
    return dataset

## Hyperparameters
batch = 2
lr = 1e-4
epochs = 5
directory = '../Fresnel/holos'
baseDir = 'images'



(train_x, train_y), (valid_x, valid_y), (test_x, test_y) = load_data(baseDir, directory,  'cropped3__2/*')


train_dataset = tf_dataset(train_x, train_y)
valid_dataset = tf_dataset(valid_x, valid_y)


model = unet()

train_steps = len(train_x)//batch
valid_steps = len(valid_x)//batch

if len(train_x) % batch != 0:
    train_steps += 1
if len(valid_x) % batch != 0:
    valid_steps += 1



model = build_model()

model.compile(loss="mean_squared_error", optimizer='adam', metrics=["accuracy"])

model.fit(train_dataset,
        validation_data=valid_dataset,
        epochs=epochs,
        steps_per_epoch=train_steps,
        validation_steps=valid_steps,
        batch_size=2)