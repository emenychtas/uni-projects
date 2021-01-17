<?php
  $rows = array();

  include("database.php");

  $db_query = "SELECT * FROM stations";
  $db_result = $db_conn->query($db_query);

  if ($db_result->num_rows > 0)
  {
    while($row = $db_result->fetch_assoc())
    {
      //echo $row["id"] . " " . $row["name"] . " " . $row["latitude"] . " " . $row["longitude"] . "\n";

      $rows[] = $row;
    }

    print json_encode($rows,JSON_UNESCAPED_UNICODE);
  }
  else echo "No stations found in the database.";

  $db_conn->close();
?>
