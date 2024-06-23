document.getElementById("data-form").addEventListener("submit", function(event) {
    event.preventDefault(); // Prevent form submission
  
    // Retrieve input values
    const methaneValue = document.getElementById("methane").value;
    const temperatureValue = document.getElementById("temperature").value;
    const humidityValue = document.getElementById("humidity").value;
  
    // Validate inputs
    if (methaneValue.trim() === "" || temperatureValue.trim() === "" || humidityValue.trim() === "") {
      alert("Please fill in all fields.");
      return;
    }
  
    // Store data in variables or send to backend
    const data = {
      methane: methaneValue,
      temperature: temperatureValue,
      humidity: humidityValue
    };
  
    // Now you can use the 'data' variable to send data to your machine learning model or backend for further processing
    console.log("Data:", data);
  });
  