<?php
	session_start();
	if ($_SESSION["admin"] != "yes")
	{
    header("Location: index.php");
    exit;
	}
?>
<!DOCTYPE html>
<html>

<head>
	<meta charset="UTF-8">
	<title>Keys - Web API Interface</title>
	<link rel="stylesheet" href="css/keys_styles.css">
</head>

<body>
	<header>
		<h1>Polution Web API Management Interface</h1>
	</header>

	<nav>
		MENU: <a href="dashboard.php">Stations</a> - <a href="keys.php">API Keys</a> | Logged in as: <?php echo $_SESSION["username"] ?> | <a href="logout.php">Logout</a>
	</nav>

	<section>

		<div id="keyData"><br>User info will be listed here...</div>

		<script>
			function showData()
			{
  			var xhttp = new XMLHttpRequest();
  			xhttp.onreadystatechange = function()
				{
    			if (this.readyState == 4 && this.status == 200)
					{
      			document.getElementById("keyData").innerHTML = this.responseText;
    			}
  			};
  			xhttp.open("GET", "key_data.php", true);
  			xhttp.send();
			}
			setInterval(showData, 1000);
		</script>

	</section>

	<footer>
		menychta@ceid.upatras.gr
	</footer>
</body>

</html>
