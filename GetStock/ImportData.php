<?php

$servername = "localhost";
$username = "root";
$password = "root";
$dbname = "History_Data";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "CREATE TABLE FB (
	His_Date DATE,
	Open_Price DECIMAL(10, 6) NOT NULL,
	High_Price DECIMAL(10, 6) NOT NULL,
	Low_Price DECIMAL(10, 6) NOT NULL,
	Close_Price DECIMAL(10, 6) NOT NULL,
	Volume DECIMAL(20, 0) NOT NULL,
	Adj_Close DECIMAL(10, 6)  NOT NULL
)";

if ($conn->query($sql) === TRUE) {
    echo "Table created successfully \n";
} else {
    echo "Error creating table: \n" . $conn->error;
}

$csv_path='./hist_data/FB-hist-03-02-2017.csv';

$sql = <<<eof
LOAD DATA LOCAL INFILE '$csv_path' INTO TABLE FB
FIELDS TERMINATED BY ',' 
LINES TERMINATED BY '\n'
IGNORE 1 ROWS
(His_Date,Open_Price,High_Price,Low_Price,Close_Price,Volume,Adj_Close)
eof;

if ($conn->query($sql) === TRUE) {
    echo "Import successfully  \n";
} else {
    echo "Error import: \n" . $conn->error;
}

$conn->close();
?>