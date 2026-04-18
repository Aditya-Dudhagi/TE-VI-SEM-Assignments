from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
import joblib
import re
import nltk
from nltk.corpus import stopwords
import os

# Download stopwords quietly at startup
try:
    nltk.download('stopwords', quiet=True)
except Exception:
    pass

app = FastAPI(title="Sentiment Analysis API")

# Setup CORS to allow frontend communication
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],  # Adjust in production
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

# Load Models
MODEL_PATH = os.path.join(os.path.dirname(__file__), 'model.pkl')
VECTORIZER_PATH = os.path.join(os.path.dirname(__file__), 'vectorizer.pkl')

try:
    model = joblib.load(MODEL_PATH)
    cv = joblib.load(VECTORIZER_PATH)
    print("Models loaded successfully.")
except Exception as e:
    print("Warning: Failed to load models. Make sure they are trained.", e)
    model = None
    cv = None

negation_words = {
    'no', 'not', 'nor', 'never', 'cannot',
    'dont', 'didnt', 'isnt', 'wasnt', 'shouldnt', 'wouldnt',
    'couldnt', 'wont', 'cant', 'aint'
}
stop_words = set(stopwords.words('english')) - negation_words

def clean_text(text: str) -> str:
    text = str(text).lower()
    text = re.sub(r"n['’]t\b", " not", text)
    text = re.sub(r"http\S+", "", text)
    text = re.sub(r"@\w+", "", text)
    text = re.sub(r"#\w+", "", text)
    text = re.sub(r"[^a-zA-Z\s]", "", text)

    words = text.split()
    words = [word for word in words if word not in stop_words]
    return " ".join(words)

# Data Models
class TweetInput(BaseModel):
    text: str

class SentimentOutput(BaseModel):
    sentiment: str
    confidence: float | None = None
    message: str

@app.post("/predict", response_model=SentimentOutput)
def predict_sentiment(req: TweetInput):
    if not model or not cv:
        return SentimentOutput(sentiment="Unknown", message="Model not loaded on server.")
    
    cleaned = clean_text(req.text)

    # Hardcoded overrides from the original jupyter notebook
    if re.search(r"\b(not|no|never|dont|didnt|cant|wont|cannot)\s+(like|love|good|great|excellent|amazing)\b", cleaned):
        return SentimentOutput(sentiment="Negative", message="Custom override triggered.")
    
    if re.search(r"\b(not|no|never|dont|didnt|cant|wont|cannot)\s+(hate|bad|terrible|awful|worst)\b", cleaned):
        return SentimentOutput(sentiment="Positive", message="Custom override triggered.")

    # Using the models
    try:
        vector = cv.transform([cleaned]).toarray()
        prediction = model.predict(vector)
        pred_label = "Positive" if prediction[0] == 1 else "Negative"

        try:
            proba = model.predict_proba(vector)[0]
            conf = max(proba)
        except AttributeError:
            conf = None

        return SentimentOutput(sentiment=pred_label, confidence=conf, message="Successfully classified Tweet.")
    except Exception as e:
        return SentimentOutput(sentiment="Error", message=f"Prediction failed: {str(e)}")

@app.get("/health")
def health_check():
    return {"status": "ok", "model_loaded": model is not None}
