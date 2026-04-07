function validateName() {
    const name = document.getElementById("name").value.trim();
    if (name === "") {
        alert("Name cannot be empty");
        return false;
    }

    const regex = /^[a-zA-Z\s]+$/;
    if (!regex.test(name)) {
        alert("Invalid name: only letters and spaces are allowed");
        return false;
    }
    return true;
}

function validateDob() {
    const dob = document.getElementById("dob").value;
    if (!dob) {
        alert("Please enter your date of birth");
        return false;
    }

    const dobDate = new Date(dob);
    const today = new Date();
    if (dobDate >= today) {
        alert("Invalid Date of Birth: cannot be today or future");
        return false;
    }
    return true;
}

function passCheck() {
    const pass1 = document.getElementById("password").value;
    const pass2 = document.getElementById("confirm-password").value;

    if (pass1.length < 8) {
        alert("Password must be at least 8 characters");
        return false;
    }

    if (pass1 !== pass2) {
        alert("Passwords do not match");
        return false;
    }

    return true;
}


function checkEmail() {
    const email = document.getElementById("email").value.trim();
    if (email === "") {
        alert("Email cannot be empty");
        return false;
    }

    const regex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    if (!regex.test(email)) {
        alert("Invalid email format");
        return false;
    }
    return true;
}

function validateNumber() {
    const mobile = document.getElementById("mobile").value.trim();

    if (mobile === "") {
        alert("Mobile number cannot be empty");
        return false;
    }

    if (mobile.length !== 10) {
        alert("Mobile number must be exactly 10 digits");
        return false;
    }

    for (let i = 0; i < mobile.length; i++) {
        if (mobile[i] < '0' || mobile[i] > '9') {
            alert("Mobile number can only contain digits");
            return false;
        }
    }

    return true;
}


function validateForm(event) {
    event.preventDefault();

    if (!validateName()) return;
    if (!checkEmail()) return;
    if (!validateDob()) return;
    if (!passCheck()) return;
    if (!validateNumber()) return;

    alert("Form submitted successfully!");
   
}


document.querySelector("form").addEventListener("submit", validateForm);
