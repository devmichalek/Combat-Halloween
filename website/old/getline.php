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
			$name = $_POST['name'];

			$name = htmlentities($name, ENT_QUOTES, "UTF-8");

			if($result = @$connection->query(
			sprintf("SELECT * FROM foes WHERE name='%s'",
			mysqli_real_escape_string($connection, $name))))
			{
				$how_many = $result->num_rows;
				if($how_many > 0)
				{
					$row = $result->fetch_assoc();
					echo $row['line'];
					$result->free_result();
				}
				else
				{
					echo '0';
				}
			}

			$connection->close();
		}
	}
	catch(Exception $e)
	{
		echo '0';
	}
?>