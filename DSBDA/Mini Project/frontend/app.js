const form = document.getElementById('analyze-form');
const tweetInput = document.getElementById('tweet-input');
const submitBtn = document.getElementById('submit-btn');
const loader = document.getElementById('loader');
const btnText = submitBtn.querySelector('span');
const resultContainer = document.getElementById('result-container');
const sentimentBox = document.getElementById('sentiment-box');
const sentimentText = document.getElementById('sentiment-text');
const confidenceValue = document.getElementById('confidence-value');
const confidenceFill = document.getElementById('confidence-fill');

form.addEventListener('submit', async (e) => {
    e.preventDefault();
    
    const text = tweetInput.value.trim();
    if (!text) return;

    // UI Loading state
    btnText.classList.add('d-none');
    loader.classList.remove('d-none');
    submitBtn.disabled = true;
    
    // Hide previous result
    resultContainer.classList.add('d-none');
    sentimentBox.className = 'sentiment-box'; // reset classes
    confidenceFill.style.width = '0%';

    try {
        // Fetch from FastAPI backend
        const response = await fetch('http://localhost:8000/predict', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ text })
        });

        if (!response.ok) {
            throw new Error('Failed to analyze sentiment.');
        }

        const data = await response.json();
        
        // Update UI with results
        showResult(data.sentiment, data.confidence);

    } catch (error) {
        console.error(error);
        alert('An error occurred. Make sure your FastAPI backend is running on http://localhost:8000');
    } finally {
        // Reset loading state
        btnText.classList.remove('d-none');
        loader.classList.add('d-none');
        submitBtn.disabled = false;
    }
});

function showResult(sentimentResponse, confidence) {
    resultContainer.classList.remove('d-none');
    
    let isPositive = sentimentResponse.toLowerCase().includes('positive');
    
    sentimentText.textContent = sentimentResponse;
    
    if (isPositive) {
        sentimentBox.classList.add('positive');
        confidenceFill.style.backgroundColor = 'var(--success)';
    } else {
        sentimentBox.classList.add('negative');
        confidenceFill.style.backgroundColor = 'var(--danger)';
    }

    // Set confidence
    let confPercent = 0;
    if (confidence) {
        confPercent = (confidence * 100).toFixed(1);
    } else {
        // If override triggered, we might not have a float confidence
        confPercent = 100.0;
    }

    confidenceValue.textContent = `${confPercent}%`;
    
    // Small delay to trigger CSS transition
    setTimeout(() => {
        confidenceFill.style.width = `${confPercent}%`;
    }, 50);
}
