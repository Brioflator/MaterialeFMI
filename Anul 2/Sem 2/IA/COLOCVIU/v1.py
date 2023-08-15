import nltk
from nltk.tokenize import word_tokenize

# read the text file
with open('input.txt', 'r') as f:
    sentences = f.readlines()

# tokenize the sentences
tokenized_sentences = [word_tokenize(sentence.lower()) for sentence in sentences]

from sklearn.feature_extraction.text import CountVectorizer

# convert tokenized sentences to bag-of-words representation
vectorizer = CountVectorizer()
bow_representation = vectorizer.fit_transform([' '.join(tokens) for tokens in tokenized_sentences])


from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split

# read the labels for each sentence (assuming they are stored in a separate file)
with open('labels.txt', 'r') as f:
    labels = f.readlines()

# convert labels to binary values (0 or 1)
binary_labels = [1 if label.strip() == 'positive' else 0 for label in labels]

# split the data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(bow_representation, binary_labels, test_size=0.2)

# train the logistic regression model
clf = LogisticRegression()
clf.fit(X_train, y_train)

# evaluate the model on the testing set
accuracy = clf.score(X_test, y_test)
print('Accuracy: {}'.format(accuracy))
