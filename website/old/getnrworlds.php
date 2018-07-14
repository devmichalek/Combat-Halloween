<?php

	session_start();

	require_once "connect.php";

	mysqli_report(MYSQLI_REPORT_STRICT);
	
	try
	{
		$connection = @new mysqli($host, $db_user, $db_password, $db_name);
		if($connection->connect_errno != 0)
		{
			throw new Exception(mysqli_connect_errno());
		}
		else
		{
			if($result = @$connection->query("SELECT * FROM worlds WHERE id"))
			{
				$how_many = $result->num_rows;
				echo $how_many;
				$result->free_result();
			}
			else
			{
				echo '0';
			}

			$connection->close();
		}
	}
	catch(Exception $e)
	{
		echo '0';
	}
?>