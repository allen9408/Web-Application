<?php
ini_set("output_buffering", "1"); 

$stock;
$day;
$month;
$year;

// function downfile($fileurl)
function downfile($stock, $day, $month, $year)
{
$a = $month - 1;
$b = $day;
$c = $year - 1;
$d = $month;
$e = $day;
$f = $year;
$count = 0;
//$filename=$fileurl;
$filename = "http://chartapi.finance.yahoo.com/instrument/1.0/$stock/chartdata;type=quote;range=1d/csv";
// echo $filename;
$file  =  fopen($filename, "rb"); 
Header( "Content-type:  application/octet-stream "); 
Header( "Accept-Ranges:  bytes "); 
Header( "Content-Disposition:  attachment;  filename= 4.doc"); 
$useless = "";
$contents = "";
while (!feof($file)) {
	if ($count < 17) {
		$useless .= fgets($file, 8192);
	} else {
		$contents .= fgets($file, 8192);
	}
	$count ++;
}
$ofilename = "./real_data/$stock-$month-$day-$year.csv";
if (file_exists($ofilename)) {
	unlink($ofilename);
}
$ofile = fopen($ofilename,"w");
fwrite($ofile,"timestamp,close,high,low,open,volume\n");
fwrite($ofile,$contents);
// echo $contents > "hahaha.csv";
fclose($file); 
fclose($ofile);
}


$day = date("d");
$month = date("m");
$year = date("Y");
$stock = "msft";


$stock = array("YHOO", "GOOG", "MSFT", "FB", "CCF");

foreach ($stock as $tmp) {
	downfile($tmp, $day, $month, $year);
	
}




?>