<?php
  $file = explode(' ',$_POST["selectFile"]);

  $station = $file[0];
  $year = $file[1];
  $pollutant = $file[2];

  include("database.php");

  $db_query = "DROP TABLE IF EXISTS ".$station.$year.$pollutant;
  $db_conn->query($db_query);

  $db_query = "DELETE FROM ".$station." WHERE year='$year' AND pollutant='$pollutant'";
  $db_conn->query($db_query);

  $db_conn->close();
  header("Location: dashboard.php");
?>
