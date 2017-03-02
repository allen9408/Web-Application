<?php
$servername = "localhost";
$username = "root";
$password = "root";

// Create connection
$conn = new mysqli($servername, $username, $password);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

// Create database
$sql = "CREATE DATABASE IF NOT EXISTS History_Data";
if ($conn->query($sql) === TRUE) {
    echo "Database created successfully \n";
} else {
    echo "Error creating database: " . $conn->error;
}

$sql = "CREATE DATABASE IF NOT EXISTS Real_Data";
if ($conn->query($sql) === TRUE) {
    echo "Database created successfully \n";
} else {
    echo "Error creating database: " . $conn->error;
}
$conn->close();
?>