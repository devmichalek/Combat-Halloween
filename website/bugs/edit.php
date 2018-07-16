<?php
	session_start();

	if(!isset($_SESSION['logged']))
	{
		header('Location: http://combathalloween.netne.net/user/loginform.php');
		exit();
	}

	if( strlen($_POST['name']) <= 0 ||
	    strlen($_POST['description']) <= 0 ||
	    strlen($_POST['location']) <= 0 ||
	    strlen($_POST['deadline']) <= 0 ||
	    strlen($_POST['author']) <= 0)
	{
		header('Location: http://combathalloween.netne.net/bugs/index.php');
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
			$name =         addslashes($_POST['name']);
			$type =         $_POST['type'];
			$actiontodo =   $_POST['actiontodo'];
			$description =  nl2br(addslashes($_POST['description']));
			$location =     addslashes($_POST['location']);
			$severity =     $_POST['severity'];
			$priority =     $_POST['priority'];
			$deadline =     addslashes($_POST['deadline']);
			$author =       addslashes($_POST['author']);
			$developer =    $_POST['developer'];
			$resolution =   $_POST['resolution'];

			if(!$connection->query("UPDATE bugs SET type='$type', action='$actiontodo', description='$description', location='$location', severity='$severity', priority='$priority', deadline='$deadline', author='$author', developer='$developer', resolution='$resolution' WHERE name='$name'"))
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