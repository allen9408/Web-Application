<?php

$servername = "localhost";
$username = "root";
$password = "";
$dbname = "History_Data";

$stock = array("YHOO", "GOOG", "MSFT", "FB", "CCF");
$day = date("d");
$month = date("m");
$year = date("Y");


// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

// Import historical data
foreach ($stock as $tmp) {

	$sql = "CREATE TABLE $tmp (
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
	    echo "Error creating table: " . $conn->error. "\n";
	}

	$csv_path="./hist_data/$tmp-hist-$month-$day-$year.csv";

	$sql = <<<eof
LOAD DATA LOCAL INFILE '$csv_path' INTO TABLE $tmp
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
}
$conn->close();

// Import real time data
$dbname = "Real_Data";
// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

foreach ($stock as $tmp) {

	$sql = "CREATE TABLE $tmp (
		Rea_Date DECIMAL(20,0) NOT NULL,
		Close_Price DECIMAL(10, 6) NOT NULL,
		High_Price DECIMAL(10, 6) NOT NULL,
		Low_Price DECIMAL(10, 6) NOT NULL,
		Open_Price DECIMAL(10, 6) NOT NULL,
		Volume DECIMAL(20, 0) NOT NULL
	)";

	if ($conn->query($sql) === TRUE) {
	    echo "Table created successfully \n";
	} else {
	    echo "Error creating table: " . $conn->error. "\n";
	}

	$csv_path="./real_data/$tmp-$month-$day-$year.csv";

	$sql = <<<eof
LOAD DATA LOCAL INFILE '$csv_path' INTO TABLE $tmp
FIELDS TERMINATED BY ',' 
LINES TERMINATED BY '\n'
IGNORE 1 ROWS
(Rea_Date,Close_Price,High_Price,Low_Price,Open_Price,Volume)
eof;

	if ($conn->query($sql) === TRUE) {
	    echo "Import successfully  \n";
	} else {
	    echo "Error import: \n" . $conn->error;
	}
}
$conn->close();



?>