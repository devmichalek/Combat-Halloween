<?php

  	session_start();

	// Check if user is logged.
  	require_once("../../user/login/isLogged.php");

  	// Check if user has admin/moderator permissions.
  	require_once("../../user/other/isModerator.php");

	require_once("../../common/head.php");
?>
    
    <!-- NAVBAR -->
    <?php require_once("../../common/navbar-b.php"); ?>
	      		<li><a class="btn-floating btn-medium pulse blue lighten-1" href="../../home.php"><i class="material-icons">home</i></a></li>
	        	<li><a class="nav btn white japokki-black" href="../index.php">Back</a></li>
	<?php require_once("../../common/navbar-e.php"); ?>
  	<?php require_once("../../common/sidenav-b.php"); ?>
  	    <li><a class="japokki-black" href="../../home.php"><i class="material-icons">home</i>Home</a></li>
  	    <li><a class="japokki-black" href="../index.php"><i class="material-icons">arrow_back</i>Back</a></li>
	<?php require_once("../../common/sidenav-e.php"); ?>
    <!-- END OF NAVBAR -->

  <div class="container center">
    <div class="row">
      <h2 class="japokki-black A22">Documentation</h2>
      <h4 class="japokki-black A4">This part of the website was made to make clear some rules that we should keep when we add/edit bug. The bug (in other words the problem) is a thing that needs developer's action. Always remember to make clear the name of the bug and to make tidy description so that developer is not wasting time to try to understand the author's means. We work with agile software development style, we do small tasks means small updates. By keeping our project growing slowly but steady we at the end have final product and that's our goal. Below you can find useful information about types and resolutions.</h4>


      <h2 class="japokki-black A22">Bug Types</h2>
      <h4 class="japokki-black A4">
        <span style="color: #ef5350;">Bug</span> - evident error, crash, fault, memory leaks, mistakes made by mechanisms etc.<br>
        <span style="color: #ffca28;">Change</span> - layout displaying, algorithm's change, change of page layout etc.<br>
        <span style="color: #66bb6a;">New Feature</span> - new system, new picture, new file, new mechanism, anything that was not before.<br>
        <span style="color: #ffca28;">Syntax Error</span> - language mistakes, suggestion to rename etc.<br>
        <span style="color: #bdbdbd;">Other</span> - just anything else that does not match the other types.
      </h4>


      <h2 class="japokki-black A22">Bug Resolutions</h2>
      <h4 class="japokki-black A4">
        <span style="color: #ef5350;">Deffered</span> - by this you tell others that bug will be done in the "far" future.<br>
        <span style="color: #ec407a;">Disagree</span> - you disagree with the author of the bug.<br>
        <span style="color: #ec407a;">Duplicated</span> - this bug has been added someday, if we see duplicated bug for more than week then we should simply remove it if we are sure.<br>
        <span style="color: #66bb6a;">Fixed</span> - the bug has been resolved, usually for the bug with repairing as the action.<br>
        <span style="color: #ef5350;">Held</span> - you had to stop to do another task but you will come back to revise this one in a short time.<br>
        <span style="color: #66bb6a;">Implemented</span> - code has been implemented, bug is resolved.<br>
        <span style="color: #ffca28;">In Development</span> - always remember to check this one if you are working the bug. Others know that someone is currently solving.<br>
        <span style="color: #9c27b0;">Irreproducible</span> - somehow is impossible to revise the bug. This is the worst scenario, for example data that you have to work on does not exist.<br>
        <span style="color: #ef5350;">Known Problem</span> - it's a very known problem, usual task like truncating the image.<br>
        <span style="color: #ab47bc;">Need More Info</span> - you don't understand the author of the bug.<br>
        <span style="color: #ef5350;">New</span> - you would likely choose it if the bug is new.<br>
        <span style="color: #ef5350;">Obsolete</span> - bug is unresolved for such a long time, if you saw a bug with deadline that passed choose this option.<br>
        <span style="color: #ef5350;">Reopen</span> - simply reopen problem.<br>
        <span style="color: #66bb6a;">Revised</span> - the bug has been resolved, used for any king of resolving like modyfing, creating etc.<br>
        <span style="color: #ec407a;">Not To Correct</span> - suggestion by the developer to not to correct.<br>
        <span style="color: #ab47bc;">Support Needed</span> - you need more hands to do this job.<br>
        <span style="color: #9c27b0;">Withdrawn</span> - you are fed up with the bug and want to leave it for someone else.
      </h4>
      
        <?php
            for($i = 0; $i < 8; ++$i)
            {
                echo '<div class="col s6 m3"><div class="card grey lighten-5"><div class="card-content">';
                echo '<img class="responsive-img" src="../../images/bugs/';
                echo $i;
                echo '.png">';
                echo '</div></div></div>';
            }
        ?>
    </div>
  </div>

<?php require_once("../../common/footer.php"); ?>