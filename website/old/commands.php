<!DOCTYPE html>
<html lang="en">
<head>
	<!-- Standard Meta -->
	<meta charset="UTF-8" />
	<meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1" />
	<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0">

	<!-- Site Properties -->
	<title>Commands - Combat Halloween</title>
	<link rel="stylesheet" href="skeleton.css">
	<link rel="stylesheet" href="normalize.css">
	<link rel="stylesheet" href="main.css">
	<link rel="shortcut icon" href="images/icon.png">

</head>
<body>
	<div class="container">

		<!-- Back -->
		<?php
			
			session_start();

			if(isset($_SESSION['commandsbackbutton']))
			{
				echo '<div class="row myfont">';
				echo '<div class="twelve columns" style="text-align: left; margin-top: 1em;">';
				echo '<a class="button primary-button" href="home.php">Back</a>';
				echo '</div></div>';
			}
		?>


		<!-- Commands -->
		<div class="row myfont">
			<div class="twelve columns" style="text-align: center; margin-top: 5em;">
				<h3 class="notopmargin nobotmargin">All Commands in Game</h3>
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

				<!-- Clear -->
				<h5 class="nobotmargin"><span class="redspan">@clear</span></h5>
				<h5 class="nobotmargin">Clear all visible tiles, objects, foes etc. Doesn't mean that you lost data, the data is "currently" pure.</h5>
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
					<span style="display: inline-block;">Back to <a href="home.php" style="color: #444444;">main site</a></span>
				</h6>
				<h6 class="myfont nobotmargin notopmargin">
					Contact me: adrmic98@gmail.com or contact@adrianmichalek.pl
				</h6>
			</footer>
		</div>
	</div>
</body>
</html>