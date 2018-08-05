<?php
	if(!isset($_SESSION['logged']))
	{
		header('Location: https://amichalek.pl/combathalloween/user/login/loginform.php');
		exit();
	}
?>