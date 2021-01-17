<?php
  $id = $_POST["selectStation"];

  include("database.php");

  $db_query = "SELECT * FROM ".$id;
  $db_result = $db_conn->query($db_query);

  if ($db_result->num_rows > 0)
  {
    while($row = $db_result->fetch_assoc())
    {
      $db_query = "DROP TABLE IF EXISTS ".$id.$row["year"].$row["pollutant"];
      $db_conn->query($db_query);
    }
  }

  $db_query = "DROP TABLE ".$id;
  $db_conn->query($db_query);

  $db_query = "DELETE FROM stations WHERE id='$id'";
  $db_conn->query($db_query);

  $db_conn->close();
  header("Location: dashboard.php");
?>
