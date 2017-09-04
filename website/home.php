<?php

	session_start();

	if(!isset($_SESSION['logged']))
	{
		header('Location: login_form.php');
		exit();
	}

	require_once "connect.php";
	mysqli_report(MYSQLI_REPORT_STRICT);
	try
	{
		$connection = @new mysqli($host, $db_user, $db_password, $db_name);
		if($connection->connect_errno != 0)
		{
			throw new Exception(mysqli_connect_errno());
		}
		else if($result = @$connection->query( sprintf("SELECT * FROM users WHERE username='%s'", mysqli_real_escape_string($connection, $_SESSION['username']))))
		{

			$row = $result->fetch_assoc();
			$_SESSION['money'] = $row['money'];
			$_SESSION['diamonds'] = $row['diamonds'];
			$_SESSION['helmet'] = $row['helmet'];
			$_SESSION['body'] = $row['body'];
			$_SESSION['shield'] = $row['shield'];
			$_SESSION['sword'] = $row['sword'];
			$_SESSION['boots'] = $row['boots'];
			$result->free_result();
		}

		$connection->close();
	}
	catch(Exception $e)
	{
		echo 'Error';
		// echo 'Error: '.$e;
	}



	function getNumber($letter, $line)
	{
		$result = "";
		for($i=0; $i<strlen($line); $i++)
		{
			if($line[$i] == $letter)
			{
				for($j=$i+1; $j<strlen($line); $j++)
				{
					if(!is_numeric($line[$j]) && $line[$j] != '-')
					{
						break;
					}
					$result .= $line[$j];
				}
				break;
			}
		}

		return $result;
	}

	function getValue($letter, $result, $deltag = false)
	{
		$final = '<span style="display: inline-block;">';

		if($deltag)	$final .= '<del>';

		if( $letter == 'l' )		$final .= 'Level: ';
		else if( $letter == 'c' )	$final .= 'Cost: ';
		else if( $letter == 'r' )	$final .= 'Diamonds: ';
		else if( $letter == 'a' )	$final .= 'Armour: ';
		else if( $letter == 'h' )	$final .= 'Health: ';
		else if( $letter == 'd' )	$final .= 'Damage: ';
		else if( $letter == 's' )	$final .= 'Speed: ';

		if($letter == 'c')
		{
			$final .= '<span style="color: #FFCF79; margin-right: 0em; margin-left: 0em;">';
		}
		else if($letter == 'r')
		{
			$final .= '<span style="color: #5597FF; margin-right: 0em; margin-left: 0em;">';
		}
		else if($result < 0)
		{
			$final .= '<span style="color: #F2583E; margin-right: 0em; margin-left: 0em;">';
		}
		else if($result > 0)
		{
			$final .= '<span style="color: #92CD00; margin-right: 0em; margin-left: 0em;">';
		}
		else
		{
			$final .= '<span style="color: #000000; margin-right: 0em; margin-left: 0em;">';
		}

		if($letter != 'l' && $letter != 'c' && $letter != 'r' && $result > 0)
		{
			$final .= '+';
		}

		if( $result == 'max' && $result != '0' )	$final .= '<mark>';
		$final .= $result;
		if( $result == 'max' && $result != '0' )	$final .= '</mark>';

		if($deltag)	$final .= '</del>';

		if($letter == 's')
		{
			$final .= '%';
		}

		if($letter == 'c')
		{
			$final .= '<img src="images/coin.png" alt="coin" onload="this.width/=2;" onload="this.height/=2;">';
		}
		else if($letter == 'r')
		{
			$final .= '<img src="images/diamond.png" alt="diamond" onload="this.width/=2;" onload="this.height/=2;">';
		}
		else if($letter == 'a')
		{
			$final .= '‰';
		}
		else if($letter == 'h' || $letter == 'd')
		{
			$final .= 'p';
		}

		$final .= '</span></span>';
		return $final;
	}

	function echoButton( $coins, $diamonds, $level, $name )
	{
		if( $coins > $_SESSION['money'] || $diamonds > $_SESSION['diamonds'] || $level == 20 )
		{
			echo '<a class="button" disabled>Upgrade</a>';
		}
		else
		{
			echo '<a class="button button-primary" href="upgrade.php?name='.$name.'&level='.$level.'">Upgrade</a>';
		}
	}

	function echoValue( $line, $name )
	{
		echo '<h5 style="margin-bottom: 0.25em;">';

		$max = false;
		if(getNumber('l', $line) == 20)
		{
			$max = true;
			echo getValue('l', 'max').' ';
		}
		else
		{
			echo getValue('l', getNumber('l', $line)).' ';
		}
		

		if($max)
			echo getValue('c', getNumber('c', $line), true).' ';
		else
			echo getValue('c', getNumber('c', $line)).' ';

		if(getNumber('r', $line) > 0 )
		{
			if($max)
				echo getValue('r', getNumber('r', $line), true).' ';
			else
				echo getValue('r', getNumber('r', $line)).' ';
		}
		echo getValue('a', getNumber('a', $line)).' ';
		echo getValue('h', getNumber('h', $line)).' ';
		echo getValue('d', getNumber('d', $line)).' ';
		echo getValue('s', getNumber('s', $line));
		echo '</h5>';
		echoButton( getNumber('c', $line), getNumber('r', $line), getNumber('l', $line), $name );
	}

	function echoGeneral()
	{
		$lines = array('helmet', 'body', 'shield', 'sword', 'boots');
		$levelgeneral = 0;
		$armourgeneral = 0;
		$healthgeneral = 0;
		$damagegeneral = 0;
		$speedgeneral = 0;

		foreach($lines as &$line)
		{
			$line = $_SESSION[ $line ];
			$levelgeneral += getNumber('l', $line);
			$armourgeneral += getNumber('a', $line);
			$healthgeneral += getNumber('h', $line);
			$damagegeneral += getNumber('d', $line);
			$speedgeneral += getNumber('s', $line);
		}

		echo '<h5 style="margin-bottom: 0.25em;">';
		echo getValue('l', intval($levelgeneral /5)).' ';
		echo getValue('a', $armourgeneral).' ';
		echo getValue('h', $healthgeneral).' ';
		echo getValue('d', $damagegeneral).' ';
		echo getValue('s', $speedgeneral);
		echo '</h5>';
	}

	$_SESSION['commandsbackbutton'] = true;
