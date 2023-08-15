from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize
# The following program removes stop words from a piece of text:
example_sent = """This is a sample sentence,
				showing off the stop words filtration."""

stop_words = set(stopwords.words('english'))

word_tokens = word_tokenize(example_sent)
# converts the words in word_tokens to lower case and then checks whether
#they are present in stop_words or not
filtered_sentence = [w for w in word_tokens if not w.lower() in stop_words]
#with no lower case conversion
filtered_sentence = []


# Performing the Stopwords operations in a file
#
# In the code below, text.txt is the original input file in which stopwords are to be removed.
# filteredtext.txt is the output file.
import io
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize

# word_tokenize accepts
# a string as an input, not a file.
stop_words = set(stopwords.words('english'))
file1 = open("text.txt")

# Use this to read file content as a stream:
line = file1.read()
words = line.split()
for r in words:
	if not r in stop_words:
		appendFile = open('filteredtext.txt','a')
		appendFile.write(" "+r)
		appendFile.close()


for w in word_tokens:
	if w not in stop_words:
		filtered_sentence.append(w)

print(word_tokens)
print(filtered_sentence)

# Tokenization
# import the existing word and sentence tokenizing
# libraries
import nltk
from nltk.tokenize import sent_tokenize, word_tokenize

text = "Natural language processing (NLP) is a field " + \
       "of computer science, artificial intelligence " + \
       "and computational linguistics concerned with " + \
       "the interactions between computers and human " + \
       "(natural) languages, and, in particular, " + \
       "concerned with programming computers to " + \
       "fruitfully process large natural language " + \
       "corpora. Challenges in natural language " + \
       "processing frequently involve natural " + \
       "language understanding, natural language" + \
       "generation frequently from formal, machine" + \
       "-readable logical forms), connecting language " + \
       "and machine perception, managing human-" + \
       "computer dialog systems, or some combination " + \
       "thereof."

print(sent_tokenize(text))
print(word_tokenize(text))

# Importing Libraries
import numpy as np
import pandas as pd

# Import dataset
dataset = pd.read_csv('Restaurant_Reviews.tsv', delimiter = '\t')

# library to clean data
import re

# Natural Language Tool Kit
import nltk

nltk.download('stopwords')

# to remove stopword
from nltk.corpus import stopwords

# for Stemming propose
from nltk.stem.porter import PorterStemmer

# Initialize empty array
# to append clean text
corpus = []

# 1000 (reviews) rows to clean
for i in range(0, 1000):
    # column : "Review", row ith
    review = re.sub('[^a-zA-Z]', ' ', dataset['Review'][i])

    # Creating the Bag of Words model
    from sklearn.feature_extraction.text import CountVectorizer

    # To extract max 1500 feature.
    # "max_features" is attribute to
    # experiment with to get better results
    cv = CountVectorizer(max_features=1500)

    # X contains corpus (dependent variable)
    X = cv.fit_transform(corpus).toarray()

    # y contains answers if review
    # is positive or negative
    y = dataset.iloc[:, 1].values

    # convert all cases to lower cases
    review = review.lower()

    # split to array(default delimiter is " ")
    review = review.split()

    # creating PorterStemmer object to
    # take main stem of each word
    ps = PorterStemmer()

    # loop for stemming each word
    # in string array at ith row
    review = [ps.stem(word) for word in review
              if not word in set(stopwords.words('english'))]

    # rejoin all string array elements
    # to create back into a string
    review = ' '.join(review)

    # append each string to create
    # array of clean text
    corpus.append(review)

# Splitting the dataset into
# the Training set and Test set
from sklearn.cross_validation import train_test_split

# experiment with "test_size"
# to get better results
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = 0.25)

# Fitting Random Forest Classification
# to the Training set
from sklearn.ensemble import RandomForestClassifier

# n_estimators can be said as number of
# trees, experiment with n_estimators
# to get better results
model = RandomForestClassifier(n_estimators=501,
                               criterion='entropy')

model.fit(X_train, y_train)
# Predicting the Test set results
y_pred = model.predict(X_test)

y_pred

