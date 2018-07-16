<?php
	session_start();

	unset($_SESSION['error']);
	unset($_SESSION['e_username']);
	unset($_SESSION['e_email']);
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
   <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=1.0">
    
	<!-- Site Properties -->
   <title>Combat Halloween</title>
   <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0-rc.2/css/materialize.min.css">
   <link rel = "stylesheet" href = "https://fonts.googleapis.com/icon?family=Material+Icons">
   <link rel="stylesheet" type="text/css" href="main.css">
   <link rel="icon" href="https://user-images.githubusercontent.com/19840443/42683508-c8c24644-868d-11e8-9a8a-cbde02588774.png">
   
   <meta http-equiv="cache-control" content="max-age=0" />
    <meta http-equiv="cache-control" content="no-cache" />
    <meta http-equiv="cache-control" content="no-store" />
    <meta http-equiv="cache-control" content="must-revalidate" />
    <meta http-equiv="expires" content="0" />
    <meta http-equiv="expires" content="Tue, 01 Jan 1980 1:00:00 GMT" />
    <meta http-equiv="pragma" content="no-cache" />
</head>
<body>
	<!-- NAVBAR -->
	<div class="navbar-fixed">
		<nav>
		    <div class="nav-wrapper">
		      	<a class="nav-main brand-logo">&nbsp;&nbsp;&nbsp;Combat&nbsp;Halloween</a>
		      	<a href="#" data-target="mobile-demo" class="sidenav-trigger"><i class="material-icons">menu</i></a>
		      	<ul id="nav-mobile" class="right hide-on-med-and-down">
			    	<li><a class="nav" href="home.php">Home</a></li>
			      	<li><a class="nav" href="#about">About</a></li>
			      	<li><a class="nav" href="#contact">Contact</a></li>
			      	<li><a class="nav" href="#section4">High Scores</a></li>
			      	<a class='dropdown-trigger btn nav-button' href='#' data-target='dropdown1'>User</a>
		    	</ul>
				<ul id='dropdown1' class='dropdown-content'>
				    <li><a class="nav" href="user/loginform.php">Log In</a></li>
					<li><a class="nav" href="user/register.php">Sign In</a></li>
				</ul>
		    </div>
		</nav>
		
	</div>
	<ul class="nav-main sidenav" id="mobile-demo">
	    <li><a class="nav" href="home.php">Home</a></li>
      	<li><a class="nav" href="#about">About</a></li>
      	<li><a class="nav" href="#contact">Contact</a></li>
      	<li><a class="nav" href="#section4">High Scores</a></li>
      	<a class='dropdown-trigger btn' href='#' data-target='dropdown2'>User</a>
      	<ul id='dropdown2' class='dropdown-content'>
			<li><a class="nav" href="user/loginform.php">Log In</a></li>
			<li><a class="nav" href="user/register.php">Sign In</a></li>
		</ul>
	</ul>

	<!-- TOP -->
	<div class="parallax-container valign-wrapper">
	    <div class="parallax"><img src="images/parallax/0"></div>
	    	<div class="container">
	    	<div class="row">
	    		<div class="col s9 white-text">
	    			<h4 class="thin-text left-align valign">Right now game is available only for windows users. I still migrate source code for linux. Download below.</h4>
	    		</div>
	    	</div>
	    	<div class="row">
	    		<div class="col 14">
	    			<a class="waves-effect waves-light btn-large hoverable nav-button z-depth-5 disabled" target="_blank" href="#">Linux<a/>
	    			<a class="waves-effect waves-light btn-large hoverable nav-button z-depth-5" target="_blank" href="#">Windows<a/>
	    		</div>
	    	</div>
    		<div class="row">
    			<div class="col 14">
    				<a class="btn waves-effect waves-light hoverable nav-button blue-grey" target="_blank" href="https://github.com/devmichalek/Combat-Halloween">Source Code<a/>
    				<a class="btn waves-effect waves-light hoverable nav-button blue-grey" target="_blank" href="#">You Tube<a/>
    			</div>
    		</div>
	    </div>
	</div>
	
	<!-- ABOUT -->
	<div id="about" class="header scrollspy">
	<div class="section white">
	    <div class="row container">
	      <h2 class="header">About</h2>
	      <p class="grey-text text-darken-3 lighten-3 info">Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Lorem ipsum dolor sit amet, consectetuer adipiscing elit.</p>
	    </div>
	</div>
	</div>


	<!-- CONTACT -->
	<div id="contact" class="header scrollspy">
		<div class="parallax-container valign-wrapper">
		    <div class="container">
		    	<div class="row center">
		    		<div class="col l10 offset-l1 valign">
		    			<h4 class="center-align white-text thin-text">Interested in working together? Contact me: devmichalek@gmail.com</h4>
		    		</div>
		    	</div>
		    </div>
		    <div class="parallax"><img src="images/parallax/1.png"></div>
		</div>
	</div>
	
	<div class="container">
		<div class="row">

	<div id="section5.1" class="header scrollspy">
	        <div class="col s12 m3">
	          <div class="card blue-grey darken-1">
	            <div class="card-content white-text">
	              <span class="card-title"><p class="info">Music</p></span>
	              <p class="info">All music stuff is made by Simon Hjort who is an instrumental composer stationed in Sweden.</p>
	            </div>
	            <div class="card-action cyan darken-2">
	              <a class="cardy" target="_blank" href="https://www.youtube.com/channel/UCsaypaIo57-x7AfxuPmW2Ow">yt</a>
	              <a class="cardy" target="_blank" href="https://soundcloud.com/simon_hjort">soundcloud</a>
	            </div>
	          </div>
	        </div>

	        <div class="col s12 m3">
	          <div class="card teal lighten-2">
	            <div class="card-content white-text">
	              <span class="card-title"><p class="info">Fonts</p></span>
	              <p class="info">Below two authors of fonts, website uses one of them. I owe you one.</p>
	            </div>
	            <div class="card-action brown darken-4">
	              <a class="cardy" target="_blank" href="https://www.behance.net/gallery/19084983/Jaapokki-Free-Font">Mikko Nuuttila</a>
	              <a class="cardy" target="_blank" href="http://www.dafont.com/badaboom-bb.font">Blambot</a>
	            </div>
	          </div>
	        </div>

	        <div class="col s12 m3">
	          <div class="card amber lighten-1">
	            <div class="card-content white-text">
	              <span class="card-title"><p class="info">Sounds</p></span>
	              <p class="info">I used to get .wav files from those two websites.</p>
	            </div>
	            <div class="card-action lime lighten-3">
	              <a class="cardy" target="_blank" href="http://soundbible.com/">soundbible</a>
	              <a class="cardy" target="_blank" href="http://www.freesound.org/">freesound</a>
	            </div>
	          </div>
	        </div>

	        <div class="col s12 m3">
	          <div class="card grey darken-2">
	            <div class="card-content white-text">
	              <span class="card-title"><p class="info">Tools</p></span>
	              <p class="info">Presumably all tools which I used, starting from converters to sprite tools.</p>
	            </div>
	            <div class="card-action grey darken-4">
	            	<a class="cardy" target="_blank" href="http://bootsnipp.com/buttons">Button Generator</a>
		            <a class="cardy" target="_blank" href="http://www.online-convert.com/">online-convert</a>
		            <a class="cardy" target="_blank" href="http://spritegen.website-performance.org/">spritegen</a>
		            <a class="cardy" target="_blank" href="https://bulkresizephotos.com/">bulkresizephotos</a>
		            <a class="cardy" target="_blank" href="https://twistedwave.com/online/">twistedwave</a>
		            <a class="cardy" target="_blank" href="http://mp3cut.net/">mp3cut.net</a>
	            </div>
	          </div>
	        </div>

			<div id="section5.2" class="header scrollspy">
	        <div class="col s12 m3">
	          <div class="card brown lighten-3">
	            <div class="card-content white-text">
	              <span class="card-title"><p class="info">Sprites</p></span>
	              <p class="info">Enormous acknowledgements for all sprite authors especially Gameart2d.com and irmirx.</p>
	            </div>
	            <div class="card-action deep-orange darken-4">
	            	<a class="cardy" target="_blank" href="http://www.gameart2d.com/freebies.html">Gameart2d.com</a>
		            <a class="cardy" target="_blank" href="http://opengameart.org/users/irmirx">irmirx</a>
		            <a class="cardy" target="_blank" href="http://opengameart.org/content/heart-0">Smileymensch</a>
		            <a class="cardy" target="_blank" href="http://loading.io/">loading.io</a>
		            <a class="cardy" target="_blank" href="http://opengameart.org/content/game-coins-sprite">craftpix.net</a>
	            </div>
	          </div>
	        </div>
	        </div>

	        <div class="col s12 m3">
	          <div class="card brown lighten-3">
	            <div class="card-content white-text">
	              <span class="card-title"><p class="info">Sprites cd.</p></span>
	              <p class="info">Follow-up to sprite authors, thanks again!</p>
	            </div>
	            <div class="card-action deep-orange darken-4">
	            	<a class="cardy" target="_blank" href="http://opengameart.org/content/high-res-fire-ball">Robert Brooks</a>
		            <a class="cardy" target="_blank" href="https://opengameart.org/content/radial-lightning-effect">13rice</a>
		            <a class="cardy" target="_blank" href="https://opengameart.org/content/arw-explosion">Chromaeleon</a>
		            <a class="cardy" target="_blank" href="https://opengameart.org/content/smoke-aura">MrBeast</a>
		            <a class="cardy" target="_blank" href="https://opengameart.org/users/bevouliincom">bevouliin.com</a>
		            <a class="cardy" target="_blank" href="http://opengameart.org/content/ui-pack">Kenney</a>
	            </div>
	          </div>
	        </div>

	        <div class="col s12 m3">
	          <div class="card green accent-2">
	            <div class="card-content white-text">
	              <span class="card-title"><p class="info">Multimedia</p></span>
	              <p class="info">Multimedia that's it.</p>
	            </div>
	            <div class="card-action blue-grey darken-4">
	            	<a class="cardy" target="_blank" href="https://www.sfml-dev.org/">SFML</a>
		            <a class="cardy" target="_blank" href="https://www.libsdl.org/projects/SDL_mixer/">SDL_Mixer</a>
	            </div>
	          </div>
	        </div>


	        <div class="col s12 m3">
	          <div class="card blue accent-1">
	            <div class="card-content white-text">
	              <span class="card-title"><p class="info">Other</p></span>
	              <p class="info">I'm guessing it's not necessery, but it's lovely.</p>
	            </div>
	            <div class="card-action blue accent-4">
	            	<a class="cardy" target="_blank" href="https://codelite.org/">CodeLite</a>
		            <a class="cardy" target="_blank" href="https://sublimetext.com/2">SublimeText2</a>
		            <a class="cardy" target="_blank" href="https://emmet.io/">Emmet</a>
		            <a class="cardy" target="_blank" href="http://www.audacityteam.org/">Audacityteam</a>
		            <a class="cardy" target="_blank" href="https://www.gimp.org/">Gimp</a>
	            </div>
	          </div>
	        </div>
	        </div>

	</div>
	</div>
	
	<div id="section4" class="header scrollspy">
		<!--<div class="container">
			<div class="row">
				<?php
					// echo "<h2>High Scores - 10 of ".$rows."</h2>";
				?>
				<div class="col s12 m12">
					<table class="striped centered responsive-table bordered">
				        <thead class="tableheader">
				          <tr>
				              <th>Nick</th>
				              <th>World</th>
				              <th>Corruption</th>
							  <th>Scores</th>
				              <th>Time</th>
				              <th>Played</th>
				          </tr>
				        </thead>
						<tbody class="member">
						<?php
						/*
							for ($x = 0; $x < 10; $x++) {
								if( $scores=mysql_fetch_assoc($records) )
								{
									echo "<tr>";
									echo "<td>".$scores['nick']."</td>";
									echo "<td>".$scores['world']."</td>";
									echo "<td>".$scores['difficulty']."</td>";
									echo "<td>".$scores['points']."</td>";
									echo "<td>".$scores['time_playing']."</td>";
									echo "<td>".$scores['date']."</td>";
									echo "</tr>";
								}
							}
						*/
						?>
						</tbody>
				     </table>
				</div>
			</div>
		</div> -->
	</div>

	<!-- Footer -->
	<footer class="page-footer">
      <div class="container">
        <div class="row">
            <div class="col s4">
                <h5 class="white-text">Admins:</h5>
                <p class="white-text">Adrian Michałek (devmichalek@gmail.com)</p>
            </div>
            <div class="col s4">
                <h5 class="white-text">Moderators:</h5>
                <p class="white-text">Sebastian Bialucha (sebastek321@gmail.com)</p>
                <p class="white-text">Kamil Gawlik (kamilgawlik@icloud.com)</p>
            </div>
            <div class="col s4">
                <h5 class="white-text">About:</h5>
                <p class="grey-text text-lighten-4">Project of SFML & QT.</p>
            </div>
        </div>
      </div>
      <div class="footer-copyright">
        <div class="container"><a class="modal-trigger waves-effect waves-light btn" href="#license">©2018 Terms of Use</a></div>
      </div>
    </footer>


    <!-- LICENSE -->
  <div id="license" class="modal modal-fixed-footer">
    <div class="modal-content">
      <h4 class="modcon">GNU GENERAL PUBLIC LICENSE</h4>
      <div><p><?php include('LICENSE.txt'); ?></p></div>
    </div>
    <div class="modal-footer">
      <a href="#!" class="modal-action modal-close waves-effect waves-green btn-flat">Agree</a>
    </div>
  </div>


	<!-- Compiled and minified JavaScript -->
	<script type="text/javascript" src="https://code.jquery.com/jquery-3.3.1.min.js"></script>
  	<script src="https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0-rc.2/js/materialize.min.js"></script>
	<script type="text/javascript" src="main.js"></script>
</body>
</html>