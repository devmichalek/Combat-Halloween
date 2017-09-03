<?php

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
		echo '<h5>';

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

		echo '<h5>';
		echo getValue('l', intval($levelgeneral /5)).' ';
		echo getValue('a', $armourgeneral).' ';
		echo getValue('h', $healthgeneral).' ';
		echo getValue('d', $damagegeneral).' ';
		echo getValue('s', $speedgeneral);
		echo '</h5>';
	}
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
				<a class="button premiumbutton" href="premium.php">Get Money</a>
				<a class="button" href="premium.php" style="background-color: #5597FF; color: white;">Get Diamonds ♦</a>
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
				<img src="images/upgrade/general.png" width="64" height="100">	
				<h4 class="notopmargin nobotmargin">General</h4>
				<?php
					echoGeneral();
				?>
			</div>

			<div class="four columns myfont" style="text-align: center; margin-top: 2em;">
				<img src="images/upgrade/helmet.png"  width="64" height="100">	
				<h4 class="notopmargin nobotmargin">Ancient Helmet</h4>
				<?php
					echoValue( $_SESSION['helmet'], 'helmet' );
				?>
			</div>

			<div class="four columns myfont" style="text-align: center; margin-top: 2em;">
				<img src="images/upgrade/body.png" width="62" height="100">
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
				<img src="images/upgrade/shield.png" width="71" height="100">	
				<h4 class="notopmargin nobotmargin">Huntress's Buckler</h4>
				<?php
					echoValue( $_SESSION['shield'], 'shield' );
				?>
				</div>
			</div>

			<div class="four columns myfont" style="text-align: center; margin-top: 2em;">
				<div class="row">
				<img src="images/upgrade/sword.png" width="74" height="100">
				<h4 class="notopmargin nobotmargin">Blade of Knights</h4>
				<?php
					echoValue( $_SESSION['sword'], 'sword' );
				?>
				</div>
			</div>

			<div class="four columns myfont" style="text-align: center; margin-top: 2em;">
				<div class="row">
				<img src="images/upgrade/boots.png" width="59" height="100">
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
				<h5 class="notopmargin nobotmargin">Prefix = '@', by this sign at first you inform game that it would be command. Let's take for an example that we want to start game, you can do this by typing simply "@play" command. Let's be honest, you don't need to know even one, I added commands for those who like typing if you are not a keyboarder just don't mess your mind. Without reading you've already know at least one, it's natural, "I want to stop playing music" - "@music off". Often you can found out more than one command for one action, so choose your favourite!</h5>
			</div>
		</div>

		<!-- In Menu -->
		<div class="row myfont">
			<div class="twelve columns" style="text-align: center; margin-top: 2em;">
				<h4 class="nobotmargin">Menu</h4>
				<!-- Play -->
				<h5 class="nobotmargin"><span class="redspan">@singleplayer</span> - <span class="redspan">@play</span>
				 - <span class="redspan">@start</span> - <span class="redspan">@go</span></h5>
				<h5 class="nobotmargin">Starts game (actually you go into next state).</h5>
				<div style="margin-top: 1.5em;"></div>

				<!-- Close application -->
				<h5 class="nobotmargin"><span class="redspan">@close</span> - <span class="redspan">@exit</span>
				 - <span class="redspan">@finish</span> - <span class="redspan">@end</span></h5>
				<h5 class="nobotmargin">Close application safe, also it saves volumes and states of music and chunks.</h5>
				<div style="margin-top: 1.5em;"></div>

				<!-- Knight specs -->
				<h5 class="nobotmargin"><span class="redspan">@helmet</span> - <span class="redspan">@body</span>
				 - <span class="redspan">@shield</span> - <span class="redspan">@sword</span> - 
				 <span class="redspan">@boots</span> - <span class="redspan">@clear</span></h5>
				<h5 class="nobotmargin">Shows the specs of particular part of the knight body as you can see above. The last one close window.</h5>
				<div style="margin-top: 1.5em;"></div>
				
				<!-- Settings -->
				<h5 class="nobotmargin"><span class="redspan">@settings</span> - <span class="redspan">@keyboard</span>
				 - <span class="redspan">@sets</span> - <span class="redspan">@keys</span></h5>
				<h5 class="nobotmargin">Shovel or exsert window with settings, it depends what you see now.</h5>
				<div style="margin-top: 1.5em;"></div>

				<!-- Reload data -->
				<h5 class="nobotmargin"><span class="redspan">@reload</span> - <span class="redspan">@connect</span>
				 - <span class="redspan">@rel</span> - <span class="redspan">@con</span></h5>
				<h5 class="nobotmargin">In case of problem with connection you can use this commands to reload data. Remember that it doesn't work if you already have loaded data. This command also works during problems when worlds are not loaded.</h5>
				<div style="margin-top: 1.5em;"></div>

				<!-- Update data -->
				<h5 class="nobotmargin"><span class="redspan">@update</span></h5>
				<h5 class="nobotmargin">The main difference between update data and reload data is that the update command works always. It's needed for example when you upgrade something on website but you have game on, then you typing this for actualization. This command is also available when you choosing world to update amount of worlds.</h5>
				<div style="margin-top: 1.5em;"></div>

				<!-- Github -->
				<h5 class="nobotmargin"><span class="redspan">@github</span></h5>
				<h5 class="nobotmargin">Opens github with view on my account, be careful, you're gonna see my beautiful face.</h5>
				<div style="margin-top: 1.5em;"></div>

				<!-- Scores -->
				<h5 class="nobotmargin"><span class="redspan">@update</span></h5>
				<h5 class="nobotmargin">Opens the part of site with scores, don't even think about it, we all know that you are not in top ten.</h5>
				<div style="margin-top: 1.5em;"></div>

				<!-- Website -->
				<h5 class="nobotmargin"><span class="redspan">@website</span></h5>
				<h5 class="nobotmargin">Opens ... adrianmichalek.pl/combathalloween, how do you feel now? You seems to be shocked.</h5>
				<div style="margin-top: 1.5em;"></div>

				<!-- Chunks -->
				<h5 class="nobotmargin"><span class="redspan">@chunk</span> - <span class="redspan">@chunk turn</span>
				 - <span class="redspan">@chunk on</span> - <span class="redspan">@chunk off</span></h5>
				<h5 class="nobotmargin">It's as easy as anything. Chunk is a .wav file so for instance noise of clicking. The first two turns chunks (on to off, off to on), the second two as it is written. Those commands works anywhere instead of editor (there are no chunks in editor).</h5>
				<div style="margin-top: 1.5em;"></div>

				<!-- Music -->
				<h5 class="nobotmargin"><span class="redspan">@music</span> - <span class="redspan">@music turn</span>
				 - <span class="redspan">@music on</span> - <span class="redspan">@music off</span></h5>
				<h5 class="nobotmargin">Music is a .ogg file that's what you hear in background. The first two turn music (on to off, off to on), the second two as it is written. Those commands works anywhere instead of editor (there is no music in editor).</h5>
				<div style="margin-top: 1.5em;"></div>

				<!-- Sound -->
				<h5 class="nobotmargin"><span class="redspan">@sound</span> - <span class="redspan">@sound turn</span>
				 - <span class="redspan">@sound on</span> - <span class="redspan">@sound off</span></h5>
				<h5 class="nobotmargin">Sound is not magic too. By sound I mean group made by chunk and music. You type the first two and music change state from on to off or off to on, then chunk do the same. The third command turns on music and chunks, the last one as you guessed. Those commands works anywhere instead of editor (there is no sound in editor).</h5>
				<div style="margin-top: 1.5em;"></div>

				<!-- Editor -->
				<h5 class="nobotmargin"><span class="redspan">@editor</span> - <span class="redspan">@edit</span></h5>
				<h5 class="nobotmargin">This is the only one (in this menu state) thing that runs editor. There are no any buttons inside of game, this is the only way of "how to open editor" ... and you need to have premium account!</h5>
				<div style="margin-top: 1.5em;"></div>
			</div>
		</div>

		<!-- Level -->
		<div class="row myfont">
			<div class="twelve columns" style="text-align: center; margin-top: 3em;">
				<h4 class="nobotmargin">Level - choosing world</h4>
				<!-- Play -->
				<h5 class="nobotmargin"><span class="redspan">@play</span> - <span class="redspan">@start</span> - <span class="redspan">@go</span></h5>
				<h5 class="nobotmargin">Finally starts the real game but first click on one world because only then you can start.</h5>
				<div style="margin-top: 1.5em;"></div>

				<!-- Back to menu -->
				<h5 class="nobotmargin"><span class="redspan">@menu</span> - <span class="redspan">@back</span>
				 - <span class="redspan">@aback</span> - <span class="redspan">@return</span></h5>
				<h5 class="nobotmargin">You are so positively surprised about menu look which I've created so you typing this to go back and admire, thanks!</h5>
				<div style="margin-top: 1.5em;"></div>
			</div>
		</div>

		<!-- Play -->
		<div class="row myfont">
			<div class="twelve columns" style="text-align: center; margin-top: 3em;">
				<h4 class="nobotmargin">Play - you are playing</h4>
				<!-- Back to level state -->
				<h5 class="nobotmargin"><span class="redspan">@level</span> - <span class="redspan">@back</span>
				 - <span class="redspan">@aback</span> - <span class="redspan">@return</span></h5>
				<h5 class="nobotmargin">Oh God! I've chosen wrong world! I need to type one of this commands to go back to level state where I can choose the right one!</h5>
				<div style="margin-top: 1.5em;"></div>

				<!-- Back to menu -->
				<h5 class="nobotmargin"><span class="redspan">@menu</span></h5>
				<h5 class="nobotmargin">I can't believe how crazy you are about menu I've made! Type @menu to go back to menu and just go away...</h5>
				<div style="margin-top: 1.5em;"></div>

				<!-- Collision -->
				<h5 class="nobotmargin"><span class="redspan">@collision</span></h5>
				<h5 class="nobotmargin">This is when magic happens, you turn on/off (depends what state you have currently). After this command you see how all collisions look like and work.</h5>
				<div style="margin-top: 1.5em;"></div>
			</div>
		</div>

		<!-- Editor -->
		<div class="row myfont">
			<div class="twelve columns" style="text-align: center; margin-top: 3em;">
				<h4 class="nobotmargin">Editor - premium accounts</h4>
				<!-- Back to menu -->
				<h5 class="nobotmargin"><span class="redspan">@menu</span> - <span class="redspan">@back</span>
				 - <span class="redspan">@aback</span> - <span class="redspan">@return</span></h5>
				<h5 class="nobotmargin">Back to menu.</h5>
				<div style="margin-top: 1.5em;"></div>

				<!-- Load -->
				<h5 class="nobotmargin"><span class="redspan">@load</span></h5>
				<h5 class="nobotmargin">Load current local world, it would be "world_" if you didn't change the path.</h5>
				<div style="margin-top: 1.5em;"></div>

				<!-- Save -->
				<h5 class="nobotmargin"><span class="redspan">@save</span></h5>
				<h5 class="nobotmargin">Save current open world, it would be "world_" if you didn't change the path.</h5>
				<div style="margin-top: 1.5em;"></div>

				<!-- Focus -->
				<h5 class="nobotmargin"><span class="redspan">@focus</span> - <span class="redspan">@focus turn</span>
				 - <span class="redspan">@focus on</span> - <span class="redspan">@focus off</span></h5>
				<h5 class="nobotmargin">By this commands you manipulate the focus. When focus is on it's let you change the path which you have set at start as "world_". By first two you change current state for instance on->off, off->on.</h5>
				<div style="margin-top: 1.5em;"></div>

				<!-- Rubbish -->
				<h5 class="nobotmargin"><span class="redspan">@rubbish</span> - <span class="redspan">@erase</span>
				 - <span class="redspan">@delete</span> - <span class="redspan">@remove</span>
				 - <span class="redspan">@cut</span> - <span class="redspan">@excise</span></h5>
				<h5 class="nobotmargin">Yea I know, too many possibilities. Each one turn current "rubbish mode" state. If it's on by click you erase not put.</h5>
				<div style="margin-top: 1.5em;"></div>
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