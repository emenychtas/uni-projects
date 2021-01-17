<?php
	include("database.php");

	echo "<h1>Web API Global Statistics:</h1>";

	$db_query = "SELECT COUNT(*) AS key_count,SUM(req_list),SUM(req_abs),SUM(req_mean) FROM users";
  $db_result = $db_conn->query($db_query);

	if ($db_result->num_rows > 0)
  {
    while($row = $db_result->fetch_assoc())
    {
			echo "API Keys: " . $row["key_count"] . "<br>";
			echo "Requests (Type: List): " . $row["SUM(req_list)"] . "<br>";
			echo "Requests (Type: Absolute): " . $row["SUM(req_abs)"] . "<br>";
			echo "Requests (Type: Mean): " . $row["SUM(req_mean)"] . "<br>";
		}
	}

	echo "<h1>Top 10 API Keys (total requests):</h1>";

	$db_query = "SELECT email,api_key,req_list+req_abs+req_mean AS total FROM users ORDER BY total DESC LIMIT 10";
  $db_result = $db_conn->query($db_query);

	if ($db_result->num_rows > 0)
  {
		$index = 0;
    while($row = $db_result->fetch_assoc())
    {
			$index = $index + 1;
			echo $index . ". Total Requests: " . $row["total"] . " - API Key: " . $row["api_key"] . " ( " . $row["email"] . " )<br>";
		}
	}

	echo "<h1>Users In Database:</h1>";

	$db_query = "SELECT * FROM users";
  $db_result = $db_conn->query($db_query);

	if ($db_result->num_rows > 0)
  {
    while($row = $db_result->fetch_assoc())
    {
			echo "Email: " . $row["email"] . "<br>";
			echo "API Key: " . $row["api_key"] . "<br>";
			echo "Requests (Type: List): " . $row["req_list"] . "<br>";
			echo "Requests (Type: Absolute): " . $row["req_abs"] . "<br>";
			echo "Requests (Type: Mean): " . $row["req_mean"] . "<br><br>";
		}
	}

	$db_conn->close();
?>
