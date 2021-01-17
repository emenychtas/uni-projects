<?php
	$x = $_POST["email"];
	$y = md5($_POST["password"]);
	$key = md5($x . $y . "pollution_web_api");

	include("database.php");

	$db_query = "INSERT INTO users (email,password,api_key) VALUES('".$x."','".$y."','".$key."')";
	$db_conn->query($db_query);

	$db_conn->close();
	header("Location: index.php");
?>
