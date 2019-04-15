<?php
// ไฟล์สำหรับลบข้อมูลในตารางเก็บข้อมูล

include 'DatabaseConfig.php';
// Create connection
$conn = mysqli_connect($Hostname, $HostUser, $HostPass, $DatabaseName);
 mysqli_set_charset($con, "utf8");

// Check connection
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}

// sql to delete a record
$sql = "DELETE FROM ParkingData";

if (mysqli_query($conn, $sql)) {
    echo "Record deleted successfully";
} else {
    echo "Error deleting record: " . mysqli_error($conn);
}

mysqli_close($conn);
?>