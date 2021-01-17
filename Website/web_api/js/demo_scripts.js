var api_key = '06109b46e5c1f64d9c6b5e7363a1b72d';
var req_type;

function reqList()
{
  var url = 'api.php?k='+api_key+'&t=list';
  var req = new XMLHttpRequest();

  req.onreadystatechange = function()
  {
    if(req.readyState == 4 && req.status == 200)
    {
      initSite(req.responseText);
    }
  }

  req.open("GET", url, true);
  req.send();
}

function reqAbsolute()
{
  req_type = "abs";

  var station = document.getElementById("station_select").value;
  var pollutant = document.getElementById("pollutant_select").value;
  var date = document.getElementById("date").value;
  var hour = document.getElementById("time").value;

  if (date == '') alert("Date not set!");
  else
  {
    if (station == "all") var url = 'api.php?k='+api_key+'&t=abs&p='+pollutant+'&d='+date+'&h='+hour;
    else var url = 'api.php?k='+api_key+'&t=abs&s='+station+'&p='+pollutant+'&d='+date+'&h='+hour;
    var req = new XMLHttpRequest();

    req.onreadystatechange = function()
    {
      if(req.readyState == 4 && req.status == 200)
      {
        showMap(req.responseText);
      }
    }

    req.open("GET", url, true);
    req.send();
  }
}

function reqMean()
{
  req_type = "mean";

  var station = document.getElementById("station_select").value;
  var pollutant = document.getElementById("pollutant_select").value;
  var date1 = document.getElementById("date1").value;
  var date2 = document.getElementById("date2").value;

  if (date1 == '') alert("Date not set!");
  else
  {
    if (date2 == '') date2 = date1;

    if (station == "all") var url = 'api.php?k='+api_key+'&t=mean&p='+pollutant+'&d1='+date1+'&d2='+date2;
    else var url = 'api.php?k='+api_key+'&t=mean&s='+station+'&p='+pollutant+'&d1='+date1+'&d2='+date2;
    var req = new XMLHttpRequest();

    req.onreadystatechange = function()
    {
      if(req.readyState == 4 && req.status == 200)
      {
        showMap(req.responseText);
      }
    }

    req.open("GET", url, true);
    req.send();
  }
}

var station_list;
var station_count;
var map, heatmap;

function initSite(data)
{
  station_list = JSON.parse(data);
  station_count = station_list.length;

  for (i = 0; i < station_count; i++)
  {
    document.getElementById("station_select").innerHTML += '<option value="' + station_list[i].id + '">' + station_list[i].name + '</option>';
  }

  map = new google.maps.Map(document.getElementById('map'), { center: {lat: 38.040898, lng: 24.636085}, zoom: 6});
}

function showMap(data)
{
  dec = JSON.parse(data);
  dec_length = dec.length;

  map = new google.maps.Map(document.getElementById('map'), { center: {lat: 38.040898, lng: 24.636085}, zoom: 6});

  for (i = 0; i < dec_length; i++)
  {
    var id, name;

    for (j = 0; j < station_count; j++)
    {
      if (dec[i].latitude == station_list[j].latitude && dec[i].longitude == station_list[j].longitude)
      {
        id = station_list[j].id;
        name = station_list[j].name;
      }
    }

    var pos = new google.maps.LatLng(dec[i].latitude, dec[i].longitude);
    var marker = new google.maps.Marker({ position:pos, map:map, title:name });

    var cont = "Station ID: " + id + "<br>Station Name: " + name + "<br><br>Pollutant: " + document.getElementById("pollutant_select").value;
    if (req_type == "abs")
    {
      cont += "<br><br>Date: " + document.getElementById("date").value + "<br>Hour: " +
        document.getElementById("time").options[document.getElementById("time").selectedIndex].text + "<br><br>Value: " + dec[i].value;
    }
    else
    {
      cont += "<br><br>Start Date: " + document.getElementById("date1").value + "<br>End Date: " +
        document.getElementById("date2").value + "<br><br>Mean: " + dec[i].mean;
    }

    marker.info = new google.maps.InfoWindow({ content: cont });
    google.maps.event.addListener(marker, 'click', function() { this.info.open(map, this); });
  }

  heatmap = new google.maps.visualization.HeatmapLayer({ data: getPoints(dec, dec_length), map:map, radius:30 });
}

function getPoints(dec, dec_length)
{
  var points = [];

  for (i = 0; i < dec_length; i++)
  {
    if (req_type == "abs") var point = { location: new google.maps.LatLng(dec[i].latitude, dec[i].longitude), weight: dec[i].value * 50 };
    else var point = { location: new google.maps.LatLng(dec[i].latitude, dec[i].longitude), weight: dec[i].mean * 50 };
    points.push(point);
  }

  return points;
}
