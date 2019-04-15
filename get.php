<?php
     include 'DatabaseConfig.php';
     //เชื่อมต่อกับ server
    $conn = mysqli_connect($Hostname, $HostUser, $HostPass, $DatabaseName);
     mysqli_set_charset($con, "utf8");
     
     // Check การเชื่อมต่อกับ server
    if (!$conn) {
        die("Connection failed: " . mysqli_connect_error());
    }

    //หำหนดตัวแปรสำหรับรับค่าจาก NodeMCU
    $d_status1 = (int)$_GET['d_status1'];
    $d_status2 = (int)$_GET['d_status2'];
    $d_status3 = (int)$_GET['d_status3'];

    //ส่งค่าที่รับได้ไปยัง database
    $sql = "INSERT INTO ParkingData (d_status1, d_status2, d_status3) VALUES ($d_status1, $d_status2, $d_status3)";

    //แสดงผลใน browser ว่าการส่งค่าไปยัง database สำเร็จหรือไม่
    if (mysqli_query($conn, $sql)) {
        echo "Insert new data successfully!";
    } else {
        echo "Error: " . $sql . "<br>" . mysqli_error($conn);
    }
    
    //ปิดการเชื่อมต่อ
    mysqli_close($conn);
?>