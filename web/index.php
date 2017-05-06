<?php
	$con = mysql_connect("localhost", "user", "password" );
	$db = mysql_select_db('database');
	
	if($con) {
		if($db) {

			$sql = "SELECT * FROM members ORDER BY points DESC";
			$records = mysql_query($sql);
			$rows = mysql_num_rows($records);

			// Load HTML
			include( "index.html" );
		}
		else {
			die('Error. Database not found.');
		}
	}
	else {
		die("Could not connect: ".mysql_error());
	}
?>