?>

<!DOCTYPE html>
<html lang="en">
<head>
	<!-- Standard Meta -->
	<meta charset="UTF-8" />
	<meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1" />
	<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0">

	<!-- Site Properties -->
	<title>Home - Combat Halloween</title>
	<link rel="stylesheet" href="skeleton.css">
	<link rel="stylesheet" href="normalize.css">
	<link rel="stylesheet" href="main.css">
	<link rel="shortcut icon" href="images/icon.png">

	<style>
		body
		{
			<?php
				if( $_SESSION['premium'] > 0 )
				{
					echo 'background-image: url("images/premiumbg.png") !important;';
					echo 'background-size: 20px 108px;';
					echo 'background-repeat: repeat-y !important;';
				}
			?>
		}
	</style>

</head>
<body>
	<div class="container">

		<!-- Download button and Log Out button and the rest -->
		<div class="row myfont nobotmargin" style="text-align: center; margin-top: 1em;">
			<div class="two columns">
				<h5>Logged as <span class="redspan">
					<?php
						echo $_SESSION['username'];
					?>
				</span></h5>
			</div>

			<div class="two columns">
				<h5>
				<span style="display: inline-block;">Since: <span class="redspan"><?php echo $_SESSION['first_time']; ?></span></span> 
				</h5>
			</div>

			<div class="eight columns">
				<a class="button premiumbutton" href="premium.php">Get Premium</a>
				<a class="button premiumbutton" href="premium.php">Money</a>
				<a class="button" href="premium.php" style="background-color: #5597FF; color: white;">Diamonds</a>
				<a class="button" href="logout.php">Log Out</a>
				<a class="button" href="premium.php">Users / Scores</a>
				<a class="button" href="premium.php">Settings</a>
				<a class="button" href="premium.php">Worlds</a>
			</div>
		</div>

		<!-- Header and upgrade section -->
		<div class="row myfont">
			<div class="twelve columns" style="text-align: center; margin-top: 5em;">
				<h3 class="notopmargin nobotmargin">Upgrade section</h3>
				<h5 class="notopmargin nobotmargin">
				<span style="display: inline-block;">Money: <span style="color: #FFCF79;"><?php echo $_SESSION['money']; ?></span><img src="images/coin.png" alt="coin" onload="this.width/=2;" onload="this.height/=2;">&nbsp;</span> 
				<span style="display: inline-block;">Diamonds: <span style="color: #5597FF;"><?php echo $_SESSION['diamonds']; ?></span><img src="images/diamond.png" alt="diamond" onload="this.width/=2;" onload="this.height/=2;"></span>
				</h5>
			</div>
		</div>

		<!-- General, Helmet and Body -->
		<div class="row">
			<div class="four columns myfont" style="text-align: center; margin-top: 2em;">
				<img src="images/upgrade/general.png" width="64" height="100" style="margin-bottom: -0.1em;">	
				<h4 class="notopmargin nobotmargin">General</h4>
				<?php
					echoGeneral();
				?>
			</div>

			<div class="four columns myfont" style="text-align: center; margin-top: 2em;">
				<img src="images/upgrade/helmet.png"  width="64" height="100" style="margin-bottom: -0.1em;">	
				<h4 class="notopmargin nobotmargin">Ancient Helmet</h4>
				<?php
					echoValue( $_SESSION['helmet'], 'helmet' );
				?>
			</div>

			<div class="four columns myfont" style="text-align: center; margin-top: 2em;">
				<img src="images/upgrade/body.png" width="62" height="100" style="margin-bottom: -0.1em;">
				<h4 class="notopmargin nobotmargin">Hospital Outfit</h4>
				<?php
					echoValue( $_SESSION['body'], 'body' );
				?>
			</div>
		</div>

		<!-- Shield, sword and boots -->
		<div class="row">
			<div class="four columns myfont" style="text-align: center; margin-top: 2em;">
				<div class="row">
				<img src="images/upgrade/shield.png" width="71" height="100" style="margin-bottom: -0.1em;">	
				<h4 class="notopmargin nobotmargin">Huntress's Buckler</h4>
				<?php
					echoValue( $_SESSION['shield'], 'shield' );
				?>
				</div>
			</div>

			<div class="four columns myfont" style="text-align: center; margin-top: 2em;">
				<div class="row">
				<img src="images/upgrade/sword.png" width="74" height="100" style="margin-bottom: -0.1em;">
				<h4 class="notopmargin nobotmargin">Blade of Knights</h4>
				<?php
					echoValue( $_SESSION['sword'], 'sword' );
				?>
				</div>
			</div>

			<div class="four columns myfont" style="text-align: center; margin-top: 2em;">
				<div class="row">
				<img src="images/upgrade/boots.png" width="59" height="100" style="margin-bottom: -0.1em;">
				<h4 class="notopmargin nobotmargin">Hermes Boots</h4>
				<?php
					echoValue( $_SESSION['boots'], 'boots' );
				?>
				</div>
			</div>
		</div>


		<!-- Commands -->
		<div class="row myfont">
			<div class="twelve columns" style="text-align: center; margin-top: 5em;">
				<h3 class="notopmargin nobotmargin">All Commands in Game</h3>
				<h5 class="notopmargin nobotmargin">Prefix = '@', by this sign at first you inform game that it would be command. Let's take for an example that we want to start game, you can do this by typing simply "@play" command. Let's be honest, you don't need to know even one, I added commands for those who like typing if you are not a keyboarder just don't mess your mind. Without reading you've already know at least one, it's natural, "I want to stop playing music" - "@music off". Often you can found out more than one command for one action, so choose your favourite! <a href="commands.php">Click here to see commands.</a></h5>
			</div>
		</div>

		<!-- Footer -->
		<div class="twelve columns" style="text-align: center; margin-top: 10em;">
			<footer>
				<h6 class="myfont nobotmargin notopmargin">
					<span style="display: inline-block;">&nbsp;&nbsp;&nbsp;Visit my github: <a href="https://github.com/Adriqun" style="color: #444444;">Adrian Michalek</a>&nbsp;&nbsp;&nbsp;</span>
					<span style="display: inline-block;">Back to <a href="logout.php" style="color: #444444;">main site</a></span>
				</h6>
				<h6 class="myfont nobotmargin notopmargin">
					Contact me: adrmic98@gmail.com or contact@adrianmichalek.pl
				</h6>
			</footer>
		</div>
	</div>
</body>
</html>