<?php
  $id = $_POST["st_id"];
  $name = $_POST["st_name"];
  $lati = $_POST["st_lati"];
  $long = $_POST["st_long"];

  include("database.php");

  $db_query = "DELETE FROM stations WHERE id='$id'";
  $db_conn->query($db_query);

  $db_query = "INSERT INTO stations (id,name,latitude,longitude) VALUES('".$id."','".$name."','".$lati."','".$long."')";
  $db_conn->query($db_query);

  $db_query = "CREATE TABLE IF NOT EXISTS ".$id." (year int(4) NOT NULL,pollutant varchar(5) NOT NULL) ENGINE=InnoDB DEFAULT CHARSET=utf8";
  $db_conn->query($db_query);

  $db_conn->close();
  header("Location: dashboard.php");
?>
