<li><div class="user-view">
	<div class="background" ></div>
  	<?php
  	    echo '<img class="circle" src=';
  	    $filepath = 'http://combathalloween.netne.net/images/users/'. $_SESSION['email'].'.jpg';
        if(@getimagesize($filepath))
            echo '"http://combathalloween.netne.net/images/users/'. $_SESSION['email'].'.jpg">';
        else
            echo '"http://combathalloween.netne.net/images/users/default.png">';
  	?>
  	<div class="name" style="color: black;"><?php echo $_SESSION['username']; ?></div>
  	<div class="email" style="color: black;"><?php echo $_SESSION['email']; ?></div>
</div></li>

<li><a class="subheader light-blue lighten-3 center" style="margin-top: -10px;"><i class="material-icons right">person</i>Account </a></li>
<li><a href="#!"><i class="material-icons">person</i>Change Username</a></li>
<li><a href="#!"><i class="material-icons">person_outline</i>Change Password</a></li>
<li><a href="#!"><i class="material-icons">email</i>Change Email</a></li>

<li><div class="divider"></div></li>
<li><a class="subheader blue lighten-3 center"><i class="material-icons right">format_paint</i>Other</a></li>
<li><a href="#!"><i class="material-icons">contacts</i>Change Image</a></li>