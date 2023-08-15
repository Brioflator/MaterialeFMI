import numpy as np
import cv2
from tensorflow.keras.layers import Conv2D, MaxPooling2D, Flatten, Dense, Dropout
from tensorflow.keras.optimizers import Adam
from sklearn.metrics import f1_score, precision_recall_fscore_support
from tensorflow.keras import layers, models, losses, optimizers
from tensorflow.keras import activations, Sequential
from tensorflow.keras.layers import Dropout
import tensorflow as tf

#id-uri - validation, train, test
file=open("../train_labels.txt", "r")
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
file = open("../validation_labels.txt", "r")
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

file = open("../sample_submission.txt", "r")
idSubmission=[]
for line in file:
    idSubmission.append(line.split(",")[0])
    #prelucrare
    #salvare
idSubmission.pop(0)
file.close()

imgsTrain = []
for id in idTrain:
    path = r"C:\\Users\\bales\\OneDrive\\Facultate\\Anul 2\\Sem 2\\IA\\COMPETITIE\\data\\" + id + ".png"
    img = cv2.imread(path, cv2.IMREAD_GRAYSCALE) # transforma in alb-negru
    #img = cv2.resize(img, (56, 56))
    #img = tf.image.resize(img, [56, 56])
    imgsTrain.append(np.array(img)) # transform in numpy array

imgsValidation = []
for id in idValidation:
    path = r"C:\\Users\\bales\\OneDrive\\Facultate\\Anul 2\\Sem 2\\IA\\COMPETITIE\\data\\" + id + ".png"
    img = cv2.imread(path, cv2.IMREAD_GRAYSCALE) # transforma in alb-negru
    #img = cv2.resize(img, (56, 56))
    #img = tf.image.resize(img, [56, 56])
    imgsValidation.append(np.array(img)) # transform in numpy array

imgsSubmission = []
for id in idSubmission:
    path = r"C:\\Users\\bales\\OneDrive\\Facultate\\Anul 2\\Sem 2\\IA\\COMPETITIE\\data\\" + id + ".png"
    img = cv2.imread(path, cv2.IMREAD_GRAYSCALE) # transforma in alb-negru
    #img = cv2.resize(img, (56, 56))
    #img = tf.image.resize(img, [56, 56])
    imgsSubmission.append(np.array(img) ) # transform in numpy array

#transform in float64 pentru a nu avea probleme la antrenare
labelTrain = np.array(labelTrain, dtype="float64")
labelValidation = np.array(labelValidation, dtype="float64")

#transform in numpy array
imgsTrain = np.array(imgsTrain)
imgsValidation = np.array(imgsValidation)
imgsSubmission = np.array(imgsSubmission)

# concatenez datele de train si validation
imgsTrain=np.concatenate((imgsTrain, imgsValidation), axis=0)
labelTrain=np.concatenate((labelTrain, labelValidation), axis=0)

# creez modelul
model = Sequential() # modelul este o secventa de layere
model.add(layers.Rescaling(scale=1./255, input_shape=(224, 224, 1))) # normalizare

model.add(Conv2D(32, kernel_size=(5, 5), activation='relu')) # adaug o convolutie cu 32 de filtre de 5x5 si 'relu' ca functie de activare
model.add(MaxPooling2D(pool_size=(3, 3))) # adaug un max pooling cu 3x3
model.add(Dropout(0.3)) # adaug un dropout cu 0.3 ca probabilitate de a lasa neuronul activ

model.add(Conv2D(32, kernel_size=(5, 5), activation='relu'))
model.add(MaxPooling2D(pool_size=(3, 3)))
model.add(Dropout(0.2)) # adaug un dropout cu 0.2 ca probabilitate de a lasa neuronul activ

model.add(Conv2D(64, kernel_size=(5, 5), activation='relu')) # adaug o convolutie cu 64 de filtre de 5x5 si 'relu' ca functie de activare
model.add(MaxPooling2D(pool_size=(3, 3)))
model.add(Dropout(0.3))

model.add(Flatten()) # adaug flatten pentru a putea adauga layere dense
model.add(Dense(8, activation='relu')) # adaug o layer dense cu 8 neuroni si relu ca functie de activare
model.add(Dense(1, activation='sigmoid')) # adaug o layer dense cu 1 neuron si sigmoid ca functie de activare pentru a avea o valoare intre 0 si 1

# aleg optimizerul si learning rate-ul
optimizer = Adam(learning_rate=0.0001, amsgrad=True)

# compilez modelul cu optimizerul ales si loss-ul binary_crossentropy
model.compile(optimizer=optimizer, loss='binary_crossentropy', metrics=['accuracy'])

model.fit(imgsTrain, labelTrain, epochs=20) # antrenez modelul pe datele de train si validation cu 20 epoci
rez = model.predict(imgsSubmission) # fac predictii pe datele de test
binary_predictions = (rez > 0.45).astype(int) # transform rezultatele in 0 sau 1

# scriu rezultatele in fisierul submissionKS.csv
fopen = open("../submissionKS.csv", "w")
fopen.write("id,class")
fopen.write("\n")
for i in range(len(idSubmission)):
    fopen.write(idSubmission[i])
    fopen.write(",")
    fopen.write(str(binary_predictions[i][0]))
    fopen.write("\n")
fopen.close()