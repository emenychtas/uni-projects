<?php
  $stations = array();
  $options_stations = "";
  $options_files = "";

  include("database.php");

  $db_query = "SELECT * FROM stations";
  $db_result = $db_conn->query($db_query);

  if ($db_result->num_rows > 0)
  {
    while($row = $db_result->fetch_assoc())
    {
      $stations[] = $row["id"];
      echo $row["id"] . " " . $row["name"] . " " . $row["latitude"] . " " . $row["longitude"] . "<br>";

      $options_stations .= "<option value=" . $row["id"] . ">" . $row["name"] . "</option>";
    }
    echo "<br>";

    foreach ($stations as $station_id)
    {
      echo "$station_id <br>";

      $db_query = "SELECT * FROM $station_id";
      $db_result = $db_conn->query($db_query);

      if ($db_result->num_rows > 0)
      {
        while($row = $db_result->fetch_assoc())
        {
          echo $row["year"] . " " . $row["pollutant"] . "<br>";
          $options_files .= "<option value='".$station_id." ".$row["year"]." ".$row["pollutant"]."'>".$station_id." ".$row["year"]." ".$row["pollutant"]."</option>";
        }
      }
      else echo "No files for this station.<br>";
      echo "<br>";
    }
  }
  else echo "No stations found in the database.<br>";

  $db_conn->close();
?>
