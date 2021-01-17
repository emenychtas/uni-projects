<?php
	$x = $_POST["username"];
	$y = md5($_POST["password"]);

	include("database.php");

	$db_query = "SELECT * FROM admin WHERE username='$x' AND password='$y'";
	$db_result = $db_conn->query($db_query);

	if ($db_result->num_rows > 0)
	{
		session_start();
		$_SESSION["username"] = $x;
		$_SESSION["admin"] = "yes";
		$db_conn->close();
		header("Location: dashboard.php");
	}
	else
	{
		$db_query = "SELECT * FROM users WHERE email='$x' AND password='$y'";
		$db_result = $db_conn->query($db_query);

		if ($db_result->num_rows > 0)
		{
			while($row = $db_result->fetch_assoc())
			{
				session_start();
				$_SESSION["username"] = $x;
				$_SESSION["api_key"] = $row["api_key"];
				$_SESSION["admin"] = "no";
				$db_conn->close();
				header("Location: user.php");
			}
		}
		else echo "Username or password is incorrect.<br>";
	}

	$db_conn->close();
?>
