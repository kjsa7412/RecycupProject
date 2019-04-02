<?php
$conn = mysqli_connect("www.recycup.com", "root", "apmsetup", "recycup_testdb");
 
$query = "select onoff, rcup1, rcup2, rcup3, rcup4, lcup1, lcup2, lcup3, lcup4 from recycup_testtable";
 
 
if($result = mysqli_query($conn, $query)){
    $row_num = mysqli_num_rows($result);
    
    echo "{";
    
        echo "\"status\":\"OK\",";
        
        echo "\"rownum\":\"$row_num\",";
    
        echo "\"result\":";
        
            echo "[";
            
                for($i = 0; $i < $row_num; $i++){
                    $row = mysqli_fetch_array($result);
                    echo "{";
                    
                    echo "\"onoff\":\"$row[onoff]\", 
					\"rcup1\":\"$row[rcup1]\", 
					\"rcup2\":\"$row[rcup2]\",
					\"rcup3\":\"$row[rcup3]\", 
					\"rcup4\":\"$row[rcup4]\", 
					\"lcup1\":\"$row[lcup1]\", 
					\"lcup2\":\"$row[lcup2]\", 
					\"lcup3\":\"$row[lcup3]\", 
					\"lcup4\":\"$row[lcup4]\"";
                    
                    echo "}";
                    if($i<$row_num-1){
                        echo ",";
                    }
                }
 
                        
                
            echo "]";
            
    echo "}";
}
 
else{
    echo "failed to get data from database.";
}
 
?>