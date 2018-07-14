<?php
	session_start();

	if(!isset($_SESSION['logged']))
	{
		header('Location: http://combathalloween.netne.net/user/loginform.php');
		exit();
	}

	if(!isset($_POST['name']) || !isset($_POST['description']) ||
	   !isset($_POST['location']) || !isset($_POST['author']))
	{
		header('Location: addreport.php');
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
			$name = $_POST['name'];
			$type = $_POST['type'];
			$actiontodo = $_POST['actiontodo'];
			$description = $_POST['description'];
			$location = $_POST['location'];
			$deadline = $_POST['deadline'];
			$author = $_POST['author'];
			$developer = $_POST['developer'];
			$status = $_POST['status'];

			if(!$connection->query("INSERT INTO bugs VALUES (NULL, '$name', '$type', '$actiontodo', '$description', '$location', '$deadline', '$author', '$developer', '$status')"))
			{
				throw new Exception($connection->error);
			}
			else
			{
				header('Location: http://combathalloween.netne.net/bugs/index.php');
			}

			$connection->close();
		}
	}
	catch(Exception $e)
	{
		echo 'Error';
		// echo 'Error: '.$e;
	}
?>