import numpy as np
import cv2
from sklearn.naive_bayes import GaussianNB

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
    img = cv2.imread(path) # citire imagine
    img = cv2.resize(img, (64,64))  # redimensionare imagini la 64x64
    imgsTrain.append(np.array(img).flatten()) # transformare in vector 1D

imgsValidation = []
for id in idValidation:
    path = r"C:\\Users\\bales\\OneDrive\\Facultate\\Anul 2\\Sem 2\\IA\\COMPETITIE\\data\\" + id + ".png"
    img = cv2.imread(path)  # citire imagine
    img = cv2.resize(img, (64, 64)) # redimensionare imagini la 64x64
    imgsValidation.append(np.array(img).flatten()) # transformare in vector 1D

imgsSubmission = []
for id in idSubmission:
    path = r"C:\\Users\\bales\\OneDrive\\Facultate\\Anul 2\\Sem 2\\IA\\COMPETITIE\\data\\" + id + ".png"
    img = cv2.imread(path) # citire imagine
    img = cv2.resize(img, (64, 64)) # redimensionare imagini la 64x64
    imgsSubmission.append(np.array(img).flatten()) # transformare in vector 1D


# acc= np.mean(predictions == labelValidation)
# print(acc)

# combinare date de antrenare si validare
imgsCombined = imgsTrain + imgsValidation
labelsCombined = labelTrain + labelValidation

# antrenare
gnb = GaussianNB()
gnb.fit(imgsCombined, labelsCombined)


fopen = open("../submissionGNB.csv", "w")
fopen.write("id,class")
fopen.write("\n")
predictions = gnb.predict(imgsSubmission) # predictii pentru datele de test (sample_submission)
for i in range(len(idSubmission)):
    fopen.write(idSubmission[i] + "," + str(predictions[i])) # scriere in fisier
fopen.close()

