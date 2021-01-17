<?php
	$db_server["host"] = "localhost";
	$db_server["username"] = "root";
	$db_server["password"] = "";
	$db_server["database"] = "web_api";

	$db_conn = new mysqli($db_server["host"],$db_server["username"],$db_server["password"],$db_server["database"]);

	if ($db_conn->connect_error)
	{
		die("DB connection failed: " . $db_conn->connect_error);
	}

	$db_conn->set_charset("utf8");
?>
