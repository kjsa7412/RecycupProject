<?php
$conn = mysqli_connect("www.recycup.com", "root", "apmsetup", "recycup_testdb");
 

$query = "UPDATE recycup_testtable SET onoff = 1";
 
mysqli_query($conn, $query)
 
?>