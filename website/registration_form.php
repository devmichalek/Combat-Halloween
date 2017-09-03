<?php
	session_start();

	unset($_SESSION['error']);

	function generateRandomString($length = 30)
	{
	    $characters = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
	    $charactersLength = strlen($characters);
	    $randomString = '';
	    for ($i = 0; $i < $length; $i++) {
	        $randomString .= $characters[rand(0, $charactersLength - 1)];
	    }
	    return $randomString;
	}

	if( isset($_POST['email']))
	{
		$success = true;

		// USERNAME
		$username = $_POST['username'];
		if((strlen($username)) < 4)
		{
			$success = false;
			$_SESSION['e_username'] = "Please choose a name with at least 4 characters.";
		}
		else if((strlen($username)) > 20)
		{
			$success = false;
			$_SESSION['e_username'] = "Name may contain at the maximum 20 characters.";
		}
		else if(!ctype_alnum($username))
		{
			$success = false;
			$_SESSION['e_username'] = "This name is unavailable.";
		}

		// EMAIL
		$email = $_POST['email'];
		$email_safe = filter_var($email, FILTER_SANITIZE_EMAIL);
		if(!filter_var($email_safe, FILTER_VALIDATE_EMAIL) || $email_safe != $email)
		{
			$success = false;
			$_SESSION['e_mail'] = "Valid adress email required.";
		}

		// PASSWORD
		$password = $_POST['password'];
		$passwordcon = $_POST['passwordcon'];
		if((strlen($password)) < 8)
		{
			$success = false;
			$_SESSION['e_password'] = "Please choose a password with at least 8 characters.";
		}
		else if((strlen($password)) > 20)
		{
			$success = false;
			$_SESSION['e_password'] = "Password may contain at the maximum 20 characters.";
		}
		else if($password != $passwordcon)
		{
			$success = false;
			$_SESSION['e_passwordcon'] = "Password does not match.";
		}
		$password_hashed = password_hash($password, PASSWORD_DEFAULT);
		
		// STATUTE
		if( !isset($_POST['statute']))
		{
			$success = false;
			$_SESSION['e_statute'] = "Please read and check terms of use.";
		}

		// RECAPTCHA
		$mysecret = "6LcmdisUAAAAAEyXWdm5N19fiP69rQUw9uJP7sU7";
		$confirm = file_get_contents('https://www.google.com/recaptcha/api/siteverify?secret='.$mysecret.'&response='.$_POST['g-recaptcha-response']);
		if(!json_decode($confirm)->success)
		{
			$success = false;
			$_SESSION['e_bot'] = "Confirm humanity.";
		}

		// REMEMBER DATA
		$_SESSION['rem_username'] = $username;
		$_SESSION['rem_email'] = $email;
		$_SESSION['rem_password'] = $password;
		$_SESSION['rem_passwordcon'] = $passwordcon;
		if(isset($_POST['statute']))
		{
			$_SESSION['rem_statute'] = true;
		}

		// OTHER
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
				// IF EMAIL EXIST
				$result = $connection->query("SELECT ID FROM users WHERE email='$email'");
				if(!$result)
				{
					throw new Exception($connection->error);
				}
				$how_many_emails = $result->num_rows;
				if($how_many_emails > 0)
				{
					$success = false;
					$_SESSION['e_mail'] = "This email already exists.";
				}

				// IF USERNAME EXISTS
				$result = $connection->query("SELECT ID FROM users WHERE username='$username'");
				if(!$result)
				{
					throw new Exception($connection->error);
				}
				$how_many_usernames = $result->num_rows;
				if($how_many_usernames > 0)
				{
					$success = false;
					$_SESSION['e_username'] = "This username already exists.";
				}

				// SUCCESS
				if( $success )
				{
					// l - level
					// c - cost
					// a - armour
					// h - health
					// d - damage
					// s - speed

					$first_time = date("d.m.Y");
					$money = 100;
					$diamonds = 75;
					$helmet = 	"l1c25r0a1h5d0s-1";
					$body = 	"l1c40r0a0h10d0s0";
					$shield = 	"l1c30r0a0h4d0s-2";
					$sword = 	"l1c40r0a0h0d64s-2";
					$boots = 	"l1c30r0a0h0d0s10";
					$world =	"&1*&";
					$activation_code = generateRandomString();

					if($connection->query("INSERT INTO users VALUES (NULL, '$username', '$password_hashed', '$email', '$first_time', '$money', '$diamonds', '$helmet', '$body', '$shield', '$sword', '$boots', '$world', '0', '0', '$activation_code')"))
					{
						$_SESSION['wellregistered'] = true;
						$_SESSION['temporaryusername'] = $username;
						$_SESSION['temporaryemail'] = $email;
						$_SESSION['activation_code'] = $activation_code;
						header('Location: welcome.php');
					}
					else
					{
						throw new Exception($connection->error);
					}
				}

				$connection->close();
			}
		}
		catch(Exception $e)
		{
			echo 'Error';
			// echo 'Error: '.$e;
		}
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
	<title>Registration - Combat Halloween</title>
	<link rel="stylesheet" href="skeleton.css">
	<link rel="stylesheet" href="normalize.css">
	<link rel="stylesheet" href="main.css">
	<link rel="shortcut icon" href="images/icon.png">
	<script src='https://www.google.com/recaptcha/api.js'></script>
