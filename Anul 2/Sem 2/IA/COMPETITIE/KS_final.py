import numpy as np
import cv2
from tensorflow.keras.layers import Conv2D, MaxPooling2D, Flatten, Dense, Dropout
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.wrappers.scikit_learn import KerasClassifier
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import f1_score, precision_recall_fscore_support, confusion_matrix
from sklearn.pipeline import Pipeline
from tensorflow.keras import layers, models, losses, optimizers
from sklearn.model_selection import GridSearchCV
from tensorflow.keras import activations, Sequential
from tensorflow.keras.layers import Dropout
import tensorflow as tf

#id-uri - validation, train, test
file=open("/kaggle/input/unibuc-brain-ad/data/train_labels.txt","r")
idTrain=[]
labelTrain=[]
for line in file:
    idTrain.append(line.split(",")[0])
    labelTrain.append(line.split(",")[1])
    #prelucrare
    #salvare
idTrain.pop(0)
labelTrain.pop(0)
file.close()

#etichete
file = open("/kaggle/input/unibuc-brain-ad/data/validation_labels.txt","r")
idValidation=[]
labelValidation=[]
for line in file:
    idValidation.append(line.split(",")[0])
    labelValidation.append(line.split(",")[1])
    #prelucrare
    #salvare
idValidation.pop(0)
labelValidation.pop(0)
file.close()

file = open("/kaggle/input/unibuc-brain-ad/data/sample_submission.txt","r")
idSubmission=[]
for line in file:
    idSubmission.append(line.split(",")[0])
    #prelucrare
    #salvare
idSubmission.pop(0)
file.close()

imgsTrain = []
for id in idTrain:
    path = r"/kaggle/input/unibuc-brain-ad/data/data/" + id + ".png"
    img = cv2.imread(path, cv2.IMREAD_GRAYSCALE)
    #img = cv2.resize(img, (56, 56))
    #img = tf.image.resize(img, [56, 56])
    imgsTrain.append(np.array(img)) #normalizare

imgsValidation = []
for id in idValidation:
    path = r"/kaggle/input/unibuc-brain-ad/data/data/" + id + ".png"
    img = cv2.imread(path, cv2.IMREAD_GRAYSCALE)
    #img = cv2.resize(img, (56, 56))
    #img = tf.image.resize(img, [56, 56])
    imgsValidation.append(np.array(img)) #normalizare

imgsSubmission = []
for id in idSubmission:
    path = r"/kaggle/input/unibuc-brain-ad/data/data/" + id + ".png"
    img = cv2.imread(path, cv2.IMREAD_GRAYSCALE)
    #img = cv2.resize(img, (56, 56))
    #img = tf.image.resize(img, [56, 56])
    imgsSubmission.append(np.array(img)) #normalizare

labelTrain = np.array(labelTrain, dtype="float64")
labelValidation = np.array(labelValidation, dtype="float64")

imgsTrain = np.array(imgsTrain)
imgsValidation = np.array(imgsValidation)
imgsSubmission = np.array(imgsSubmission)

imgsTrain=np.concatenate((imgsTrain, imgsValidation), axis=0)
labelTrain=np.concatenate((labelTrain, labelValidation), axis=0)

model = Sequential()
model.add(layers.Rescaling(scale=1./255, input_shape=(224, 224, 1)))

model.add(Conv2D(32, kernel_size=(5, 5), activation='relu'))
model.add(MaxPooling2D(pool_size=(3, 3)))
model.add(Dropout(0.3))

model.add(Conv2D(32, kernel_size=(5, 5), activation='relu'))
model.add(MaxPooling2D(pool_size=(3, 3)))
model.add(Dropout(0.2))

model.add(Conv2D(64, kernel_size=(5, 5), activation='relu'))
model.add(MaxPooling2D(pool_size=(3, 3)))
model.add(Dropout(0.3))

model.add(Flatten())
model.add(Dense(8, activation='relu'))
model.add(Dense(1, activation='sigmoid'))

optimizer = Adam(learning_rate=0.0001, amsgrad=True)
model.compile(optimizer=optimizer, loss='binary_crossentropy', metrics=['accuracy'])

model.fit(imgsTrain, labelTrain, epochs=20)
rez = model.predict(imgsSubmission)
binary_predictions = (rez > 0.45).astype(int)

predicted = np.round(rez).flatten()

fopen = open("/kaggle/working/submissionKS.csv","w")
fopen.write("id,class")
fopen.write("\n")
for i in range(len(idSubmission)):
    fopen.write(idSubmission[i])
    fopen.write(",")
    fopen.write(str(binary_predictions[i][0]))
    fopen.write("\n")
fopen.close()