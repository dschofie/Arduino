"""
Brendan Sheehy (bsheehy@umd.edu)
ENEE 408I/0101
30th April 2018

cnn.py

Trains a simple image classifier using a convolutional neural network with one
hidden layer.  By default, it looks for data in the following directories:
	[this directory]/data/train
	[this directory]/data/test
"""

import numpy as np
from keras.models import Sequential
from keras.models import load_model
from keras.layers import Conv2D
from keras.layers import MaxPooling2D
from keras.layers import Flatten
from keras.layers import Dense
from keras.preprocessing.image import ImageDataGenerator
from keras.preprocessing import image

cnn = Sequential()
cnn.add(Conv2D(32, (3, 3), input_shape = (64, 64, 3), activation = 'relu'))
cnn.add(MaxPooling2D(pool_size = (2, 2)))
cnn.add(Conv2D(32, (3, 3), activation = 'relu'))
cnn.add(MaxPooling2D(pool_size = (2, 2)))
cnn.add(Flatten())
cnn.add(Dense(units = 128, activation = 'relu'))
cnn.add(Dense(units = 1, activation = 'sigmoid'))
print('[INFO] Configured convolutional network')

cnn.compile(optimizer = 'adam', loss = 'binary_crossentropy', \
	metrics = ['accuracy'])
print('[INFO] Compiled network')

train_datagen = ImageDataGenerator(rescale = 1./255, shear_range = 0.2, \
	zoom_range = 0.2, horizontal_flip = True)
test_datagen = ImageDataGenerator(rescale = 1./255)
training_set = train_datagen.flow_from_directory('data/train', \
	target_size = (64, 64), batch_size = 32, class_mode = 'binary')
test_set = test_datagen.flow_from_directory('data/test', \
	target_size = (64, 64), batch_size = 32, class_mode = 'binary')

"""
You'll need to change steps_per_epoch and validation_steps to fit the size of 
your available training set.  Fiddle with the number of epochs at your own 
leisure; I'm pretty sure the library call auto-aborts if it detects the 
classifier starting to overfit after the end of an epoch.
"""
cnn.fit_generator(training_set, steps_per_epoch = 850, epochs = 25, \
	validation_data = test_set, validation_steps = 250)
print('[INFO] Trained network')

cnn.save('fall.h5')
print('[INFO] Saved network; all done.')
