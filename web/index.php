<?php
	$con = mysql_connect("localhost", "unvisible", "password" );
	$db = mysql_select_db('unvisible');

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