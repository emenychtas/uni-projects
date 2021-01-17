<?php
  $station = $_POST["selectFileStation"];
  $year = $_POST["fi_year"];
  $pollutant = $_POST["selectPollutant"];
  $file = "uploads/data.dat";
  move_uploaded_file($_FILES["fi_filename"]["tmp_name"], $file);

  include("database.php");

  $db_query = "DROP TABLE IF EXISTS ".$station.$year.$pollutant;
  $db_conn->query($db_query);

  $db_query = "CREATE TABLE ".$station.$year.$pollutant."
      (date DATE NOT NULL,h1 FLOAT NOT NULL,h2 FLOAT NOT NULL,h3 FLOAT NOT NULL,
      h4 FLOAT NOT NULL,h5 FLOAT NOT NULL,h6 FLOAT NOT NULL,h7 FLOAT NOT NULL,
      h8 FLOAT NOT NULL,h9 FLOAT NOT NULL,h10 FLOAT NOT NULL,h11 FLOAT NOT NULL,
      h12 FLOAT NOT NULL,h13 FLOAT NOT NULL,h14 FLOAT NOT NULL,h15 FLOAT NOT NULL,
      h16 FLOAT NOT NULL,h17 FLOAT NOT NULL,h18 FLOAT NOT NULL,h19 FLOAT NOT NULL,
      h20 FLOAT NOT NULL,h21 FLOAT NOT NULL,h22 FLOAT NOT NULL,h23 FLOAT NOT NULL,
      h24 FLOAT NOT NULL) ENGINE = CSV;";
  $db_conn->query($db_query);

  $db_query = "LOAD DATA LOCAL INFILE '".$file."' INTO TABLE ".$station.$year.$pollutant."
      FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '\"' LINES TERMINATED BY '\r\n'
      (@var,h1,h2,h3,h4,h5,h6,h7,h8,h9,h10,h11,h12,h13,h14,h15,h16,h17,h18,h19,h20,h21,h22,h23,h24)
      SET date = STR_TO_DATE(@var,'%d-%m-%Y')";
  $db_conn->query($db_query);

  $db_query = "DELETE FROM ".$station." WHERE year='$year' AND pollutant='$pollutant'";
  $db_conn->query($db_query);

  $db_query = "INSERT INTO ".$station." (year,pollutant) VALUES('".$year."','".$pollutant."')";
  $db_conn->query($db_query);

  $db_conn->close();
  unlink($file);
  header("Location: dashboard.php");
?>
