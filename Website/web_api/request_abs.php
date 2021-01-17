<?php
  $pollutant = $_GET["p"];
  $date = $_GET["d"];
  $hour = $_GET["h"];
  $station = (isset($_GET["s"])) ? $_GET["s"] : "all";

  $year = explode('-',$date)[0];

  $stations = array();
  $rows = array();

  include("database.php");

  if ($station ==  "all")
  {
    $db_query = "SELECT * FROM stations";
    $db_result = $db_conn->query($db_query);

    if ($db_result->num_rows > 0)
    {
      while($row = $db_result->fetch_assoc())
      {
        $stations[] = $row["id"];
      }
    }
  }
  else $stations[] = $station;

  foreach ($stations as $st)
  {
    $table = $st.$year.$pollutant;

    $db_query = "SELECT * FROM
        (SELECT latitude,longitude FROM stations WHERE id='$st') x
        JOIN
        (SELECT h".$hour." AS value FROM ".$table." WHERE date='$date') y";
    $db_result = $db_conn->query($db_query);

    if ($db_result->num_rows > 0)
    {
      while($row = $db_result->fetch_assoc())
      {
        $rows[] = $row;
      }
    }
  }

  print json_encode($rows,JSON_UNESCAPED_UNICODE);

  $db_conn->close();
?>
