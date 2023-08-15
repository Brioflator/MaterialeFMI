import numpy as np
import cv2
from sklearn import svm

#id-uri - validation, train, test
file=open("train_labels.txt","r")
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
file = open("validation_labels.txt","r")
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

file = open("sample_submission.txt","r")
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
    img = cv2.imread(path)
    img = cv2.resize(img, (64,64))
    imgsTrain.append(np.array(img).flatten())

imgsValidation = []
for id in idValidation:
    path = r"C:\\Users\\bales\\OneDrive\\Facultate\\Anul 2\\Sem 2\\IA\\COMPETITIE\\data\\" + id + ".png"
    img = cv2.imread(path)
    img = cv2.resize(img, (64, 64))
    imgsValidation.append(np.array(img).flatten())

imgsSubmission = []
for id in idSubmission:
    path = r"C:\\Users\\bales\\OneDrive\\Facultate\\Anul 2\\Sem 2\\IA\\COMPETITIE\\data\\" + id + ".png"
    img = cv2.imread(path)
    img = cv2.resize(img, (64, 64))
    imgsSubmission.append(np.array(img).flatten())


# acc= np.mean(predictions == labelValidation)
# print(acc)

imgsCombined = imgsTrain + imgsValidation
labelsCombined = labelTrain + labelValidation

clf = svm.SVC()
clf.fit(imgsCombined, labelsCombined)



fopen = open("submissionSVM.csv","w")
fopen.write("id,class")
fopen.write("\n")
predictions = clf.predict(imgsSubmission)
for i in range(len(idSubmission)):
    fopen.write(idSubmission[i])
    fopen.write(",")
    fopen.write(str(predictions[i]))

fopen.close()