</head>
<body>

	<div class="container">
		
		<!-- Header -->
		<div class="twelve columns">
			<section class="header" style="text-align: center; margin-top: 6em;">
				<div class="title myfont">
					<h2>Sign Up your account - Combat <span style="color: #F2583E; margin-right: 0em; margin-left: 0em; display: inline-block;">Halloween</span></h2>
				</div>
			</section>
		</div>


		<form method="post">
			<div class="row myfont">
			    <div class="offset-by-three six columns myfont" style="text-align: center; margin-top: 3em;">
			      <label for="exampleEmailInput" style="text-align: center;">Your username</label>
			      <input class="u-full-width" type="text" placeholder="username" id="exampleEmailInput" name="username" value="<?php
					if(isset($_SESSION['rem_username']))
					{
						echo $_SESSION['rem_username'];
						unset($_SESSION['rem_username']);
					}?>">
			    </div>

			    <div class="offset-by-three six columns myfont" style="text-align: center; margin-top: 1em;">
			      <label for="exampleEmailInput" style="text-align: center;">Your email</label>
			      <input class="u-full-width" type="email" placeholder="email" id="exampleEmailInput" name="email" value="<?php
					if(isset($_SESSION['rem_email']))
					{
						echo $_SESSION['rem_email'];
						unset($_SESSION['rem_email']);
					}?>">
			    </div>
			</div>

			<div class="row myfont">
			    <div class="offset-by-three six columns myfont" style="text-align: center; margin-top: 1em;">
			      <label for="exampleEmailInput" style="text-align: center;">Your password</label>
			      <input class="u-full-width" type="password" placeholder="password" id="exampleEmailInput" name="password" value="<?php
					if(isset($_SESSION['rem_password']))
					{
						echo $_SESSION['rem_password'];
						unset($_SESSION['rem_password']);
					}?>">
			    </div>

			    <div class="offset-by-three six columns myfont" style="text-align: center; margin-top: 1em;">
			      <label for="exampleEmailInput" style="text-align: center;">Confirm password</label>
			      <input class="u-full-width" type="password" placeholder="password" id="exampleEmailInput" name="passwordcon" value="<?php
					if(isset($_SESSION['rem_passwordcon']))
					{
						echo $_SESSION['rem_passwordcon'];
						unset($_SESSION['rem_passwordcon']);
					}?>">
			    </div>
		  	</div>

		  	<label class="example-send-yourself-copy" style="text-align: center; margin-top: 1em;">
			    <input type="checkbox" name="statute" <?php
					if(isset($_SESSION['rem_statute']))
					{
						echo "checked";
						unset($_SESSION['rem_statute']);
					}
					?>/>
				<span class="label-body myfont">I accept terms of use.</span>
			</label>

			<div class="g-recaptcha" style="margin: auto; margin-top: 1em; display: table;" data-sitekey="6LcmdisUAAAAAL5BuJQEYffeBS-LklUxKw8DLDwn"></div>

			
			<div style="text-align: center; margin-top: 1em;">
				<input class="button-primary myfont" type="submit" value="Register">
			</div>
		</form>


		<?php
			// Errors.
			echo '<div class="twelve columns myfont" style="text-align: center; color: red;">';
			if( isset($_SESSION['e_username']))
			{
				echo $_SESSION['e_username'];
				unset($_SESSION['e_username']);
			}
			else if( isset($_SESSION['e_mail']))
			{
				echo $_SESSION['e_mail'];
				unset($_SESSION['e_mail']);
			}
			else if( isset($_SESSION['e_password']))
			{
				echo $_SESSION['e_password'];
				unset($_SESSION['e_password']);
			}
			else if( isset($_SESSION['e_passwordcon']))
			{
				echo $_SESSION['e_passwordcon'];
				unset($_SESSION['e_passwordcon']);
			}
			else if( isset($_SESSION['e_statute']))
			{
				echo $_SESSION['e_statute'];
				unset($_SESSION['e_statute']);
			}
			else if( isset($_SESSION['e_bot']))
			{
				echo $_SESSION['e_bot'];
				unset($_SESSION['e_bot']);
			}
			echo '</div>';
		?>
		
		<!-- Footer -->
		<div class="twelve columns" style="text-align: center; margin-top: 3em;">
			<footer>
				<h6 class="myfont nobotmargin notopmargin">
					<span style="display: inline-block;">&nbsp;&nbsp;&nbsp;Back to <a href="index.php" style="color: #444444;">main site</a>&nbsp;&nbsp;&nbsp;</span>
					<span style="display: inline-block;">Already have an account? <a href="login_form.php" style="color: #444444;">Log In</a></span>
				</h6>
			</footer>
		</div>

	</div>
</body>
</html>