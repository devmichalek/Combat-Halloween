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
  	<div class="name japokki-black"><?php echo $_SESSION['username']; ?></div>
  	<div class="email japokki-black"><?php echo $_SESSION['email']; ?><br>Permissions: <span style="color: red;"><?php echo $_SESSION['permissions']; ?></span></div>
    </div></li>

    <li><a class="subheader center bg-black japokki-white" style="margin-top: -10px;"><i class="material-icons right char-white">person</i>Account </a></li>
    <li><a class="japokki-black" href="http://combathalloween.netne.net/user/other/profile.php#changeUsername"><i class="material-icons">person</i>Change Username</a></li>
    <li><a class="japokki-black" href="http://combathalloween.netne.net/user/other/profile.php#changePassword"><i class="material-icons">drag_handle</i>Change Password</a></li>
    <li><a class="japokki-black" href="http://combathalloween.netne.net/user/other/profile.php#changeEmail"><i class="material-icons">email</i>Change Email</a></li>
    
    <li><div class="divider"></div></li>
    <li><a class="subheader center bg-black japokki-white"><i class="material-icons right char-white">format_paint</i>Other </a></li>
    <li><a class="japokki-black" href="http://combathalloween.netne.net/user/other/profile.php#changeAvatar"><i class="material-icons">contacts</i>Change Avatar</a></li>