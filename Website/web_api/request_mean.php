<?php
  $pollutant = $_GET["p"];
  $date1 = $_GET["d1"];
  $date2 = (isset($_GET["d2"])) ? $_GET["d2"] : $_GET["d1"];
  $station = (isset($_GET["s"])) ? $_GET["s"] : "all";

  $year = explode('-',$date1)[0];

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
        (SELECT SUM(value)/COUNT(*) AS mean FROM
        (SELECT (h1+h2+h3+h4+h5+h6+h7+h8+h9+h10+h11+h12+h13+h14+h15+h16+h17+h18+h19+h20+h21+h22+h23+h24)/24 AS value
        FROM ".$table." WHERE date BETWEEN '$date1' AND '$date2') z) y";
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
