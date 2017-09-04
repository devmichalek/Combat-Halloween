<?php
	session_start();

	unset($_SESSION['error']);
	unset($_SESSION['e_username']);
	unset($_SESSION['e_mail']);
	unset($_SESSION['e_password']);
	unset($_SESSION['e_passwordcon']);
	unset($_SESSION['e_bot']);
?>

<!DOCTYPE html>
<html lang="en">
<head>
	<!-- Standard Meta -->
	<meta charset="UTF-8" />
	<meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1" />
	<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0">

	<!-- Site Properties -->
	<title>Combat Halloween</title>
	<link rel="stylesheet" href="skeleton.css">
	<link rel="stylesheet" href="normalize.css">
	<link rel="stylesheet" href="main.css">
	<link rel="shortcut icon" href="images/icon.png">
</head>
<body>
	<div class="container">
		<!-- Log In button and Sign Up button-->
		<div class="twelve columns">
			<div class="row" style="text-align: right; margin-top: 1em;">
				<a class="button button myfont" href="login_form.php">Log In</a>
				<a class="button button-primary myfont" href="registration_form.php">Sign Up</a>
			</div>
		</div>

		<!-- Header -->
		<div class="twelve columns">
			<section class="header" style="text-align: center; margin-top: 5em;">
				<div class="title myfont">
					<h2>A dead simple, free, <span style="color: #F2583E; margin-right: 0em; margin-left: 0em; display: inline-block;">2D platform</span> game.</h2>
				</div>
			</section>
		</div>
		<div class="twelve columns" style="text-align: center; margin-top: 1em;">
			<a class="button button-primary myfont" href="#">Download</a>
		</div>

		
		<!-- Specs -->
		<div class="row">
			<div class="six columns" style="text-align: center; margin-top: 5em;">
					<img class="value-img" src="images/0.png" width="240" height="124">
					<h5 class="myfont">
						Take a magical sword as well as tough shield and go fight with monsters lurking and waiting in bushes for you. Don't you want to battle all alone with them? Hold on for next update with multiplayer option!
					</h5>
			</div>
			<div class="six columns" style="text-align: center; margin-top: 5em;">
					<img class="value-img" src="images/1.png" width="240" height="124">
					<h5 class="myfont">
					Built own worlds and see how the others struggle with your unnique traps and foes placed right.
					World editor is much fun plus you don't have to spend lots of time learning. It's as easy as anything.
					</h5>
			</div>
		</div>

		<!-- About -->
		<div class="row">
			<div class="twelve columns" style="text-align: left; margin-top: 5em;">
					<h3 class="myfont nobotmargin">About</h3>
			</div>
			<div class="twelve columns" style="text-align: left;">
					<h5 class="myfont">
					Combat Halloween is something made by my own fantasies, because I like programming for then seeing effects of my work, like a moving and fighting skeleton or fairly alive animations with own goal in game. I would like to remind that I'm  not graphic designer or else music maker. Just programming stuff with support as Gimp, tho. For any advice about game like a new rapid falling spikes able to kill character in one second, because you are fucking insane about spikes, you have to contact me by email at the bottom of this website that you've opened.
					</h5>
			</div>
		</div>

		<!-- Code -->
		<div class="row">
			<div class="twelve columns" style="text-align: left; margin-top: 5em;">
					<h3 class="myfont  nobotmargin">Code & Structure & Assets</h3>
			</div>
			<div class="twelve columns" style="text-align: left;">
					<h5 class="myfont">
					Let's start with code. <b>C++</b> and <b>SFML</b> nothing less nothing more. <b>Skeleton</b> framework is used in every part of this website. Structure is simple, one huge class called <b>engine</b> contains all smaller classes such as <b>intro</b>, <b>logging</b>, <b>menu</b> etc. Then in all of those smaller classes we can find something like buttons, background, music, keyboard mechanism. About assets: More often than not I used to take sprites from <a href="http://www.gameart2d.com/" target="_blank">Game Art 2D</a> and <a href="https://opengameart.org/" target="_blank">Open Game Art</a>. Music is made by <a href="https://soundcloud.com/simon_hjort" target="_blank">Simon Hjort</a> who is an instrumental composer stationed in Sweden. Chunks used to be taken from random sites with appropriate permits.
					</h5>
			</div>
		</div>

		<!-- Footer -->
		<div class="twelve columns" style="text-align: center; margin-top: 10em;">
			<footer>
				<h6 class="myfont nobotmargin notopmargin">
					<span style="display: inline-block;">&nbsp;&nbsp;&nbsp;Visit my github: <a href="https://github.com/Adriqun" style="color: #444444;">Adrian Michalek</a>&nbsp;&nbsp;&nbsp;</span>
					<span style="display: inline-block;">Back to <a href="http://adrianmichalek.pl/" style="color: #444444;">main site</a></span>
				</h6>
				<h6 class="myfont nobotmargin notopmargin">
					Contact me: adrmic98@gmail.com or contact@adrianmichalek.pl
				</h6>
			</footer>
		</div>

	</div>
</body>
</html>