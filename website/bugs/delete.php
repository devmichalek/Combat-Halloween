<?php
	session_start();

	if(!isset($_SESSION['logged']))
	{
		header('Location: http://combathalloween.netne.net/user/loginform.php');
		exit();
	}

	require_once "../connect.php";
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
		    $IDname = $_GET['IDname'];
		    $sql = "DELETE FROM bugs WHERE IDname='".$IDname."'";

			if(!$connection->query($sql))
			{
				throw new Exception($connection->error);
			}
			else
			{
				header('Location: http://combathalloween.netne.net/bugs/index.php');
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