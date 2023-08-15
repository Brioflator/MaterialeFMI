import numpy as np
import cv2
from sklearn.ensemble import RandomForestClassifier

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
    img = cv2.resize(img, (64,64)) # redimensionare imagine la 64x64
    imgsTrain.append(np.array(img).flatten()) # transformare in vector 1D

imgsValidation = []
for id in idValidation:
    path = r"C:\\Users\\bales\\OneDrive\\Facultate\\Anul 2\\Sem 2\\IA\\COMPETITIE\\data\\" + id + ".png"
    img = cv2.imread(path) # citire imagine
    img = cv2.resize(img, (64, 64)) # redimensionare imagine la 64x64
    imgsValidation.append(np.array(img).flatten()) # transformare in vector 1D

imgsSubmission = []
for id in idSubmission:
    path = r"C:\\Users\\bales\\OneDrive\\Facultate\\Anul 2\\Sem 2\\IA\\COMPETITIE\\data\\" + id + ".png"
    img = cv2.imread(path) # citire imagine
    img = cv2.resize(img, (64, 64)) # redimensionare imagine la 64x64
    imgsSubmission.append(np.array(img).flatten()) # transformare in vector 1D


# acc= np.mean(predictions == labelValidation)
# print(acc)

# combinare train si validation
imgsCombined = imgsTrain + imgsValidation
labelsCombined = labelTrain + labelValidation

# antrenare

# parametrul n_estimators=200 face ca sa se antreneze 200 de arbori
# parametrul max_features=0.5 face ca la fiecare nod sa se ia 50% din feature-uri
# parametrul max_depth=20 face ca la fiecare nod sa se ia 20 de nivele
# parametrul n_jobs=-1 face ca antrenarea sa se faca pe toate nucleele procesorului
clf = RandomForestClassifier(n_estimators=200, max_features=0.5, max_depth=20, n_jobs=-1)
clf = clf.fit(imgsCombined, labelsCombined)

# afisare predictii
fopen = open("../submissionRF.csv", "w")
fopen.write("id,class")
fopen.write("\n")
for i in range(len(idSubmission)):
    fopen.write(idSubmission[i])
    fopen.write(",")
    fopen.write(str(clf.predict([imgsSubmission[i]]))[2:3]) # [2:3] ia doar prima cifra din predictie (0 sau 1)
    fopen.write("\n")
fopen.close()

