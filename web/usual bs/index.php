<?php
	$con = mysql_connect("localhost", "id959266_adriqun_scores", "100krotka" );
	$db = mysql_select_db('id959266_scores');

	if($con) {
		if($db) {

			// Load HTML
			include( "index.html" );
		}
		else {
			die('Error. Database not found.');
		}
	}
	else {
		die('Error.');
	}
?>