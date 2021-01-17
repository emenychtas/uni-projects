<!DOCTYPE html>
<html>

<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="initial-scale=1.0">
	<title>Demo - Web API Demo</title>
	<link rel="stylesheet" href="css/demo_styles.css">
	<script>
		window.onload = function()
		{
  		reqList();
		};
	</script>
</head>

<body>
	<header>
		<h1>Polution Web API Demo Website</h1>
	</header>

	<section>

		<div class="controls">
		<select id="station_select">
			<option value="all">All</option>
		</select>
		<select id="pollutant_select">
			<option value="CO">CO</option>
			<option value="NO">NO</option>
			<option value="NO2">NO2</option>
			<option value="O3">O3</option>
			<option value="SO2">SO2</option>
			<option value="PM25">PM25</option>
			<option value="PM10">PM10</option>
			<option value="Benz">Benz</option>
		</select>
		<br><br>
		<input type="date" id="date">
		<select id="time">
			<option value="1">00:00</option> <option value="2">01:00</option> <option value="3">02:00</option>
			<option value="4">03:00</option> <option value="5">04:00</option> <option value="6">05:00</option>
			<option value="7">06:00</option> <option value="8">07:00</option> <option value="9">08:00</option>
			<option value="10">09:00</option> <option value="11">10:00</option> <option value="12">11:00</option>
			<option value="13">12:00</option> <option value="14">13:00</option> <option value="15">14:00</option>
			<option value="16">15:00</option> <option value="17">16:00</option> <option value="18">17:00</option>
			<option value="19">18:00</option> <option value="20">19:00</option> <option value="21">20:00</option>
			<option value="22">21:00</option> <option value="23">22:00</option> <option value="24">23:00</option>
		</select>
		<button type="button" onclick="reqAbsolute()">Absolute</button>
		<br><br>
		<input type="date" id="date1">
		<input type="date" id="date2">
		<button type="button" onclick="reqMean()">Mean</button>
		<br><br>
		</div>

		<div id="map"></div>

	</section>

	<footer>
		menychta@ceid.upatras.gr
	</footer>

	<script src="js/demo_scripts.js"></script>
	<script src="https://maps.googleapis.com/maps/api/js?key=AIzaSyDntS7X8DyRAtj_L8LJBy05vTnliW_J5mw&libraries=visualization"></script>
</body>

</html>
