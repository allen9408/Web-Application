<?php

$servername = "localhost";
$username = "root";
$password = "root";
$dbname = "History_Data";

$stock = array("YHOO", "GOOG", "MSFT", "FB", "CCF");

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

foreach ($stock as $tmp) {
	$result = $conn->query("SELECT * FROM $tmp");
	print_r($result->fetch_all());
	$result->close();
}

$conn->close();

?>