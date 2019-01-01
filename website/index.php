<?php
	session_start();
	
	unset($_SESSION['error']);
	unset($_SESSION['e_username']);
	unset($_SESSION['e_email']);
	unset($_SESSION['e_password']);
	unset($_SESSION['e_passwordcon']);
	unset($_SESSION['e_bot']);

	require_once("common/head.php");
?>

<!-- NAVBAR -->
	<?php require_once("common/navbar-b.php"); ?>

	<li><a class="japokki-white A3" href="#about">About</a></li>
	<li><a class="japokki-white A3" href="#section4">High Scores</a></li>
	<li><a class="btn-floating btn-medium pulse blue lighten-1" href="home.php"><i class="material-icons">home</i></a></li>

	<?php
		if(!isset($_SESSION['logged']))
		{
			echo '<li><a class="btn-floating pulse amber lighten-1" href="other/commands.php" data-target="mobile-demo"><i class="material-icons">receipt</i></a></li>';
			echo "<li><a class='dropdown-trigger btn blue-grey darken-1 japokki-white' href='#' data-target='dropdown1'>User</a></li>";
		}
	?>

	<?php
		require_once("common/navbar-e.php");

		if(!isset($_SESSION['logged']))
		{
			echo "<ul id='dropdown1' class='dropdown-content'>";
			echo '<li><a class="japokki-black" href="user/login/loginform.php">Log In</a></li>';
			echo '<li><a class="japokki-black" href="user/register/registerform.php">Sign Up</a></li>';
			echo '</ul>';
		}

		require_once("common/sidenav-b.php");
	?>

	<li><a href="#about" class="japokki-black"><i class="material-icons">short_text</i>About </a></li>
	<li><a href="#section4" class="japokki-black"><i class="material-icons">insert_chart</i>High Scores </a></li>
	<li><a href="home.php" class="japokki-black"><i class="material-icons">home</i>Home </a></li>

	<?php
		if(!isset($_SESSION['logged']))
		{
			echo '<li><a class="dropdown-trigger japokki-black" href="#" data-target="dropdown2"><i class="material-icons">person</i>User</a></li>';
			echo "<ul id='dropdown2' class='dropdown-content'>";
			echo '<li><a class="japokki-black" href="user/login/loginform.php">Log In</a></li>';
			echo '<li><a class="japokki-black" href="user/register/registerform.php">Sign Up</a></li>';
			echo '</ul>';
		}

		require_once("common/sidenav-e.php");
	?>
<!-- END OF NAVBAR -->

