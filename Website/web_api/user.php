<?php
	session_start();
	if ($_SESSION["admin"] != "no")
	{
    header("Location: index.php");
    exit;
	}
?>
<!DOCTYPE html>
<html>

<head>
	<meta charset="UTF-8">
	<title>User - Web API Interface</title>
	<link rel="stylesheet" href="css/user_styles.css">
</head>

<body>
	<header>
		<h1>Polution Web API Management Interface</h1>
	</header>

	<nav>
		Logged in as: <?php echo $_SESSION["username"] ?> | <a href="logout.php">Logout</a>
	</nav>

	<section>

		<div class="userinfo">
		<br><h2>Stats and API Key</h2>

		<?php
			include("database.php");

			$db_query = "SELECT * FROM users WHERE email='".$_SESSION["username"]."'";
		  $db_result = $db_conn->query($db_query);

			if ($db_result->num_rows > 0)
		  {
		    while($row = $db_result->fetch_assoc())
		    {
					echo "API Key: " . $row["api_key"] . "<br><br>";
					echo "Requests (Type: List): " . $row["req_list"] . "<br>";
					echo "Requests (Type: Absolute): " . $row["req_abs"] . "<br>";
					echo "Requests (Type: Mean): " . $row["req_mean"] . "<br><br>";
				}
			}

			$db_conn->close();
		?>
	</div>

	</section>

	<footer>
		menychta@ceid.upatras.gr
	</footer>
</body>

</html>
