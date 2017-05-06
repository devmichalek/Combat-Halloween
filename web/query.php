<?php

	$server   = 'localhost';
	$username = 'user';
	$password = 'password';
	$db       = 'database';
	$conn     = mysqli_connect($server, $username, $password, $db);
	 
	$nick  = mysqli_real_escape_string($conn, strip_tags($_POST['nick']));
	$world  = mysqli_real_escape_string($conn, strip_tags($_POST['world']));
	$difficulty  = mysqli_real_escape_string($conn, strip_tags($_POST['difficulty']));
	$points  = mysqli_real_escape_string($conn, strip_tags($_POST['points']));
	$time_playing  = mysqli_real_escape_string($conn, strip_tags($_POST['time_playing']));
	$date  = mysqli_real_escape_string($conn, strip_tags($_POST['date']));
	 
	$ins_sql = "INSERT INTO members ( id, nick, world, difficulty, points, time_playing, date) VALUES ( NULL, '$nick', '$world', '$difficulty', '$points', '$time_playing', '$date' )";
	 
	if( mysqli_query( $conn, $ins_sql ) ) {
	    echo 'UDALO SIE KURWA MAC\n';
	}
	else {
	    echo 'NIE DZIALA KURWA MAC\n';
	}
?>