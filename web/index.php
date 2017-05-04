<?php
	$con = mysql_connect("", "", "" );
	$db = mysql_select_db('');
	
	if($con) {
		if($db) {

			$sql = "SELECT * FROM members ORDER BY points DESC";
			$records = mysql_query($sql);

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