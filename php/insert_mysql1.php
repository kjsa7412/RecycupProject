<?php

foreach ($_REQUEST as $key => $value)
{
	if ($key == "r_1") {
		$r_1 = $value;
	}
	if ($key == "r_2") {
		$r_2 = $value;
	}
	if ($key == "r_3") {
		$r_3 = $value;
	}
	if ($key == "r_4") {
		$r_4 = $value;
	}
	if ($key == "l_1") {
		$l_1 = $value;
	}
	if ($key == "l_2") {
		$l_2 = $value;
	}
	if ($key == "l_3") {
		$l_3 = $value;
	}
	if ($key == "l_4") {
		$l_4 = $value;
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

    $query = "UPDATE $tablename SET  rcup1 = rcup1 + $r_1, rcup2 = rcup2 + $r_2, rcup3 = rcup3 + $r_3, rcup4 = rcup4 + $r_4, lcup1 = lcup1 + $l_1, lcup2 = lcup2 + $l_2, lcup3 = lcup3 + $l_3, lcup4 = lcup4 + $l_4";
  	$result = mysql_query($query);
  } else {
  	echo('Unable to connect to database.');
  }

?>