                    <!-- If user is logged then show log out button -->
                    <?php
                        if(isset($_SESSION['logged']))
                        {
                            echo "<li><a class='dropdown-trigger btn red darken-1 japokki-white' href='http://combathalloween.netne.net/user/login/logout.php'>Log Out</a></li>";
                        }
                    ?>
                </ul>   <!-- End of the list -->
            </div>  <!-- row -->
        </div>  <!-- navbar-wrapper -->
    </nav>
</div>  <!-- navbar-fixed -->
<!-- NAVBAR END -->