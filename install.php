<?php
     include 'DatabaseConfig.php';

    // Create connection
    $conn = mysqli_connect($Hostname, $HostUser, $HostPass, $DatabaseName);
    // Check connection
    if (!$conn) {
        die("Connection failed: " . mysqli_connect_error());
    }

    $sql = "CREATE TABLE ParkingData (
        d_status1 INT NOT NULL,
        d_status2 INT NOT NULL,
        d_status3 INT NOT NULL,
        reg_date TIMESTAMP
        )";
        
        if (mysqli_query($conn, $sql)) {
            echo "Table ParkingData created successfully";
        } else {
            echo "Error creating table: " . mysqli_error($conn);
        }

    mysqli_close($conn);
?>