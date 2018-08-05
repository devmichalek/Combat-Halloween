<?php
	session_start();
	session_unset();
	header('Location: https://amichalek.pl/combathalloween/index.php');
	exit();
?>