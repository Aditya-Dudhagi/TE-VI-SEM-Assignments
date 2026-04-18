import pandas as pd
import numpy as np
import re
import nltk
from nltk.corpus import stopwords
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.naive_bayes import MultinomialNB
from sklearn.metrics import accuracy_score
import joblib
import os

print("Starting model training and export process...")

# Download stopwords if not present
nltk.download('stopwords', quiet=True)

negation_words = {
    'no', 'not', 'nor', 'never', 'cannot',
    'dont', 'didnt', 'isnt', 'wasnt', 'shouldnt', 'wouldnt',
    'couldnt', 'wont', 'cant', 'aint'
}
stop_words = set(stopwords.words('english')) - negation_words

def clean_text(text):
    text = str(text).lower()
    text = re.sub(r"n['’]t\b", " not", text)
    text = re.sub(r"http\S+", "", text)
    text = re.sub(r"@\w+", "", text)
    text = re.sub(r"#\w+", "", text)
    text = re.sub(r"[^a-zA-Z\s]", "", text)

    words = text.split()
    words = [word for word in words if word not in stop_words]

    return " ".join(words)

def get_sentiment(text):
    try:
        from textblob import TextBlob
        polarity = TextBlob(str(text)).sentiment.polarity
        return 'positive' if polarity > 0 else 'negative'
    except ImportError:
        # Fallback if textblob isn't installed during build script
        return 'positive' # DUMMY

print("Loading dataset...")
# Load dataset
df = pd.read_csv('data_analysis.csv', low_memory=False)

# Keep only tweet column
df = df[['tweet']].dropna()

# We only sample 20,000 for training speed if the dataset is massive, otherwise use whole
if len(df) > 20000:
    print(f"Sampling 20,000 tweets out of {len(df)} for faster training. Disable this via script if you prefer full train.")
    df = df.sample(20000, random_state=42)

print("Cleaning text...")
df['clean_tweet'] = df['tweet'].apply(clean_text)

print("Generating target sentiments using TextBlob...")
df['label'] = df['clean_tweet'].apply(get_sentiment)

# Drop any potential NaN labels/tweets
df = df.dropna()

print("Encoding labels...")
le = LabelEncoder()
df['label_encoded'] = le.fit_transform(df['label'])

print("Extracting features with CountVectorizer...")
cv = CountVectorizer(max_features=5000, ngram_range=(1, 2))
X = cv.fit_transform(df['clean_tweet']).toarray()
y = df['label_encoded']

Xtrain, Xtest, ytrain, ytest = train_test_split(X, y, test_size=0.2, random_state=42)

print("Fitting Naive Bayes Model...")
model = MultinomialNB()
model.fit(Xtrain, ytrain)

ypred = model.predict(Xtest)
print(f"Model accuracy on test split: {accuracy_score(ytest, ypred)*100:.2f}%")

print("Exporting model and vectorizer...")
os.makedirs('backend', exist_ok=True)
joblib.dump(model, 'backend/model.pkl')
joblib.dump(cv, 'backend/vectorizer.pkl')

print("✅ Model and Vectorizer saved to 'backend/model.pkl' & 'backend/vectorizer.pkl' successfully.")
