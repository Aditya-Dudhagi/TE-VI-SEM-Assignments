# TweetPulse ✨

**TweetPulse** is a modern, full-stack Machine Learning web application that analyzes the sentiment of tweets in real-time. Built around a custom-trained Naive Bayes NLP model, it classifies text statements as either 'Positive' or 'Negative' with an ultra-premium, glassmorphic user interface.

![Modern UI Design](https://img.shields.io/badge/UI-Glassmorphic-blue)
![Backend](https://img.shields.io/badge/Backend-FastAPI-009688)
![ML](https://img.shields.io/badge/Machine%20Learning-Scikit--learn-orange)

## 🌟 Features
- **Scikit-Learn NLP Model**: Utilizes `CountVectorizer` and `MultinomialNB` trained on over 20,000 tweets.
- **FastAPI Backend**: A lightning-fast, async Python API serving the serialized ML `.pkl` artifacts.
- **Dynamic Frontend**: A beautiful custom-built Vanilla HTML/CSS architecture featuring interactive background blobs, smooth success/error transitions, and confidence-bar visualizers without any bulky frameworks.
- **Edge-case Catching**: Contains intelligent negation-aware override systems to correctly catch "not good" or "never bad" logic that standard Bag-of-Words models often miss.

## 🛠️ Architecture
```
DSBDAL_mini_project/
├── data_analysis.csv        # The original tweet dataset
├── tweet.ipynb              # Original exploratory Jupyter Notebook
├── train_and_export.py      # Production script to train & export ML Models
├── backend/
│   ├── main.py              # FastAPI Web Server
│   ├── requirements.txt     # Python backend dependencies
│   ├── model.pkl            # Serialized Naive Bayes Model
│   └── vectorizer.pkl       # Serialized CountVectorizer
└── frontend/
    ├── index.html           # Main Application UI
    ├── styles.css           # Glassmorphism & Animations
    └── app.js               # Frontend fetch() API logic
```

## 🚀 Quickstart Guide

### 1. Environment Setup
Make sure you have Python 3.9+ installed. Navigated to the root of the project directory.
It is recommended to use a virtual environment:
```bash
python -m venv venv
.\venv\Scripts\activate   # On Windows
```

### 2. Install Dependencies
Install all required libraries for the backend server:
```bash
pip install -r backend/requirements.txt
```

### 3. (Optional) Re-Train the Model
If you've updated the `data_analysis.csv` dataset, you can regenerate the `.pkl` files:
```bash
python train_and_export.py
```

### 4. Run the Backend API
Start the FastAPI server utilizing `uvicorn`. The API will be hosted on `localhost:8000`.
```bash
uvicorn backend.main:app --reload
```

### 5. Launch the Web UI
Simply open `frontend/index.html` inside your favorite web browser! Type a sentence and click **Analyze Sentiment** to test the pipeline.

## 🤖 Tech Stack
* **Python**: Base ML Data Processing
* **Pandas / NLTK / TextBlob**: Data cleaning & tokenization
* **Scikit-Learn**: Machine Learning Models
* **FastAPI**: Backend REST API Configuration
* **HTML5 / CSS3 / JavaScript (Vanilla)**: The client side interface
