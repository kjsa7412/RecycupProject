<?PHP
echo "#";

$host="localhost"; // Host name
$username="root"; // Mysql username
$password="apmsetup"; // Mysql password
$db_name="recycup_testdb"; // Database name
$v = array();
mysql_connect("$host", "$username", "$password")or die("cannot connect");
mysql_select_db("$db_name")or die("cannot select DB");


$sql = "SELECT onoff FROM recycup_testtable";
$result = mysql_query($sql);
$v =mysql_fetch_array($result);
echo "?";
echo $v[0];
//echo($result);
?>