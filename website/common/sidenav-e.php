    <!-- If user is logged then show log out button -->
    <?php
        if(isset($_SESSION['logged']))
        {
            echo '<li><a class="japokki-black" href="http://combathalloween.netne.net/user/login/logout.php"><i class="material-icons">exit_to_app</i>Log Out</a></li>';
        }
    ?>

<!-- End of the list -->
</ul>
<!-- SIDENAV END -->