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
	<title>Dashboard - Web API Interface</title>
	<link rel="stylesheet" href="css/dashboard_styles.css">
</head>

<body>
	<header>
		<h1>Polution Web API Management Interface</h1>
	</header>

	<nav>
		MENU: <a href="dashboard.php">Stations</a> - <a href="keys.php">API Keys</a> | Logged in as: <?php echo $_SESSION["username"] ?> | <a href="logout.php">Logout</a>
	</nav>

	<section>

		<h1>Stations In Database:</h1>

		<?php include("station_data.php"); ?>

	</section>

	<aside>

		<h1>Add a station:</h1>

		<form action="sql_add_station.php" method="post" enctype="multipart/form-data">
			Station ID:<br>
			<input type="text" name="st_id"><br><br>
			Station Name:<br>
			<input type="text" name="st_name"><br><br>
			Station Latitude:<br>
			<input type="text" name="st_lati"><br><br>
			Station Longitude:<br>
			<input type="text" name="st_long"><br><br>
			<input type="submit" value="Add Station" name="submit">
		</form>

		<h1>Delete a station:</h1>

		<form action="sql_delete_station.php" method="post" enctype="multipart/form-data">
			<select name="selectStation">
				<?php echo $options_stations; ?>
			</select>
			<input type="submit" value="Delete Station" name="submit">
		</form>

		<h1>Add a file:</h1>

		<form action="sql_add_file.php" method="post" enctype="multipart/form-data">
			<select name="selectFileStation">
				<?php echo $options_stations; ?>
			</select>
			<br><br>Year:<br>
			<input type="text" name="fi_year"><br><br>
			Pollutant:<br>
			<select name="selectPollutant">
				<option value="CO">CO</option>
				<option value="NO">NO</option>
				<option value="NO2">NO2</option>
				<option value="O3">O3</option>
				<option value="SO2">SO2</option>
				<option value="PM25">PM2.5</option>
				<option value="PM10">PM10</option>
				<option value="Benz">Benz</option>
			</select>
			<br><br><input type="file" name="fi_filename"><br><br>
			<input type="submit" value="Add File" name="submit">
		</form>

		<h1>Delete a file:</h1>

		<form action="sql_delete_file.php" method="post" enctype="multipart/form-data">
			<select name="selectFile">
				<?php echo $options_files; ?>
			</select>
			<input type="submit" value="Delete File" name="submit"><br><br>
		</form>

	</aside>

	<footer>
		menychta@ceid.upatras.gr
	</footer>
</body>

</html>
