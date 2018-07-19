<?php
	session_start();

	if(!isset($_SESSION['logged']))
	{
		header('Location: http://combathalloween.netne.net/user/loginform.php');
		exit();
	}

	if( strlen($_GET['resolutionselect']) <= 0 || strlen($_GET['developerselect']) <= 0)
	{
		header('Location: http://combathalloween.netne.net/bugs/index.php');
		exit();
	}

	$_SESSION['resolutionselect'] = $_GET['resolutionselect'];
	$_SESSION['developerselect'] = $_GET['developerselect'];

	header('Location: http://combathalloween.netne.net/bugs/index.php');
	exit();
?>