import numpy as np
import cv2
from sklearn import svm

# open trainLabels.npy
trainLabels = np.load("trainLabels.npy")
# open trainImages.npy
trainImages = np.load("trainImages.npy")
# open testImages.npy
testImages = np.load("testImages.npy")

# run svm
clf = svm.SVC()
clf.fit(trainImages, trainLabels)


predictions = clf.predict(testImages)

# write to file
fopen = open("submissionSVM.csv","w")
fopen.write("id,class")
fopen.write("\n")
for i in range(len(predictions)):
    fopen.write(str(i))
    fopen.write(",")
    fopen.write(str(predictions[i]))
    fopen.write("\n")
fopen.close()