<?php
     include 'DatabaseConfig.php';
    // $con = mysqli_connect('localhost','root','12342018','myproject');
    $conn = mysqli_connect($Hostname, $HostUser, $HostPass, $DatabaseName);
     mysqli_set_charset($con, "utf8");
     
     // Check connection
    if (!$conn) {
        die("Connection failed: " . mysqli_connect_error());
    }

    $sql = "SELECT * FROM ParkingData ORDER BY reg_date DESC  LIMIT 1";
    $result = mysqli_query($conn, $sql);

    if (mysqli_num_rows($result) > 0) {
            // output data of each row
            while($row = mysqli_fetch_assoc($result)) {
                $myObj->d_status1 = $row["d_status1"];
                $myObj->d_status2 = $row["d_status2"];
                $myObj->d_status3 = $row["d_status3"];

                $myJSON = json_encode($myObj);
                echo $myJSON;
            }
        } else {
            echo "0 results";
        }

    mysqli_close($con);
?>