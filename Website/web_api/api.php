<?php
  $key = $_GET["k"];
  $type = $_GET["t"];

  if ($type == "list" || $type == "abs" || $type == "mean")
  {
    include("database.php");

    $db_query = "SELECT * FROM users WHERE api_key='$key'";
    $db_result = $db_conn->query($db_query);

    if ($db_result->num_rows > 0)
    {
      $db_query = "UPDATE users SET req_".$type." = req_".$type." + 1 WHERE api_key='$key'";
      $db_conn->query($db_query);
      $db_conn->close();

      include("request_".$type.".php");
    }
    else
    {
      echo "API key not valid.";
      $db_conn->close();
    }
  }
  else echo "API request type not valid.";
?>
