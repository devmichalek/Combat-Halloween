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
		    $sql = "SELECT * FROM bugs";
    		$records = $connection->query($sql);
    
    		$basicstr = "nn";
    		if($_SESSION['email'] == "devmichalek@gmail.com")		$basicstr = "am";
    		else if($_SESSION['email'] == "sebastek321@gmail.com")	$basicstr = "sb";
    		else if($_SESSION['email'] == "kamilgawlik@icloud.com")	$basicstr = "kg";
    
    		$num = 1;
    		while($row=$records->fetch_assoc())
    		{
    			if($row['author'] == $_SESSION['email'])
    				++$num;
    		}
    
    		// Prepare name.
    		$temp = str_repeat("0", 4 - strlen(strval($num)));
    		
    		// Free memory.
    		mysqli_data_seek($records, 0);
    		$records->free_result();
		    
            $IDname = $basicstr.$temp.strval($num);
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

			if(!$connection->query("INSERT INTO bugs VALUES (NULL, '$IDname', '$name', '$type', '$actiontodo', '$description', '$location', '$severity', '$priority', '$deadline', '$author', '$developer', '$resolution')"))
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