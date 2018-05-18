"""
Brendan Sheehy (bsheehy@umd.edu)
ENEE 408I/0101
30th April 2018

load_cnn.py

A simple script for playing with a classifier (trained in cnn.py) inside the 
Python interpreter.  The intended use for this file is simply as follows:
	python
	>>> execfile('load_cnn.py')
	[INFO] Classifier loaded
	>>> classify('data/verify/fubar.jpg')
	Prone: This dude's toast
	>>>
	
etc. ad infinitum
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
from keras.models import load_model

def label(str):
	tst_img = image.load_img(str, target_size = (64, 64))
	tst_img = image.img_to_array(tst_img)
	tst_img = np.expand_dims(tst_img, axis = 0)
	rc = cnn.predict(tst_img)
	
	if rc[0][0] == 1:
		print('Standing: He\'ll probably be fine')
	else:
		print('Prone: Ths dude\'s toast')

cnn = load_model('fall.h5')
print('[INFO] Classifier loaded')
