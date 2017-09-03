<?php

	session_start();

	if(!isset($_SESSION['logged']))
	{
		header('Location: home.php');
		exit();
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

	if( isset( $_GET['name'] ) && isset( $_GET['level'] ) )
	{
    	// Connect.
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
				$name = $_GET['name'];
				$level = $_GET['level'];
				unset( $_GET['name'] );
				unset( $_GET['level'] );

				$armour_add = 0;
				$health_add = 0;
				$damage_add = 0;
				$speed_add = 0;
				$diamond_multiplier = 0;

				if( $level < 10 )
				{
					if( $name == 'helmet' )
					{
						$armour_add = 3.5;
						$health_add = 3;
						$speed_add = -1;
					}
					else if( $name == 'body' )
					{
						$armour_add = 2;
						$health_add = 5;
					}
					else if( $name == 'shield' )
					{
						$armour_add = 4;
						$health_add = 1;
						$speed_add = -2;
					}
					else if( $name == 'sword' )
					{
						$damage_add = 24;
						$speed_add = -2;
					}
					else if( $name == 'boots' )
					{
						$armour_add = 1.5;
						$speed_add = 10;
					}
				}
				else
				{
					$diamond_multiplier = 1;

					if( $name == 'helmet' )
					{
						$armour_add = 27;
						$health_add = 23;
					}
					else if( $name == 'body' )
					{
						$armour_add = 18;
						$health_add = 54;
					}
					else if( $name == 'shield' )
					{
						$armour_add = 32;
						$health_add = 13;
					}
					else if( $name == 'sword' )
					{
						$damage_add = 972;
					}
					else if( $name == 'boots' )
					{
						$armour_add = 12.5;
					}
				}

				$line = $_SESSION[ $name ];
				$newmoney = $_SESSION['money'] -getNumber('c', $line);
				$newdiamonds = $_SESSION['diamonds']  -getNumber('r', $line);

				$mystr = 'l'.(getNumber('l', $line) +1).'c'.intval((getNumber('c', $line)*1.8)).'r'.(getNumber('r', $line) +$diamond_multiplier).'a'.(getNumber('a', $line) +$armour_add).'h'.(getNumber('h', $line) +$health_add).'d'.(getNumber('d', $line) +$damage_add).'s'.(getNumber('s', $line) +$speed_add);

				$username_now = $_SESSION['username'];
				$connection->query("UPDATE users SET $name='$mystr' WHERE username='$username_now'");
				$connection->query("UPDATE users SET money='$newmoney' WHERE username='$username_now'");
				$connection->query("UPDATE users SET diamonds='$newdiamonds' WHERE username='$username_now'");

				$_SESSION[ $name ] = $mystr;
				$_SESSION['money'] = $newmoney;
				$_SESSION['diamonds'] = $newdiamonds;

				$connection->close();

				// echo $name.' ';
				// echo $username_now.' ';
				// echo $mystr;

				header('Location: home.php');
			}
		}
		catch(Exception $e)
		{
			echo 'Error';
			// echo 'Error: '.$e;
		}
  	}
  	else
  	{
  		echo 'Nope';
  	}
?>