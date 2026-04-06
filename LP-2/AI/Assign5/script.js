const chatbot = document.getElementById("chatbot");
const chatbox = document.getElementById("chatbox");
const userInput = document.getElementById("userInput");
const chatbotBtn = document.getElementById("chatbotBtn");

function toggleChat() {
    const isOpen = chatbot.classList.toggle("open");
    chatbotBtn.setAttribute("aria-expanded", String(isOpen));

    if (isOpen) {
        userInput.focus();
    }
}

function escapeHtml(text) {
    return text
        .replace(/&/g, "&amp;")
        .replace(/</g, "&lt;")
        .replace(/>/g, "&gt;")
        .replace(/\"/g, "&quot;")
        .replace(/'/g, "&#039;");
}

function appendMessage(type, text) {
    chatbox.innerHTML += `<div class="${type}-message">${escapeHtml(text)}</div>`;
    chatbox.scrollTop = chatbox.scrollHeight;
}

function getBotReply(message) {
    if (message.includes("hello") || message.includes("hi") || message.includes("hey")) {
        return "Hello. Welcome to FreshMart support. How can I help you today?";
    }

    if (message.includes("delivery") || message.includes("shipping")) {
        return "Standard delivery takes 24 hours in city areas and 48 hours for nearby towns.";
    }

    if (message.includes("return") || message.includes("refund")) {
        return "Returns are accepted within 3 days. Refunds are processed in 2-4 business days after quality check.";
    }

    if (message.includes("contact") || message.includes("support") || message.includes("agent")) {
        return "You can reach our support team at support@freshmart.com or call +91 9876543210.";
    }

    if (message.includes("order") || message.includes("track")) {
        return "To track your order, share your order ID in the app under My Orders > Track.";
    }

    if (message.includes("product") || message.includes("item") || message.includes("available")) {
        return "We offer fresh fruits, vegetables, dairy, staples, snacks, and daily household products.";
    }

    return "I can help with delivery, orders, returns, products, and contact support. Please tell me what you need.";
}

function showTypingAndReply(message) {
    const typingId = `typing-${Date.now()}`;

    chatbox.innerHTML += `
        <div class="bot-message" id="${typingId}">
            <span class="typing"><span></span><span></span><span></span></span>
        </div>
    `;
    chatbox.scrollTop = chatbox.scrollHeight;

    setTimeout(() => {
        const typingEl = document.getElementById(typingId);
        if (typingEl) {
            typingEl.remove();
        }
        appendMessage("bot", getBotReply(message));
    }, 550);
}

function sendMessage() {
    const text = userInput.value.trim();

    if (!text) {
        return;
    }

    appendMessage("user", text);
    userInput.value = "";
    showTypingAndReply(text.toLowerCase());
}

function sendQuickMessage(message) {
    userInput.value = message;
    sendMessage();
}

userInput.addEventListener("keydown", (event) => {
    if (event.key === "Enter") {
        sendMessage();
    }
});