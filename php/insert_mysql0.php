<?php

foreach ($_REQUEST as $key => $value)
{
	if ($key == "onoff") {
		$onoff = $value;
	}
}

//
// EDIT: Your mysql database account information
//
$username="root";
$password="apmsetup";
$database="recycup_testdb";
$tablename = "recycup_testtable";
$localhost="localhost";


// Check Connection to Database
if (mysql_connect($localhost, $username, $password))
  {
  	@mysql_select_db($database) or die ("Unable to select database");

    // Next two lines will write into your table 'test_table_name_here' with 'yourdata' value from the arduino and will timestamp that data using 'now()'

    $query = "UPDATE $tablename SET onoff = $onoff";
  	$result = mysql_query($query);
  } else {
  	echo('Unable to connect to database.');
  }

?>