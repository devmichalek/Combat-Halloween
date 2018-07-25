<?php

	// Start session.
	session_start();

	// Check if user is logged.
  	require_once("../../user/login/isLogged.php");

  	// Check if user has admin permissions.
  	require_once("../../user/other/isAdmin.php");

  	// Get $host, $db_user, $db_password and $db_name
	require_once("../../connect.php");

	// Set flag to see more details about errors.
	mysqli_report(MYSQLI_REPORT_STRICT);

	try
	{
		$connection = @new mysqli($host, $db_user, $db_password, $db_name);
	    if($connection->connect_errno != 0)
	    	throw new Exception(mysqli_connect_errno());
	    else
		{
		    $sql = "DELETE FROM bugs WHERE IDname='".$_GET['IDname']."'";
			if(!$connection->query($sql))
				throw new Exception($connection->error);
			else
			{
				header('Location: ../index.php');
				exit();
			}

			$connection->close();
		}
	}
	catch(Exception $e)
	{
		//echo 'Error';
		echo 'Error: '.$e;
	}
?>