<!-- TOP -->
<div class="parallax-container valign-wrapper">
	<div class="parallax"><img src="images/parallax/0"></div>
	<div class="container">
		<div class="row">
			<div class="col s9">
				<h4 class="left-align valign japokki-white A7" style="background-color: rgba(20, 20, 20, 0.2); border-radius: 10px; padding: 25px;">Some text some text some text some text some text some text some text some text some text some text some text.</h4>
			</div>
		</div>
		<div class="row">
			<a class="btn-large hoverable z-depth-5 disabled japokki-white" target="_blank" href="#">Linux<a/>
				<a class="btn-large hoverable z-depth-5 disabled japokki-white" target="_blank" href="#">Windows<a/>
				</div>
				<div class="row">
					<a class="btn hoverable blue-grey darken-1 japokki-white" target="_blank" href="https://github.com/devmichalek/Combat-Halloween">Source Code<a/>
						<a class="btn hoverable blue-grey darken-1 disabled japokki-white" target="_blank" href="#">You Tube<a/>
						</div>
					</div>
				</div>

				<!-- ABOUT -->
				<div id="about" class="scrollspy">
					<div class="section white">
						<div class="row container">
							<h2 class="japokki-black">About</h2>
							<p class="japokki-black A2">Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Lorem ipsum dolor sit amet, consectetuer adipiscing elit.</p>
						</div>
					</div>
				</div>

				<div class="container">
					<div class="row">

						<div id="section655555" class="scrollspy japokki">
							<div class="col s12 m3">
								<div class="card blue-grey darken-1">
									<div class="card-content">
										<span class="card-title"><p class="info">Music</p></span>
										<p class="info">All music stuff is made by Simon Hjort who is an instrumental composer stationed in Sweden.</p>
									</div>
									<div class="card-action cyan darken-2">
										<a target="_blank" href="https://www.youtube.com/channel/UCsaypaIo57-x7AfxuPmW2Ow">yt</a>
										<a target="_blank" href="https://soundcloud.com/simon_hjort">soundcloud</a>
									</div>
								</div>
							</div>

							<div class="col s12 m3">
								<div class="card teal lighten-2">
									<div class="card-content">
										<span class="card-title"><p class="info">Fonts</p></span>
										<p class="info">Below two authors of fonts, website uses one of them. I owe you one.</p>
									</div>
									<div class="card-action brown darken-4">
										<a target="_blank" href="https://www.behance.net/gallery/19084983/Jaapokki-Free-Font">Mikko Nuuttila</a>
										<a target="_blank" href="https://www.dafont.com/badaboom-bb.font">Blambot</a>
									</div>
								</div>
							</div>

							<div class="col s12 m3">
								<div class="card amber lighten-1">
									<div class="card-content">
										<span class="card-title"><p class="info">Sounds</p></span>
										<p class="info">I used to get .wav files from those two websites.</p>
									</div>
									<div class="card-action lime lighten-3">
										<a target="_blank" href="http://soundbible.com/">soundbible</a>
										<a target="_blank" href="http://www.freesound.org/">freesound</a>
									</div>
								</div>
							</div>

							<div class="col s12 m3">
								<div class="card grey darken-2">
									<div class="card-content">
										<span class="card-title"><p class="info">Tools</p></span>
										<p class="info">Presumably all tools which I used, starting from converters to sprite tools.</p>
									</div>
									<div class="card-action grey darken-4">
										<a target="_blank" href="http://bootsnipp.com/buttons">Button Generator</a>
										<a target="_blank" href="http://www.online-convert.com/">online-convert</a>
										<a target="_blank" href="http://spritegen.website-performance.org/">spritegen</a>
										<a target="_blank" href="https://bulkresizephotos.com/">bulkresizephotos</a>
										<a target="_blank" href="https://twistedwave.com/online/">twistedwave</a>
										<a target="_blank" href="http://mp3cut.net/">mp3cut.net</a>
									</div>
								</div>
							</div>

							<div id="section5.2" class="scrollspy">
								<div class="col s12 m3">
									<div class="card brown lighten-3">
										<div class="card-content">
											<span class="card-title"><p class="info">Sprites</p></span>
											<p class="info">Enormous acknowledgements for all sprite authors especially Gameart2d.com and irmirx.</p>
										</div>
										<div class="card-action deep-orange darken-4">
											<a target="_blank" href="http://www.gameart2d.com/freebies.html">Gameart2d.com</a>
											<a target="_blank" href="http://opengameart.org/users/irmirx">irmirx</a>
											<a target="_blank" href="http://opengameart.org/content/heart-0">Smileymensch</a>
											<a target="_blank" href="http://loading.io/">loading.io</a>
											<a target="_blank" href="http://opengameart.org/content/game-coins-sprite">craftpix.net</a>
										</div>
									</div>
								</div>
							</div>

							<div class="col s12 m3">
								<div class="card brown lighten-3">
									<div class="card-content">
										<span class="card-title"><p class="info">Sprites cd.</p></span>
										<p class="info">Follow-up to sprite authors, thanks again!</p>
									</div>
									<div class="card-action deep-orange darken-4">
										<a target="_blank" href="http://opengameart.org/content/high-res-fire-ball">Robert Brooks</a>
										<a target="_blank" href="https://opengameart.org/content/radial-lightning-effect">13rice</a>
										<a target="_blank" href="https://opengameart.org/content/arw-explosion">Chromaeleon</a>
										<a target="_blank" href="https://opengameart.org/content/smoke-aura">MrBeast</a>
										<a target="_blank" href="https://opengameart.org/users/bevouliincom">bevouliin.com</a>
										<a target="_blank" href="http://opengameart.org/content/ui-pack">Kenney</a>
									</div>
								</div>
							</div>

							<div class="col s12 m3">
								<div class="card green accent-2">
									<div class="card-content">
										<span class="card-title"><p class="info">Multimedia</p></span>
										<p class="info">Multimedia that's it.</p>
									</div>
									<div class="card-action blue-grey darken-4">
										<a target="_blank" href="https://www.sfml-dev.org/">SFML</a>
										<a target="_blank" href="https://www.libsdl.org/projects/SDL_mixer/">SDL_Mixer</a>
									</div>
								</div>
							</div>


							<div class="col s12 m3">
								<div class="card blue accent-1">
									<div class="card-content">
										<span class="card-title"><p class="info">Other</p></span>
										<p class="info">I'm guessing it's not necessery, but it's lovely.</p>
									</div>
									<div class="card-action blue accent-4">
										<a target="_blank" href="https://codelite.org/">CodeLite</a>
										<a target="_blank" href="https://sublimetext.com/2">SublimeText2</a>
										<a target="_blank" href="https://emmet.io/">Emmet</a>
										<a target="_blank" href="http://www.audacityteam.org/">Audacityteam</a>
										<a target="_blank" href="https://www.gimp.org/">Gimp</a>
									</div>
								</div>
							</div>
						</div>

					</div>
				</div>

			</div>
		</div>

	<?php require_once("common/footer.php"); ?>