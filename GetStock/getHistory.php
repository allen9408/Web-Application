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
//$filename=$fileurl;
$filename = "http://ichart.yahoo.com/table.csv?s=$stock&a=$a&b=$b&c=$c&d=$d&e=$e&f=$f&g=d&ignore=.csv";
// echo $filename;
$file  =  fopen($filename, "rb"); 
Header( "Content-type:  application/octet-stream "); 
Header( "Accept-Ranges:  bytes "); 
Header( "Content-Disposition:  attachment;  filename= 4.doc"); 
$contents = "";
while (!feof($file)) {
 $contents .= fread($file, 8192);
}
$ofilename = "./hist_data/$stock-hist-$month-$day-$year.csv";
// check whether the file exists
if (file_exists($ofilename)) {
	unlink($ofilename);
}
$ofile = fopen($ofilename,"w");
fwrite($ofile,$contents);
// echo $contents > "hahaha.csv";
fclose($file); 
fclose($ofile);
}


$day = date("d");
$month = date("m");
$year = date("Y");


$stock = array("YHOO", "GOOG", "MSFT", "FB", "CCF");

foreach ($stock as $tmp) {
	downfile($tmp, $day, $month, $year);
	
}




?>